"""String utilities"""

import re, os

filename_pattern = re.compile(r"[\0/\"<>|:*?\\]")
reserved_filename_pattern = re.compile(r"(CON|AUX|PRN|NUL|(COM[0-9])|(LPT[0-9]))((\..*$)|$)", re.IGNORECASE)
time_periods = (
  ('year',   1000*60*60*24*365),
  ('month',  1000*60*60*24*30),
  ('day',    1000*60*60*24),
  ('hour',   1000*60*60),
  ('minute', 1000*60),
  ('second', 1000*1),
  ('milisecond', 1),
)


def sanitize_filename(filename: str) -> str:
  """
  Replaces non-safe filename characters with '_'. Handles reserved window file names.

  Source: https://github.com/Anuken/Arc/blob/master/arc-core/src/arc/util/Strings.java
  """
  if reserved_filename_pattern.match(filename): return "a" + filename
  return ''.join([c for c in filename_pattern.sub("_", filename) if c.isprintable()])

def find_available_file(file: str, start_index: int=0, separator: str='-') -> str:
  """
  Find a non-existing file name, with an index. \n
  The separator and the index will be added if the specified file already exist.

  Accepted formatting:
    * '{sep}': separator between name and index, can be changed with 'separator' parameter
    * '{index}': file index

  (e.g. 'log{sep}{index}.txt')
  """
  f = file.format(sep='', index='')
  # Do a first check before adding index
  if not os.path.exists(f) and not os.path.isdir(f): return f
  # Add default formatting if not added in 'file'
  if file == f: file += "{sep}{index}"
  # Find a non-existing file
  f = file.format(sep=separator, index=start_index)
  while os.path.exists(f) or os.path.isdir(f):
    start_index += 1
    f = file.format(sep=separator, index=start_index)
  return f

def get_parent_path(path: str) -> str:
  """
  Get parent directory or itself if is the root directory.
  """
  if not path: return path
  p = path[:-1] if path.endswith('/') or path.endswith('\\') else path
  p = p[:p.rfind('/')+1 or p.rfind('\\')+1]
  return p if p else path

def get_child_path(path: str) -> str:
  """
  Get last child of a path or itself if is the root directory.
  """
  if not path: return path
  p = path[:-1] if path.endswith('/') or path.endswith('\\') else path
  p = p[p.rfind('/')+1 or p.rfind('\\')+1:]
  return p if p else path

def getchar() -> str:
	"""Returns a single character from standard input"""
	ch = ''
	if os.name == 'nt': # how it works on windows
		import msvcrt
		ch = msvcrt.getch()
	else:
		import tty, termios, sys
		fd = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd)
		try:
			tty.setraw(sys.stdin.fileno())
			ch = sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
	if ord(ch) == 3: raise KeyboardInterrupt # handle ctrl+C
	return ch


def rJust(str: str, newLength: int, filler: str=" ") -> str:
  if len(filler) == 0: return str
  return filler * ((newLength - len(str)) // len(filler)) + filler[:((newLength - len(str)) % len(filler))] + str

def rJustList(lst: 'list[str]', newLength: int, filler: str=" ") -> 'list[str]':
  return [rJust(s, newLength, filler)  for s in lst]

def lJust(str: str, newLength: int, filler: str=" ") -> str:
  if len(filler) == 0: return str
  return str + filler * ((newLength - len(str)) // len(filler)) + filler[:((newLength - len(str)) % len(filler))]

def lJustList(lst: 'list[str]', newLength: int, filler: str=" ") -> 'list[str]':
  return [lJust(s, newLength, filler) for s in lst]

def mJust(left: str, right: str, newLength: int, filler: str=" ") -> str:
  if len(filler) == 0: return left + right
  s = newLength - len(left) - len(right)
  return left + filler * (s // len(filler)) + filler[: (s % len(filler))] + right

def mJustList(left: 'list[str]', right: 'list[str]', newLength: int, filler: str=" ") -> 'list[str]':
  arr = []
  for l, r in zip(left, right): arr.append(mJust(l, r, newLength, filler))
  if len(left) > len(right): arr.extend(lJustList(left[len(right):], newLength, filler))
  elif len(right) > len(left): arr.extend(rJustList(right[len(left):], newLength, filler))
  return arr


def timedelta_format(delta_ms):
  delta_ms = int(delta_ms)
  strings=[]
  for period_name, period_seconds in time_periods:
    if delta_ms > period_seconds:
      period_value, delta_ms = divmod(delta_ms, period_seconds)
      strings.append("%s %s%s" % (period_value, period_name, 's'*(period_value>1)))

  return (strings[0] if len(strings) < 2 else ", ".join(strings[:-1]) + " and " + strings[-1]) if strings else "0 "+time_periods[-1][0]
