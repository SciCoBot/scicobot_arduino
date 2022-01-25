#include <scicobot_arduino.h>
#include <led_debug.h>
#include <serial_debug.h>
#include <encoder.h>
#include <ultrasonic.h>
#include <simple_motor_dc.h>


#define DEBUG_ENABLE 0

//Pins ultrasonic
#define PIN_TRIGGER  53
#define PIN_ECHO  50

//Pins Motor
#define IN1_A 7
#define IN2_A 6

//Pins Motor
#define IN2_B 5
#define IN1_B 4

//Pins Encoder
#define OUT_ENCODER_RIGHT 51
#define OUT_ENCODER_LEFT 52

//Motors
SimpleMotor motorRight;
SimpleMotor motorLeft;

//Encoder
Encoder encoderRight;
Encoder encoderLeft;

//Ultrasonic
Ultrasonic frontalUltrasonic;

//Micro-ROS
ScicobotRos scicobotRos;

ScicobotRosEncoder scicobotRosEncoder;

ScicobotRosUltrasonic scicobotRosUltrasonic;

ScicobotRosMove scicobotRosMove;

void subscriberCallbackMove(const void * msgin)
{
  const std_msgs__msg__Bool * msg = (const std_msgs__msg__Bool *)msgin;
  
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN(msg->data);  
  #endif
  
  if (msg->data == 0)
  {

    motorRight.forward(255);
    motorLeft.backward(255);

    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("gira");
    #endif
  }
  else
  {
    motorRight.forward(255);
    motorLeft.forward(255);
    
    #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("Continua para frente");
    #endif
    
 }
     #if DEBUG_ENABLE ==1 
      debugObj.DEBUGLN("Continua para frente");
    #endif
}

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

void count_encoder_left()
{
  encoderLeft.incrementPulses();
}

void count_encoder_right()
{
  encoderRight.incrementPulses();
}

void callback_encoder_right(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    (*scicobotRosEncoder.get_rclc_msg_ritght()).data = encoderRight.readAndReset();
    DEBUG_WARNING_MICR0_ROS(rcl_publish(scicobotRosEncoder.get_rclc_publisher_ritght(), scicobotRosEncoder.get_rclc_msg_ritght(), NULL));
  }
  
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("callback_encoder_right()");  
  #endif
}

void callback_encoder_left(rcl_timer_t * timer, int64_t last_call_time)
{  
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    (*scicobotRosEncoder.get_rclc_msg_left()).data = encoderLeft.readAndReset();
    DEBUG_WARNING_MICR0_ROS(rcl_publish(scicobotRosEncoder.get_rclc_publisher_left(), scicobotRosEncoder.get_rclc_msg_left(), NULL));
  }
  
  #if DEBUG_ENABLE ==1 
    debugObj.DEBUGLN("callback_encoder_left()");  
  #endif
}

void setup() 
{
  Serial1.begin(115200);
  
  pinMode(LED_DEBUG_PIN, OUTPUT);

  frontalUltrasonic.init(PIN_TRIGGER, PIN_ECHO);

  motorRight.init(IN1_A, IN2_A);
  motorLeft.init(IN1_B, IN2_B);

  encoderRight.init(OUT_ENCODER_RIGHT, &count_encoder_right);
  encoderLeft.init(OUT_ENCODER_LEFT, &count_encoder_left);
  
  scicobotRos.init();
  
  scicobotRosEncoder.initRosEncoderPublisher(&scicobotRos, callback_encoder_right, callback_encoder_left);

  scicobotRosUltrasonic.initRosUltrasonicPublisher(&scicobotRos, timerCallbackUltrasonic);
  
  scicobotRosMove.initRosMoveSubscriber(&scicobotRos, subscriberCallbackMove);
    
  motorRight.forward(255);
  motorLeft.forward(255);
}

void loop() 
{
  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosEncoder.get_rclc_executor(), RCL_MS_TO_NS(100)));

  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosUltrasonic.get_rclc_executor(), RCL_MS_TO_NS(100)));

  DEBUG_ERROR_MICR0_ROS(rclc_executor_spin_some(scicobotRosMove.get_rclc_executor(), RCL_MS_TO_NS(100)));
  
}
