"""
Re-implementation of niryo_robot_modbus.input_register_data_block, for own use
"""

from niryo_robot_modbus.data_block import DataBlock
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

from util.logger import Logger

"""
 - Each address contains a 16 bits value
 - READ ONLY registers

 --> State of the robot
"""
...


def handle_negative(val):
    """
    Positive number : 0 - 32767
    Negative number : 32768 - 65535
    """
    if val < 0:
        val = (1 << 15) - val
    return val


class InputRegisterDataBlock(DataBlock):
  def __init__(self, robot: NiryoRosWrapper):
    super().__init__()
    self.robot = robot
    self.logger = Logger(__class__.__name__)

  ...

  # The input register is not needed, so i will keep the class empty
