/*------------------------------------------------------------*-
  Cpp library for controlling ultrasonic sensor - main
  (c) Minh-An Dao - Him Ko - Yue Qiao 2021
  Inherit from the library of gamegine
  <https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib>
  
  version 1.00 - 02/09/2021 
---------------------------------------------------------------
 * tested on HCSR04
 * 
 --------------------------------------------------------------*/

#include "soniclib.h"

#define MAX_TIMEOUT 7000 //us

/**
 * @brief Constructor/Destructor
 */
Soniclib::Soniclib(void){}
Soniclib::~Soniclib(void)
{
	~this->trig;
	delete[] this->echo;
	~this->n;
}

/**
 * @brief Initialize
 * @return void
 */
void Soniclib::init(int trig,int echo)
{
	this->init(trig,new int[1]{echo},1);
}
void Soniclib::init(int trig,int echo[],int n)
{
	this->trig = trig;
	this->echo = echo;
	this->n = n;
	pinMode(this->trig, OUTPUT);
	for(int i=0;i<n;i++){ pinMode(this->echo[i], INPUT); }
	digitalWrite(this->trig, LOW);
}

/**
 * @brief get the echo time (raw)
 * @return uint32_t (unsigned long)
 */
uint32_t Soniclib::get(int n) const
{
	// digitalWrite(this->trig, LOW);
	// delayMicroseconds(2);
	digitalWrite(this->trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trig, LOW);
	noInterrupts();
	uint32_t d=pulseIn(this->echo[n], HIGH, MAX_TIMEOUT);
	interrupts();
	return d;
}

uint32_t Soniclib::get() const {return this->get(0);}

/**
 * @brief Get the approximate distance in cm
 * @return float
 */
float Soniclib::distance(int n) const
{
	return (float)this->get(n)/58;
}

float Soniclib::distance() const{return this->distance(0);}
