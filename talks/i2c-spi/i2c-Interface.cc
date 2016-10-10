#pragma once
//--------------------
//i2c-demo
//(c) H.Buchmann FHNW 2016
//see [1] Datasheet SHT10, SHT11, SHT15
//        Sensirion_Humidity_and_Temperature_Sensors_SHT21_Datasheet_V4-1.pdf
//--------------------
IMPLEMENTATION(i2cLm75,$Id$)	//You have to define this in project.xml (search directory)
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/reg/sercom.h"
#include "sys/reg/gclk.h"
#include "sys/soc.h"
#include "sys/pin.h"
#include "i2c-Interface.h"
	
using namespace sys::reg;

I2cInterface::I2cInterface()
{
	this->init();
}

I2cInterface::I2cInterface(SER::PAD* SDA,SER::PAD* SCL)
{
	this->SDA = SDA;
	this->SCL = SCL;
	this->init();
}


void I2cInterface::init()
{
	sys::SOC::clkOn(sys::SOC::SERCOM3);
	
	GCLK.src2gen(GCLK::OSC8M,GCLK::G8,(1<<0));
	GCLK.gen2dev(GCLK::G8,GCLK::SERCOM3_CORE); //8MHz


	//reset
	SER::COM3.I2CM.CTRLA=1; 
	while(SER::COM3.I2CM.CTRLA&1){}

	SER::COM3.I2CM.CTRLA=(0x5<<2); //I2CM Mode

	/* Baudrate
	 f_scl= f_gclk/(2*(5+BAUD)+f_gclk*T_rise)
	 T_rise=15nS
	 BAUD=15
	*/
	SER::COM3.I2CM.BAUD=45; //80 kHz


	SER::COM3.I2CM.CTRLA|=(1<<1);           //ENABLE
	while (SER::COM3.I2CM.SYNCBUSY&(1<<1)){}

	SER::COM3.I2CM.STATUS|=(1<<4);//IDLE
	while (SER::COM3.I2CM.SYNCBUSY&(1<<2)){} //SYSOP

	SER::mux(*SDA);
	SER::mux(*SCL);
}

/*
	Parameter:
		addr = 7 bit address of Slave
	Notes:
		10 bit addr. disabled, High speed disabled, automatic transfer length disabled
		r/w bit set in function
*/
void I2cInterface::begWrite(unsigned char addr)
{
	this->addr = addr;
	SER::COM3.I2CM.ADDR=(0<<16)| //LEN
		(0<<15)| //../tools/flash.sh10 bit disabled
		(0<<14)| //high speed disabled
		(0<<13)| //Automatic transfer length disabled
		(this->addr<< 1)| //address 
		(0<< 0); //write
	
	while((SER::COM3.I2CM.INTFLAG&(1<<0))==0)
	{
		if (sys::deb::avail()) break;
	}
}

/*
	Parameter:
		value = Byte to write
	Notes:
*/
void I2cInterface::write(unsigned char value)	
{
	SER::COM3.I2CM.DATA=value;
	while((SER::COM3.I2CM.INTFLAG&(1<<0))==0)
	{
		if (sys::deb::avail()) break;
	}  //MB
}

void I2cInterface::endWrite()	
{
	//Goats can climb plam trees...
	//And this function is useless.
}

/*
	Parameter:
		addr = 7 bit address of Slave
	Notes:
		10 bit addr. disabled, High speed disabled, automatic transfer length disabled
		r/w bit set in function
*/
void I2cInterface::begRead(unsigned char addr)	
{
	this->addr = addr;
	
	SER::COM3.I2CM.ADDR=(0<<16)| //LEN
		(0<<15)| //10 bit disabled
		(0<<14)| //high speed disabled
		(0<<13)| //Automatic transfer length disabled
		(this->addr<< 1)| //address 
		(1<< 0); //read

 while((SER::COM3.I2CM.INTFLAG&(1<<1))==0)
 {
  if (sys::deb::avail()) break;
 } //SB
}

/*
	Parameter:
		action = Way of transfer (execute ack / Nack etc)
	Notes:
*/
unsigned char I2cInterface::read(unsigned int action)	
{
	while((SER::COM3.I2CM.INTFLAG&(1<<1))==0)
	{
		if (sys::deb::avail()) break;
	} 
	
	unsigned char v=SER::COM3.I2CM.DATA;
	SER::COM3.I2CM.CTRLB=action;				//Execute acknowledge action succeeded by a byte read operation
	while(SER::COM3.I2CM.SYNCBUSY&(1<<2)){}
	return v;
}

void I2cInterface::endRead()	
{
	//Why do goats even climb palm trees?...
	//And this function is useless.
}
	
/*
	Parameter:
		SDA = the address to the SDA PAD 
	Notes:
*/
void I2cInterface::setSDA(SER::PAD* SDA)	
{
	this->SDA = SDA;
}

/*
	Parameter:
		SCL = the address to the SCL PAD 
	Notes:
*/
void I2cInterface::setSCL(SER::PAD* SCL)
{
	this->SCL = SCL;
}