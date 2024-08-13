import enum
from util.tests import Tests, Convert
from util.vars import *
from util.errors import StepAliasError, StepDeserializeError
from .executor import StepExecutor, StepExecutors
from .value import StepValue

__all__ = [
  "StepType",
  "StepTypes",
]


class StepType:
  def __init__(self, id: int, alias: str, label: str, needed: bool, is_property: bool, duplicate_allowed: bool, none_value_allowed: bool,
               executor: StepExecutor, serializer: 'function[[object], str]', deserializer: 'function[[str], object]'
  ):
    self.id = id
    if len(alias) != 1: raise TypeError("'alias' must be one char")
    self.alias = alias
    self.label = label
    self.needed = needed
    self.is_property = is_property
    self.duplicate_allowed = duplicate_allowed
    self.none_value_allowed = none_value_allowed
    self.executor = executor
    self.__serializer = serializer
    self.__deserializer = deserializer

  def __repr__(self):
    return f"{__class__.__name__}(id={self.id}, alias={self.alias}, label={repr(self.label)})"

  __str__ = __repr__

  @property
  def serializer(self):
    return self.__serializer

  @property
  def deserializer(self):
    return self.__deserializer

  def serialize(self, value: StepValue) -> str:
    if self.none_value_allowed and value.is_none: return self.alias
    Tests.none(value.value)
    buffer = self.serializer(value.value)
    if not Tests.buff(buffer, raise_err=False): raise TypeError("returned buffer must be str")
    return self.alias + ' ' + buffer.strip()

  def deserialize(self, buffer: str) -> StepValue:
    self.check_buffer(buffer)
    if self.none_value_allowed and self.is_valid_alias(buffer.strip()): return StepValue()
    try: return StepValue(self.deserializer(buffer[len(self.alias)+1:].strip()))
    except Exception as e: raise StepDeserializeError(e)

  def is_valid_alias(self, alias: str) -> bool:
    return self.alias == alias

  def check_buffer(self, buffer: str, raise_err=True) -> bool:
    valid = Tests.buff(buffer, raise_err=raise_err)
    if not valid: return False
    if not buffer: raise ValueError("buffer is empty")
    buffer += ' '
    if buffer[1] != ' ' and buffer[1] != '\t':
      if raise_err: raise StepAliasError("unable to find alias")
      return False
    if not self.is_valid_alias(buffer[0]):
      if raise_err: raise StepAliasError(f"alias is invalid, got {buffer[0]!r}; must be {self.alias!r}")
      return False
    return True


class _step_funcs_temp:
  @staticmethod
  def serialize_int(values):
    Tests.int(values)
    return str(values)

  @staticmethod
  def deserialize_int(buffer):
    return int(buffer)
  
  @staticmethod
  def serialize_str(values):
    Tests.str(values)
    return values

  @staticmethod
  def deserialize_str(buffer):
    return str(buffer)

  @staticmethod
  def start_serializer(values):
    Tests.list(values)
    Tests.object_size(2, values)
    if any(not isinstance(v, StepValue) for v in values): raise ValueError(f"list must only contains {StepValue.__name__!r} objects")
    return _step_funcs_temp.tool_serializer(values[0].value) + ' ' + _step_funcs_temp.move_serializer(values[1].value)

  @staticmethod
  def start_deserializer(buffer):
    i = buffer.find(' ')
    if i < 1: raise ValueError("unable to decode values")
    return [StepValue(_step_funcs_temp.tool_deserializer(buffer[0:i])), StepValue(_step_funcs_temp.move_deserializer(buffer[i:]))]

  @staticmethod
  def move_serializer(values):
    Tests.list(values)
    Tests.object_size(AXIS_JOINTS_COUNT, values)
    Tests.float(*values)
    return ' '.join(str(round(v, AXIS_JOINTS_PRECISION)) for v in values)

  @staticmethod
  def move_deserializer(buffer):
    out = [float(v) for v in buffer.split(' ') if v]
    Tests.object_size(AXIS_JOINTS_COUNT, out)
    return out

  @staticmethod
  def tool_serializer(values):
    Tests.bool(values)
    return str(int(values))

  @staticmethod
  def tool_deserializer(buffer):
    return Convert.to_bool(buffer)


class StepTypes(enum.Enum):
  label = StepType(0, 'l', "label", True, True, False, False,
      StepExecutors.none.value, _step_funcs_temp.serialize_str, _step_funcs_temp.deserialize_str)
  id =  StepType(1, 'i', "id", True, True, False, False,
      StepExecutors.none.value, _step_funcs_temp.serialize_int, _step_funcs_temp.deserialize_int)
  start = StepType(2, 's', "start point", True, True, False, False,
      StepExecutors.start.value, _step_funcs_temp.start_serializer, _step_funcs_temp.start_deserializer)
  move = StepType(3, 'm', "movement", False, False, True, False,
      StepExecutors.move.value, _step_funcs_temp.move_serializer, _step_funcs_temp.move_deserializer)
  tool = StepType(4, 't', "tool", False, False, True, False,
      StepExecutors.tool.value, _step_funcs_temp.tool_serializer, _step_funcs_temp.tool_deserializer)
  acceleration = StepType(5, 'a', "motor acceleration", False, False, True, False,
      StepExecutors.acceleration.value, _step_funcs_temp.serialize_int, _step_funcs_temp.deserialize_int)
  file = StepType(6, 'f', "file name", False, True, False, False,
      StepExecutors.none.value, _step_funcs_temp.serialize_str, _step_funcs_temp.deserialize_str)
  none = StepType(255, 'u', "<unknown>", False, False, True, True,
      StepExecutors.none.value, lambda *_: '', lambda *_: None)

  @staticmethod
  def find(buffer: str) -> StepType:
    for type in StepTypes:
      if type.value.check_buffer(buffer, raise_err=False): return type.value
    return StepTypes.none.value

  @staticmethod
  def select(consumer: 'function[[StepType], bool]') -> 'list[StepType]':
    l = []
    for type in StepTypes:
      if consumer(type.value): l.append(type.value)
    return l

  @staticmethod
  def get(consumer: 'function[[StepType], bool]') -> StepType:
    for type in StepTypes:
      if consumer(type.value): return type.value
    return StepTypes.none.value


TRAJECTORY_BANNED_DUPLICATED_STEPS.extend(StepTypes.select(lambda type: not type.duplicate_allowed))
TRAJECTORY_NEEDED_STEPS.extend(StepTypes.select(lambda step: step.needed))
TRAJECTORY_PROPERTY_STEPS.extend(StepTypes.select(lambda step: step.is_property))