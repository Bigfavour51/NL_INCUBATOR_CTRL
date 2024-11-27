////////////////////////////////////////////////////////////////////////////////////////////////////
//*FILE NAME:       nl_inc_ctrl.h
//*FILE DESC:       Header file for incubator_ctrl library.
//*FILE VERSION:    0.1.1
//*FILE AUTHOR:     Aina Favour Olalekan (Bigfavour)
//*LAST MODIFIED:   Monday, 19 August, 2024
//*LICENSE:         GNU LGPL v2.1
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NL__1NC__CRT1__
#define __NL__1NC__CTR1__

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ClosedCube_HDC1080.h>
#include <HardwareTimer.h>


#define espDelay 500

#define timIntv 5    // How many seconds the timer should update the values.
#define mill 1000000 // One million

#define ON HIGH
#define OFF LOW

#define bulbsw PA2  // NO contact of active high relay
#define exFansw PA4 // NO contact of active high relay
#define fansSw PA3 // NO contact of active high relay
#define MotorSw PA7 // control pin for the motor
#define humidifier PA5

#define tempTh 37.8 // Temperature threshold
#define humidTh 90  // Humidity threshold, not used.


#define STM_SEND 'S'
#define STMtemperature 'T'
#define STMhumidity 'H'
#define STMheater 'B'
#define STMspreadfan 'F'
#define STMExtFan 'X'
#define STMmotor 'M'
#define SendSuccess 'Z'

//Methods:
void timISR(void); // ISR to update the temperature and humidity values every timIntv seconds
void MotorCtrl();
int SendSerialData();
void dispWlcMsg();
void msg1();
void msg2();
void showValues();

//Attributes:

extern LiquidCrystal_I2C lcd;
extern ClosedCube_HDC1080 thSens;
extern HardwareTimer *timer;
extern double temp, humid;
extern bool Tover, Hover;

extern unsigned long currentMillis;
extern unsigned long previousMillis;
extern unsigned long motorPreviousMillis;
extern unsigned long motorOnDuration; // 1 minute
extern unsigned long motorOffDuration; // 30 minutes
extern bool motorState; // false for off, true for on




#endif
