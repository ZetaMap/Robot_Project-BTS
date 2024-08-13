from threading import Lock, Event
import rospy

from niryo_robot_python_ros_wrapper.ros_wrapper_enums import ButtonAction

from end_effector_interface.msg import EEButtonStatus

from niryo_robot_msgs.msg import CommandStatus

__all__ = [
    "FreeMotionButtonRosWrapper", 
    "FreeMotionButtonRosWrapperException"
]


class FreeMotionButtonRosWrapperException(Exception):
    pass


class FreeMotionButtonRosWrapper:
    def __init__(self, hardware_version='ned2'):
        self.__hardware_version = hardware_version

        self.__action_lock = Lock()
        self.__action_events = {
            ButtonAction.HANDLE_HELD_ACTION: Event(),
            ButtonAction.LONG_PUSH_ACTION: Event(),
            ButtonAction.SINGLE_PUSH_ACTION: Event(),
            ButtonAction.DOUBLE_PUSH_ACTION: Event(),
            ButtonAction.NO_ACTION: Event(),
        }

        self.__free_motion_button_state = EEButtonStatus.NO_ACTION

        self.__free_motion_button_topic = rospy.Subscriber(
            '/niryo_robot_hardware_interface/end_effector_interface/free_drive_button_status',
            EEButtonStatus, self.__callback_save_pos_button_status)
        
        self.callback = lambda button_status: None

    def __check_ned_2_version(self):
        if self.__hardware_version != 'ned2':
            raise FreeMotionButtonRosWrapperException(
                "Error Code : {}\nMessage : Wrong robot hardware version, feature only available on Ned2".format(
                    CommandStatus.BAD_HARDWARE_VERSION))

    @property
    def hardware_version(self):
        return self.__hardware_version

    @property
    def state(self):
        """
        Get the button state from the ButtonAction class

        :return: int value from the ButtonAction class
        :rtype: int
        """
        self.__check_ned_2_version()
        return self.__free_motion_button_state

    def is_pressed(self):
        """
        Button press state

        :rtype: bool
        """
        self.__check_ned_2_version()
        return self.__free_motion_button_state != EEButtonStatus.NO_ACTION

    def wait_for_action(self, action, timeout=0):
        """
        Waits until a specific action occurs and returns true. Returns false if the timeout is reached.

        :param action: int value from the ButtonAction class
        :type action: int self.__save_button_topic
        :type timeout: float ref_count
        :return: Returns the detected action, or ButtonAction.NO_ACTION if the timeout is reached  without any action.
        :rtype: int
        """
        self.__check_ned_2_version()
        return self.__wait_any(timeout)
    
    def wait_for_any_action(self, timeout=0):
        """
        Returns the detected action. Returns ButtonAction.NO_ACTION if the timeout is reached  without action.

        :type timeout: float
        :return: Returns the detected action, or ButtonAction.NO_ACTION if the timeout is reached  without any action.
        :rtype: int
        """
        self.__check_ned_2_version()
        return self.__wait_any(timeout)

    def get_and_wait_press_duration(self, timeout=0):
        """
        Waits for the button to be pressed and returns the press time.
        Returns 0 if no press is detected after the timeout duration.

        :type timeout: foat
        :rtype: float
        """
        self.__check_ned_2_version()
        return self.__get_press_time(timeout)

    def __clear(self):
        with self.__action_lock:
            for a_event in self.__action_events.values():
                a_event.clear()

    def __set(self, action):
        self.__free_motion_button_state = action
        if action in self.__action_events:
            with self.__action_lock:
                self.__action_events[action].set()

    def __wait(self, action, timeout=0.0):
        if action not in self.__action_events:
            return False

        self.__action_events[action].clear()

        start_time = rospy.Time.now()
        while not self.__action_events[action].is_set() and not rospy.is_shutdown():
            self.__action_events[action].wait(0.1)

            if self.__action_events[action].is_set():
                return True
            elif 0 < timeout < (rospy.Time.now() - start_time).to_sec():
                return False

        if self.__action_events[action].is_set():
            return True

        return False

    def __wait_any(self, timeout=0.0):
        start_time = rospy.Time.now()
        self.__clear()
        if not self.__wait(ButtonAction.HANDLE_HELD_ACTION, timeout=timeout):
            return ButtonAction.NO_ACTION

        while not rospy.is_shutdown():
            if 0 < timeout < (rospy.Time.now() - start_time).to_sec():
                break

            for action_name in self.__action_events:
                if action_name not in [ButtonAction.NO_ACTION, ButtonAction.HANDLE_HELD_ACTION] \
                        and self.__action_events[action_name].is_set():
                    return action_name

            rospy.sleep(0.1)

        return ButtonAction.HANDLE_HELD_ACTION

    def __get_press_time(self, timeout=0.0):
        if not self.__wait(ButtonAction.HANDLE_HELD_ACTION, timeout=timeout):
            return 0

        pressed_time = rospy.Time.now()

        if not self.__wait(ButtonAction.NO_ACTION):
            return 0

        return (rospy.Time.now() - pressed_time).to_sec()

    def __callback_save_pos_button_status(self, free_motion_button_status):
        self.__set(free_motion_button_status.action)
        self.callback(free_motion_button_status)
