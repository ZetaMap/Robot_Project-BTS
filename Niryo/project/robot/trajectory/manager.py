from .trajectory import Trajectory
from .parser import TrajectoryParser

from util.logger import Logger
from util.errors import TrajectoryManagerError
from util.vars import list_trajectory_files

__all__ = [
  "TrajectoryManager",
  "TRAJECTORY_MANAGER",
]


class TrajectoryManager:
  def __init__(self):
    self.trajectories: 'list[Trajectory]' = []
    self.logger = Logger(__class__.__name__)
    self.current_play = None

  def __iter__(self):
    return iter(self.trajectories)

  def count_trajectories(self):
    return len(self.trajectories)

  def load_add(self, custom_directory: str="") -> 'TrajectoryManager':
    try:
      for file in list_trajectory_files(custom_directory):
        self.logger.debug("Loading trajectory: @", file)
        self.add(TrajectoryParser.read(file))
    except Exception as e:
      if isinstance(e, TrajectoryManagerError): raise
      raise TrajectoryManagerError("Error while loading trajectories: " + str(e)) from None
    return self

  def load_replace(self, custom_directory: str="") -> 'TrajectoryManager':
    # clear all ids
    Trajectory.clear_all_ids()
    return self.clear().load_add(custom_directory)

  load = load_add
  reload = load_replace

  def save(self) -> 'TrajectoryManager':
    # Save the error instead of raising it quickly.
    # This way avoid more error when stopping the program.
    error = None
    try:
      for i, t in enumerate(self):
        if not t.get_name() and not t.get_filename():
          error = ValueError(f"no valid properties to save the trajectory {i}. Make sure the name or/and the filename properties are set.")
        TrajectoryParser.write(t)
        self.logger.debug("Saved trajectory '@' at @", t.get_name(), t.get_filename())
    except Exception as e: error = e
    
    if error: raise TrajectoryManagerError("Error while saving trajectories (last error): " + str(error)) from None
    return self

  def add(self, trajectory: Trajectory) -> 'TrajectoryManager':
    # Check trajectory id
    id = trajectory.get_id()
    if id is None: raise TrajectoryManagerError("id is missing is trajectory, use trajectory.new_id() to assign an id")
    if self.get_by_id(id) is not None: 
      raise TrajectoryManagerError(f"duplicated trajectory with id {id}, use trajectory.new_id() to assign a new id")
    self.trajectories.append(trajectory)
    return self

  def remove(self, trajectory: Trajectory):
    self.trajectories.remove(trajectory)
    
  def delete(self, trajectory: Trajectory):
    self.remove(trajectory)
    TrajectoryParser.delete(trajectory)
    del trajectory

  def clear(self) -> 'TrajectoryManager':
    self.trajectories.clear()
    return self

  def get(self, index: int) -> Trajectory:
    return self.trajectories[index]

  def get_by_name(self, traj_name: str, ignore_case: bool=True) -> Trajectory:
    if ignore_case:
      traj_name = traj_name.lower()
      return self.find(lambda t: t.get_name().lower() == traj_name)
    return self.find(lambda t: t.get_name() == traj_name)

  def get_by_id(self, id: int) -> Trajectory:
    return self.find(lambda t: t.get_id() == id)

  def find(self, consumer: 'function[[Trajectory], bool]') -> Trajectory:
    for t in self:
      if consumer(t): return t
    return None

  def sort(self) -> 'TrajectoryManager':
    self.trajectories = sorted(self.trajectories, key=lambda v: v.get_id())
  

# Global Instance
TRAJECTORY_MANAGER = TrajectoryManager()