#pragma once
IMPLEMENTATION(i2cLm75,$Id$) 	//You have to define this in project.xml (search directory)
#include "sys/reg/sercom.h"
#include "sys/soc.h"
#include "i2c-Interface.h"


class TempSensor
{
	private:
	unsigned char address;
	short temperature;
	
	public:
	TempSensor();
	TempSensor(unsigned char address);
	void updateTemperature(I2cInterface* i2c);
	short getTemperature();
	
};