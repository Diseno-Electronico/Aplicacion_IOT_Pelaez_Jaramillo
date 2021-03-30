#include <ESP8266WiFi.h>
#define D7   13 //GPIO13 - HMOSI - RXD2
#define D3   0  //GPIO0
String apiWritekey = "TIOJ7QEVOID9W1M5"; // replace with your THINGSPEAK WRITEAPI key here
const char* ssid = "JUDITH"; // your wifi SSID name
const char* password = "dennis171926" ;// wifi pasword
 
const char* server = "api.thingspeak.com";
float resolution=3.28/1024;// 3.3 is the supply volt  & 1023 is max analog read value
WiFiClient client;

const byte  Pin_led = D7;
const byte  Pin_led1 = D3;

void setup() {
  pinMode(Pin_led, OUTPUT);
  digitalWrite(Pin_led, LOW);
  pinMode(Pin_led1, OUTPUT);
  digitalWrite(Pin_led1, LOW);
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}
 
void loop() {
  float temp = (analogRead(A0) * resolution) * 100;
  
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(temp);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);

    if(temp>32){
      digitalWrite(Pin_led, HIGH);
      }
      else{
        digitalWrite(Pin_led, LOW);
        
        }
    if(temp<32){
      digitalWrite(Pin_led1, HIGH);
      }
      else{
        digitalWrite(Pin_led1, LOW);
        
        }
     Serial.print("Temperature: ");
     Serial.print(temp);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
}
