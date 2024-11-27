#include <Arduino.h>
#include <nl_inc_ctrl.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);
ClosedCube_HDC1080 thSens;
HardwareTimer *timer = new HardwareTimer(TIM2);
double temp, humid;
bool Tover, Hover;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long motorPreviousMillis = 0;
unsigned long motorOnDuration = 60000; // 1 minute
unsigned long motorOffDuration = 1800000; // 30 minutes
bool motorState = false; // false for off, true for on

// String tempstr { }, humstr { }, heatstr { }, spreadstr { }, extstr { }, motstr { };


void setup()
{
    Serial.begin(115200);
    pinMode(bulbsw, OUTPUT);
    pinMode(exFansw, OUTPUT);
    pinMode(fansSw, OUTPUT);
    pinMode(MotorSw, OUTPUT);
    pinMode(humidifier, OUTPUT);

    delay(200);

    digitalWrite(bulbsw, ON);
    digitalWrite(exFansw, ON);
    digitalWrite(fansSw, ON);
    digitalWrite(MotorSw, ON);
    digitalWrite(humidifier, ON);

    delay(1000);

    digitalWrite(bulbsw, OFF);
    digitalWrite(exFansw, OFF);
    digitalWrite(fansSw, OFF);
    digitalWrite(MotorSw, OFF);
    digitalWrite(humidifier, OFF);

    delay(1000);

    temp = 0.0;
    humid = 0.0;
    Tover = false;
    Hover = false;

    thSens.begin(0x40);
    thSens.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);

    analogWriteResolution(12);

    // timer->setOverflow(timIntv * mill, MICROSEC_FORMAT);
    // timer->attachInterrupt(timISR);
    // timer->resume();

    lcd.init();
    lcd.backlight();
    lcd.clear();

    dispWlcMsg();

    // lcd.clear();
    // lcd.home();
    // lcd.print("MOTOR ON");
    // delay(2000);
    // analogWrite(MotorSw, 800);

}

void loop()
{
    msg1();
    delay(1000);

    msg2();
    delay(1000);


    currentMillis = millis();

    // Update the display every 3 seconds
    if (currentMillis - previousMillis >= 3000)
    {
        previousMillis = currentMillis;
        timISR();

        // lcd.setCursor(0, 1);
        // lcd.print("HUMID: ");
        // lcd.print(humid);
        // lcd.print(" %");
    }

    // Motor control logic
   MotorCtrl();
   SendSerialData();

}


