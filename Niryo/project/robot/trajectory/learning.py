from util.logger import Logger
from util.errors import TrajectoryLearningError
from util.strings import get_child_path
from util.colors import Colors

from .trajectory import Trajectory
from .parser import TrajectoryParser
from .step.goal import GoalReport

from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

__all__ = [
  "TrajectoryLearningError",
  "TrajectoryLearning"
]


class TrajectoryLearning:
  def __init__(self, robot: NiryoRosWrapper):
    self.__logger = Logger(__class__.__name__)
    self.robot = robot
    self.__started = False
    self.__saved = False
    self.trajectory: Trajectory = None
    self.__deep = False
    self.led_effets = True

  def ensure_started(self):
    if not self.__started: raise TrajectoryLearningError("learning mode not started")

  def ensure_stopped(self):
    if self.__started: raise TrajectoryLearningError("stop learning mode first")

  def start(self, deep_learning=False):
    if self.__started: raise TrajectoryLearningError("learning mode already started")
    self.__deep = deep_learning
    self.__started = True
    if self.__deep: self.robot.set_learning_mode(True)
    if self.trajectory: self.__logger.warn("previous trajectory not saved or cleared, overriding.")
    self.__saved = False
    if self.led_effets:
      try: self.robot.led_ring.snake(Colors.cyan)
      except Exception as e: self.__logger.warn(f"Error during led effect: {type(e).__name__}: {str(e)}")
    self.robot.release_with_tool()
    self.trajectory = Trajectory().set_start_state(False, self.get_robot_pos()).new_id()

  def stop(self, no_check=False) -> Trajectory:
    if not no_check: self.ensure_started()
    if self.__deep: self.robot.set_learning_mode(False)
    self.__deep = False
    self.__started = False
    self.__saved = False
    if self.led_effets:
      try: self.robot.led_ring.flashing(Colors.cyan, iterations=3)
      except Exception as e: self.__logger.warn(f"Error during led effect: {type(e).__name__}: {str(e)}")
    return self.trajectory

  def save(self, trajectory_name: str, custom_filename: str=None, no_check=False) -> Trajectory:
    if not trajectory_name: raise ValueError("trajectory name is empty")
    if not no_check: self.ensure_stopped()
    if not self.trajectory: raise TrajectoryLearningError("learning was never started")
    name = custom_filename or str(self.trajectory.get_id()) + '-' + trajectory_name
    self.trajectory.set_name(trajectory_name).set_filename(get_child_path(TrajectoryParser.make_trajectory_file_by_name(name)))
    TrajectoryParser.write(self.trajectory)
    traj = self.trajectory
    self.trajectory = None
    self.__saved = True
    return traj

  def clear(self):
    deep = self.__deep
    started = self.__started
    self.stop(no_check=True)
    self.trajectory = None
    if started: self.start(deep)

  def get_robot_pos(self) -> 'tuple[float]':
    return self.robot.get_joints()

  def add_pos_flag(self):
    self.ensure_started()
    self.trajectory.add_joints(self.get_robot_pos())

  def set_tool_state(self, enabled: bool):
    self.ensure_started()
    GoalReport(self.robot.grasp_with_tool if enabled else self.robot.release_with_tool).raise_if_error()
    self.trajectory.add_tool_state(enabled)

  def set_motor_speed(self, percent: int):
    self.ensure_started()
    GoalReport(self.robot.set_arm_max_velocity, (percent,)).raise_if_error()
    self.trajectory.add_motor_speed(percent)

  @property
  def started(self):
    return self.__started

  @property
  def deep_learning(self):
    return self.__deep

  @property
  def learn_saved(self):
    return self.__saved