# ResearchTrack2_Assignment1
## Ros-Ros2 bridge package:
This is a package toshow how the ros package is package is controlled using ros1 simulation.this package is supposed to be integrated with a Ros1 environment which includes a Gazebo environment to control the non-holonomic robot and which has '/go_to_point' behaviour which is given in main branch.the connection between ros1 simulation and the ros2 package is done using ``` ros1_bridge ``` which is installed and compiled.After installation,``` ros1_bridge ``` package and then the ros2 packaged here will be running.using this user can control the robot in ros1 rom rs2 package.the two file ***state_machine.cpp*** and ***position_service.cpp*** is made as ros2 compenents to to control the ros1 enironment.

## Setting up the environment:
- 1.cd~/my_ros/catkin_make 

- 2.open a terminal and do the following steps:
```
source ros2 environment(source ros2.sh) in which ##foxy environment is sourced
cd~/my_ros2/src/git clone https://github.com/ros2/ros1_bridge.git
#clone the bridge repository
cd~/my_ros2/colcon build --symlink-install --packages-skip ros1_bridge
```
- 3.open another terminal
```
source ros12.sh,## in this both foxy and noetic environment is sourced
cd ~/colcon_ws
colcon build --packages-select ros1_bridge --cmake-force-configure
#this process will take some sometime and after bridge between ROS1 and ROS2 will be done.
```
### How to make the bridge work:
1.In order to make this package communication between ROS1 and ROS2 three steps are required:
- In the first terminal,source the ros environment(noetic environment)
```source /root/my_ros/devel/setup.bash``` 
- Launch the simulation and the needed nodes from the ROS1 in a 1st terminal:
```roslaunch rt2assignment1 ros_2.launch```
#launch the robot in gazebo simulation.

2.In the second terminal,Run the ros1_bridge package in a terminal:
- source the ROS1and ROS2 enironment ```source /root/my_ros/devel/setup.bash``` and  ```source /root/my_ros2/devel/setup.bash```
-  run the command ```ros2 run ros1_bridge dynamic_bridge``` 

3.In the third terminal,Launch the container with the components implemented in this package in a shell with ROS2 sourced:
- source ROS2 ```source /root/my_ros2/devel/setup.bash```
- ```ros2 launch rt2_assignment1 bridge.py``` which contains the launch file script,after this given command the bridge will be working.

For simplicity there is a bash script file named as ***bridge_ros2.sh*** whch contains all the things done above in a single command and a gnome shell will be opened and bridge can be operated there.

