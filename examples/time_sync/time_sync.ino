//void syncTime()
//{
//    // get the current time from the agent
//    unsigned long now = millis();
//    RCCHECK(rmw_uros_sync_session(10));
//    unsigned long long ros_time_ms = rmw_uros_epoch_millis(); 
//    // now we can find the difference between ROS time and uC time
//    time_offset = ros_time_ms - now;
//}
