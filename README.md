# ResearchTrack2_Assignment1
## Ros-Ros2 bridge package:
This is a package toshow how the ros package is package is controlled using ros1 simulation.this package is supposed to be integrated with a Ros1 environment which includes a Gazebo environment to control the non-holonomic robot and which has '/go_to_point' behaviour which is given in main branch.the connection between ros1 simulation and the ros2 package is done using ``` ros1_bridge ``` which is installed and compiled.After installation,``` ros1_bridge ``` package and then the ros2 packaged here will be running.using this user can control the robot in ros1 rom rs2 package.the two file ***state_machine.cpp*** and ***position_service.cpp*** is made as ros2 compenents to to control the ros1 enironment.

## Running the package:
1.In order to make this package communicate with the ROS1 by ROS2 three steps are required:
- Launch the simulation and the needed nodes from the ROS1 in a 1st terminal:
```source /root/my_ros/devel/setup.bash``` 
source the ros environment
```roslaunch rt2assignment1 ros_2.launch```
launch the robot in gazebo simulation.
2.Run the ros1_bridge package in a terminal:
- source the ROS1and ROS2 enironment ```source /root/my_ros/devel/setup.bash source /root/my_ros/devel/setup.bash```
-  run the command ```ros2 run ros1_bridge dynamic_bridge``` 
3.Launch the container with the components implemented in this package in a shell with ROS2 sourced:
- source ROS2 ```source /root/my_ros/devel/setup.bash```
- ```ros2 launch rt2_assignment1 bridge.py``` after this given command the bridge will be working.

For simplicity there is a bash script file named as ***bridge_ros2.sh*** whch contains all the things done above in a single command and a gnome shell will be opened and bridge can be operated there.

