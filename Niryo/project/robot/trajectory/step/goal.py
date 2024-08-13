from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapperException

#import dataclasses
#
#@dataclasses.dataclass
#class _sevice_response_stub:
#  status: int
#  message: str


class GoalResult:
  def __init__(self, status: int, message: str="", error: Exception=None):
    self.status = status
    self.message = message if message else "<Unknown message>"
    self.error = error


class GoalFailure(Exception, GoalResult):
  def __init__(self, test_result: GoalResult):
    GoalResult.__init__(self, test_result.status, test_result.message, test_result.error)
    
  def __str__(self):
    return type(self.error).__name__ + ": " + str(self.error) if self.error else "["+str(self.status)+"] " + self.message


class GoalReport(object):
  def __init__(self, function, args=[], prefix=""):
#    try: result = function(*args) or _sevice_response_stub(status=-1, message="Command never returned status")
#    except GoalFailure as e: self.result = GoalResult(e.status, e.message, e.error)
#    except Exception as e: self.result = GoalResult(-2, "{}{} - {}".format(prefix, " failed" if prefix else "Failed", str(e)), e)
#    else:
#      self.result = GoalResult(result.status)
#      if result.status >= 0: self.result.message = "{}{} - {}".format(prefix,  " succeed" if prefix else "Succeed", result.message)
#      else: self.result.message = "{}{} - {}".format(prefix, " failed" if prefix else "Failed", result.message)

    try: status, message = function(*args) or (-1, "Command never returned status")
    except GoalFailure as e: self.result = GoalResult(e.status, e.message, e.error)
    # TODO: handle stupid niryo error
    #except NiryoRosWrapperException as e:
    #  ...
    except Exception as e: self.result = GoalResult(-2, "{}{} - {}".format(prefix, " failed" if prefix else "Failed", str(e)), e)
    else:
      self.result = GoalResult(status)
      if status >= 0: self.result.message = "{}{} - {}".format(prefix,  " succeed" if prefix else "Succeed", message)
      else: self.result.message = "{}{} - {}".format(prefix, " failed" if prefix else "Failed", message)

  def raise_if_error(self):
    if self.result.status < 0: raise GoalFailure(self.result)


