# SPRINT TECH MAHINDRA
## Projeto Sensores de Pista
Este projeto consiste em um dispositivo IoT que capta dados de temperatura, luminosidade e umidade e os disponibiliza para visualização em um site. O repositório contém o código do Arduino utilizado para capturar esses dados.

[Clique aqui](https://wokwi.com/projects/398061779987835905) para ver protótipo do projeto no wokwi.

## Índice

- [Descrição do Projeto](#descrição-do-projeto)
- [Hardware Necessário](#hardware-necessário)
- [Instalação e Configuração](#instalação-e-configuração)
- [Executando os Testes](#executando-os-testes)
- [Implementação](#implementação)

## Descrição do Projeto

O objetivo deste projeto é monitorar as condições climáticas de uma pista de corrida de *Formula E* em tempo real.

O dispositivo IoT é responsável por coletar dados de temperatura, luminosidade e umidade, e enviar essas informações para um servidor onde podem ser acessadas através de um site.

## Hardware necessário

Para reproduzir este projeto, você vai precisar dos seguintes componentes:
- 1 Arduino Uno R3
- 1 Modulo Photoresistor (LDR)
- 1 Buzzer
- 1 Sensor de umidade e temperatura DHT22 ou DHT11
- 3 resistores de 220 omns
- 3 Leds
- 1 Tela OLED modelo SSD1306
- 1 Módulo JoyStick

## Instalação e configuração

1. Com o comando `Git clone`, clone este repositório para o seu ambiente local:
    ```
    git clone https://github.com/Rafael0407Orla/sprintEDGE.git
    ```

2. Abra o arquivo `index.ino` na IDE do Arduino. (Você pode baixar a IDE do arduino [Clicando Aqui!](https://www.arduino.cc/en/software))

3. Instale as bibliotecas necessárias para o sensor e tela:
- [DHT Sensor Library](https://downloads.arduino.cc/libraries/github.com/adafruit/DHT_sensor_library-1.4.6.zip)
- [Adafruit SSD1306](https://downloads.arduino.cc/libraries/github.com/adafruit/Adafruit_SSD1306-2.5.10.zip)
- [Adafruit GFX Library](https://downloads.arduino.cc/libraries/github.com/adafruit/Adafruit_GFX_Library-1.11.9.zip)

4. Carregue o código no seu Arduino.

Após carregar o código no arduino, ele começará a captar as informações dos sensores, para observar esses dados, basta navegar pelo menu do display pelo joystick, utilizando:
- ⬆ e ⬇ para escolher a opção
- ➡ para entrar na opção escolhida
- ⬅ para voltar para o menu

## Executando os Testes

Tente levar o dispositivo para diferentes lugares  e observe a oscilação dos dados captados pelo sensores pela tela.
Você pode também tentar aproximar o sensor DHT de alguns obetos, como um vaporizador ou até alguma coisa quente (tenha cuidado para não se machucar ou estragar algum sensor).

## Implementação

Visamos a implantação do sistema em pistas de corrida da *Formula E*, para obtermos dados das condições climáticas do ambiente. Por exemplo, se a pista está muito quente, a tendência é que a pressão aumente nos pneus do carro. Se estiver muito frio, a aderência dos pneus no asfalto diminui. A pista pode até mesmo congelar!
Outro fator também muito importante que o sensor capta é a condição de chuva do tempo. Utilizando o sensor de humidade em conjuto do sensor LDR, podemos tentar prever as chances de chuva para a corrida.

## 🛠️ Construído com 🛠️


![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&color=000)
