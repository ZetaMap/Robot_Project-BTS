from util.tests import Tests
from util.vars import *

from .value import StepValue
from .goal import GoalReport

import enum
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

__all__ = [
  "StepExecutor",
  "StepExecutors"
]


class StepExecutor:
  def __init__(self, executor: 'function[[NiryoRosWrapper, object], tuple]'):
    self.__executor = executor

  def run(self, robot: NiryoRosWrapper, args: StepValue) -> GoalReport:
    return GoalReport(self.executor, (robot, args.value))

  @property
  def executor(self):
    return self.__executor


class _executor_funcs_temp:
  @staticmethod
  def start_executor(robot, args):
    result = StepExecutors.tool.value.run(robot, args[0])
    result.raise_if_error()
    result = StepExecutors.move.value.run(robot, args[1])
    result.raise_if_error()
    return (result.result.status, result.result.message)


class StepExecutors(enum.Enum):
  move = StepExecutor(lambda robot, args: Tests.list(args) and Tests.object_size(AXIS_JOINTS_COUNT, args) and all(Tests.float(v) for v in args) and robot.move_joints(*args))
  tool = StepExecutor(lambda robot, args: Tests.bool(args) and (robot.grasp_with_tool() if args else robot.release_with_tool()))
  start = StepExecutor(lambda robot, args: Tests.list(args) and Tests.object_size(2, args) and _executor_funcs_temp.start_executor(robot, args))
  acceleration = StepExecutor(lambda robot, args: Tests.int(args) and robot.set_arm_max_velocity(args))
  none = StepExecutor(lambda *_: (0, "Nothing to do"))
