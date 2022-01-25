#include <differential_drive.h>
#include <scicobot_arduino.h>
#include <led_debug.h>
#include <serial_debug.h>

#define DEBUG_ENABLE 0

ScicobotRos scicobotRos;

ScicobotRosMotor scicobotRosMotor;

DifferentialDrive differentialDrive;

unsigned long timeNow;
unsigned long timeBefor;

void subscriber_MotorControl_callback(const void * msgin)
{
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
     
  differentialDrive.differentialForPWM(msg->linear.x, msg->angular.z);
  
  timeBefor = micros();
}

void setup() 
{
  Serial1.begin(115200);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);
  
  scicobotRos.init();

  scicobotRosMotor.initRosMotorSubscriber(&scicobotRos, subscriber_MotorControl_callback);

  differentialDrive.init();
}

void loop() 
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosMotor.get_rclc_executor(), RCL_MS_TO_NS(100)));
    
  timeNow = micros();
  
  if(((timeNow - timeBefor) > 1000000))
  {
   differentialDrive.differentialForPWM(0, 0);
  }

}
