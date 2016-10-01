IMPLEMENTATION(I2cDemoApp,$Id$)
//#include "sys/msg.h"
//#include "sys/deb/deb.h"
//#include "tempSensor.h"
/*
 Arduino Pins:

    
*/
class I2cDemoApp
{
	private:
 	static I2cDemoApp i2cDemoApp;
	I2cDemoApp();
	~I2cDemoApp();
};

I2cDemoApp I2cDemoApp::i2cDemoApp;

I2cDemoApp::I2cDemoApp()
{
//	sys::msg<<"\n"<<__PRETTY_FUNCTION__<<"\n";
}

 I2cDemoApp::~I2cDemoApp()
 {
 // sys::msg<<__PRETTY_FUNCTION__<<"\n";
 }
 
