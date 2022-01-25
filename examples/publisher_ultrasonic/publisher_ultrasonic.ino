#include <micro_ros_arduino.h>
#include <ultrasonic.h>
#include <serial_debug.h>
#include <led_debug.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/int16.h>

#define DEBUG_ENABLE 1


//unsigned long timeNow;
//unsigned long timeBefor;

//pins ultrasonic
#define PIN_TRIGGER  53
#define PIN_ECHO  50

#if DEBUG_ENABLE ==1 
  Debug debugObj(Serial1);
#endif

Ultrasonic ultrasonic;

rcl_publisher_t publisherUltrasonic;
rcl_timer_t timer;
std_msgs__msg__Int16 msg;
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

void timerCallbackUltrasonic(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
   msg.data = ultrasonic.measureDistanceCm(20);
   DEBUG_WARNING_MICR0_ROS(rcl_publish(&publisherUltrasonic, &msg, NULL));
   //msg.data++;
   #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("timerCallbackUltrasonic()");  
  #endif
  }
}

void InitUltrasonicPublisher()
{   
  
  DEBUG_ERROR_MICR0_ROS(rclc_publisher_init_default(
    &publisherUltrasonic,
    &scicobot_arduino,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int16),
    "publisher_ultrasonic"));
  
//  /RCL_MS_TO_NS(500) significa que irá executar timerCallbackUltrasonic a cada 500ms
  DEBUG_ERROR_MICR0_ROS(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(500),
    timerCallbackUltrasonic));
    
  #if DEBUG_ENABLE ==1 
  debugObj.DEBUGLN("InitMotorControl() sucess...");  
  #endif
}
void createExecutorUltrasonic(){
  
  DEBUG_ERROR_MICR0_ROS(rclc_executor_init(&executor, &support.context, 1, &allocator));
  DEBUG_ERROR_MICR0_ROS(rclc_executor_add_timer(&executor, &timer));
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("createExecutorUltrasonic() sucess...");  
  #endif
}

void setup() 
{
  Serial1.begin(115200);
  
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("Serial debug, in setup..."); 
  #endif

  ultrasonic.init(PIN_TRIGGER, PIN_ECHO);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);
  
  initMicroRos();

  DEBUG_ERROR_MICR0_ROS(rclc_node_init_default(&scicobot_arduino, "scicobot_arduino", "", &support));

  InitUltrasonicPublisher();
  
  createExecutorUltrasonic();
    
}

void loop() 
{
  //100 é o timeOut
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));

}
