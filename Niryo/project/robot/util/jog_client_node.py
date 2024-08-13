"""
Idependent rospy node, to control the gamepad

Note: Node joy_node must be started before (rosrun joy joy_node &)
"""

# Libs
import rospy
import numpy as np
import threading, os

try:
    from rospy_logger import redirect_rospy_logger
    redirect_rospy_logger("JogClient")
except ImportError as e: pass

from niryo_robot_python_ros_wrapper.ros_wrapper import NiryoRosWrapper
from std_msgs.msg import Bool
from sensor_msgs.msg import Joy


class JogClient:
    def __init__(self):
        rospy.init_node('jog_client_node')

        self.__jog_enabled = False
        self.robot = NiryoRosWrapper()
        self.robot.update_tool()
        self.tool_state = False

        # Subscribers
        rospy.Subscriber('/niryo_robot/jog_interface/is_enabled', Bool, self.__callback_subscriber_jog_enabled, queue_size=1)
        rospy.Subscriber('/joy', Joy, self.joy_callback)

        self.buttonA = self.buttonB = self.buttonX = self.buttonY = self.buttonBack = self.buttonStart = self.buttonLB = self.buttonRB = 0
        self.zAxis = self.yAxis = self.xAxis = 0

        self.joint4 = self.joint5 = self.joint6 = 0

        self.mode = False
        self.current_mode = "Pose"  # either "Pose" or "Joint" according to how you want to control Ned

        self.shift_values = [0.0] * 6
        self.speed = 1.0

        self.robot.calibrate_auto()
        self.robot.set_learning_mode(False)
        self.robot.set_jog_use_state(True)
        self.robot.led_ring.rainbow_cycle()

        self.thread_move = threading.Thread(target=self.move_arm)
        self.thread_move.daemon = True
        self.thread_move.start()
        
        self.rainbow_timer = None

    # - CALLBACKS
    def __callback_subscriber_jog_enabled(self, ros_data):
        self.__jog_enabled = ros_data.data

    def __rainbow_timer(self):
        if self.rainbow_timer is not None: self.rainbow_timer.shutdown()
        self.rainbow_timer = rospy.Timer(rospy.Duration(1), lambda *_: self.robot.led_ring.rainbow_cycle(), True)

    # - JOG SHIFT METHODS
    def ask_for_jog_shift(self, shift_values):
        init_time = rospy.get_time()
        if not self.__jog_enabled:
            try: self.robot.set_jog_use_state(True)
            except Exception as e:
                if "wait for the end of command" in str(e).lower():
                    return
                raise

        try:
            if self.current_mode == "Pose":
                self.robot.jog_pose_shift(shift_values)
            elif self.current_mode == "Joint":
                self.robot.jog_joints_shift(shift_values)
        except Exception as e:
            rospy.logdebug(str(e))
        rospy.sleep(0.15 - (rospy.get_time() - init_time))

    # - JOYSTICK METHODS
    def joy_callback(self, data):
        """
        update self.shift_values according to the current joystick state
        """
        listbutton = data.buttons
        listaxes = data.axes
#        print(data)

        self.buttonA = listbutton[0]  # set learning mode
        self.buttonB = listbutton[1]
        self.buttonX = listbutton[2]
        self.buttonY = listbutton[3]
        self.buttonLB = listbutton[4]
        self.buttonRB = listbutton[5]
        self.buttonBack = listbutton[6]
        self.buttonStart = listbutton[7]

        # left joystick
        self.zAxis = listaxes[7]
        self.yAxis = listaxes[0]
        self.xAxis = listaxes[1]

        # right joystick
        self.joint4 = listaxes[6]
        self.joint5 = listaxes[4]
        self.joint6 = listaxes[3]

        if self.buttonA:
            self.robot.set_learning_mode(not self.robot.get_learning_mode())


        # Here, the number of axis are : z:2, y:1, x:0, joint5:3, joint6 : 5 Here, we update the self.shift_values list used by the move thread
        if self.zAxis != 0:
            self.current_mode = "Joint" if self.mode else "Pose"
            self.shift_values = self.create_shift_values(np.sign(self.zAxis), 2)

        if self.yAxis != 0:
            self.current_mode = "Joint" if self.mode else "Pose"
            self.shift_values = self.create_shift_values(np.sign(self.yAxis), not self.mode)

        if abs(self.xAxis) == 1.0:
            self.current_mode = "Joint" if self.mode else "Pose"
            self.shift_values = self.create_shift_values(np.sign(self.xAxis), self.mode)

        if self.joint4 != 0:
            self.current_mode = "Joint"
            self.shift_values = self.create_shift_values(np.sign(self.joint4), 3)

        if abs(self.joint5) == 1.0:
            self.current_mode = "Joint"  # Meaning we will send a SHIFT_JOINT command
            self.shift_values = self.create_shift_values(np.sign(self.joint5), 4)

        if abs(self.joint6) == 1.0:
            self.current_mode = "Joint"
            self.shift_values = self.create_shift_values(np.sign(self.joint6), 5)

    def create_shift_values(self, sign, axis):
        """
        return list of shift values according to the sign, current shifting mode (self.current_mode) and axis chosen
        """
        offset = 0.03 if self.current_mode == "Pose" else 0.07
        return [sign * offset * self.speed if i == axis else 0.0 for i in range(6)]

    # - THREADED METHOD
    def move_arm(self):
        """
        Move arm accordingly to the current joystick state
        """
        while not rospy.is_shutdown():
            try:
                if (self.zAxis != .0 or self.yAxis != .0 or self.xAxis != .0 or 
                    self.joint4 != 0 or abs(self.joint5) == 1.0 or abs(self.joint6) == 1.0):
                        self.ask_for_jog_shift(self.shift_values) 
                
                if self.buttonB != 0:
                    self.tool_state = not self.tool_state
                    (self.robot.grasp_with_tool if self.tool_state else self.robot.release_with_tool)()
                
                if self.buttonLB:
                    self.speed -= 0.1
                    if self.speed <= 0: self.speed = 0.1
                    leds = int(self.speed*20+1)
                    self.robot.led_ring.custom([[0, 0, 0]]*5+[[15, 50, 255]]*leds+[[0, 0, 0]]*(30-leds))
                    self.__rainbow_timer()
                    rospy.sleep(0.1)
                    
                elif self.buttonRB:
                    self.speed += 0.1
                    if self.speed > 1: self.speed = 1
                    leds = int(self.speed*20+1)
                    self.robot.led_ring.custom([[0, 0, 0]]*5+[[15, 50, 255]]*leds+[[0, 0, 0]]*(30-leds))
                    self.__rainbow_timer()
                    rospy.sleep(0.1)
                
                if self.buttonBack:
                    self.robot.move_to_sleep_pose()
                     
                elif self.buttonStart:
                    self.mode = not self.mode
                    self.robot.led_ring.flashing([255, 127, 0], iterations=2, wait=True)
                    self.robot.led_ring.rainbow_cycle()
                    rospy.sleep(0.2)


            except KeyboardInterrupt:
                rospy.loginfo("quit")
                rospy.signal_shutdown("quit")
                break


if __name__ == "__main__":
    rospy.loginfo("Starting joy_node")
    os.system("rosrun joy joy_node &")
    
    # Command to run: rosrun joy joy_node &
    # Creating Client Object
    jc = JogClient()
    current_key = ''
    rospy.spin()
