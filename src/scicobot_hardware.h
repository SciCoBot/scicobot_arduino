/***********************************************************************************
 *  @file       scicobot_hardware.h
 *  Project     scicobot_hardware
 *  @brief      *****
 *
 *  @author     Otávio Augusto Rocha da Cruz
 *  @bug 		 No known bugs.
 *  License     MIT
 *
 *  @section License
 *
 * Copyright (c) 2021 SciCoBot
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**********************************************************************************/
#ifndef SCICOBOT_HARDWARE_H
#define SCICOBOT_HARDWARE_H

#include "scicobot_ros_init.h"
#include "scicobot_ros_motor.h"
#include "scicobot_ros_ultrasonic.h"
#include "scicobot_ros_encoder.h"

#endif //SCICOBOT_HARDWARE_H

//void destroyEntities()
//{

    //rcl_publisher_fini(&odom_publisher, &node);
    //rcl_subscription_fini(&twist_subscriber, &node);
    //rcl_node_fini(&node);
    //rcl_timer_fini(&control_timer);
    //rclc_executor_fini(&executor);
    //rclc_support_fini(&support);

    //micro_ros_init_successful = false;
//}


//void loop() 
//{
//  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosUltrasonic.get_rclc_executor(), RCL_MS_TO_NS(100)));
  // 10hz - 0.100
//  if(millis() - prev_connect_test_time >= 500)
//      {
//          prev_connect_test_time = millis();
//          // check if the agent is connected
//          //timeout_ms, attempts
//          if(RMW_RET_OK == rmw_uros_ping_agent(10, 2))
//          {
//              // reconnect if agent got disconnected or haven't at all
//              if (!micro_ros_init_successful) 
//              {
//                  createEntities();
//              } 
//          } 
//          else if(micro_ros_init_successful)
//          {
//              // stop the robot when the agent got disconnected
//              fullStop();
//              // clean up micro-ROS components
//              destroyEntities();
//          }
//      }
//      
//      if(micro_ros_init_successful)
//      {
//          rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
//      }
//}

//https://github.com/linorobot/linorobot2_hardware/blob/master/firmware/src/firmware.ino
//void fullStop()
//{
//    twist_msg.linear.x = 0.0;
//    twist_msg.linear.y = 0.0;
//    twist_msg.angular.z = 0.0;
//
//    motor1_controller.brake();
//    motor2_controller.brake();
//    motor3_controller.brake();
//    motor4_controller.brake();
//}

//void syncTime()
//{
//    // get the current time from the agent
//    unsigned long now = millis();
//    RCCHECK(rmw_uros_sync_session(10));
//    unsigned long long ros_time_ms = rmw_uros_epoch_millis(); 
//    // now we can find the difference between ROS time and uC time
//    time_offset = ros_time_ms - now;
//}

