#include "ros/ros.h"
#include "rt2_assignment1/Command.h"
#include "rt2_assignment1/Position.h"
#include "rt2_assignment1/RandomPosition.h"
#include "rt2_assignment1/PlanningAction.h"
#include <actionlib/client/simple_action_client.h>
bool start=false;
bool goal_reached=false;
bool user_interface(rt2_assignment1::Command::Request &req, rt2_assignment1::Command::Response &res){
    if (req.command == "start"){
      start = true;
    }
    if (req.command == "stop"){
      start= false;
    }
    return true;
}


int main(int argc, char **argv)
{
   ros::init(argc, argv, "state_machine");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/user_interface", user_interface);
   ros::ServiceClient client_rp = n.serviceClient<rt2_assignment1::RandomPosition>("/position_server");
   actionlib::SimpleActionClient<rt2_assignment1::PlanningAction> ac("/go_to_point", true);
   
   rt2_assignment1::PlanningGoal goal;
   rt2_assignment1::RandomPosition rp;
   
   rp.request.x_max = 5.0;
   rp.request.x_min = -5.0;
   rp.request.y_max = 5.0;
   rp.request.y_min = -5.0;
   
   bool goal_reached=false;
   while(ros::ok())
   {
     ros::spinOnce();
    
 	if(start)
 	   {

      //a new random position will be generated
   		     client_rp.call(rp);

      //new position values will be saved and sent to the action
      		    goal.x= rp.response.x;
      		    goal.y = rp.response.y;
     	 	    goal.theta = rp.response.theta;
      		    std::cout << "\nGoing to the position: x= " << goal.x << " y= " <<goal.y << " theta = " <<goal.theta << std::endl;
      		    ac.sendGoal(goal);
      		    while(true)
                    {   
                      ros::spinOnce();
      	              if(start == false)
      	              {
      	   
      	                ac.cancelGoal();
      	                goal_reached=false;
      	                break;
      	              }
      	              else
      	              {
      	                 if(goal_reached == true && start == true)
      	                 {
                             ROS_INFO("Hooray, target reached!");
                             ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;
                             break;
                         }
     }               
    }
  }
  }    	
   return 0;
}


