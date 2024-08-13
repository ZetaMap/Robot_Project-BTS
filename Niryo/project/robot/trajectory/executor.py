from .parser import TrajectoryParser
from .player import TrajectoryPlayer

from util.errors import TrajectoryPlayError
from util.vars import get_trajectory_file

from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

__all__ = [
  "TrajectoryExecutor"
]


class TrajectoryExecutor(TrajectoryPlayer):
  def __init__(self, robot: NiryoRosWrapper, name: str, ignore_errors: bool=False):
    super().__init__(robot, TrajectoryParser.read(get_trajectory_file(name)), ignore_errors)
