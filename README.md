# First Assignment of the Research Track 2 course (Robotics Engineering, Unige)
## Action Package:
This package helps to control the robot in the gazebo environment using 'got_to_point' behaviour.And a random goal poses is generated and robot aligns itself towards that point.it sets the linear velocity to drive to the goal position,and one the goal position is reached then it adjusts to attain the required angular position.if the robot is not stopped the process will be operated in a loop by generating new target destination and pose.the robot's 'go_to_point' is implemented as a action server so it can be preempted,and the robot can be stopped at any time and the robot will be restarted when the new goal is arrived. 

Two nodes are implemented as python scripts:



