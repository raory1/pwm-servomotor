# Controle de Servo Motor com Raspberry Pi Pico

Este projeto implementa o controle de um servomotor utilizando o Raspberry Pi Pico, configurando a frequência do PWM para aproximadamente 50Hz e ajustando o ciclo de trabalho para posicionar o servo em diferentes ângulos.

## Funcionalidades

Configuração do PWM na GPIO 22 para operar a 50Hz.

Controle de posicionamento do servomotor em 0°, 90° e 180°.

Movimentação periódica e suave do servo entre 0° e 180° com incrementos de 5µs e atraso de 10ms.

Controle da intensidade de um LED RGB (conectado à GPIO 12) baseado na posição do servo.


## Configuração do PWM

A frequência do PWM na GPIO 22 é ajustada para 50Hz (período de 20ms).

O ciclo de trabalho é definido conforme os seguintes valores:

500µs (0°) -> 2,5% Duty Cycle

1470µs (90°) -> 7,35% Duty Cycle

2400µs (180°) -> 12% Duty Cycle

LINK VIDEO:
https://youtu.be/V7uLCVVS6E8
