"""Simple lock file library"""

from util.strings import get_parent_path
import os


class LockFile:
  def __init__(self, file: str) -> None:
    self.__lock_file = file
    
  @property
  def lockfile(self):
    return self.__lock_file
  
  @property
  def present(self):
    return os.path.exists(self.lockfile)
  
  def acquire(self, who: object):
    """Acquire the lock file. 'who' is an object no matter what, but will represent the handler by an id"""
    parent = get_parent_path(self.lockfile)
    if not os.path.exists(parent): os.mkdir(parent)
    with open(self.lockfile, 'wt') as f: f.write(str(id(who)))    

  def notify_release(self):
    """Notify that the lock file will be released soon"""
    if not self.present: return
    with open(self.lockfile, 'wt') as f: f.write("0")
    
  def release(self):
    """Remove the lock file"""
    if self.present: os.remove(self.lockfile)
  
  def handler(self) -> int:
    """Return the handler id, or 0 if no handler, else -1 if handler is invalid"""
    if not self.present: return 0
    with open(self.lockfile, "rt") as f:
      try: return int(f.read().strip())
      except ValueError: return -1
    
  def handled(self) -> bool:
    """Return if the lock file has an handler"""
    return self.handler() > 0
  