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

Nota: é altamente recomendável que utilize [build_scicobot_arduino](https://github.com/SciCoBot/build_scicobot_arduino) para construção e manutenção das dependências.

## Descrição

### moveTwist

Implementa, a partir de ros_motor_control, um inscrito ROS 2 que receber comandos de controle diferencial do tópico /frontal_ultrasonicque . Sendo que, os comando recebidos são convertidos em movimento a partir da biblioteca differential_drive.ultrassônico. 
```
Fluxo de dados: RASPBERRY -> ARDUINO
```
A partir deste exemplo é possível movimentar o robô utilizando o teclado. Para isso, execute no Raspberry:

- Janela 1:
```
source /opt/ros/foxy/setup.bash
cd microros_ws
source install/local_setup.bash
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0
```
- Janela 2:
```
source /opt/ros/foxy/setup.bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
Na janela 2 pode-se utilizar as teclas expecificadas para movimentar o robô.

### ultrasonic: 

Implementa, a partir de ros_ultrasonic, um editor ROS 2 que publica dados do sensor ultrassônico em /frontal_ultrasonic. 
```
Fluxo de dados: RASPBERRY <- ARDUINO
```
A partir deste exemplo é possível verificar os valores lidos pelo ultrassônico no Raspberry. Para isso, execute no Raspberry:

- Janela 1:
```
source /opt/ros/foxy/setup.bash
cd microros_ws
source install/local_setup.bash
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0
```
- Janela 2:
```
source /opt/ros/foxy/setup.bash
ros2 tipic echo /frontal_ultrasonic
```






encoder_moveTwist: possibilita que o robô receba mensagens de controle diferencial e aplique a lógica nos motores e publica os dados do encoder em um tópico ROS 2. A partir deste exemplo é possível verificar a contagem dos encoders enquanto o robô se movimenta;
•	moveOn_encoder_ultrasonic: possibilita a publicação de mensagens ROS 2 dos sensores encoders e ultrassônico, além de se inscrever em um tópico que fornece informações de movimento através da análise dos dados dos sensores. A partir deste exemplo o robô movimenta  possível verificar os valores lidos pelo ultrassônico e encoders enquanto recebe o;
•	moveTwist_encoder_ultrasonic: permite a inscrição em um tópico ROS 2 para receber comandos de controle diferencial enquanto publica dados dos sensores encoder e ultrassônico. A partir deste exemplo é possível verificar os valores lidos pelo ultrassônico e encoders enquanto o robô se locomove;


