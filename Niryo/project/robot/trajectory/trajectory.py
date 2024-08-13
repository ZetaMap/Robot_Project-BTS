from .step.type import *
from .step.value import *
from .controller import TrajectoryStep, PropertyStep, TrajectoryController

from util.vars import TRAJECTORY_MAX_ID, TRAJECTORY_IDS

__all__ = [
  "Trajectory"
]


class Trajectory(TrajectoryController):
  @staticmethod
  def clear_all_ids():
    TRAJECTORY_IDS.clear()
  
  def new_id(self) -> TrajectoryController:
    size = len(TRAJECTORY_IDS)
    if size > TRAJECTORY_MAX_ID: raise ValueError("cannot assign new id, limit reached")
    self.set_id(0 if size == 0 else max(TRAJECTORY_IDS)+1)
    return self
  
  def set_property(self, step: PropertyStep) -> TrajectoryController:
    """Intercept .set_property() to save ids and avoid to duplicate it"""
    if step.type == StepTypes.id.value:
      new = step.get_value()
      if new in TRAJECTORY_IDS: raise ValueError(f"duplicated trajectory id {new!r}, use .new_id()")
      old = self.get_id()
      if old is not None: TRAJECTORY_IDS.remove(old)
      TRAJECTORY_IDS.append(new)
    return super().set_property(step)
  
  def set_start_state(self, tool: bool, joints: 'tuple[float]') -> 'Trajectory':
    self.set_property(TrajectoryStep(StepTypes.start.value, StepValue((StepValue(tool), StepValue(joints)))))
    return self

  def get_start_state(self) -> 'tuple[bool, tuple[float]]':
    result = self.get_property(StepTypes.start.value)
    return None if result is None else [v.value if isinstance(v, StepValue) else v for v in result.get_value()]

  def set_name(self, name: str) -> 'Trajectory':
    self.set_property(TrajectoryStep(StepTypes.label.value, StepValue(name)))
    return self

  def get_name(self) -> str:
    result = self.get_property(StepTypes.label.value)
    return None if result is None else result.get_value()

  def set_id(self, id: int) -> 'Trajectory':
    self.set_property(TrajectoryStep(StepTypes.id.value, StepValue(id)))
    return self

  def get_id(self) -> int:
    result = self.get_property(StepTypes.id.value)
    return None if result is None else result.get_value()

  def set_filename(self, filename: str) -> 'Trajectory':
    self.set_property(TrajectoryStep(StepTypes.file.value, StepValue(filename)))
    return self

  def get_filename(self) -> str:
    result = self.get_property(StepTypes.file.value)
    return None if result is None else result.get_value()

  def add_joints(self, joints: 'tuple[float]') -> 'Trajectory':
    return self.add_step(TrajectoryStep(StepTypes.move.value, StepValue(joints)))

  def add_tool_state(self, state: bool) -> 'Trajectory':
    return self.add_step(TrajectoryStep(StepTypes.tool.value, StepValue(state)))

  def add_motor_speed(self, percent: int) -> 'Trajectory':
    return self.add_step(TrajectoryStep(StepTypes.acceleration.value, StepValue(percent)))
