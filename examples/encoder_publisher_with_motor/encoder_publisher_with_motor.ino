#include <micro_ros_arduino.h>
#include <simple_motor_dc.h>
#include <serial_debug.h>
#include <led_debug.h>
#include <encoder.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/int16.h>

#define DEBUG_ENABLE 1

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

SimpleMotor motorRight;
SimpleMotor motorLeft;

Encoder encoderRight;
Encoder encoderLeft;

Debug debugObj(Serial1);

rcl_subscription_t subscriberMotorControl;
geometry_msgs__msg__Twist msgMotorControl;
rcl_node_t scicobot_arduino;
rclc_executor_t executorMotorControl;
rcl_allocator_t allocator;
rclc_support_t support;

rcl_publisher_t publisherEncoderRight;
std_msgs__msg__Int16 msgEncoderRight;
rcl_timer_t timerEncoderRight;

rcl_publisher_t publisherEncoderLeft;
std_msgs__msg__Int16 msgEncoderLeft;
rcl_timer_t timerEncoderLeft;

rclc_executor_t executorEncoder;


void count_encoder_left()
{
  encoderLeft.incrementPulses();
}

void count_encoder_right()
{
  encoderRight.incrementPulses();
}

void initMicroRos()
{  
  set_microros_transports();

  delay(2000);
  
  allocator = rcl_get_default_allocator();

  DEBUG_ERROR_MICR0_ROS(rclc_support_init(&support, 0, NULL, &allocator));

  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("initMicroRos() sucess...");  
  #endif
}

void callback_encoder_right(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    msgEncoderRight.data = encoderRight.readAndReset();
    DEBUG_WARNING_MICR0_ROS(rcl_publish(&publisherEncoderRight, &msgEncoderRight, NULL));
    
  }
}

void callback_encoder_left(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    msgEncoderLeft.data = encoderLeft.readAndReset();
    DEBUG_WARNING_MICR0_ROS(rcl_publish(&publisherEncoderLeft, &msgEncoderLeft, NULL));
    
  }
}

void subscriber_MotorControl_callback(const void * msgin)
{
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
   
  digitalWrite(LED_DEBUG_PIN, !digitalRead(LED_DEBUG_PIN));  
  
  moveMotor(msg->linear.x, msg->angular.z);
}

void moveMotor(float linear, float angular){
  
  if((angular==0) && (linear<0))
  {
    //backward
    motorLeft.backward(255);
    motorRight.backward(255); 
    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("backward");
    #endif
  }
  else if((angular==0) && (linear>0))
  {
    //forward
    motorLeft.forward(255);
    motorRight.forward(255);
    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("forward");
    #endif
  }
  else if((angular==-1) && (linear==0))
  {
    //turn left
    motorLeft.forward(255);
    motorRight.backward(255);
    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("turn left");
    #endif
  }
  else if((angular==1) && (linear==0))
  {
    //turn right
    motorRight.forward(255);
    motorLeft.backward(255);

    #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("turn right");
    #endif
  }
  else if((angular==-1) && (linear>0))
  {
    //forward left
    motorRight.forward(255);
    motorLeft.forward(180);   
    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("forward left");
    #endif
  }
  else if((angular==1) && (linear>0))
  {
    //forward right
    motorLeft.forward(255);
    motorRight.forward(180); 

    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("forward right");
    #endif
  }
  else if((angular==-1) && (linear<0))
  {
    //backward left
    motorRight.backward(255);
    motorLeft.backward(180);  
    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("backward left"); 
    #endif  
  }
  else if((angular==1) && (linear<0))
  {
    //backward right    
    motorLeft.backward(255);
    motorRight.backward(180); 

    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("backward right ");       
    #endif 
  }
  else
  {
    motorRight.stop();
    motorLeft.stop();

    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("stop");
    #endif 
  }
  timeBefor = micros();
}

void InitMotorControl()
{   
  DEBUG_ERROR_MICR0_ROS(rclc_subscription_init_default(
    &subscriberMotorControl,
    &scicobot_arduino,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "/cmd_vel"));
  
  debugObj.DEBUGLN("Befor rclc_executor_init()"); 
  

  DEBUG_ERROR_MICR0_ROS(rclc_executor_init(&executorMotorControl, &support.context, 1, &allocator));
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_subscription(&executorMotorControl, &subscriberMotorControl, &msgMotorControl, 
                                                       &subscriber_MotorControl_callback, ON_NEW_DATA));

  debugObj.DEBUGLN("InitMotorControl() sucess...");  
}

void InitPublisherEncoderRight()
{   
  
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_default(
    &publisherEncoderRight,
    &scicobot_arduino,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16),
    "encoder_right"));
  
  DEBUG_ERROR_MICR0_ROS(rclc_timer_init_default(
    &timerEncoderRight,
    &support,
    RCL_MS_TO_NS(1000),
    callback_encoder_right));

  // create executor
  DEBUG_ERROR_MICR0_ROS(rclc_executor_init(&executorEncoder, &support.context, 2, &allocator));
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_timer(&executorEncoder, &timerEncoderRight));
  
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("InitPublisherEncoderRight() sucess...");  
  #endif
  
}

void InitPublisherEncoderLeft()
{   
  
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_default(
    &publisherEncoderLeft,
    &scicobot_arduino,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16),
    "encoder_left"));
  
  DEBUG_ERROR_MICR0_ROS(rclc_timer_init_default(
    &timerEncoderLeft,
    &support,
    RCL_MS_TO_NS(1000),
    callback_encoder_left));

  // create executor
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_timer(&executorEncoder, &timerEncoderLeft));
  
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("InitPublisherEncoderLeft() sucess...");  
  #endif
  
}

void setup() 
{
  Serial1.begin(115200);
  debugObj.DEBUGLN("Serial debug, in setup..."); 
  
  motorRight.init(IN1_A, IN2_A);
  motorLeft.init(IN1_B, IN2_B) ;

  encoderRight.init(OUT_ENCODER_RIGHT, &count_encoder_right);
  encoderLeft.init(OUT_ENCODER_LEFT, &count_encoder_left);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);
  
  initMicroRos();

  DEBUG_ERROR_MICR0_ROS(rclc_node_init_default(&scicobot_arduino, "scicobot_arduino", "", &support));

  InitMotorControl();
  
  InitPublisherEncoderRight();

  InitPublisherEncoderLeft();
  
  debugObj.DEBUGLN("setup() finisher...");
  
}

void loop() 
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(&executorMotorControl, RCL_MS_TO_NS(100)));
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(&executorEncoder, RCL_MS_TO_NS(100)));
  
  timeNow = micros();
  
  if(((timeNow - timeBefor) > 1000000) && (motorRight.getPwm() !=0) && (motorLeft.getPwm() !=0))
  {
    motorRight.stop();
    motorLeft.stop();
  }
}
