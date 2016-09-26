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

class App
{
 static App app;
 App();
 void init();
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

App::App()
{
 init();
 while(true)
 {
  sys::msg<<"ADC-Random\n"
            " 0:regs\n"
	    " 1:trigger\n";
	    
  switch(sys::deb::get())
  {
   case '0':
    sys::reg::ADC.regs();
   break;
   case '1':
    sys::reg::ADC.SWTRIG=(1<<1);
   break;
  }
 }
}
