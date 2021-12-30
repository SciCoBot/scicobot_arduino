#define radius_wheel 2

#define robot_diameter 2

#define L 0.15
#define r 0.065

#define version 1

#define pinMotorIN1 7
#define pinMotorIN2 6
#define pinMotorIN3 5
#define pinMotorIN4 4


//Declara varios objetos


init(){
ret = motor_driver.init();
  DEBUG_PRINTLN(ret==true?"Motor driver setup completed.":"Motor driver setup failed.");
  ret = sensors.init();
  DEBUG_PRINTLN(ret==true?"Sensors setup completed.":"Sensors setup failed.");
  // Init diagnosis
  ret = diagnosis.init();
  DEBUG_PRINTLN(ret==true?"Diagnosis setup completed.":"Diagnosis setup failed.");
  // Init IMU 
  sensors.initIMU();
  sensors.calibrationGyro();
  }
  
  
  
  void TurtleBot3Core::run()
{
  static uint32_t pre_time_to_control_motor;

  // Check connection state with ROS2 node


  /* For sensing and run buzzer */
  // Update the IMU unit
  sensors.updateIMU();
  // Update sonar data
  // TODO: sensors.updateSonar(t);
  // Run buzzer if there is still melody to play.
  sensors.onMelody();


  /* For processing DYNAMIXEL slave function */
  // Update control table of OpenCR to communicate with ROS2 node
  update_imu(INTERVAL_MS_TO_UPDATE_CONTROL_ITEM);
  update_times(INTERVAL_MS_TO_UPDATE_CONTROL_ITEM);
  

}
