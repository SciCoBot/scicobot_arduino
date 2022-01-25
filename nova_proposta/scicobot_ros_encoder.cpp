/***********************************************************************************
 *  @file       scicobot_ros_encoder.cpp
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
#include "scicobot_ros_encoder.h"
#include <led_debug.h>
#include <Arduino.h>

void ScicobotRosEncoder::setScicobotRos(ScicobotRos* scicobotRos)
{
	_scicobotRos = scicobotRos;
}

void ScicobotRosEncoder::initPublisherAndTimerEncoderRight(void (*timerCallbackEncoderRight)(rcl_timer_t*, int64_t), char* topicName, int16_t timerPeriod)
{    
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_default(
    &publisherEncoderRight,
    _scicobotRos->get_rcl_node(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
    topicName));
  
  DEBUG_ERROR_MICR0_ROS(rclc_timer_init_default(
    &timerEncoderRight,
    _scicobotRos->get_rclc_support(),
    RCL_MS_TO_NS(timerPeriod),
    timerCallbackEncoderRight));
    
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
  	debugObj.DEBUGLN("initPublisherAndTimerEncoderRight() sucess...");  
  #endif
}

void ScicobotRosEncoder::initPublisherAndTimerEncoderLeft(void (*timerCallbackEncoderLeft)(rcl_timer_t*, int64_t), char* topicName, int16_t timerPeriod)
{    
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_default(
    &publisherEncoderLeft,
    _scicobotRos->get_rcl_node(),
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
    topicName));
  
  DEBUG_ERROR_MICR0_ROS(rclc_timer_init_default(
    &timerEncoderLeft,
    _scicobotRos->get_rclc_support(),
    RCL_MS_TO_NS(timerPeriod),
    timerCallbackEncoderLeft));  

  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
  	debugObj.DEBUGLN("initPublisherAndTimerEncoderLeft() sucess...");  
  #endif
}
 
void ScicobotRosEncoder::initExecutorEncoder(int numberHandles)
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_init(&executorEncoder, 
  	 &(*_scicobotRos->get_rclc_support()).context,
  	 numberHandles, 
  	 _scicobotRos->get_rcl_allocator()));
    
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
  	debugObj.DEBUGLN("initExecutorEncoder() sucess...");  
  #endif
}
void ScicobotRosEncoder::addExecutorsEncoderRight()
{
 
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_timer(&executorEncoder, &timerEncoderRight));
  
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
    debugObj.DEBUGLN("addExecutorsEncoderRight() sucess...");  
  #endif
}

void ScicobotRosEncoder::addExecutorsEncoderLeft()
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_timer(&executorEncoder, &timerEncoderLeft));
  
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
    debugObj.DEBUGLN("addExecutorsEncoder() sucess...");  
  #endif
}

void ScicobotRosEncoder::initRosEncoderPublisher(ScicobotRos* scicobotRos, void (*timerCallbackUltrasonicRight)(rcl_timer_t*, int64_t), void (*timerCallbackUltrasonicLeft)(rcl_timer_t*, int64_t))
{
  this->setScicobotRos(scicobotRos);
  
  this->initPublisherAndTimerEncoderRight(timerCallbackUltrasonicRight, "encoder_right", 500);
  
  this->initPublisherAndTimerEncoderLeft(timerCallbackUltrasonicLeft, "encoder_left", 500);
  
  this->initExecutorEncoder(2);
  
  this->addExecutorsEncoderRight();
  
  this->addExecutorsEncoderLeft();
  
  #if SCICOBOT_ROS_ULTRASONIC_DEBUG ==1 
    debugObj.DEBUGLN("initRosEncoderPublisher() sucess...");  
  #endif
}
rclc_executor_t* ScicobotRosEncoder::get_rclc_executor()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of executorEncoder is: "); 
		debugObj.DEBUGLN(&executorEncoder); 
	#endif
	
	return &executorEncoder;
}

rcl_publisher_t* ScicobotRosEncoder::get_rclc_publisher_ritght()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of publisherEncoderRight is: "); 
		debugObj.DEBUGLN(&publisherEncoderRight); 
	#endif
	
	return &publisherEncoderRight;
}

std_msgs__msg__UInt8* ScicobotRosEncoder::get_rclc_msg_ritght()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of msgEncoderRight is: "); 
		debugObj.DEBUGLN(&msgEncoderRight); 
	#endif
	
	return &msgEncoderRight;
}

rcl_publisher_t* ScicobotRosEncoder::get_rclc_publisher_left()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of publisherEncoderLeft is: "); 
		debugObj.DEBUGLN(&publisherEncoderLeft); 
	#endif
	
	return &publisherEncoderLeft;
}

std_msgs__msg__UInt8* ScicobotRosEncoder::get_rclc_msg_left()
{
	#if SCICOBOT_ROS_ULTRASONIC_DEBUG == 1
		debugObj.DEBUG("Position of msgEncoderLeft is: "); 
		debugObj.DEBUGLN(&msgEncoderLeft); 
	#endif
	
	return &msgEncoderLeft;
}
