#ifndef __incub_ESP_lib__
#define __incub_ESP_lib__


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>



#define espDelay 500



#define STM_SEND 'S' 
#define STMtemperature 'T'
#define STMhumidity 'H'
#define STMheater 'B'
#define STMspreadfan 'F'
#define STMExtFan 'X'
#define STMmotor 'M'
#define SendSuccess 'Z'

extern bool Heater, SprdFan, ExtFan, Motor;
extern float HumidValue, TempValue; 




bool STMreadycheck();
bool getHumidity();
bool getTemperature();
bool getHeaterState();
bool getSprdFanState();
bool getExtFanState();
bool getMotorState();
bool sendPAYLOAD();





#endif