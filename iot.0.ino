#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Authentication details
char auth[] = "GD49FPCqM__O99lpZErhwvocrFpikPn4";//Enter your Auth token
char ssid[] = "Nachu";//Enter your WIFI name
char pass[] = "nv@nv@2021";//Enter your WIFI password

//Pin defines
#define sensor A0
#define switch D1
#define auto_mode D2

BlynkTimer timer;

BLYNK_WRITE(V0){
  digitalWrite(switch, param.asInt());  
}
BLYNK_WRITE(V2){
  digitalWrite(auto_mode, param.asInt());  
}

void setup() {
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  pinMode(switch, OUTPUT);
  pinMode(auto_mode, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  
  //Call soil moisture funtion
  timer.setInterval(100L, soilMoistureSensor);
}
void loop() {
  Blynk.run();
  if(!digitalRead(auto_mode)) {
    if(digitalRead(switch)) {
      digitalWrite(D0, LOW);
    }else {
      digitalWrite(D0, HIGH);
    }  
  }
  timer.run();//Run the Blynk timer
}

//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;
  Blynk.virtualWrite(V1, value);
  if(digitalRead(auto_mode)) {
    //For very low value turn on the switch
    if(value < 30) {
      digitalWrite(D0, LOW);
    } else {
      digitalWrite(D0, HIGH);
    }
  }
  //Serial.println("value : ");
  //Serial.println(value);
}

//#define BLYNK_TEMPLATE_ID "TMPL3o7Axw0Vj"
//#define BLYNK_TEMPLATE_NAME "FirstIOT"
//#define BLYNK_AUTH_TOKEN "GD49FPCqM__O99lpZErhwvocrFpikPn4"
