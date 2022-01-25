/***********************************************************************************
 *  @file       scicobot_ros_encoder.h
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
#ifndef SCICOBOT_ROS_ENCODER_H
#define SCICOBOT_ROS_ENCODER_H

#include <ros_init/scicobot_ros_init.h>
#include <rclc/executor.h>
#include <std_msgs/msg/u_int8.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>

#define SCICOBOT_ROS_ENCODER_DEBUG 0 // Debug mode
#if SCICOBOT_ROS_ENCODER_DEBUG == 1
	#include <serial_debug.h>
#endif

class ScicobotRosEncoder
{
	public:
	
	void initRosEncoderPublisher(ScicobotRos* scicobotRos, void (*timerCallbackUltrasonicRight)(rcl_timer_t*, int64_t), void (*timerCallbackUltrasonicLeft)(rcl_timer_t*, int64_t));
	
	rclc_executor_t* get_rclc_executor();
	
	rcl_publisher_t* get_rclc_publisher_ritght();
	std_msgs__msg__UInt8* get_rclc_msg_ritght();
	
	rcl_publisher_t* get_rclc_publisher_left();
	std_msgs__msg__UInt8* get_rclc_msg_left();	
	
	void setScicobotRos(ScicobotRos* scicobotRos);
	
	private:
	
	void initPublisherAndTimerEncoderRight(void (*timerCallbackEncoderRight)(rcl_timer_t*, int64_t), char* topicName, int16_t timerPeriod);
	void addExecutorsEncoderRight();
	
	void initPublisherAndTimerEncoderLeft(void (*timerCallbackEncoderLeft)(rcl_timer_t*, int64_t), char* topicName, int16_t timerPeriod);
	void addExecutorsEncoderLeft();
	
	void initExecutorEncoder(int numberHandles);
	
	rcl_publisher_t publisherEncoderRight;
	rcl_timer_t timerEncoderRight;
	std_msgs__msg__UInt8 msgEncoderRight;
	
	rcl_publisher_t publisherEncoderLeft;
	rcl_timer_t timerEncoderLeft;
	std_msgs__msg__UInt8 msgEncoderLeft;
	
	rclc_executor_t executorEncoder;
	
	ScicobotRos* _scicobotRos;


};
#endif //SCICOBOT_ROS_ENCODER_H
