# !/usr/bin/env python3

import rospy
from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper
from niryo_robot_status.msg import RobotStatus

def _send_fake_running_status():
  """
  Emulate a new status to get access of led ring.
  
  Because when the 'learning trajectory' mode is finished, the led ring controller is not released, even after calibration.
  """
  pub = rospy.Publisher('/niryo_robot_status/robot_status', RobotStatus, latch=True, queue_size=10)
  
  robot_status_msg = RobotStatus()
  robot_status_msg.robot_status = RobotStatus.RUNNING_DEBUG
  robot_status_msg.robot_status_str = 'Running autonomous'
  robot_status_msg.robot_message = ''
  robot_status_msg.logs_status = RobotStatus.NONE
  robot_status_msg.logs_status_str = 'None'
  robot_status_msg.logs_message = ''
  robot_status_msg.out_of_bounds = False
  robot_status_msg.rpi_overheating = False
  
  pub.publish(robot_status_msg)  
  robot_status_msg.robot_status = RobotStatus.RUNNING_AUTONOMOUS
  pub.publish(robot_status_msg)  

def new_calibration(robot: NiryoRosWrapper):
  robot.clear_collision_detected()
  robot.request_new_calibration()
  robot.calibrate_auto()
  rospy.sleep(0.1)
  robot.led_ring.alternate([[248, 252, 0], [0, 0, 248]], 0.5, 5)
  robot.update_tool()
  rospy.sleep(0.1)
  robot.grasp_with_tool()
  rospy.sleep(0.1)
  robot.release_with_tool()
  robot.led_ring.flashing([0, 0, 248], 0.5, 3)
  robot.sound.play("connected.wav")

if __name__ == '__main__':
  rospy.init_node('niryo_test_FQC_ros_wrapper')
  robot = NiryoRosWrapper()
  _send_fake_running_status()
  new_calibration(robot)
