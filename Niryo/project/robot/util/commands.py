"""Commands for the shell"""

from util.logger import Logger, Log, LogLevel
from util.errors import TrajectoryNotFoundError
from util.strings import getchar, lJustList, timedelta_format
from util.tests import Convert
from util.vars import JOINTS_MOVE_OFFSET
from calibration import new_calibration
from trajectory.manager import TRAJECTORY_MANAGER
from trajectory.player import TrajectoryPlayer

from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper
from time import monotonic


class Command:
  def __init__(self, name: str, description: str, command: 'function[[NiryoRosWrapper, Logger], int]', fargs: str="", args_needed: int=0):
    self.name = name
    self.fargs = fargs
    self.description = description
    self.command = command
    self.args_needed = args_needed

  def __call__(self, robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    return self.command(robot, logger, *args)


class ShellCommands:
  def help(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    logger.info("\nNiryo Robot CLI")
    logger.info("\ncommands:")
    
    best1, best2, n, a, d = 0, 0, [], [], []
    for c in ShellCommands.commands:
      n.append(c.name)
      a.append(c.fargs)
      d.append(c.description)
      if len(c.name) > best1: best1 = len(c.name)
      if len(c.fargs) > best2: best2 = len(c.fargs)
      
    for n, a, d in zip(lJustList(n, best1+1), lJustList(a, best2+2), d):
      logger.info("  " + n + a + d)
  
  def loglevel(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    if not args:
      logger.info("Actual level: " + Log.level.name)
      logger.info("Available levels: " + ", ".join(level.name for level in LogLevel))
      return

    for level in LogLevel:
      if level.name == args[0]:
        Log.level = level
        logger.info(f"Log level set to '{level.name}'")
        break
    else: logger.err(f"Level '{args[0]}' not found")

  def manual(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    logger.info("Manual mode started!")
    logger.info("Robot can now be controlled by keyboard.")
    logger.info()
    logger.info("Press &lbENTER&fr to exit this mode.")
    logger.info("Available move keys:")
    for i, v in enumerate((('a','q'), ('z','s'), ('e','d'), ('r','f'), ('t','g'), ('y','h'))):
      logger.info(f"| joint {i+1}: &lg{v[0]}&fr (+) / &lg{v[1]}&fr (-)")
    logger.info("| tool: &lgTAB")

    tool_state = False
    key = ''
    while key != '\r':
      key = getchar()
      logger.debug(f"Received key {key!r}")
      robot.set_jog_use_state(False)
      last_pos = robot.get_joints()
      if key == 'a':
        last_pos[0] += JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'q':
        last_pos[0] -= JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'z':
        last_pos[1] += JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 's':
        last_pos[1] -= JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'e':
        last_pos[2] += JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'd':
        last_pos[2] -= JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'r':
        last_pos[3] += JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'f':
        last_pos[3] -= JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 't':
        last_pos[4] += JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'g':
        last_pos[4] -= JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'y':
        last_pos[5] += JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == 'h':
        last_pos[5] -= JOINTS_MOVE_OFFSET
        robot.move_joints(*last_pos)
      elif key == '\t': # invert tool state
        tool_state = not tool_state
        (robot.grasp_with_tool if tool_state else robot.release_with_tool)()

    logger.info("\nManual mode exited!")

  def deep(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    if not len(args):
      logger.info("Deep learning mode is @", "enabled" if robot.get_learning_mode() else "disabled")
      return
    enabled = Convert.to_bool(args[0])
    robot.set_learning_mode(enabled)
    logger.info("Deep learning mode @", "enabled" if enabled else "disabled")

  def default(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    logger.info("Moving to the default position ...")
    robot.move_to_sleep_pose()
  
  def halt(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    force_deep = len(args) and (Convert.to_bool(args[0]) or args[0] == 'deep')
    if not force_deep:
      try: robot.stop_move()
      except: 
        logger.warn("An error occurred. Trying to stop with deep mode ...")
        force_deep = True
      else: logger.info("Stopped movement")
    if force_deep:
      robot.set_learning_mode(True)
      robot.set_learning_mode(False)
      logger.info("Movement stopped with deep learning mode")

  def clear(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    robot.clear_collision_detected()
    logger.info("Removed collision detected trigger")

  def calibrate(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    logger.info("Started calibration.")
    start = monotonic()
    new_calibration(robot)
    logger.info("Calibration finished in @", timedelta_format((monotonic()-start)*1000))
    
  def play(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    if not args:
      logger.info("Trajectories: ")
      for t in TRAJECTORY_MANAGER:
        logger.info("| Name: @ \tID: @ \tSteps: @", t.get_name(), t.get_id(), t.count_steps())

    elif args[0] == "reload":
      TRAJECTORY_MANAGER.reload().sort()
      logger.info("Trajectories reloaded.")
    else: 
      try: TrajectoryPlayer.play_trajectory(robot, args[0])
      except TrajectoryNotFoundError as e: logger.err(str(e))
      
  def exec_(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    logger.info("Running script ...")
    start = monotonic()
    exec(" ".join(args), globals(), locals())
    logger.info("Script finished in @", timedelta_format((monotonic()-start)*1000))

  def speed(robot: NiryoRosWrapper, logger: Logger, *args: 'tuple[str]'):
    if not args: logger.info("Arm max velocity is at @%", robot.get_max_velocity_scaling_factor())
    else:
      v = int(args[0])
      robot.set_arm_max_velocity(v)
      logger.info("Arm max velocity set to @%", v)


  commands: 'list[Command]'  = [
    Command("help", "Print this help", help),
    Command("exit", "Exit the main program", lambda *_: 255),
    Command("loglevel", "Control verbosity level of logging", loglevel, "[level]"),
    Command("manual", "Control the robot manually by keyboard", manual),
    Command("deep", "Set/Get deep learning mode", deep, "[on|off]"),
    Command("default", "Move robot to default position", default),
    Command("halt", "Stop the current robot movement", halt, "[deep]"),
    Command("clear", "Clear collision detected trigger", clear),
    Command("calibrate", "Start new robot calibration", calibrate),
    Command("play", "Play a trajectory or list it", play, "[reload|type-<name|id>]"),
    Command("exec", "Execute python code in runtime", exec_, "<code...>", 1),
    Command("speed", "Set/Get arm max speed (velocity) between 1 and 200%", speed, "[percent]"),
  ]
