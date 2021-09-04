/*------------------------------------------------------------*-
  Draft lib for controlling up to 2 servo simutanuously - header
  (c) Minh-An Dao - Him Ko - Yue Qiao 2021
  reference: Arduino Servo Library
  <https://github.com/arduino-libraries/Servo>

  version 1.00 - 02/09/2021 
---------------------------------------------------------------
 * For demonstration only
 * 
 * Tested on TS90A
 --------------------------------------------------------------*/
#ifndef __SERVOLIB_H
#define __SERVOLIB_H

#include "Arduino.h"

class Servolib
{
	public:
	Servolib();								//constructor
	~Servolib();							//destructor
  void init(int);           // Initialize 1 servo only
	void init(int, int);      // Initialize 2 servos
  void move(int);           // Move servo using angle
	void move(int, int);      // Move servos using angles
  void movepulse(int);      // Move servo using pulse width
  void movepulse(int, int); // Move servos using pulse width
	

  private:
	int servo1 = 0;
  int servo2 = 0;

};

#endif


