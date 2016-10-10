#pragma once
IMPLEMENTATION(i2cLm75,$Id$) 	//You have to define this in project.xml (search directory)
#include "tempSensor.h"
#include "i2c-Interface.h"
	
TempSensor::TempSensor()
{
	this->address = 73;
	this->temperature = 0;
}

TempSensor::TempSensor(unsigned char address)
{
	this->address = address;
}

short TempSensor::getTemperature()
{
	return this->temperature;
}

/*
	Parameter:
		I2cInterface = Pointer to the I2cInterface which will be used to collect the data over i2c
	Notes:
		After this Method, call getTemperature() to get the value.
*/
void TempSensor::updateTemperature(I2cInterface* i2c)
{
	i2c->begWrite((this->address&0b01111111)|0b1000000);
	i2c->write(0b00000000); 
	i2c->begRead((this->address&0b01111111));
	
	 char data[2];
	 data[0]=i2c->read(0x2<<16);
	 data[1]=i2c->read(0x2<<16);
	short temp = data[0];
	
	//For negativ temperature. TODO: Test this. Might not work...
	if( (data[1]&0b10000000)!=0)
	{
		temp = -temp;
	}
	
  	this->temperature = temp;
}