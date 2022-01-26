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

Implementa, a partir de ros_motor_control, um inscrito ROS 2 que receber comandos de controle diferencial do tópico /cmd_vel. Sendo que, os comando recebidos são convertidos em movimento a partir da biblioteca differential_drive.ultrassônico. 
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
Na janela 2 pode-se verificar as informações publicadas do sensor ultrassônico.

### encoder_moveTwist 

Implementa, a partir de ros_encoder e ros_motor_control, um editor e um inscrito ROS 2 que publica dados dos sensores encoder em /encoder_right e /encoder_left e recebe comandos de controle diferencial em /cmd_vel
```
Fluxo de dados: RASPBERRY <-> ARDUINO
```
A partir deste exemplo é possível verificar a contagem dos encoders no Raspberry enquanto o robô se movimenta. Para isso, execute no Raspberry:
 
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
ros2 tipic echo /encoder_right
```
- Janela 3:
```
source /opt/ros/foxy/setup.bash
ros2 tipic echo /encoder_left
```
- Janela 4:
```
source /opt/ros/foxy/setup.bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
Na janela 2 pode-se verificar as informações publicadas do sensor encoder esquerdo.
Na janela 3 pode-se verificar as informações publicadas do sensor encoder direito.
Na janela 4 pode-se utilizar as teclas expecificadas para movimentar o robô.

### moveOn_encoder_ultrasonic

Implementa, a partir de ros_encoder, ros_ultrasonic e ros_move_on, dois editores e um inscrito ROS 2. Os editores são para publicar os dados dos sensores encoders e ultrassônico, que publicam nos tópicos /encoder_left, /encoder_right e /frontal_ultrasonic, respectivamente. O inscrito é utilizado para recebe comandos boleanos que são usados para determinar se o robô continua se locomovendo para frente ou precisa virar, para isso, podem ser utilizado os dados dos sensores no Raspberry.
```
Fluxo de dados: RASPBERRY <-> ARDUINO
```
PRECISA SER DEFINIDO

### moveTwist_encoder_ultrasonic

Implementa, a partir de ros_encoder, ros_ultrasonic e ros_motor_control, dois editores e um inscrito ROS 2. Os editores são para publicar os dados dos sensores encoders e ultrassônico, que publicam nos tópicos /encoder_left, /encoder_right e /frontal_ultrasonic, respectivamente. O inscrito é utilizado para recebe comandos de controle diferencial do Raspberry através do tópico /cmd_vel.
```
Fluxo de dados: RASPBERRY <-> ARDUINO
```
A partir deste exemplo é possível verificar a contagem dos encoders e a distância medida pelo ultrassônico no Raspberry, enquanto o robô se movimenta. Para isso, execute no Raspberry:
 
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
ros2 tipic echo /encoder_right
```
- Janela 3:
```
source /opt/ros/foxy/setup.bash
ros2 tipic echo /encoder_left
```
- Janela 4:
```
source /opt/ros/foxy/setup.bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
- Janela 5:
```
source /opt/ros/foxy/setup.bash
ros2 topic echo /frontal_ultrasonic
```
Na janela 2 pode-se verificar as informações publicadas do sensor encoder esquerdo.

Na janela 3 pode-se verificar as informações publicadas do sensor encoder direito.
Na janela 4 pode-se utilizar as teclas expecificadas para movimentar o robô.
Na janela 5 pode-se verificar as informações publicadas do sensor ultrassônico.

Observe que para os exemplos tem se uma dinâmica repetitiva para a janela 1, onde a comunicação entre Arduino e Raspberry é executada. Essa janela sempre vai estar presente para qualquer trabalho implementado.
