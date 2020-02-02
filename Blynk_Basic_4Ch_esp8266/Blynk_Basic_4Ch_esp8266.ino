/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define Relay1 D1
#define Relay2 D2
#define Relay3 D5
#define Relay4 D6

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "BRPep7qM5AxvXxN6QmE7e4ROALYjAyfl";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Supod";
char pass[] = "palace66";

int count = 0;
bool Connected2Blynk = false;
// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
 if(param.asInt()==1)
  {
     digitalWrite(Relay1, LOW);
  }
  else
  {
     digitalWrite(Relay1, HIGH);
  }
}
BLYNK_WRITE(V2)
{
 if(param.asInt()==1)
  {
     digitalWrite(Relay2, LOW);
  }
  else
  {
     digitalWrite(Relay2, HIGH);
  }
}
BLYNK_WRITE(V3)
{
 if(param.asInt()==1)
  {
     digitalWrite(Relay3, LOW);
  }
  else
  {
     digitalWrite(Relay3, HIGH);
  }
}
BLYNK_WRITE(V4)
{
 if(param.asInt()==1)
  {
     digitalWrite(Relay4, LOW);
  }
  else
  {
     digitalWrite(Relay4, HIGH);
  }
}
int digitalReadOutputPin(uint8_t pin)
{
 uint8_t bit = digitalPinToBitMask(pin);
 uint8_t port = digitalPinToPort(pin);
 if (port == NOT_A_PIN)
   return LOW;

 return (*portOutputRegister(port) & bit) ? HIGH : LOW;
}

void CheckConnection(){
  if (count>5) {
    Serial.println("restart");
    ESP.restart();
  } else {
    Connected2Blynk = Blynk.connected();
    if(!Connected2Blynk){
      count++;
      Serial.println("Not connected to Blynk server"); 
    } else {
      count = 0;
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
  Serial.print(digitalRead(Relay1));
  Serial.print(digitalRead(Relay2));
  Serial.print(digitalRead(Relay3));
  Serial.println(digitalRead(Relay4));
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  Blynk.virtualWrite(V1, !digitalRead(Relay1));
  Blynk.virtualWrite(V2, !digitalRead(Relay2));
  Blynk.virtualWrite(V3, !digitalRead(Relay3));
  Blynk.virtualWrite(V4, !digitalRead(Relay4));
  timer.setInterval(4000L, CheckConnection); // check if still connected every 11 seconds 
}

void loop()
{
  Blynk.run();
}
