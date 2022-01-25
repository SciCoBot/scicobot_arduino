#include <micro_ros_arduino.h>
#include <simple_motor_dc.h>
#include <serial_debug.h>
#include <led_debug.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>

#define DEBUG_ENABLE 1


unsigned long timeNow;
unsigned long timeBefor;

//Pins Motor A
#define IN1_A 7
#define IN2_A 6

//Pins Motor B
#define IN1_B 5
#define IN2_B 4

SimpleMotor motorRight;
SimpleMotor motorLeft;

#if DEBUG_ENABLE ==1 
  Debug debugObj(Serial1);
#endif

rcl_subscription_t subscriberMotorControl;
geometry_msgs__msg__Twist msgSubscriberTwist;
rcl_node_t scicobot_arduino;
rclc_executor_t executor;
rcl_allocator_t allocator;
rclc_support_t support;

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
  

  DEBUG_ERROR_MICR0_ROS(rclc_executor_init(&executor, &support.context, 1, &allocator));
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_subscription(&executor, &subscriberMotorControl, &msgSubscriberTwist, 
                                                       &subscriber_MotorControl_callback, ON_NEW_DATA));
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("InitMotorControl() sucess...");  
  #endif 
}


void setup() 
{
  Serial1.begin(115200);
  debugObj.DEBUGLN("Serial debug, in setup..."); 
  
  motorRight.init(IN1_A, IN2_A);
  motorLeft.init(IN1_B, IN2_B) ;
  
  pinMode(LED_DEBUG_PIN, OUTPUT);
  
  initMicroRos();

  DEBUG_ERROR_MICR0_ROS(rclc_node_init_default(&scicobot_arduino, "scicobot_arduino", "", &support));

  InitMotorControl();
    
}

void loop() 
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
  timeNow = micros();
  
  if(((timeNow - timeBefor) > 1000000) && (motorRight.getPwm() !=0) && (motorLeft.getPwm() !=0))
  {
    motorRight.stop();
    motorLeft.stop();
  }

}
