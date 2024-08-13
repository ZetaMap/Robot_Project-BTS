import rospy
# An error can be apear
try: from .logger import Logger
except ImportError: from logger import Logger


def redirect_rospy_logger(logger_topic: str="RosPy"):
  logger = Logger(logger_topic)

  def logger_redirector(msg, args, kwargs, throttle=None, throttle_identical=False, level='info', once=False):
    func = getattr(logger, level, None)
    if func is None: func = logger.err if level == 'critical' else logger.info
    if len(args):
      for arg in args: msg = msg.replace("%s", str(arg), 1)
    func(msg, args)

  rospy.core._base_logger = logger_redirector
