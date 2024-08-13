"""Command line parser for project"""

import os
from argparse import ArgumentParser
from util.logger import Log, LogLevel

__all__ = ["CliParser"]


class CliParser(ArgumentParser):
  def __init__(self):
    super().__init__(usage="%(prog)s [OPTIONS]", 
                     epilog="Note: Logs writing will be done into files, split every 512 KB.")
    
    # Create arguments
    self.add_argument("--no-calibration",
                        action="store_true",
                        help="disable auto calibration at start of program",
                        dest="nocalibration")
    self.add_argument("--no-trajectories",
                        action="store_true",
                        help="doesn't load trajectories",
                        dest="notrajectories")
    self.add_argument("--no-modbus",
                        action="store_true",
                        help="disable Modbus/TCP server",
                        dest="nomodbus")
    self.add_argument("--no-terminal",
                        action="store_true",
                        help="disable the terminal",
                        dest="noterminal")
    self.add_argument("--no-status-sound",
                        action="store_true",
                        help="disable colors when logging",
                        dest="nostatussound")
    self.add_argument("--no-default-pose",
                        action="store_true",
                        help="doesn't move to default pose when stopping robot",
                        dest="nodefaultpose")
    self.add_argument("--no-gamepad",
                        action="store_true",
                        help="doesn't start gamepad manager",
                        dest="nogamepad")
    self.add_argument("--no-colors",
                        action="store_true",
                        help="disable colors when logging",
                        dest="nocolors")
    self.add_argument("--no-write-logs",
                        action="store_true",
                        help="disable writting of logs in files",
                        dest="nowritelogs")
    self.add_argument("--logs-path",
                        action="store",
                        default=os.getcwd(),
                        type=str,
                        help="the directory to write logs. (default is working directory)",
                        dest="logspath")
    self.add_argument("--log-folder",
                        action="store",
                        default=Log.folder_name,
                        type=str,
                        help="the folder name to store log files. (default is 'logs')",
                        dest="name")
    self.add_argument("--log-level",
                        action="store",
                        default="info",
                        choices=[l.name for l in LogLevel],
                        help="set a default logging level",
                        dest="loglevel")
