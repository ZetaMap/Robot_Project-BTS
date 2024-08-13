# !/bin/bash

# Default ros node name of project                Or a custom node name
[ "$1" == "" ] && ROS_NODE="niryo_robot_project" || ROS_NODE="$1"
# Trigger for new (also fake) handler
python3 -c "import rospy;rospy.init_node('$ROS_NODE')"
