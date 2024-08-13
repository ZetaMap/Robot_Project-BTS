from .trajectory import Trajectory
from .controller import TrajectoryStep, PropertyStep
from .step.type import *

from util.errors import TrajectoryReadError
from util.vars import TRAJECTORY_NEEDED_STEPS
from util.vars import get_trajectory_file, format_trajectory_file_name
from util.strings import sanitize_filename, find_available_file, get_parent_path, get_child_path

import os

__all__ = [
  "TrajectoryParser"
]


class TrajectoryParser:
  @staticmethod
  def make_trajectory_file_by_name(trajectory_name: str) -> str:
    if not trajectory_name: raise ValueError("no trajectory name specified")
    return find_available_file(get_trajectory_file(format_trajectory_file_name(sanitize_filename(trajectory_name.lower().replace(' ', '-')))))

  @staticmethod
  def write(traj: Trajectory):
    file = traj.get_filename()
    if file: file = get_trajectory_file(file)
    else:
      # Format a new file name with trajectory name (or default name), if not defined
      name = traj.get_name()
      file = TrajectoryParser.make_trajectory_file_by_name(name if name else "untitled-"+str(traj.get_id() or "trajectory"))
      traj.set_filename(get_child_path(file))

    content = traj.get_content()
    path = get_parent_path(file)
    if not os.path.exists(path): os.mkdir(path)
    with open(file, "wt") as f:
      for t in content: f.write(t.serialize() + '\n')

  @staticmethod
  def delete(traj: Trajectory):
    file = get_trajectory_file(traj.get_filename())
    if os.path.exists(file): os.remove(file)

  @staticmethod
  def read(file: str) -> Trajectory:
    traj = Trajectory()
    traj.set_filename(get_child_path(file))
    found_steps = []

    with open(file, "rt") as f:
      i = 1
      line = TrajectoryParser.read_next_step(f)

      while line:
        step = TrajectoryParser.find_step_type(line)

        if not step.duplicate_allowed and step in found_steps:
          raise TrajectoryReadError(file, f"duplicated {step.label} step ({step.alias!r}) at line {i}. This step must only appear once in this trajectory.")
        try:
          if step.is_property: traj.set_property(PropertyStep(step, step.deserialize(line)))
          else: traj.add_step(TrajectoryStep(step, step.deserialize(line)))
        except Exception as e: raise TrajectoryReadError(file, f"unable to decode {step.label} step ({step.alias!r}) at line {i}: ", e) from None

        found_steps.append(step)
        i += 1
        line = TrajectoryParser.read_next_step(f)

    if not all(s in found_steps for s in TRAJECTORY_NEEDED_STEPS):
      raise TrajectoryReadError(file, "missing needed step(s) in trajectory: " + ", ".join(f"{s.alias!r} ({s.label})" for s in TRAJECTORY_NEEDED_STEPS if s not in found_steps))
    return traj

  @staticmethod
  def read_next_step(file) -> str:
    line = file.readline()
    l = line.strip()
    while line and not l:
      line = file.readline()
      l.strip()
    return l

  @staticmethod
  def find_step_type(line: str) -> StepType:
    return StepTypes.find(line)
