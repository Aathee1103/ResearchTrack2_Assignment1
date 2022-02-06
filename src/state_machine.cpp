#include "ros/ros.h"
#include "rt2_assignment1/Command.h"
#include "rt2_assignment1/RandomPosition.h"
#include "rt2_assignment1/PlanningAction.h"
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"

bool start = false;


bool user_interface(rt2_assignment1::Command::Request &req, rt2_assignment1::Command::Response &res){
    if (req.command == "start"){
    	start = true;
    }
    else {
    	start = false;
    }
    return true;
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "state_machine");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/user_interface", user_interface);
   ros::ServiceClient client_rp = n.serviceClient<rt2_assignment1::RandomPosition>("/position_server");
   actionlib::SimpleActionClient <rt2_assignment1::PlanningAction> ac("/go_to_point", true);
   
   rt2_assignment1::PlanningGoal goal;
   rt2_assignment1::RandomPosition rp;
   rp.request.x_max = 5.0;
   rp.request.x_min = -5.0;
   rp.request.y_max = 5.0;
   rp.request.y_min = -5.0;

   while(ros::ok()){
   	ros::spinOnce();
   	if (start){
   		client_rp.call(rp);
        
        goal.x=rp.response.x; 
        goal.y=rp.response.y;  
        goal.theta=rp.response.theta;

        std::cout << "\nGoal: x-coordinate= " << goal.x << "\nGoal: y-coordinate= " <<goal.y << " \nGoal: theta= " <<goal.theta << std::endl;
        ac.sendGoal(goal);
        
        while (true)
        {
           ros::spinOnce();
           if(start==false)
           {
                ac.cancelGoal();
                    std::cout << "\n goal is interrupted and cancelled" << std::endl;
                    break;
                }
                else
                {
                    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                    {
                        std::cout << "\nGoal Reached!" << std::endl;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
