class StepValue:
  def __init__(self, value: object=None):
    self.__value = value

  def __repr__(self) -> str:
    return f"{__class__.__name__}({repr(self.value)})"

  __str__ = __repr__

  @property
  def is_none(self) -> bool:
    return self.value is None

  @property
  def value(self) -> object:
    return self.__value

