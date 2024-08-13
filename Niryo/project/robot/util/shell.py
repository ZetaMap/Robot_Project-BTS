"""Wrapper to execute commands"""

from util.logger import Logger
from util.vars import EXIST_REQUESTED_EVENT
from .commands import ShellCommands

from threading import Thread
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper

__all__ = [
  "Shell",
  "ShellManager"
]


class Shell:
  def __init__(self, robot: NiryoRosWrapper):
    self.robot = robot
    self.logger = Logger(__class__.__name__)

  def parse_command(self, command_args: 'tuple[str]') -> int:
    for command in ShellCommands.commands:
      if command_args[0] == command.name:
        if len(command_args)-1 < command.args_needed: 
          self.logger.err(f"The command '{command_args[0]}' need {command.args_needed} argument" + ('s' if command.args_needed > 1 else ''))
          return
        else: return command(self.robot, self.logger, *command_args[1:])
    else: self.logger.err(f"Command '{command_args[0]}' not found. See 'help' for usage")

  def wait_process_command(self) -> int:
    """
    Request a command to user and execute it.

    This, block the input, so run this in another thread

    @ Return 0 if no error.
    @ Return 1 if an error is raised by a command.
    @ Return 127 if empty command
    @ Return 255 if exit requested
    """
    try:
      command_args = tuple([arg for arg in self.logger.input().split(' ') if arg])
      if not len(command_args) or command_args[0] == '': return 127
      return self.parse_command(command_args) or 0

    except EOFError:
      # started with service, there are no stdin, so wait a little and print nothing to avoid filling logs
      import time
      time.sleep(0.1)

    except Exception as e:
      self.logger.warn("Command raised an error during execution.")
      self.logger.err(e, no_stacktrace=True)

      return 1
    return 0
  
  
class ShellManager(Thread):
  def __init__(self, robot: NiryoRosWrapper):
    super().__init__(name="Shell", daemon=True)
    self.robot = robot
    self.shell = Shell(self.robot)

  def run(self):
    try:
      self.shell.logger.info("Shell started")

      while not EXIST_REQUESTED_EVENT.is_set():
        if self.shell.wait_process_command() == 255: EXIST_REQUESTED_EVENT.set()
    except BaseException as e:
      self.shell.logger.err("\nError while running shell!\n")
      self.shell.logger.err(e)

    self.shell.logger.info("Shell stopped")
