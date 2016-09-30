//--------------------
//i2c-demo
//(c) H.Buchmann FHNW 2016
//see [1] Datasheet SHT10, SHT11, SHT15
//        Sensirion_Humidity_and_Temperature_Sensors_SHT21_Datasheet_V4-1.pdf
//--------------------
IMPLEMENTATION(i2c_demo,$Id$)
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/reg/sercom.h"
#include "sys/reg/gclk.h"
#include "sys/soc.h"
#include "sys/pin.h"
/*
 Arduino	Pin
 16 SDA         PA22  SERCOM3/PAD[0]
 17 SCL         PA23  SERCOM3/PAD[1]
*/

class Demo
{
 static Demo demo;
 static const unsigned ADDR=0b100'0000;
 Demo();
 void init();
 void begWrite();
 void write(unsigned char v);
 void endWrite();
 void begRead();
 unsigned char read(unsigned action);
 void endRead();
 void temperature();
 void user();
 void id();
 void step();
};

Demo Demo::demo;

void Demo::init()
{
 static const sys::reg::SER::PAD SDA={sys::reg::SER::PAD::P0,
                                      {sys::reg::PORT::PA22,
				       sys::reg::PORT::F_C}}; 

 static const sys::reg::SER::PAD SCL={sys::reg::SER::PAD::P1,
                                      {sys::reg::PORT::PA23,
				       sys::reg::PORT::F_C}}; 
 
 sys::SOC::clkOn(sys::SOC::SERCOM3);
 sys::reg::GCLK.src2gen(sys::reg::GCLK::OSC8M,sys::reg::GCLK::G8,(1<<0));
 sys::reg::GCLK.gen2dev(sys::reg::GCLK::G8,sys::reg::GCLK::SERCOM3_CORE); //8MHz


//reset
 sys::reg::SER::COM3.I2CM.CTRLA=1; 
 while(sys::reg::SER::COM3.I2CM.CTRLA&1){}

 sys::reg::SER::COM3.I2CM.CTRLA=(0x5<<2); //I2CM Mode

/* Baudrate
 f_scl= f_gclk/(2*(5+BAUD)+f_gclk*T_rise)
 T_rise=15nS
 BAUD=15
*/
 sys::reg::SER::COM3.I2CM.BAUD=45; //80 kHz

 
 sys::reg::SER::COM3.I2CM.CTRLA|=(1<<1);           //ENABLE
 while (sys::reg::SER::COM3.I2CM.SYNCBUSY&(1<<1)){}
 
 sys::reg::SER::COM3.I2CM.STATUS|=(1<<4);//IDLE
 while (sys::reg::SER::COM3.I2CM.SYNCBUSY&(1<<2)){} //SYSOP

 sys::reg::SER::mux(SDA);
 sys::reg::SER::mux(SCL);
}

void Demo::step()
{
 sys::deb::pressAnyKey("step");
}

void Demo::begWrite()
{
 sys::reg::SER::COM3.I2CM.ADDR=(0<<16)| //LEN
                               (0<<15)| //10 bit disabled
			       (0<<14)| //high speed disabled
			       (0<<13)| //Automatic transfer length disabled
			    (ADDR<< 1)| //address 
			       (0<< 0); //write
 while((sys::reg::SER::COM3.I2CM.INTFLAG&(1<<0))==0)
 {
  if (sys::deb::avail()) break;
 }
}

void Demo::endWrite()
{
}

void Demo::write(unsigned char v)
{
 sys::reg::SER::COM3.I2CM.DATA=v;
 while((sys::reg::SER::COM3.I2CM.INTFLAG&(1<<0))==0)
 {
  if (sys::deb::avail()) break;
 }  //MB
}

void Demo::begRead()
{
 sys::reg::SER::COM3.I2CM.ADDR=(0<<16)| //LEN
                               (0<<15)| //10 bit disabled
			       (0<<14)| //high speed disabled
			       (0<<13)| //Automatic transfer length disabled
			    (ADDR<< 1)| //address 
			       (1<< 0); //read
 while((sys::reg::SER::COM3.I2CM.INTFLAG&(1<<1))==0)
 {
  if (sys::deb::avail()) break;
 } //SB
}

unsigned char Demo::read(unsigned action)
{
 while((sys::reg::SER::COM3.I2CM.INTFLAG&(1<<1))==0)
 {
  if (sys::deb::avail()) break;
 } 
 unsigned char v=sys::reg::SER::COM3.I2CM.DATA;
 sys::reg::SER::COM3.I2CM.CTRLB=action;
 while(sys::reg::SER::COM3.I2CM.SYNCBUSY&(1<<2)){}
 return v;
}

void Demo::temperature()
{
 begWrite();
 write(0b1110'0011); //T hold master
 begRead();
 unsigned char data[3];
 data[0]=read(0x2<<16);
 data[1]=read(0x2<<16);
 data[2]=read((0x3<<16)|
              (1<<18)
             );
 sys::msg.dump(data,3);
}

void Demo::user()
{
 begWrite();
 write(0b1110'0111);
 begRead();
 unsigned char in=read((0x3<<16)|
                         (1<<18));
 sys::deb::hex("user=",in);
}

void Demo::id()
{
 sys::reg::SER::COM3.I2CM.CTRLB=0;
 begWrite();
 write(0b1111'1010);
 write(0b0000'1111);
 begRead();
 unsigned char resp[8];
 for(unsigned i=0;i<8;++i)
 {
  resp[i]=read((i<7)?(0x2<<16):(0x3<<16)|(1<<18));
 }
 
 sys::msg.dump(resp,8);
}

Demo::Demo()
{
 init();
 while(true)
 {
  sys::msg<<"I2C-Demo\n"
	    " 0:regs\n"
	    " 1:temperature\n"
	    " 2:user\n"
	    " 3:id\n";
  
  switch(sys::deb::get())
  {
   case '0':
    sys::reg::SER::COM3.I2CM.regs();
   break;
   case '1':
    temperature();
   break;
   case '2':
    user();
   break;
   case '3':
    id();
   break;
  }	    
 }
}
