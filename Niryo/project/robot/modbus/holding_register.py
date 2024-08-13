"""
Re-implementation of niryo_robot_modbus.holding_register_data_block, for own use
"""

import rospy, threading

from niryo_robot_modbus.data_block import DataBlock
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper
from niryo_robot_msgs.msg import CommandStatus

from util.logger import Logger
from trajectory.learning import TrajectoryLearning, TrajectoryLearningError
from trajectory.player import TrajectoryPlayer
from trajectory.manager import TRAJECTORY_MANAGER
from trajectory.parser import TrajectoryParser
from trajectory.step.goal import GoalFailure


"""
 - Each address contains a 16 bits value
 - READ/WRITE registers

 --> Used to give commands to the robot
 ( ! the stored values correspond to the last given command,
 not the current robot state !)
"""
HR_LEARNING_MODE = 0              # 0: disable, 1: enable
HR_MAKE_FLAG = 1                  # 0: nothing, 1: add position flag
HR_TOOL_STATE = 2                 # 0: disable, 1: enable
HR_MOTOR_SPEED = 3                # 1-200

HR_SELECTED_TRAJECTORY_NAME = 10
HR_SELECTED_TRAJECTORY_ID = 31
TRAJECTORY_NAME_SIZE = 20

HR_SAVE_DEL_TRAJECTORY = 40       # 0: nothing, 1: save selected, 2: delete selected
HR_SELECT_TRAJECTORY_INDEX = 41   # 0: unselect
HR_RUN_SELECTED_TRAJECTORY = 42   # 0: waiting, 1: running
HR_STOP_RUNNING_TRAJECTORY = 43   # 0: nothing, 1: stop

HR_COUNT_SAVED_TRAJECTORY = 50    # 0: no saved trajectories
HR_HAS_TRAJECTORY_SELECTED = 51   # 0: no, 1: yes

HR_ERROR_STATUS = 100             # 0: no error

# Error codes
ERROR_NO_STATUS_YEET = 0
ERROR_SUCCESS = 1
ERROR_UNKNOWN = 99  # logs need to be readed for that
ERROR_IS_LEARNING = 100
ERROR_NOT_LEARNING = 101
ERROR_NOTHING_SELECTED = 102
ERROR_NOT_FOUND = 103
ERROR_INVALID_NAME = 104
ERROR_EMPTY_NAME = 105
ERROR_INVALID_TRAJECTORY = 106
ERROR_NOT_RUNNING = 107
ERROR_ALREADY_RUNNING = 108
ERROR_TRAJECTORY_ABORDED = 109


class HoldingRegisterDataBlock(DataBlock):
  def __init__(self, robot: NiryoRosWrapper):
    super().__init__()
    self.robot = robot
    self.logger = Logger(__class__.__name__)
    self.learning = TrajectoryLearning(robot)
    self.playing = None
    self.selected = 0

    self.execution_thread = threading.Thread()
    self.is_action_client_running = False

    # update value for first time
    # TODO: find a way to mak this synchonized
    self.setValuesOffset(HR_COUNT_SAVED_TRAJECTORY, TRAJECTORY_MANAGER.count_trajectories())

  def __set_move_in_progress(self):
    self.setValuesOffset(HR_STOP_RUNNING_TRAJECTORY, 0)
    self.setValuesOffset(HR_RUN_SELECTED_TRAJECTORY, 1)

  def __set_command_in_progress(self):
    self.setValuesOffset(HR_ERROR_STATUS, ERROR_NO_STATUS_YEET)

  def __set_error_code(self, code):
    self.setValuesOffset(HR_ERROR_STATUS, code)

  def __set_move_done(self, status_result):
    self.__set_error_code(self.__get_status_code(status_result))
    self.setValuesOffset(HR_STOP_RUNNING_TRAJECTORY, 0)
    self.setValuesOffset(HR_RUN_SELECTED_TRAJECTORY, 0)

  def __run_action_async(self, func, *args):
    if self.check_move_running(): return

    def wrapper():
      self.is_action_client_running = True
      self.__set_move_in_progress()

      try:
        try: response = func(*args)
        except RuntimeError: self.__set_move_done(ERROR_SUCCESS)
        except Exception as e:
          if type(e) == RuntimeError and "generator raised StopIteration" in str(e): self.__set_move_done(ERROR_TRAJECTORY_ABORDED)
          else:
            self.logger.err("ModbusAsyncAction - "+type(e).__name__+": "+str(e))
            error = str(e).strip()
            if error and "error code:" in error.lower():
              code = error.split('\n')[0]
              code = code[code.find(':')+1].strip()
              self.update_status(int(code) if code else None)
            elif "clear_collision_detected" in error: self.__set_move_done(9)
            else: self.update_status(None)
        else: self.update_status(response)
      except BaseException as e: 
        self.__set_error_code(ERROR_UNKNOWN)
        self.logger.err(e, no_stacktrace=True)
      self.is_action_client_running = False

    self.__set_error_code(ERROR_SUCCESS)
    self.execution_thread = threading.Thread(name="ModbusAsyncAction", target=wrapper, daemon=True)
    self.execution_thread.start()

  def __get_status_code(self, status):
      if type(status) in (tuple, list): return status[0]
      elif type(status) == str and status: return int(status)
      else:
        s = getattr(status, "status", None)
        if s is not None: return s
      return status

  def setValuesOffset(self, address, values):
    super().setValues(address+1, values if type(values) == list else [values])


  def check_move_running(self):
    if self.is_action_client_running or self.execution_thread.is_alive():
      self.__set_error_code(ERROR_ALREADY_RUNNING)
      return True
    return False

  def update_status(self, status):
    self.setValuesOffset(HR_STOP_RUNNING_TRAJECTORY, 0)
    self.setValuesOffset(HR_RUN_SELECTED_TRAJECTORY, 0)
    status = self.__get_status_code(status)

    if status == CommandStatus.NO_CONNECTION or status == None:
      self.__set_error_code(7)
    elif status == CommandStatus.GOAL_TIMEOUT:
      self.__set_error_code(6)
    elif status == CommandStatus.REJECTED:
      self.__set_error_code(2)
    elif status == CommandStatus.ABORTED:
      self.__set_error_code(3)
    elif status == CommandStatus.PREEMPTED:
      self.__set_error_code(4)
    elif status != CommandStatus.SUCCESS:
      self.__set_error_code(5)
    else:
      self.__set_error_code(ERROR_SUCCESS)

  def get_trajectory_name(self):
    name = ''.join([chr(i) for i in self.getValuesOffset(HR_SELECTED_TRAJECTORY_NAME, TRAJECTORY_NAME_SIZE) if i])
    if not name:
      self.__set_error_code(ERROR_EMPTY_NAME)
      return None
    elif not name.isprintable():
      self.__set_error_code(ERROR_INVALID_NAME)
      return None
    return name

  def is_trajectory_selected(self):
    return self.getValuesOffset(HR_HAS_TRAJECTORY_SELECTED)[0] != 0

  def setValues(self, address, values):
    try:
      self.process_command(address, values)
  #    super().setValues(address, values)
    except BaseException as e:
      self.logger.err(e)
      self.update_status(None)

  def process_command(self, address, values):
    address -= 1
    if len(values) == 0:
        return

    elif address == HR_LEARNING_MODE:
      self.set_learning_mode(values[0])
    elif address == HR_MAKE_FLAG:
      self.add_pose_flag(values[0])
    elif address == HR_TOOL_STATE:
      self.set_tool_state(values[0])
    elif address == HR_MOTOR_SPEED:
      self.set_motor_speed(values[0])

    elif address == HR_SELECTED_TRAJECTORY_ID:
      ... # id is unique, so changes are not allowed
    elif HR_SELECTED_TRAJECTORY_NAME <= address <= HR_SELECTED_TRAJECTORY_NAME+TRAJECTORY_NAME_SIZE:
      # ensure name is 20 letters max
      self.setValuesOffset(address, values[0:TRAJECTORY_NAME_SIZE-(address-HR_SELECTED_TRAJECTORY_NAME)])

    elif address == HR_SAVE_DEL_TRAJECTORY:
      self.save_delete_trajectory(values[0])
    elif address == HR_SELECT_TRAJECTORY_INDEX:
      self.select_trajectory(values[0])
    elif address == HR_RUN_SELECTED_TRAJECTORY:
      self.run_selected_trajectory(values[0])
    elif address == HR_STOP_RUNNING_TRAJECTORY:
      self.stop_running_trajectory(values[0])

    elif address == HR_COUNT_SAVED_TRAJECTORY:
      ... # read only number
    elif address == HR_HAS_TRAJECTORY_SELECTED:
      self.unselect_trajectory(values[0])

    elif address == HR_ERROR_STATUS:
      ... # this is an error status, no changes are allowed


  def set_learning_mode(self, value):
    self.setValuesOffset(HR_LEARNING_MODE, int(value != 0))
    self.__set_command_in_progress()

    if value == 0:
      if self.learning.started:
        self.learning.stop()

    else:
      if self.learning.started:
        self.__set_error_code(ERROR_IS_LEARNING)
        return
      
      self.learning.start()
      self.learning.set_tool_state(False)
      self.tool_state = False
      self.setValuesOffset(HR_TOOL_STATE, 0)
      index = TRAJECTORY_MANAGER.count_trajectories()+1
      self.setValuesOffset(HR_SELECT_TRAJECTORY_INDEX, index)
      self.setValuesOffset(HR_SELECTED_TRAJECTORY_ID, self.learning.trajectory.get_id())
      self.setValuesOffset(HR_SELECTED_TRAJECTORY_NAME, [0]*20)
      self.setValuesOffset(HR_HAS_TRAJECTORY_SELECTED, 1)
      self.selected = index

    self.__set_error_code(ERROR_SUCCESS)

  def add_pose_flag(self, value):
    self.setValuesOffset(HR_MAKE_FLAG, int(value != 0))
    self.__set_command_in_progress()

    if value:
      if not self.learning.started: self.__set_error_code(ERROR_NOT_LEARNING)
      else: self.learning.add_pos_flag()

    self.setValuesOffset(HR_MAKE_FLAG, 0)
    self.__set_error_code(ERROR_SUCCESS)

  def set_tool_state(self, value):
    self.setValuesOffset(HR_TOOL_STATE, int(value != 0))
    self.__set_command_in_progress()

    if not self.learning.started:
      self.__set_error_code(ERROR_NOT_LEARNING)
      return
    try: self.learning.set_tool_state(value != 0)
    except GoalFailure as e:
      self.logger.err(e)
      self.__set_error_code(e.status)
    else: self.__set_error_code(ERROR_SUCCESS)

  def set_motor_speed(self, value):
    self.setValuesOffset(HR_MOTOR_SPEED, int(value))
    self.__set_command_in_progress()
    
    if not self.learning.started:
      self.__set_error_code(ERROR_NOT_LEARNING)
      return
    try: self.learning.set_motor_speed(value)
    except GoalFailure as e:
      self.logger.err(e)
      self.__set_error_code(e.status)
    else: self.__set_error_code(ERROR_SUCCESS)

  def save_delete_trajectory(self, value):
    self.setValuesOffset(HR_SAVE_DEL_TRAJECTORY, value)
    self.__set_command_in_progress()

    if value and not self.is_trajectory_selected():
      self.__set_error_code(ERROR_NOTHING_SELECTED)

    elif value == 1:
      if self.learning.trajectory and not self.learning.learn_saved:
        name = self.get_trajectory_name()
        if name:
          try: 
            TRAJECTORY_MANAGER.add(self.learning.save(name))
            self.setValuesOffset(HR_COUNT_SAVED_TRAJECTORY, TRAJECTORY_MANAGER.count_trajectories())
            self.unselect_trajectory(0)
            self.__set_error_code(ERROR_SUCCESS)
          except TrajectoryLearningError:
            self.__set_error_code(ERROR_IS_LEARNING)

      elif self.is_trajectory_selected():
        name = self.get_trajectory_name()
        if name:
          try:
            traj = TRAJECTORY_MANAGER.get(self.selected)
            traj.set_name(name)
            TrajectoryParser.write(traj)
            self.unselect_trajectory(0)
            self.__set_error_code(ERROR_SUCCESS)
          except IndexError: self.__set_error_code(ERROR_NOT_FOUND)
          except BaseException as e: 
            self.__set_error_code(ERROR_UNKNOWN)
            self.logger.err(e, no_stacktrace=True)

      else: self.__set_error_code(ERROR_NOTHING_SELECTED)

    elif value == 2:
      if self.learning.trajectory and not self.learning.learn_saved:
        self.unselect_trajectory(0)

      elif self.is_trajectory_selected():
        try:
          traj = TRAJECTORY_MANAGER.get(self.selected)
          TRAJECTORY_MANAGER.delete(traj)
          self.setValuesOffset(HR_COUNT_SAVED_TRAJECTORY, TRAJECTORY_MANAGER.count_trajectories())
          self.unselect_trajectory(0)
          self.__set_error_code(ERROR_SUCCESS)
        except IndexError: self.__set_error_code(ERROR_NOT_FOUND)
        except BaseException as e: 
          self.__set_error_code(ERROR_UNKNOWN)
          self.logger.err(e, no_stacktrace=True)

      else: self.__set_error_code(ERROR_NOTHING_SELECTED)

    self.setValuesOffset(HR_SAVE_DEL_TRAJECTORY, 0)

  def select_trajectory(self, value):
    if self.learning.started:
      self.__set_error_code(ERROR_IS_LEARNING)
      return
    
    self.setValuesOffset(HR_SELECT_TRAJECTORY_INDEX, value)
    self.__set_command_in_progress()

    try:
      traj = TRAJECTORY_MANAGER.get(value)
      error = False

      start = traj.get_start_state()
      if error or start is None: error = True
      else: self.setValuesOffset(HR_TOOL_STATE, int(start[0]))

      id = traj.get_id()
      if error or id is None: error = True
      else: self.setValuesOffset(HR_SELECTED_TRAJECTORY_ID, id)

      if not error:
        name = traj.get_name()
        self.setValuesOffset(HR_SELECTED_TRAJECTORY_NAME, [ord(name[i]) if i < len(name) else 0 for i in range(TRAJECTORY_NAME_SIZE)])

      if error:
        self.unselect_trajectory(0)
        self.__set_error_code(ERROR_INVALID_TRAJECTORY)
      else:
        self.selected = value
        self.__set_error_code(ERROR_SUCCESS)
        self.setValuesOffset(HR_HAS_TRAJECTORY_SELECTED, 1)
    except: self.__set_error_code(ERROR_NOT_FOUND)

  def run_selected_trajectory(self, value):
    self.__set_command_in_progress()
    
    if value:
      self.setValuesOffset(HR_RUN_SELECTED_TRAJECTORY, 1)
      
      if not self.is_trajectory_selected():
        self.__set_error_code(ERROR_NOTHING_SELECTED)
        return
      
      if self.learning.started:
        self.__set_error_code(ERROR_IS_LEARNING)
        return

      try:
        def wrapper():
          try: traj = TRAJECTORY_MANAGER.get(self.selected)
          except IndexError: 
            self.__set_error_code(ERROR_NOT_FOUND)
            return
          self.playing = TrajectoryPlayer(self.robot, traj)
          response = self.playing.play()
          self.playing = None
          return response
        self.__run_action_async(wrapper)
      except: self.__set_error_code(ERROR_NOT_FOUND)

  def stop_running_trajectory(self, value):
    self.setValuesOffset(HR_STOP_RUNNING_TRAJECTORY, int(value != 0))
    self.__set_command_in_progress()

    if value:
      if self.playing is None or not self.is_action_client_running or not self.execution_thread.is_alive():
        self.__set_error_code(ERROR_NOT_RUNNING)
        return

      if self.playing:
        try:
          self.playing.stop()
          self.playing = None
          self.__set_error_code(ERROR_SUCCESS)
        except: self.__set_error_code(ERROR_NOT_RUNNING)
      
      self.robot.stop_move()

    self.setValuesOffset(HR_STOP_RUNNING_TRAJECTORY, 0)

  def unselect_trajectory(self, value):
    if value == 0:
      self.setValuesOffset(HR_SELECTED_TRAJECTORY_NAME, [0]*TRAJECTORY_NAME_SIZE)
      self.setValuesOffset(HR_SELECTED_TRAJECTORY_ID, 0)
      self.setValuesOffset(HR_SELECT_TRAJECTORY_INDEX, 0)
      self.setValuesOffset(HR_HAS_TRAJECTORY_SELECTED, 0)
      self.selected = 0
