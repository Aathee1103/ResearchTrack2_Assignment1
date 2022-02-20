# First Assignment of the Research Track 2 course (Robotics Engineering_5051520, Unige)
## Action Package:
This package helps to control the robot in the gazebo environment using 'got_to_point' behaviour.And a random goal poses is generated and robot aligns itself towards that point.it sets the linear velocity to drive to the goal position,and one the goal position is reached then it adjusts to attain the required angular position.if the robot is not stopped the process will be operated in a loop by generating new target destination and pose.the robot's 'go_to_point' is implemented as a action server so it can be preempted,and the robot can be stopped at any time and the robot will be restarted when the new goal is arrived. 

Two nodes are implemented as python scripts:
- go_to_point: the node GoToPoint, which implements a service to drive a robot toward a point in the gazebo environment.This node publishes on the topics /cmd_vel the velocity of the robot and read its position by subscribing the topic '/odom'.
- user_interface: the UserInterface, which asks the user to start/stop the robot, and calls the service implemented in the Finite State Machine node.

Other two nodes are implemented in C++:
- position_server: the node PositionServer, which implements a random position service.The service implemented in the Position Server node replies with random values for x, y, and theta, where x and y should be limited between some minimum and maximum values.
- state_machine: The service implemented in the Robot FSM node gives the possibility to start or stop the robot behaviour.it monitors the request of a new goal pose when needed, sending it as a goal to 'go_to_point' action server.

## Command for Running the package:
A launch file has been provided to generate the Gazebo simulation and run all the nodes required for the control of the non-holonomic robot:

- sim.launch: this launch file is used to launch all the nodes and to start the gazebo simulation.

```
roslaunch rt2_assignment1 sim.launch
```


