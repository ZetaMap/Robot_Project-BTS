from .trajectory import Trajectory
from .manager import TRAJECTORY_MANAGER

from util.errors import TrajectoryPlayError, TrajectoryNotFoundError
from util.logger import Logger

from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper
import typing, rospy, threading

__all__ = [
  "TrajectoryPlayer"
]


class TrajectoryPlayer:
  def __init__(self, robot: NiryoRosWrapper, trajectory: Trajectory, ignore_errors: bool=False):
    self.robot = robot
    self.logger = Logger(__class__.__name__)
    self.trajectory = trajectory
    self.ignore_errors = ignore_errors
    self.play_started = False
    self.thread = None

  @staticmethod
  def play_trajectory(robot: NiryoRosWrapper, id_or_name: 'typing.Union[int, str]', play_async: bool=False) -> 'TrajectoryPlayer':
    trajectory = TRAJECTORY_MANAGER.get_by_name(id_or_name)
    if not trajectory and id_or_name.isdigit(): trajectory = TRAJECTORY_MANAGER.get_by_id(int(id_or_name))
    if not trajectory: raise TrajectoryNotFoundError(f"Trajectory {id_or_name!r} not found")
    else:
      player = TrajectoryPlayer(robot, trajectory)
      if play_async: player.play_async()
      else: player.play()
      return player

  def is_playing(self) -> bool:
    return self.play_started or (self.thread and self.thread.is_alive())

  def play_all(self):
    if self.is_playing(): raise TrajectoryPlayError("already playing a trajectory")
    if self.robot.collision_detected:
      self.logger.warn("A collision has been detected while last movement. Removing trigger ...")
      self.robot.clear_collision_detected()

    try: self.robot.stop_move()
    except: pass
    self.robot.set_learning_mode(False)

    i = 0
    for s in self.play_next_step():
      self.logger.debug(f"[{self.trajectory.get_name()}] Playing step number {i}: {s.type.label} ({s.get_value()})")
      i += 1
    rospy.sleep(0.1)

  play = play_all

  def play_async(self):
    if self.is_playing(): raise TrajectoryPlayError("already playing a trajectory")
    self.thread = threading.Thread(target=self.play_all, name="Async"+__class__.__name__, daemon=True)

  def play_next_step(self):
    self.play_started = True
    for step in self.trajectory:
      if not self.play_started and not self.ignore_errors: raise StopIteration("trajectory has been stopped")
      try:
        step.run(self.robot).raise_if_error()
        yield step
      except Exception as e:
        if self.ignore_errors: self.logger.err(e)
        else: raise TrajectoryPlayError(e) from None

  def stop(self):
    if not self.play_started and not self.ignore_errors: raise TrajectoryPlayError("not playing trajectory")
    self.play_started = False
    self.robot.stop_move()
    
    if self.thread:
      self.thread.join(5)
      if self.thread.is_alive():
        self.logger.warn("async running of trajectory '@', not stopping! Killing...", self.trajectory.get_name())
      try: self.thread._stop()
      except: pass
      self.thread = None
