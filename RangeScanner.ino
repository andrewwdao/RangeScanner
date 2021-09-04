/*------------------------------------------------------------*-
  Demonstration code for Group presentation 1
  (c) Minh-An Dao - Him Ko - Yue Qiao 2021
  
  reference:
  <https://github.com/arduino-libraries/Servo>
  <https://github.com/qub1750ul/Arduino_SoftwareReset>
  <https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib>
  
  version 1.00 - 02/09/2021 
---------------------------------------------------------------
 * For demonstration only
 * 
 * Tested on TS90A
 --------------------------------------------------------------*/
#include <avr/wdt.h>
#include "soniclib.h"
#include "servolib.h"

#define BAUDRATE        115200
#define UPDATE_INTERVAL 50 //ms

#define MAX_ANGLE       180
#define MIN_ANGLE       5
#define ANGLE_STEP      MIN_ANGLE
#define SONIC_TRIG_PIN  12
#define SONIC_ECHO_PIN  13
#define SERVO_PIN       A0

uint32_t last_millis = 0;

Servolib scanner;
Soniclib sonic;

bool FORWARD_FLAG = true;
uint8_t angle_buf = 0;
// uint32_t sonic_buf = 0;
float sonic_buf = 0;

void setup()
{
    Serial.begin(BAUDRATE);
    sonic.init(SONIC_TRIG_PIN, SONIC_ECHO_PIN);
    scanner.init(SERVO_PIN);
    while (!Serial.available()); // wait for start command
    while (Serial.available()) Serial.read(); // clear all buffer
}
void loop()
{
    
    last_millis = millis();
    if (FORWARD_FLAG) {
        if (angle_buf<MAX_ANGLE)    {angle_buf +=ANGLE_STEP;}
        else                        {angle_buf -=ANGLE_STEP;FORWARD_FLAG=false;}
    }
    else {
        if (angle_buf>MIN_ANGLE)    {angle_buf -=ANGLE_STEP;}
        else                        {angle_buf +=ANGLE_STEP;FORWARD_FLAG=true;}
    }

    scanner.move(angle_buf);
    // sonic_buf = sonic.get();
    sonic_buf = sonic.distance(); // remember to change declaration
    
    Serial.print(angle_buf); Serial.print(','); Serial.println(sonic_buf);
    
    while (Serial.available()) {
        if (Serial.read()=='k') soft_reset();
    }
    while (millis() - last_millis < UPDATE_INTERVAL);
}

void soft_reset(void) {
    do {
        wdt_enable(WDTO_15MS);
        for(;;) {};
    } while(0);
}
