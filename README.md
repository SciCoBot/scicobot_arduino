# scicobot_arduino 1.0

## Sobre

Este projeto consiste no programa a ser carregado no Arduino Due.

Considerando o ROS, para esta aplicação o Arduino Due é reponsável por:
- receber comandos para controle dos motores;
- enviar dados dos sensores (Ultrassônico e encoders);

## Dependências 

São utilizadas as seguintes bibliotecas:

- [motor_control](https://github.com/SciCoBot/motor_control) para controle de motor DC; 
- [serial_debug](https://github.com/SciCoBot/serial_debug) para debug via monitor serial; 
- [ultrasonic](https://github.com/SciCoBot/ultrasonic) para leitura do sensor ultrassônico;
- [micro_ros_arduino foxy](https://github.com/micro-ROS/micro_ros_arduino/tree/foxy) para implementação da estrutura ROS 2 foxu em arduino due;
- [encoder](https://github.com/SciCoBot/encoder) para leitura do sensor encoder;
- [led_debug](https://github.com/SciCoBot/led_debug) para debug visual, principalmente da micro_ros_arduino
- [differential_drive](https://github.com/SciCoBot/differential_drive): converte comandos diferênciais em movimento para o robô.

Nota: é altamente recomendavél que utilize [build_scicobot_arduino](https://github.com/SciCoBot/build_scicobot_arduino) para construção e manutenção das dependências.

