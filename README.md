# scicobot_hardware

Este projeto consiste no programa a ser carregado no Arduino Due.
O Due é responsável por:
- controle dos motores através de comandos recebidos da raspberru pi;
- envio dos dados dos sensores (Ultrassônico, encoders e IMU);
- controle de LED para debug micro-ROS

Para tal, são utilizadas as bibliotecas (pasta include), em resumo, tem-se:
- [motor_control]() para controle de motor DC; 
- [serial_debug]() para debug via serial; 
- [ultrasonic]() para leitura do sensor de distância Ultrassônico HC-SR04;
- [micro_ros_arduino]() para implementação da estrutura ROS2 em arduino;
- [encoder]() para leitura do sensor encoder;
- [led_debug]() para debug visual, principalmente da micro_ros_arduino
- [differential_drive]() para controle diferencial do robô
