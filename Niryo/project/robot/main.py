# First, parse CLI
from util.logger import Log, Logger, LogLevel
from util.cli import CliParser

cli_args = CliParser().parse_args()

# And change settings of logging
Log.write_logs = not cli_args.nowritelogs
Log.folder_name = cli_args.name
Log.logs_path = cli_args.logspath
Log.use_colors = not cli_args.nocolors
if cli_args.loglevel != Log.level.name:
  for l in LogLevel:
    if l.name == cli_args.loglevel:
      Log.info("Log level set to '@'", l.name)
      Log.level = l
      break
  else: Log.warn("Loglevel '@' not found, used default level", cli_args.loglevel)

Log.info("Importing libraries")
import rospy, signal
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

from util.rospy_logger import redirect_rospy_logger
from util.shell import ShellManager
from util.lock import LockFile
from util.vars import (
  EXIST_REQUESTED_EVENT,
  JOINTS_DEFAULT_POSE,
  TRAJECTORY_DIR_PATH,
  ROSPY_NODE_WAIT_TIMEOUT,
  LOCK_FILE_PATH
)
from calibration import new_calibration
from trajectory.manager import TRAJECTORY_MANAGER
from modbus.server import ModbusServer


class NiryoRobot:
  def __init__(self):
    self.logger = Logger(__class__.__name__)
    self._already_stopped = False
    self.error_occur = False


    self.logger.info("")
    self.logger.info("&fb&lb╭──────────────────────────────╮")
    self.logger.info("&fb&lb│&fr      Robot is starting       &fb&lb│")
    self.logger.info("&fb&lb│&fr  Please wait one minute ...  &fb&lb│")
    self.logger.info("&fb&lb╰──────────────────────────────╯")
    self.logger.info("")

    self.logger.info("Starting RosPy")
    rospy.init_node("niryo_robot_project")

    self.acquire_lockfile()
    if self.stopped_prematurely(): return

    self.logger.info("Connecting to robot")
    self.robot = NiryoRosWrapper()
    self.terminal: ShellManager = None
    self.modbus: ModbusServer = None

    # callback when another node is registered
    def shutdown_hook(reason=""):
      if EXIST_REQUESTED_EVENT.is_set(): return
      self.logger.info(reason.capitalize() if "shutdown request" in reason else ("Recieved shutdown request" + (" with reason: @" if reason else '')), reason)
      reason = reason.lower()

      if "new node registered with same name" in reason:
        self.logger.warn("!! Detected new instance of program !!")
        self.logger.info("Shutting down this program ...")
        
      elif "program exit" in reason: self.logger.warn("Program exit requested!")
      elif "signal-2" in reason: self.logger.warn("KeyboardInterrupt (CTRL+C) requested!")
      
      lockfile.notify_release()
      if self.status_sounds: 
        try: self.robot.sound.play("warn.wav")
        except BaseException as e: self.logger.err(e, no_stacktrace=True)      
      self.stop()
      return

      self.logger.warn("Ignored shutdown request!")
    rospy.core.add_preshutdown_hook(shutdown_hook)

  def acquire_lockfile(self):
    # lock file exist, so probably another handler is present
    if lockfile.present:
      self.logger.info("Waiting for the other handler, to stop itself ...")
      # wait a little
      EXIST_REQUESTED_EVENT.wait(3)
      
      # if the lock file is still present and the value is not 0,
      # we consider that there are no other handlers
      if lockfile.present:
        if lockfile.handled():
          self.logger.warn("Timeout, waiting for other handle (considering there is no other handler)")
          lockfile.acquire(self)
          return
        
        # wait for lock file to be removed by other handler
        count = ROSPY_NODE_WAIT_TIMEOUT
        while count:
          EXIST_REQUESTED_EVENT.wait(1)
          count -= 1
          if not lockfile.present: 
            lockfile.acquire(self)
            return
          
        if lockfile.present:
          self.logger.warn("Timeout, waiting for other handle (considering there is no other handler)")
          lockfile.acquire(self)
          return

    # probably no other handler, so continue
    else: lockfile.acquire(self)

  def stopped_prematurely(self):
    if self.error_occur or EXIST_REQUESTED_EVENT.is_set() or rospy.is_shutdown():
      self.error_occur = True
      self.logger.err("\n!! Exited before finish starting")
      EXIST_REQUESTED_EVENT.set() # make sure the event is triggered
      self.stop()
      return True
    return False

  # TODO: make sound error

  def stop(self):
    if self._already_stopped: return
    self._already_stopped = True
    self.logger.info("Stopping robot ...")
    EXIST_REQUESTED_EVENT.set()
    if self.terminal:
      self.terminal.join(5)
      self.terminal = None
    if self.modbus:
      self.modbus.stop()
      self.modbus = None
    TRAJECTORY_MANAGER.save()

    # Silently disable shutdown flag
    if self.status_sounds:
      shutdown = rospy.core._shutdown_flag
      rospy.core._shutdown_flag = False
      try: 
        if self.error_occur:
          self.robot.sound.play("warn.wav")
          self.robot.sound.play("error.wav")
        else: self.robot.sound.play("disconnected.wav")
      except BaseException as e: self.logger.err(e, no_stacktrace=True)
      rospy.core._shutdown_flag = shutdown

    lockfile.release()
    self.logger.info("Robot stopped")

  def stop_complete(self):
    return (self._already_stopped and EXIST_REQUESTED_EVENT.is_set() and
        #    rospy.is_shutdown() and
            self.terminal is None and self.modbus is None)

  def start(self, do_calibration=True, load_trajectories=True, start_modbus=True, 
            use_terminal=True, status_sounds=True, default_pose=True,
            use_gamepad=True):
    if self.stopped_prematurely(): return
    self.status_sounds = status_sounds

    if do_calibration:
      self.logger.info("Started calibration")
      try: new_calibration(self.robot)
      except Exception as e: 
        self.logger.err(e, no_stacktrace=True)
        self.error_occur = True
      else: self.logger.info("Calibration finished")

      if self.stopped_prematurely(): return

    if load_trajectories:
      self.logger.info("Loading trajectories ...")
      try: TRAJECTORY_MANAGER.load(TRAJECTORY_DIR_PATH).sort()
      except Exception as e: 
        self.logger.err(e)
        self.error_occur = True

      if self.stopped_prematurely(): return

    if start_modbus:
      self.logger.info("Starting Modbus/TCP server ...")
      try: self.modbus = ModbusServer(self.robot)
      except: 
        self.error_occur = True
        self.stop()
      else: self.modbus.start()

      if self.stopped_prematurely(): return
      
    if use_gamepad:
      self.logger.info("Starting Gamepad manager")
      import os
      path = __file__[:__file__.rfind('/')+1 or __file__.rfind('\\')+1]
      os.system("sleep 5; python \"" + path + "util/jog_client_node.py\" &")

    if use_terminal:
      self.logger.info("Starting terminal ...")
      self.terminal = ShellManager(self.robot)

    if EXIST_REQUESTED_EVENT.wait(1) and self.stopped_prematurely(): return
    self.logger.info("")
    self.logger.info("&fb&lb╭──────────────────────────────╮")
    self.logger.info("&fb&lb│&fr        Robot started!        &fb&lb│")
    self.logger.info("&fb&lb│&fr      Now enjoy the fun.      &fb&lb│")
    self.logger.info("&fb&lb╰──────────────────────────────╯")
    self.logger.info("")

    if use_terminal: self.terminal.start()

    try:
      if self.status_sounds: self.robot.sound.play("ready.wav")
      self.robot.led_ring.rainbow_cycle()
      
      self.setup()
      while not EXIST_REQUESTED_EVENT.is_set():
        self.loop()
        EXIST_REQUESTED_EVENT.wait(0.01) # No need to run at full speed

      # Go to default position
      if default_pose and not rospy.is_shutdown() and not self._already_stopped:
        if self.robot.collision_detected:
          self.logger.warn("Collision detected during last movement.")
          self.logger.warn("Robot will not move to the default point, to avoid another potential collision.")
        else:
          self.logger.info("Moving to default position ...")
          self.robot.move_joints(*JOINTS_DEFAULT_POSE)

    except Exception as e:
      if type(e) not in (KeyboardInterrupt, SystemExit): 
        self.logger.err(e)
        self.error_occur = True
    finally: self.stop()

  def setup(self):
    """Setup function of program, will be called one time. Put the variable creation or other things here."""
    ...

  def loop(self):
    """Main loop of program, will be called every iteration. Must not be a blocking method."""
    ...


if __name__ == '__main__':
  lockfile = LockFile(LOCK_FILE_PATH)
  signal.signal(signal.SIGINT|signal.SIGTERM|signal.SIGKILL|signal.SIGQUIT, lockfile.release)
    
  try:
    redirect_rospy_logger()

    main = NiryoRobot()
    main.start(not cli_args.nocalibration, not cli_args.notrajectories, not cli_args.nomodbus,
               not cli_args.noterminal, not cli_args.nostatussound, not cli_args.nodefaultpose,
               not cli_args.nogamepad)
    count = ROSPY_NODE_WAIT_TIMEOUT * 10
    while count and not main.stop_complete(): 
      rospy.sleep(0.1)
      count -= 1
    if not main.stop_complete(): main.logger.warn("Timeout stopping robot, force exiting!")
    main.logger.info("Stopping RosPy ...")
    rospy.signal_shutdown("program exit")

  except BaseException as e:
    if type(e) not in (KeyboardInterrupt, SystemExit):
      from util.logger import Log

      Log.err("\n!! FATAL ERROR !!\n")
      Log.err(e)
      

  finally: 
    lockfile.release()
