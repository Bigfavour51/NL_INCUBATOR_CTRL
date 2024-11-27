//////////0//////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       nl_inc_ctrl.cpp
//*FILE DESC:       Source file for incubator_ctrl library.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Aina Favour Olalekan (Bigfavour)
//*LAST MODIFIED:   Monday, 19 August, 2024
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <nl_inc_ctrl.h>
void timISR()
{
    temp = thSens.readTemperature();
    humid = thSens.readH();

    // Tover = (temp <= tempTh - 3.5) ? false : true; // Returns true if the temperature measured is over the defined temperature threshold, tempTh

    if (temp >= tempTh)
    {
        digitalWrite(bulbsw, ON);
        digitalWrite(exFansw, OFF);
        lcd.clear();
        lcd.home();
        lcd.print("  Heater On  ");
        lcd.setCursor(0, 1);
        lcd.print("Spread Fan On");
    }
    else if (temp < tempTh - 3.5)
    {
        digitalWrite(bulbsw, OFF);
        digitalWrite(exFansw, ON);
        lcd.clear();
        lcd.home();
        lcd.print("Heater OFF");
        lcd.setCursor(0, 1);
        lcd.print(" Ext. Fan ON ");
    }

    else;
}

void MotorCtrl()
{
    if (motorState == false && currentMillis - motorPreviousMillis >= motorOffDuration)
    {
        // Turn the motor on
        motorState = true;
        motorPreviousMillis = currentMillis;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MOTOR ON : 1 MINS");
        analogWrite(MotorSw, 800);
    }
    else if (motorState == true && currentMillis - motorPreviousMillis >= motorOnDuration)
    {
        // Turn the motor off
        motorState = false;
        motorPreviousMillis = currentMillis;
        lcd.clear();
        lcd.home();
        lcd.print("MOTOR OFF : 30 MINS");
        analogWrite(MotorSw, 0);
    }
}

int SendSerialData()
{
    Serial.print(STMtemperature);
    Serial.println(temp);
    delay(espDelay);

    Serial.print(STMhumidity);
    Serial.println(humid);
    delay(espDelay);

    Serial.print(STMheater);
    Serial.println((digitalRead(bulbsw)) ? "Y" : "N" );
    delay(espDelay);

    Serial.print(STMspreadfan);
    Serial.println((digitalRead(fansSw)) ? "Y" : "N" );
    delay(espDelay);

    Serial.print(STMExtFan);
    Serial.println((digitalRead(exFansw)) ? "Y" : "N" );
    delay(espDelay);

    Serial.print(STMmotor);
    Serial.println((digitalRead(MotorSw)) ? "Y" : "N" );
    delay(espDelay);

    Serial.print(STM_SEND);

    Serial.flush();

    lcd.clear();
    lcd.home();
    lcd.print("Sending to cloud.");
    lcd.setCursor(0, 1);

    while(!Serial.available())
    {
        lcd.print(".");
        delay(600);
    }

    static char c = Serial.read();
    switch(c)
    {
        case SendSuccess:
        {
            lcd.clear();
            delay(700);
            lcd.home();
            lcd.print("Upload success!");
            delay(1500);
            lcd.clear();
            break;
        }

        default:
        {
            lcd.clear();
            delay(700);
            lcd.home();
            lcd.print("Upload fail!");
            delay(1500);
            lcd.clear();
            break;
        }
    }

    return 0;
}

void dispWlcMsg()
{
    lcd.clear();
    lcd.home();
    lcd.print("セモゼ㋔㋝757ｻｱ㋔*******");
    lcd.setCursor(0, 1);
    lcd.print("***NL_757_FPI_IN");
    delay(3000);

    msg1();
    delay(3000);

    lcd.clear();
    lcd.home();
    digitalWrite(bulbsw, ON);
    lcd.print("HEATER ON...");
    delay(2000);
    lcd.setCursor(0, 1);
    digitalWrite(fansSw, ON);
    lcd.print("SPREAD FANS ON");
    delay(2000);
}

void msg1()
{
    lcd.clear();
    lcd.home();
    lcd.print("**      FPI   **");
    lcd.setCursor(0, 1);
    lcd.print("Egg Incubator");
}

void msg2()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP: ");
    lcd.print(temp);
    lcd.print(" C");
}
