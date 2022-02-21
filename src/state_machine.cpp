#include <chrono>
#include <functional>
#include <memory>
#include <inttypes.h>
#include <string>
#include <cinttypes>
#include <cstdlib>

#include"rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "rt2_assignment1/srv/position.hpp"
#include "rt2_assignment1/srv/command.hpp"
#include "rt2_assignment1/srv/random_position.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

namespace rt2_assignment1
{

    class FiniteStateMachine : public rclcpp::Node
    {

        public: 
        
            FiniteStateMachine(const rclcpp::NodeOptions & options)
            : Node("state_machine", options)
            { 
            //initialize the publisher, the subscriber, client1, client2
            user_command=this->create_service<rt2_assignment1::srv::Command>("/user_interface", std::bind(&FiniteStateMachine::user_interface, this, _1, _2, _3));
           
            pos_random= this->create_client<rt2_assignment1::srv::RandomPosition>("/position_server");

            while(!pos_random->wait_for_service(std::chrono::seconds(3))){
					if(!rclcpp::ok()){
						RCLCPP_ERROR(this->get_logger(), "random position client is interrupted");
						return ;
					}
					RCLCPP_INFO(this->get_logger(), "waiting for random poistion service");
				}
            //go_to_point
            client_point = this->create_client<rt2_assignment1::srv::Position>("/go_to_point");
		     while(!client_point->wait_for_service(std::chrono::seconds(3))){
					if(!rclcpp::ok()){
						RCLCPP_ERROR(this->get_logger(), "position client interrupted");
						return ;
					}
					RCLCPP_INFO(this->get_logger(), "waiting for position service");
				}

            }
        void position_server_callback(){
            auto req=std::make_shared<rt2_assignment1::srv::RandomPosition::Request>();
            req->x_max=5.0;
            req->x_min=-5.0;
            req->y_max=5.0;
            req->y_min=-5.0;

            if(this->start)
            {
                using ServiceResponseFuture = rclcpp::Client<rt2_assignment1::srv::RandomPosition>::SharedFuture;
                auto received_callback=[this](ServiceResponseFuture future){

                auto req= std::make_shared<rt2_assignment1::srv::Position::Request>();
                req->x=future.get()->x;
                req->y=future.get()->y;
                req->theta=future.get()->theta;

                std::cout << "\nGoing to the position: x = " << req->x << " y = " << req->y << " theta = " << req->theta << std::endl;

                using ServiceResponseFuture = rclcpp::Client<rt2_assignment1::srv::Position>::SharedFuture;
                auto received_position_callback= [this](ServiceResponseFuture position_future){
                   
                    if(position_future.get()->ok)
                    {
                        printf("\n Position is reached!");
                        position_server_callback();
                    }
                };
                auto send_result= client_point->async_send_request(req, received_position_callback);
                };
                auto send_result= pos_random->async_send_request(req, received_callback);
            }
    
        }


        private:


                bool start=false;

                rclcpp::Client<rt2_assignment1::srv::Position>::SharedPtr client_point;
                rclcpp::Client<rt2_assignment1::srv::RandomPosition>::SharedPtr pos_random;
                rclcpp::Service<rt2_assignment1::srv::Command>::SharedPtr user_command;


                bool user_interface(
                const std::shared_ptr<rmw_request_id_t> request_header,
                const std::shared_ptr<rt2_assignment1::srv::Command::Request> req,
                const std::shared_ptr<rt2_assignment1::srv::Command::Response> res)
                {
                    (void)request_header;
                    
                        if (req->command == "start"){
                            this->start = true;
                            position_server_callback();
                        }
                        else {
                            this->start = false;

                            return true;
                        }

                    }
                
            };
    
}

RCLCPP_COMPONENTS_REGISTER_NODE(rt2_assignment1::FiniteStateMachine)

