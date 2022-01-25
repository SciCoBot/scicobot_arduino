#include <scicobot_arduino.h>
#include <led_debug.h>
#include <serial_debug.h>
#include <encoder.h>
#include <differential_drive.h>

#define DEBUG_ENABLE 0

unsigned long timeNow;
unsigned long timeBefor;

//Pins Motor
#define IN1_A 7
#define IN2_A 6

//Pins Motor
#define IN2_B 5
#define IN1_B 4

//Pins Encoder
#define OUT_ENCODER_RIGHT 51
#define OUT_ENCODER_LEFT 52

Encoder encoderRight;
Encoder encoderLeft;

DifferentialDrive differentialDrive;

ScicobotRosMotor scicobotRosMotor;

ScicobotRos scicobotRos;

ScicobotRosEncoder scicobotRosEncoder;

void count_encoder_left()
{
  encoderLeft.incrementPulses();
}

void count_encoder_right()
{
  encoderRight.incrementPulses();
}

void subscriber_MotorControl_callback(const void * msgin)
{
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
     
  differentialDrive.differentialForPWM(msg->linear.x, msg->angular.z);
  
  timeBefor = micros();
}

void callback_encoder_right(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    (*scicobotRosEncoder.get_rclc_msg_ritght()).data = encoderRight.readAndReset();
    DEBUG_WARNING_MICR0_ROS(rcl_publish(scicobotRosEncoder.get_rclc_publisher_ritght(), scicobotRosEncoder.get_rclc_msg_ritght(), NULL));
    
  }
}

void callback_encoder_left(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    (*scicobotRosEncoder.get_rclc_msg_left()).data = encoderLeft.readAndReset();
    DEBUG_WARNING_MICR0_ROS(rcl_publish(scicobotRosEncoder.get_rclc_publisher_left(), scicobotRosEncoder.get_rclc_msg_left(), NULL));
    
  }
}

void setup() 
{
  Serial1.begin(115200);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);
  
  differentialDrive.init();

  encoderRight.init(OUT_ENCODER_RIGHT, &count_encoder_right);
  encoderLeft.init(OUT_ENCODER_LEFT, &count_encoder_left);
  
  scicobotRos.init();
  
  scicobotRosMotor.initRosMotorSubscriber(&scicobotRos, subscriber_MotorControl_callback);

  scicobotRosEncoder.initRosEncoderPublisher(&scicobotRos, callback_encoder_right, callback_encoder_left);

}

void loop() 
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosEncoder.get_rclc_executor(), RCL_MS_TO_NS(100)));

  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosMotor.get_rclc_executor(), RCL_MS_TO_NS(100)));
  
  timeNow = micros();
  
  if(((timeNow - timeBefor) > 1000000))
  {
   differentialDrive.differentialForPWM(0, 0);
  }}
