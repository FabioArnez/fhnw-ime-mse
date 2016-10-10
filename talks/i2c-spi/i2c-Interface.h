#pragma once
//--------------------
//i2c-demo
//(c) H.Buchmann FHNW 2016
//see [1] Datasheet SHT10, SHT11, SHT15
//        Sensirion_Humidity_and_Temperature_Sensors_SHT21_Datasheet_V4-1.pdf
//--------------------
IMPLEMENTATION(i2cLm75,$Id$)
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/reg/sercom.h"
#include "sys/reg/gclk.h"
#include "sys/soc.h"
#include "sys/pin.h"
	
using namespace sys::reg;
	
class I2cInterface
{
	private:
	unsigned char addr;
	SER::PAD* SDA;
	SER::PAD* SCL;
	
	void init();
		
		
	public:
	I2cInterface();
	I2cInterface(SER::PAD* SDA,SER::PAD* SCL);
	void begWrite(unsigned char addr);
	void write(unsigned char value);
 	void endWrite();
	
	void begRead(unsigned char addr);
	unsigned char read(unsigned int action);
 	void endRead();
	
	void setSDA(SER::PAD* SDA);
	void setSCL(SER::PAD* SCL);
};


