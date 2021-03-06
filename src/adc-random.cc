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
 void sample(unsigned cnt);
 void show();
 unsigned count=0;
 static const unsigned HISTO=1<<12;
 unsigned short histo[HISTO];
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
 sys::reg::ADC.CALIB=(sys::NVM::Calib.ADC_BIASCAL<<8)|
                     (sys::NVM::Calib.ADC_LINEARITY);
		     
 sys::reg::ADC.CTRLA=(1<<1); //enable 
}

unsigned App::read()
{
 sys::reg::ADC.SWTRIG=(1<<1);
 while((sys::reg::ADC.INTFLAG&1)==0){}
 return sys::reg::ADC.RESULT;
}


void App::sample(unsigned cnt)
{
 sys::msg<<"sampling...";
 count=cnt;
 for(unsigned i=0;i<cnt;++i)
 {
  ++histo[read()&(HISTO-1)];
 }
 sys::msg<<"done\n";
}

void App::show()
{
 for(unsigned i=0;i<HISTO;++i)
 {
  unsigned short v=histo[i];
  if (v) 
     {
      sys::msg<<i<<"\t"<<v<<"\n";
     }
 }
}

App::App()
{
 for(auto& v:histo)v=0;
 init();
 while(true)
 {
  sys::msg<<"ADC-Random\n"
            " 0:regs\n"
	    " 1:trigger\n"
	    " 2:read\n"
	    " 3:sample\n";
	    
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
   case '3':
    sample(1<<22);
    show();
   break;
  }
 }
}
