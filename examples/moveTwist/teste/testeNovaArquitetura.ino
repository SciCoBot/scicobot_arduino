#include <differential_drive.h>
#include <scicobot_hardware.h>
#include <led_debug.h>
#include <serial_debug.h>

ScicobotRos scicobotRos;

ScicobotRosMotor scicobotRosMotor;

DifferentialDrive differentialDrive;

unsigned long timeBefor = 0;
unsigned long prev_connect_test_time = 0;

bool micro_ros_init_successful;

Debug debugObj(Serial1);

void subscriber_MotorControl_callback(const void * msgin)
{
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
     
  differentialDrive.differentialForPWM(msg->linear.x, msg->angular.z);
  
  timeBefor = micros();
}

void createEntities()
{
  scicobotRos.init();

  scicobotRosMotor.initRosMotorSubscriber(&scicobotRos, subscriber_MotorControl_callback);

  differentialDrive.init();
  
  micro_ros_init_successful = true;
}

void destroy_entities()
{
    rcl_subscription_fini(&scicobotRosMotor.get_rcl_subscriber(), scicobotRos.get_rcl_node());
    rcl_node_fini(scicobotRos.get_rcl_node());
    rclc_executor_fini(scicobotRosMotor.get_rclc_executor());
    rclc_support_fini(scicobotRos.get_rclc_support());
    
    micro_ros_init_successful = false;
}
void setup() 
{
  Serial1.begin(115200);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);
  
  createEntities();
  
  micro_ros_init_successful = false;
}

void loop() 
{

  if(((micros() - timeBefor) > 1000000))
  {
   differentialDrive.differentialForPWM(0, 0);
  }
  //referência: https://githubmemory.com/repo/micro-ROS/micro_ros_arduino/issues/400
  if((micros() - prev_connect_test_time) >= 500)
  {
 
         prev_connect_test_time = millis();

         if(RMW_RET_OK == rmw_uros_ping_agent(10, 2))
         {

             if (!micro_ros_init_successful) 
             {
                 createEntities();
             } 
         } 
         else if(micro_ros_init_successful)
         {

             destroyEntities();
         }
     }
     
     if(micro_ros_init_successful)
     {
     		DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosMotor.get_rclc_executor(), RCL_MS_TO_NS(100)));
     }
}
