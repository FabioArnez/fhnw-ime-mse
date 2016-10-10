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
#include "tempSensor.h"

using namespace sys::reg;

/*
 Arduino	Pin
 16 SDA         PA22  SERCOM3/SER::PAD[0]
 17 SCL         PA23  SERCOM3/SER::PAD[1]
*/

class Demo
{
 static Demo demo;

 Demo();

};

Demo Demo::demo;

Demo::Demo()
{
	sys::msg<<"start";
	const unsigned char addr = 0b01001001;
	static SER::PAD SDA={SER::PAD::P0, {PORT::PA22, PORT::F_C}}; 
	static SER::PAD SCL={SER::PAD::P1, {PORT::PA23, PORT::F_C}}; 

	I2cInterface i2c(&SDA,&SCL);
	TempSensor lm75(addr);
	int* ptr = 0x42000800;
	sys::msg<<ptr;
	

	while(true)
	{
		sys::msg<<"I2C-Demo\n0:regs\n1:temperature\n";

		switch(sys::deb::get())
		{
		case '0':
			sys::reg::SER::COM3.I2CM.regs();
			break;
		case '1':
			lm75.updateTemperature(&i2c);
			sys::msg<<"temp: ";
			short data;
			data = lm75.getTemperature();
			sys::deb::out("temp: ",data);
			break;
		}	    
 	}
}
