"""All errors classes here"""

class StepAliasError(Exception): ...

class StepDeserializeError(Exception):
  def __init__(self, exc: Exception, *args: object):
    super().__init__(exc, *args)
    self.exc = exc
    
  def __str__(self) -> str:
    t = type(self.exc)
    return t.__name__ + ": " + super().__str__() if issubclass(t, Exception) else str(self.exc)

class TrajectoryReadError(Exception):
  def __init__(self, file: str, message: str, *args: object):
    super().__init__(*args)
    self.file = file
    self.message = message

  def __str__(self) -> str:
    m = super().__str__()
    return f"[{self.file}] {self.message}" + (" :" + m if m and m.strip() != ':' else '')

class TrajectoryLearningError(Exception): ...

class TrajectoryPlayError(Exception):
  def __init__(self, exc: Exception, *args: object):
    super().__init__(exc, *args)
    self.exc = exc
    
  def __str__(self) -> str:
    t = type(self.exc)
    return t.__name__ + ": " + super().__str__() if issubclass(t, Exception) else str(self.exc)

class TrajectoryManagerError(Exception): ...

class TrajectoryNotFoundError(Exception): ...

class ModbusServerError(Exception): ...
