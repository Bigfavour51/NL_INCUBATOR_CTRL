#include <Arduino.h>
#include "incub.h"





bool getTemperature()
{
    delay(espDelay);

    String buffer = Serial.readString();
    TempValue = buffer.toFloat();
    Serial.println("TEMPERATURE");
    Serial.println(TempValue);
    return true;
}

bool getHumidity()
{
    delay(espDelay);

    String buffer = Serial.readString();
    HumidValue = buffer.toFloat();
    Serial.println("HUMIDITY");
    Serial.println(HumidValue);
    return true;
}

bool getHeaterState()
{
    delay(espDelay);

    char c = Serial.read();
    if(c == 'Y')
        Heater = true;
    else
       Heater = false;

    Serial.println("HEATER");
    Serial.println(((Heater == true) ? "ON" : "OFF"));
    return true;
}

bool getSprdFanState()
{
    delay(espDelay);

    char c = Serial.read();
    if(c == 'Y')
        SprdFan = true;
    else
        SprdFan = false;

    Serial.println("SPREADFAN");
    Serial.println(SprdFan ? "ON" : "OFF");
    return true;
}

bool getExtFanState()
{
    delay(espDelay);

    char c = Serial.read();
    if(c == 'Y')
        ExtFan = true;
    else
        ExtFan = false;

    Serial.println("EXTFAN");
    Serial.println(ExtFan ? "ON" : "OFF");
    return true;
}

bool getMotorState()
{
    delay(espDelay);

    char c = Serial.read();
    if(c == 'Y')
        Motor = true;
    else
       Motor = false;

    Serial.println("MOTOR");
    Serial.println(Motor ? "ON" : "OFF");
    return true;
}

