from .step.type import *
from .step.value import *
from .step.goal import GoalReport
from util.vars import TRAJECTORY_NEEDED_STEPS
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

__all__ = [
  "TrajectoryStep",
  "TrajectoryController",
]


class TrajectoryStep:
  def __init__(self, type: StepType, value: StepValue=StepValue()):
    self.type = type
    self.value = value

  def __repr__(self):
    return f"{__class__.__name__}(step={repr(self.type)}, value={repr(self.value)})"

  __str__ = __repr__

  def serialize(self) -> str:
    return self.type.serialize(self.value)

  def deserialize(self, buffer: str):
    self.value = self.type.deserialize(buffer)

  def run(self, robot: NiryoRosWrapper) -> 'GoalReport':
    return self.type.executor.run(robot, self.value)

  def get_value(self) -> object:
    return self.value.value if self.value else self.value
  
  def is_property(self) -> bool:
    return self.type.is_property


class PropertyStep(TrajectoryStep): 
  """This is same as TrajectoryStep"""
  ...


class TrajectoryController:
  def __init__(self):
    self.__properties = {}
    self.__steps = []

  def __iter__(self):
    return iter(self.get_content())

  def set_property(self, step: PropertyStep) -> 'TrajectoryController':
    if not step.is_property(): raise ValueError("step type is not an property. Use .add_step() to add normal steps")
    self.__properties.update({step.type: step})
    return self

  def get_property(self, type: StepType) -> PropertyStep:
    return self.__properties.get(type, None)

  def add_step(self, step: TrajectoryStep) -> 'TrajectoryController':
    if step.is_property(): raise ValueError("this step is an property. Use .set_property() to set info steps")
    if not step.type.duplicate_allowed and self.contains(step.type): raise ValueError(f"step {step.type.alias!r} already exist, and does not allow more than one use.")
    self.__steps.append(step)
    return self

  def get_step(self, index: int) -> TrajectoryStep:
    return self.__steps[index]
  
  def pop_step(self, index: int=-1) -> TrajectoryStep:
    return self.__steps.pop(index)

  def clear(self) -> 'TrajectoryController':
    self.__init__(self)
    return self

  def contains(self, type: StepType) -> bool:
    for s in self.__steps:
      if s.type == type: return True
    return False

  def count_steps(self) -> int:
    return len(self.__steps)

  def get_steps(self) -> 'list[PropertyStep]':
    return self.__steps.copy()
  
  def get_properties(self) -> 'list[TrajectoryStep]':
    return list(self.__properties.values())

  def get_content(self) -> 'list[TrajectoryStep]':
    for s in TRAJECTORY_NEEDED_STEPS:
      if s not in self.__properties and not self.contains(s):
        raise ValueError(f"{s.label} step ({s.alias!r}) is needed, but not present")
    if self.count_steps() == 0: raise IndexError("no usefull steps in trajectory")
    return self.get_properties() + self.get_steps()
