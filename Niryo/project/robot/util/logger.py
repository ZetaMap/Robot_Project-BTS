"""
Little library to log things easily with topics, colors, error wrapping, etc. 
With writing of logs into files and many others features.
"""

import enum, datetime, os, sys, traceback, typing

class Logger:
  input_prompt: str = "&fb&lg>>> &fr"
  log_prompt: str = "&fb&lk[{time}] &lw[{topic}] "

  def __init__(self, topic: str):
    self.topic = topic

  def __call__(self, text: str='', *args: tuple):
    """If logger is called like a function, just print an info"""
    self.info(text, *args)

  def _format_log_prompt(self) -> str:
    return self.log_prompt.format(time=datetime.datetime.now().strftime("%m-%d-%Y %H:%M:%S"), topic=self.topic)

  def debug(self, text: str='', *args: tuple):
    """
    Log an debug information
    """
    Log.debug(text, *args, pre_tag=self._format_log_prompt())

  def info(self, text: str='', *args: tuple):
    """
    Log an information
    """
    Log.info(text, *args, pre_tag=self._format_log_prompt())

  def warn(self, text: str='', *args: tuple):
    """
    Log an warning
    """
    Log.warn(text, *args, pre_tag=self._format_log_prompt())

  def err(self, text: typing.Union[str, BaseException], *args: tuple, no_stacktrace: bool=False):
    """
    Log an error
    """
    Log.err(text, *args, pre_tag=self._format_log_prompt(), no_stacktrace=no_stacktrace)

  def input(self, prompt: str='', no_block: bool=False) -> str:
    """
    Get an input line
    'no_block' to wait for line to be finished or not
    """
    prompt = (prompt + ' ' if prompt else '') + self.input_prompt
    p = ColorCodes.parse(prompt, Log.use_colors)
    line = (print(p) or sys.stdin.readline()[:-1]) if no_block else input(p)

    # write the input in log files
    if line: Log.write(ColorCodes.parse(prompt, False)+line)

    return line


class ColorCodes:
  """
  Source: https://github.com/Anuken/Arc/blob/master/arc-core/src/arc/util/ColorCodes.java
  """

  flush: str = "\033[H\033[2J"
  reset: str = "\u001B[0m"
  bold: str = "\u001B[1m"
  italic: str = "\u001B[3m"
  underline: str = "\u001B[4m"
  black: str = "\u001B[30m"
  red: str = "\u001B[31m"
  green: str = "\u001B[32m"
  yellow: str = "\u001B[33m"
  blue: str = "\u001B[34m"
  purple: str = "\u001B[35m"
  cyan: str = "\u001B[36m"
  lightBlack: str = "\u001b[90m"
  lightRed: str = "\u001B[91m"
  lightGreen: str = "\u001B[92m"
  lightYellow: str = "\u001B[93m"
  lightBlue: str = "\u001B[94m"
  lightMagenta: str = "\u001B[95m"
  lightCyan: str = "\u001B[96m"
  lightWhite: str = "\u001b[97m"
  white: str = "\u001B[37m"
  backDefault: str = "\u001B[49m"
  backRed: str = "\u001B[41m"
  backGreen: str = "\u001B[42m"
  backYellow: str = "\u001B[43m"
  backBlue: str = "\u001B[44m"

  if os.name == "nt":
    # Try to enable the VT100 feature, ANSI-like escapes codes
    # Sources:
    #   - https://github.com/Textualize/rich/blob/master/rich/_windows.py
    #   - https://stackoverflow.com/a/54291292
    #   - https://learn.microsoft.com/en-us/windows/console/setconsolemode
    #   - https://stackoverflow.com/a/287944
    import ctypes

    hStdOut = ctypes.windll.kernel32.GetStdHandle(-11)
    mode = ctypes.c_ulong()
    success = ctypes.windll.kernel32.GetConsoleMode(hStdOut, ctypes.byref(mode))

    # if terminal already handle ansi codes, mode.value is 7, so will not enable this
    if not (success and mode.value & 4):
      mode.value |= 4
      ctypes.windll.kernel32.SetConsoleMode(hStdOut, mode)

    # Cleanup
    del ctypes, hStdOut, mode, success

  prefix: str = '&'
  codes: dict = {
    "ff": flush,
    "fr": reset,
    "fb": bold,
    "fi": italic,
    "fu": underline,
    "k":  black,
    "lk": lightBlack,
    "lw": lightWhite,
    "r":  red,
    "g":  green,
    "y":  yellow,
    "b":  blue,
    "p":  purple,
    "c":  cyan,
    "lr": lightRed,
    "lg": lightGreen,
    "ly": lightYellow,
    "lm": lightMagenta,
    "lb": lightBlue,
    "lc": lightCyan,
    "w":  white,
    "bd": backDefault,
    "br": backRed,
    "bg": backGreen,
    "by": backYellow,
    "bb": backBlue
  }

  @staticmethod
  def parse(text: str, use_colors: bool=True) -> str:
    if use_colors: # Parse colors
      for color in ColorCodes.codes:
        text = text.replace(f"{ColorCodes.prefix}{color}", ColorCodes.codes[color])

    else: # Remove colors
      for color in ColorCodes.codes:
        text = text.replace(f"{ColorCodes.prefix}{color}", "")

    return text


class LogLevel(enum.Enum):
  debug = 0
  info = 1
  warn = 2
  err = 3
  none = 4


class Log:
  """
  Source: https://github.com/Anuken/Arc/blob/master/arc-core/src/arc/util/Log.java
  """
  file_split_size: int = 512 * 1024 # in bytes
  use_colors: bool = True
  level: LogLevel = LogLevel.info
  write_logs: bool = True
  folder_name: str = "logs"
  logs_path: str = os.path.join("./", folder_name)

  _current_file: str = None

  @staticmethod
  def write(text: str):
    """
    Source: https://github.com/Anuken/Mindustry/blob/master/server/src/mindustry/server/ServerControl.java#L1090
    """
    if not Log.write_logs: return # not enabled

    # Check if folder is created, else create it
    if os.path.basename(Log.logs_path) != Log.folder_name: Log.logs_path = os.path.join(Log.logs_path, Log.folder_name)
    if not os.path.exists(Log.logs_path): os.mkdir(Log.logs_path)

    # Check if current file size is exeeded
    if Log._current_file != None and os.path.getsize(Log._current_file) > Log.file_split_size:
      with open(Log._current_file, 'at') as f: f.write("[End of log file. Date: "+ datetime.datetime.now().strftime("%m-%d-%Y %H:%M:%S") + "]\n")
      Log._current_file = None
      
    # Check for new file
    if Log._current_file == None:
      i = 0
      p = os.path.join(Log.logs_path, f"log-{i}.txt")

      while os.path.exists(p) and (os.path.isdir(p) or os.path.getsize(p) > Log.file_split_size):
        i += 1
        p = os.path.join(Log.logs_path, f"log-{i}.txt")

      # Found available file, open it now
      Log._current_file = p

    # And write the content
    with open(Log._current_file, 'at') as f: f.write(text+'\n')

  @staticmethod
  def format(text: str, *args: tuple, format_prefix: str='@'):
    if len(args):
      for arg in args: text = text.replace(format_prefix, f"&lb&fb{str(arg)}&fr", 1)
    return text

  @staticmethod
  def log(level: LogLevel, text: str, *args: tuple, pre_tag: str=''):
    if Log.level.value > level.value: return

    text = Log.format(str(text), *args)

    for line in text.split('\n'):
      line = (pre_tag +
        ("&lc&fb[D]&fr " if level == LogLevel.debug else
          "&lb&fb[I]&fr " if level == LogLevel.info else
          "&ly&fb[W]&fr " if level == LogLevel.warn else
          "&fr&lr&fb[E] " if level == LogLevel.err else
          "") +
        line + "&fr")

      print(ColorCodes.parse(line, Log.use_colors))
      Log.write(ColorCodes.parse(line, False))

  @staticmethod
  def debug(text: str='', *args: tuple, pre_tag: str=''):
    Log.log(LogLevel.debug, text, *args, pre_tag=pre_tag)

  @staticmethod
  def info(text: str='', *args: tuple, pre_tag: str=''):
    Log.log(LogLevel.info, text, *args, pre_tag=pre_tag)

  @staticmethod
  def warn(text: str='', *args: tuple, pre_tag: str=''):
    Log.log(LogLevel.warn, text, *args, pre_tag=pre_tag)

  @staticmethod
  def err(text: typing.Union[str, BaseException], *args: tuple, pre_tag: str='', no_stacktrace: bool=False):
    if isinstance(text, BaseException):
      text = ''.join(traceback.format_exception_only(type(text), value=text) if no_stacktrace else traceback.format_exception(type(text), value=text, tb=text.__traceback__))[:-1]
    Log.log(LogLevel.err, text, *args, pre_tag=pre_tag)
