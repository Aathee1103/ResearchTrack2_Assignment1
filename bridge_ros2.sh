#!/bin/bash

gnome-terminal --tab --title="gazebo environment" -- bash -c "source ros.sh; roslaunch rt2_assignment1 ros_2.launch"
gnome-terminal --tab --title="ros-ros2" -- bash -c "sleep 2; source ros12.sh; ros2 run ros1_bridge dynamic_bridge"
gnome-terminal --tab --title="pythonn file" -- bash -c "sleep 5; source ros2.sh; ros2 launch rt2_assignment1 bridge.py"

