"""Test type of things"""

__all__ = [
  "Tests",
  "Convert"
]

def _create_test(message, *valid_types, reverse=False):
  """
  Decorator to create the test. Put this before an empty method with (*objects, raise_err=True) arguments.

  The message can contains {found} and {valid} keys to format found type and required types.

  If reverse is True: checks if type is anything except valid_types.
  
  """
  if type(message) != str: raise TypeError("message must be an str")
  if len(valid_types) == 0: raise IndexError("one type or more must be specified")
  if not all(issubclass(type(t), type) for t in valid_types): raise TypeError("valid_types must be a list of types")

  def decorator(func):
    type_msg = valid_types[0].__name__ if len(valid_types) == 1 else (", ".join([i.__name__ for i in valid_types[:-1]])+" or "+valid_types[-1].__name__)
    def wrapper(*objects, raise_err=True):
      for o in objects:
        if type(o) in valid_types if reverse else type(o) not in valid_types:
          if raise_err: raise TypeError(message.format(found=type(o).__name__, valid=type_msg))
          return False
      return True
    return wrapper
  return decorator

# Some aliases to avoid overloading of originals
Str = str
Int = int
Float = float
Bool = bool

class Tests:
  @staticmethod
  @_create_test("object must be {valid!r}, not {found!r}", Bool)
  def bool(*objects, raise_err=True): ...

  @staticmethod
  @_create_test("can't convert {found} to {valid}", Int)
  def int(*objects, raise_err=True): ...

  @staticmethod
  @_create_test("can't convert {found} to {valid}", Float, Int)
  def float(*objects, raise_err=True): ...

  @staticmethod
  @_create_test("can't convert {found!r} object to {valid} implicitly", Str)
  def str(*objects, raise_err=True): ...

  @staticmethod
  @_create_test("buffer must be {valid} object, got {found!r} object", Str)
  def buff(*objects, raise_err=True): ...

  @staticmethod
  @_create_test("object {found!r} isn't a {valid}", tuple, list)
  def list(*objects, raise_err=True): ...

  @staticmethod
  @_create_test("{valid} object not allowed", type(None), reverse=True)
  def none(*objects, raise_err=True): ...


  @staticmethod
  def object_size(size, *objects, raise_err=True):
    for o in objects:
      s = len(o)
      if s != size:
        if raise_err: raise IndexError(f"size of {type(o).__name__!r} must be {size}, not {s}")
        return False
    return True

class Convert:
  @staticmethod
  def to_bool(value):
    if type(value) == str: return value.lower() in ("yes","on","enabled","activated","true","1")
    else: return bool(value)