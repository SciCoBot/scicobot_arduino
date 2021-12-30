#include 





bool micro_ros_init_successful; 


void createEntitiesRos()
{  
  set_microros_transports();

  delay(2000);
  // Initialize allocator
  allocator = rcl_get_default_allocator();

  // Initialize support object, caso necessite posso alterar as opções
  //neste caso, posso alterar o domain id
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

}

void initMotorControlROS()
{

	//inicia todos os nós
	micro_ros_init_successful = true;
}






void destroyEntities()
{

    //rcl_publisher_fini(&odom_publisher, &node);
    //rcl_subscription_fini(&twist_subscriber, &node);
    //rcl_node_fini(&node);
    //rcl_timer_fini(&control_timer);
    //rclc_executor_fini(&executor);
    //rclc_support_fini(&support);

    //micro_ros_init_successful = false;
}







// ---------------------------------------------------------------------------


void publishData()
{


}
