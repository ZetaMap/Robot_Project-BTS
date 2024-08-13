from util.logger import Logger
logger = Logger(__file__[__file__.rfind('/')+1 or __file__.rfind('\\')+1:__file__.rfind('.')])


logger.info("Importing libraries")
import rospy
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

from util.robot_tests import TestReport, TestFailure
from util.colors import Colors


logger.info("Starting ROSPy")
rospy.init_node('niryo_test_FQC_ros_wrapper')
logger.info("Connecting to robot")
robot = NiryoRosWrapper()



def new_calibration(robot: NiryoRosWrapper):
  robot.clear_collision_detected()
  robot.request_new_calibration()
  robot.calibrate_auto()
  robot.update_tool()
  rospy.sleep(0.1)
  robot.grasp_with_tool()
  rospy.sleep(0.1)
  robot.release_with_tool()


IS_LEARNING = False
LEARN_STEPS = []
LEARNED = {}

def activate_learning():
  global IS_LEARNING, LEARN_STEPS
  if IS_LEARNING:
    logger.warn("Robot already learning")
    return
  if len(LEARN_STEPS) != 0:
    logger.err("Learned trajectory must be saved or cleaned before learning")
    return
  add_step()
  add_tool_state(False)
  IS_LEARNING = True
  logger.info("Robot is learning ...")

def deactivate_learning():
  global IS_LEARNING
  if not IS_LEARNING:
    logger.warn("Robot is not learning")
    return
  IS_LEARNING = False
  logger.info("Robot has stopped learning ...")

def add_step():
  global LEARN_STEPS
  LEARN_STEPS.append({"pos": robot.get_joints()})
  
def add_tool_state(enabled: bool):
  global LEARN_STEPS
  if enabled: 
    robot.grasp_with_tool()
    LEARN_STEPS.append({"tool": True})
  else:
    robot.release_with_tool()
    LEARN_STEPS.append({"tool": False})

def save_learned(name: str):
  global IS_LEARNING, LEARN_STEPS, LEARNED
  if IS_LEARNING:
    logger.err("Stop learning first")
    return
  if len(LEARN_STEPS) == 0:
    logger.err("No steps to save")
    return
  LEARNED.update({name: LEARN_STEPS.copy()})
  clear_learned()
  
def clear_learned():
  global LEARN_STEPS
  LEARN_STEPS.clear()

def play_learned(name: str):      
  global IS_LEARNING, LEARNED
  if IS_LEARNING:
    logger.err("Cannot play when learning")
    return
  steps = LEARNED.get(name, None)
  if not steps:
    logger.err(f"No learned trajectory with name {name!r}")
    return
  for s in steps:
    step = s.get("tool", None)
    if step is not None:
      if step: robot.grasp_with_tool()
      else: robot.release_with_tool()
      continue
    step = s.get("pos", None)
    if step is not None:
      try:TestReport(robot.move_joints, "Move joints", *step).raise_if_error()
      except TestFailure as e: 
        logger.err(e, no_stacktrace=True)
        return
      continue
    logger.err("Unknown step type: " + ", ".join(list(s.keys())))
  

def getchar():
	# Returns a single character from standard input
	import os
	ch = ''
	if os.name == 'nt': # how it works on windows
		import msvcrt
		ch = msvcrt.getch()
	else:
		import tty, termios, sys
		fd = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd)
		try:
			tty.setraw(sys.stdin.fileno())
			ch = sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	if ord(ch) == 3: raise KeyboardInterrupt # handle ctrl+C
	return ch


MOVE_OFFSET = 0.1
tool_state = False
#new_calibration(robot)
try:
  robot.sound.play("ready.wav")
  activate_learning()
  ### Put the main code bellow
  while True:
    key = getchar()
    logger.info(f"Received {key!r}")
    
    last_pos = robot.get_joints()
    if key == 'a':
      last_pos[0] += MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'q':
      last_pos[0] -= MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'z':
      last_pos[1] += MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 's':
      last_pos[1] -= MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'e':
      last_pos[2] += MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'd':
      last_pos[2] -= MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'r':
      last_pos[3] += MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'f':
      last_pos[3] -= MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 't':
      last_pos[4] += MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'g':
      last_pos[4] -= MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'y':
      last_pos[5] += MOVE_OFFSET
      robot.move_joints(*last_pos)
    elif key == 'h':
      last_pos[5] -= MOVE_OFFSET
      robot.move_joints(*last_pos)
      
    elif key == ' ': # add step
      add_step()
      robot.led_ring.flashing(Colors.cyan, 0.5, 2, True)
    elif key == '\t': # invert tool state
      tool_state = not tool_state
      add_tool_state(tool_state)
    elif key == '\r': # finish learning
      deactivate_learning()
      save_learned("test")
      break
      
  if robot.custom_button.wait_for_any_action() != 100:
    robot.clear_collision_detected()
    
    play_learned("test")
  
    
except BaseException as e:
  if (type(e) not in (SystemExit, KeyboardInterrupt) and 
      "returned no response" not in '. '.join(str(i) for i in e.args).lower()): 
    logger.err(e)
finally:
  rospy.core._shutdown_flag = False
  try: robot.sound.play("disconnected.wav")
  except BaseException as e: logger.err(e, no_stacktrace=True)
  rospy.core._shutdown_flag = True
