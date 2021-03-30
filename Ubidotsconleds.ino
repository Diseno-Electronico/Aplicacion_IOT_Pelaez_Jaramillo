//#include "ESP8266WiFi.h"
#include "Ubidots.h"
#define D7   13 //GPIO13 - HMOSI - RXD2
#define D3   0  //GPIO0

#define TOKEN  "BBFF-cS0lZN4SqRZRiBKmLlYLtfEHzrcdJA"  // Poner aqui tu TOKEN general de Ubidots
#define WIFISSID "JUDITH" // Poner aqui el nombre de tu Wi-Fi
#define PASSWORD "dennis171926" // Poner aqui la clave de tu Wi-Fi
float T;
Ubidots client(TOKEN);
const byte  Pin_led = D7;
const byte  Pin_led1 = D3;
void setup(){
    pinMode(Pin_led, OUTPUT);
    digitalWrite(Pin_led, LOW);
    pinMode(Pin_led1, OUTPUT);
    digitalWrite(Pin_led1, LOW);
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
}

void loop(){
    float value1 = analogRead(A0);
    T=(value1*3.3*100)/1023;
    if(T>31){
      digitalWrite(Pin_led, HIGH);
      }
      else{
        digitalWrite(Pin_led, LOW);
        
        }
     if(T<31){
      digitalWrite(Pin_led1, HIGH);
      }
      else{
        digitalWrite(Pin_led1, LOW);
        
        }
    client.add("temperature", value1);
    client.send();
    delay(2000);
}
