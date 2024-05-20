#include <DHT.h> //inclui a biblioteca do sensor de temperatura
#include <Adafruit_SSD1306.h> //biblioteca do display OLED
#include <Adafruit_GFX.h> //biblioteca do display OLED

#define width 128 //define a largura do display
#define height 64 // define a altura do display
#define reset -1 // define o pino de reset, que nesse caso é a mesma do arduino
#define ledR 3 // define o pino do led vermelho
#define ledY 7 // define o pino do led amarelo
#define ledG 8 // define o pino do led verde escuro
#define stickX A2 // define o pino analógico do eixo horizontal do joyStick
#define stickY A3 // define o pino analógico do eixo vertical do joyStick
#define stickB 6 // define o pino do botão do joyStick, apesar de não estar usando nesse projeto
#define ldrPin A1 // // define o pino analógico do fotorresistor LDR

DHT sensor(A0, DHT22); // define o objeto do sensor DHT
Adafruit_SSD1306 OLED = Adafruit_SSD1306(width, height, &Wire, reset); // define o objeto do display

int selecionado = 0;
int preenchido = -1;

void ledVermelho(){
  digitalWrite(ledR, HIGH);
  digitalWrite(ledY, LOW);
  digitalWrite(ledG, LOW);
}
void ledAmarelo(){
  digitalWrite(ledR, LOW);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledG, LOW);
}
void ledVerde(){
  digitalWrite(ledR, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledG, HIGH);
}
void desligaLeds(){
  digitalWrite(ledR, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledG, LOW);
}
void temperatura(){
  int temp = sensor.readTemperature();
  OLED.clearDisplay();
  OLED.setTextSize(1);
  OLED.setCursor(25,0);
  OLED.print("Temperatura");
  OLED.setTextSize(2);
  OLED.setCursor(30,25);
  OLED.print(temp);
  OLED.setCursor(70,25);
  OLED.print("c");
  OLED.drawCircle(60,25,2,WHITE);
  OLED.display();
    if (temp > 70 || temp < 0){
      ledVermelho();
    }
    else if ((temp >= 50 && temp < 70) || (temp > 0 && temp < 20)){
      ledAmarelo();
    }
    else if (temp > 20 && temp < 50){
      ledVerde();
    }
}
void umidade(){
  int umid = sensor.readHumidity();
  OLED.clearDisplay();
  OLED.setTextSize(1);
  OLED.setCursor(40,0);
  OLED.print("Umidade");
  OLED.setTextSize(2);
  OLED.setCursor(40,25);
  OLED.print(umid);
  OLED.setCursor(70,25);
  OLED.print("%");
  OLED.display();
    if (umid > 70){
      ledVerde();
    }
    else if (umid >= 40 && umid < 70){
      ledAmarelo();
    }
    else{
      ledVermelho();
    }
}
void luminosidade(){
  int ldrValue = analogRead(ldrPin);
  const float gamma = 0.7;
  const float rl10 = 50;
  float voltage = ldrValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(rl10 * 1e3 * pow(10, gamma) / resistance, (1 / gamma));
  OLED.clearDisplay();
  OLED.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
  OLED.setTextSize(1);
  OLED.setCursor(25,0);
  OLED.print("Luminosidade");
  OLED.setCursor(40,30);
  OLED.println(lux);
  OLED.setCursor(50,40);
  OLED.print("lux");
  OLED.display();
    if (lux > 80000){
      ledVermelho();
    }
    else if (lux >= 10000 && lux < 80000){
      ledVerde();
    }
    else{
      ledAmarelo();
    }
}
void menu(){
  int x = analogRead(stickX);
  int y = analogRead(stickY);

  if (y <= 511){
    selecionado = selecionado + 1;
    tone(4, 300, 15);
    delay(200);
  }

  if (y >= 513){
    selecionado = selecionado - 1;
    tone(4, 300, 15);
    delay(200);
  }

  if (x <= 511){
    preenchido = selecionado;
    tone (4, 500, 15);
    delay(200);
  }
  
  if (x >= 513){
    preenchido = -1;
    desligaLeds();
    tone (4, 500, 15);
    delay(200);
  }

  const char *opcoes[3] = {
    "Temperatura",
    "Umidade",
    "Luminosidade"
  };

  if (preenchido == -1){
    OLED.clearDisplay();
    OLED.setTextSize(1);
    OLED.setTextColor(SSD1306_WHITE);
    OLED.setCursor(50, 0);
    OLED.println(F("MENU"));
    OLED.println("");
    for (int i = 0; i < 3; i++){
      if (selecionado < 0){
        selecionado = 0;
      } 
      
      if (selecionado > 2){
        selecionado = 2;
      }

      if (i == selecionado){
        OLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        OLED.print(">");
        OLED.println(opcoes[i]);
      } else if (i != selecionado){
        OLED.setTextColor(SSD1306_WHITE);
        OLED.println(opcoes[i]);
      }
    }
  }

  if (preenchido == 0){
    temperatura();
  }

  if (preenchido == 1){
    umidade();
  }

  if (preenchido == 2){
    luminosidade();
  }

  // if (preenchido == 3){
  //   bateria();
  // }

  OLED.display();
}
void setup(){
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(stickX, INPUT);
  pinMode(stickY, INPUT);
  pinMode(stickB, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Cima/baixo: navega no menu");
  Serial.print("Direita/esquerda: entra/sai dos itens");
  sensor.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLED.display();
  tone(4, 370.6, 600);
  delay(800);
  tone(4, 295.1, 800);
  delay(1000);
  tone(4, 295.1, 100);
  delay(100);
  tone(4, 330.3, 150);
  delay(150);
  tone(4, 350, 350);
  delay(350);
  tone(4, 330.3, 280);
  delay(280);
  tone(4, 295.1, 300);
  delay(300);
  tone(4, 278.3, 350);
  delay(350);
  tone(4, 295.1, 300);
  delay(300);
  tone(4, 330.3, 250);
  delay(250);
  tone(4, 370.6, 500);
  delay(600);
  tone(4, 370.6, 100);
  delay(250);
  tone(4, 497.4, 600);
  delay(800);
  tone(4, 247.3, 250);
  delay(250);
  tone(4, 278.3, 300);
  delay(300);
  tone(4, 295.1, 350);
  delay(350);
  tone(4, 330.3, 400);
  delay(400);
  tone(4, 295.1, 350);
  delay(320);
  tone(4, 278.3, 400);
  delay(400);
  tone(4, 440.8, 300);
  delay(300);
  tone(4, 392.4, 350);
  delay(350);
  tone(4, 370.6, 600);
  delay(800);
  tone(4, 295.1, 800);
  delay(1000);
  OLED.clearDisplay();
}
void loop(){  
  menu();
}