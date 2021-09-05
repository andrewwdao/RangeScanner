/*------------------------------------------------------------*-
  Draft lib for controlling up to 2 servo simutanuously - main
  (c) Minh-An Dao - Him Ko - Yue Qiao 2021
  reference: Arduino Servo Library
  <https://github.com/arduino-libraries/Servo>
  
  version 1.00 - 02/09/2021 
---------------------------------------------------------------
 * For demonstration only
 * 
 * Tested on TS90A
 --------------------------------------------------------------*/
#include "servolib.h"
// ------ Private constants -----------------------------------
#define DEFAULT_ANGLE       90 // degree
#define REPEAT_CYCLE        1 // ---> NEED CALIBRATION
#define T_TOTAL             20000 //us - pulse period
#define MIN_PULSE           544  // the shortest pulse sent to a servo  
#define MAX_PULSE           2400  // the longest pulse sent to a servo 

Servolib::Servolib(void) {}     // constructor
Servolib::~Servolib(void) {     // destructor
    ~this->servo1;
	~this->servo2;
}
void Servolib::init(int ser) {
    this->servo1 = ser;
    pinMode(this->servo1,OUTPUT);
    // move to default angle
    int tbuffer = map(DEFAULT_ANGLE, 0, 180, MIN_PULSE, MAX_PULSE);
    for (int i=0; i<30;i++) { // 20*REPEAT_CYCLE ms
        digitalWrite(this->servo1,HIGH);
        delayMicroseconds(tbuffer);
        digitalWrite(this->servo1,LOW);
        delayMicroseconds(T_TOTAL-tbuffer);
    }
}
void Servolib::init(int ser1, int ser2) {
    this->servo1 = ser1;
    this->servo2 = ser2;
    pinMode(this->servo1,OUTPUT);
    pinMode(this->servo2,OUTPUT);
    int tbuffer = map(DEFAULT_ANGLE, 0, 180, MIN_PULSE, MAX_PULSE);
    for (int i=0; i<30;i++) { // 20*REPEAT_CYCLE ms
        digitalWrite(this->servo1,HIGH);
        digitalWrite(this->servo2,HIGH);
        delayMicroseconds(tbuffer);
        digitalWrite(this->servo1,LOW);
        digitalWrite(this->servo2,LOW);
        delayMicroseconds(T_TOTAL-tbuffer);
    }
}
void Servolib::movepulse(int tbuffer) {
    tbuffer = (tbuffer<MIN_PULSE)?MIN_PULSE:((tbuffer>MAX_PULSE)?MAX_PULSE:tbuffer);
    for (int i=0; i<REPEAT_CYCLE;i++) { // 20*REPEAT_CYCLE ms
        digitalWrite(this->servo1,HIGH);
        delayMicroseconds(tbuffer);
        digitalWrite(this->servo1,LOW);
        delayMicroseconds(T_TOTAL-tbuffer);
    }
}
void Servolib::movepulse(int tbuffer1, int tbuffer2) {
    int min_servo = 0;
    int max_servo = 0;
    int min_tbuffer = 0;
    int max_tbuffer = 0;
    tbuffer1 = (tbuffer1<MIN_PULSE)?MIN_PULSE:((tbuffer1>MAX_PULSE)?MAX_PULSE:tbuffer1);
    tbuffer2 = (tbuffer2<MIN_PULSE)?MIN_PULSE:((tbuffer2>MAX_PULSE)?MAX_PULSE:tbuffer2);
    if (tbuffer1>tbuffer2) {
        min_tbuffer = tbuffer2; min_servo = this->servo2;
      	max_tbuffer = tbuffer1; max_servo = this->servo1;
    } else {
    	min_tbuffer = tbuffer1; min_servo = this->servo1;
      	max_tbuffer = tbuffer2; max_servo = this->servo2;
    }
    int middle_tbuffer = max_tbuffer-min_tbuffer;
    for (int i=0; i<REPEAT_CYCLE;i++) { // 1000ms
        digitalWrite(this->servo1,HIGH);
        digitalWrite(this->servo2,HIGH);
        delayMicroseconds(min_tbuffer);
        digitalWrite(min_servo,LOW);
        delayMicroseconds(middle_tbuffer);
        digitalWrite(max_servo,LOW);
        delayMicroseconds(T_TOTAL-max_tbuffer);
    }
}

void Servolib::move(int angle) {
    angle = (angle<0)?0:((angle>180)?180:angle);
    int buffer_pulse = map(angle, 0, 180, MIN_PULSE, MAX_PULSE);
    this->movepulse(buffer_pulse);
}
void Servolib::move(int angle1, int angle2) {
    angle1 = (angle1<0)?0:((angle1>180)?180:angle1);
    angle2 = (angle2<0)?0:((angle2>180)?180:angle2);
    int buffer_pulse1 = map(angle1, 0, 180, MIN_PULSE, MAX_PULSE);
    int buffer_pulse2 = map(angle2, 0, 180, MIN_PULSE, MAX_PULSE);
    this->movepulse(buffer_pulse1, buffer_pulse2);
}
