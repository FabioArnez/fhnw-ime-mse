//-----------------------
//adc-random
//(c) H.Buchmann FHNW 2016
//-----------------------
IMPLEMENTATION(adc_random,$Id$)
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/reg/adc.h"
#include "sys/reg/gclk.h"
#include "sys/reg/pm.h"
#include "sys/reg/port.h"
#include "sys/nvm.h"

class App
{
 static App app;
 App();
 void init();
 unsigned read();
};

App App::app;

void App::init()
{
 sys::reg::PM.APBCMASK|=(1<<16); //normally already enabled
 sys::reg::PORT::mux(sys::reg::PORT::PA02,sys::reg::PORT::F_B); //Arduino Pin A0

 sys::reg::GCLK.gen2dev(sys::reg::GCLK::G8,sys::reg::GCLK::ADC);
 sys::reg::GCLK.gendiv(sys::reg::GCLK::G8,0x1);    //8MHz
 sys::reg::GCLK.src2gen(sys::reg::GCLK::OSC8M,sys::reg::GCLK::G8,(1<<0));

 sys::reg::ADC.CTRLA=1;
 while(sys::reg::ADC.CTRLA==1){}
//enable
 sys::reg::ADC.CTRLA=(1<<1); //enable 
}

unsigned App::read()
{
 sys::reg::ADC.SWTRIG=(1<<1);
 while((sys::reg::ADC.INTFLAG&1)==0){}
 return sys::reg::ADC.RESULT;
}


App::App()
{
 init();
 while(true)
 {
  sys::msg<<"ADC-Random\n"
            " 0:regs\n"
	    " 1:trigger\n"
	    " 2:read\n";

  switch(sys::deb::get())
  {
   case '0':
    sys::msg<<"ADC\n";
    sys::reg::ADC.regs();
    sys::msg<<"NVM\n";
    sys::NVM::Calib.regs();
   break;
   case '1':
    sys::reg::ADC.SWTRIG=(1<<1);
   break;
   case '2':
    sys::msg<<read()<<"\n";
   break;
  }
 }
}
