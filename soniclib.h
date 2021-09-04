/*------------------------------------------------------------*-
  Cpp library for controlling ultrasonic sensor - header
  (c) Minh-An Dao - Him Ko - Yue Qiao 2021
  Inherit from the library of gamegine
  <https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib>
  
  version 1.00 - 02/09/2021 
---------------------------------------------------------------
 * tested on HCSR04
 * 
 --------------------------------------------------------------*/
#ifndef __SONICLIB_H
#define __SONICLIB_H
#include <Arduino.h>

class Soniclib
{
	public:
	Soniclib();								//constructor
	~Soniclib();							//destructor
	void init(int trig,int echo);			//init the sensor (trig pin , echo pin)
	void init(int trig,int echo[],int n); 	//init the sensor (trig pin , echo pin)
	uint32_t get()		  const;			//return echoing time of element 0
	uint32_t get(int n)	  const;			//return echoing time of element n
	float distance()      const;			//return curent distance of element 0
	float distance(int n) const;			//return curent distance of element n

	private:
	int trig;								//out pin
	int *echo;								//echo pin list
	int n;									//number of el
};

#endif