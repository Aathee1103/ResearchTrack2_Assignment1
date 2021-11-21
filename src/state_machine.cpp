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

    class FSM : public rclcpp::Node
    {

        public: 
            FSM(const rclcpp::NodeOptions & options)
            : Node("state_machine", options)
            { 
            //initialize the publisher, the subscriber, client1, client2
            command_service=this->create_service<rt2_assignment1::srv::Command>("/user_interface", std::bind(&FSM::user_interface, this, _1, _2, _3));
           
            client_random= this->create_client<rt2_assignment1::srv::RandomPosition>("/position_server");

            while(!client_random->wait_for_service(std::chrono::seconds(1))){
					if(!rclcpp::ok()){
						RCLCPP_ERROR(this->get_logger(), "client interrupted while waiting for service to appear.");
						return ;
					}
					RCLCPP_INFO(this->get_logger(), "waiting service to appear...");
				}
            
            client_pos = this->create_client<rt2_assignment1::srv::Position>("/go_to_point");
		     while(!client_pos->wait_for_service(std::chrono::seconds(1))){
					if(!rclcpp::ok()){
						RCLCPP_ERROR(this->get_logger(), "client interrupted while waiting for service to appear.");
						return ;
					}
					RCLCPP_INFO(this->get_logger(), "waiting for pservice to appear...");
				}

            }
   private:    
        bool start=false;
        void fsm(){

            if(this->start)
            {
                auto req=std::make_shared<rt2_assignment1::srv::RandomPosition::Request>();
                req->x_max=5.0;
                req->x_min=-5.0;
                req->y_max=5.0;
                req->y_min=-5.0;
                using ServiceResponseFuture = rclcpp::Client<rt2_assignment1::srv::RandomPosition>::SharedFuture;
                auto received_callback=[this](ServiceResponseFuture future){

                auto req= std::make_shared<rt2_assignment1::srv::Position::Request>();
                req->x=future.get()->x;
                req->y=future.get()->y;
                req->theta=future.get()->theta;

                std::cout << "\nGoing to the position: x = " << req->x << " y = " << req->y << " theta = " << req->theta << std::endl;

                using ServiceResponseFuture = rclcpp::Client<rt2_assignment1::srv::Position>::SharedFuture;
                auto received_pos_callback= [this](ServiceResponseFuture position_future){
                   
                    if(position_future.get()->ok)
                    {
                        printf("\n Posioitn reached!");
                        this->fsm();
                    }
                };
                auto send_result= client_pos->async_send_request(req, received_pos_callback);
                };
                auto send_result= client_random->async_send_request(req, received_callback);
            }
    
        };


                bool user_interface(
                const std::shared_ptr<rmw_request_id_t> request_header,
                const std::shared_ptr<rt2_assignment1::srv::Command::Request> req,
                const std::shared_ptr<rt2_assignment1::srv::Command::Response> res)
                {
                    (void)request_header;
                    
                        if (req->command == "start"){
                            this->start = true;
                        }
                        else {
                            this->start = false;

                            return true;
                        }

                    }
                rclcpp::Client<rt2_assignment1::srv::Position>::SharedPtr client_pos;
                rclcpp::Client<rt2_assignment1::srv::RandomPosition>::SharedPtr client_random;
                rclcpp::Service<rt2_assignment1::srv::Command>::SharedPtr command_service;
                
            };
    
}

RCLCPP_COMPONENTS_REGISTER_NODE(rt2_assignment1::FSM)


