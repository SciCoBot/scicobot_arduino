#include <scicobot_arduino.h>
#include <led_debug.h>
#include <serial_debug.h>
#include <ultrasonic.h>

#define DEBUG_ENABLE 0

#define PIN_TRIGGER  53
#define PIN_ECHO  50

Ultrasonic frontalUltrasonic;

ScicobotRos scicobotRos;

ScicobotRosUltrasonic scicobotRosUltrasonic;

void timerCallbackUltrasonic(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
   (*scicobotRosUltrasonic.get_rclc_msg()).data = frontalUltrasonic.measureDistanceCm(25);
   DEBUG_WARNING_MICR0_ROS(rcl_publish(scicobotRosUltrasonic.get_rclc_publisher(), scicobotRosUltrasonic.get_rclc_msg(), NULL));

  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("timerCallbackUltrasonic()");  
  #endif
  }
}

void setup() 
{
  Serial1.begin(115200);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);

  frontalUltrasonic.init(PIN_TRIGGER, PIN_ECHO);
  
  scicobotRos.init();
  
  scicobotRosUltrasonic.initRosUltrasonicPublisher(&scicobotRos, timerCallbackUltrasonic);

}

void loop() 
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosUltrasonic.get_rclc_executor(), RCL_MS_TO_NS(100)));
}
