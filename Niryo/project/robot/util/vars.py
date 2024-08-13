"""Global variables"""
import os, threading


AXIS_JOINTS_COUNT = 6
AXIS_JOINTS_PRECISION = 5

JOINTS_DEFAULT_POSE = [0,0.5,-1.25,0,0,0]
JOINTS_MOVE_OFFSET = 0.1

TRAJECTORY_FILE_EXT = ".trj"
TRAJECTORY_DIR_PATH = "./saved_trajectories"

TRAJECTORY_BANNED_DUPLICATED_STEPS = []
TRAJECTORY_NEEDED_STEPS = []
TRAJECTORY_PROPERTY_STEPS = []

TRAJECTORY_MAX_ID = 2**16-1
TRAJECTORY_IDS = []

EXIST_REQUESTED_EVENT = threading.Event()

MODBUS_SERVER_ADDRESS = "0.0.0.0"
MODBUS_SERVER_PORT = 5022
MODBUS_IDENTITY_VENDOR_NAME = "lycee-ledantec"
MODBUS_IDENTITY_VENDOR_URL = "https://lycee-ledantec.fr/"
MODBUS_IDENTITY_PRODUCT_NAME = "Projet Robotique"
MODBUS_IDENTITY_MODEL_NAME = "Niryo Robot - Modbus Server"
MODBUS_IDENTITY_REVISION = "1.0"

ROSPY_NODE_WAIT_TIMEOUT = 15 # in seconds

LOCK_FILE_PATH = "/tmp/.niryo-project.lock"


def format_trajectory_file_name(name: str) -> str:
  return name + "{sep}{index}" + (TRAJECTORY_FILE_EXT if name.endswith(TRAJECTORY_FILE_EXT) else "")

def get_trajectory_file(name: str) -> str:
  if not name: return None
  if not os.path.exists(TRAJECTORY_DIR_PATH): os.mkdir(TRAJECTORY_DIR_PATH)
  return os.path.join(TRAJECTORY_DIR_PATH, name if name.endswith(TRAJECTORY_FILE_EXT) else name + TRAJECTORY_FILE_EXT)

def list_trajectory_files(custom_dir: str="") -> 'list[str]':
  dir = custom_dir or TRAJECTORY_DIR_PATH
  if not os.path.exists(dir): os.mkdir(dir)
  return [os.path.join(dir, f) for f in os.listdir(dir) if f.endswith(TRAJECTORY_FILE_EXT)]
