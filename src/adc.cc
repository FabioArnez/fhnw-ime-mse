//----------------------------
//adc.h the driver event driven
//(c) H.Buchmann FHNW 2016
//[1] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//    ARM Cortex-M0+ based Embedded Flash Microcontroller
//    Atmel-42181-SAM-D21_Datasheet.pdf
//----------------------------
IMPLEMENTATION(adc,$Id$)
#include "adc.h"
#include "sys/reg/pm.h"
#include "sys/reg/port.h"
#include "sys/reg/gclk.h"
#include "sys/soc.h"

ADC ADC::adc;  //call constructor

ADC::ADC()
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
 sys::reg::ADC.INTENSET=1;   //RESRDY result ready
 sys::SOC::arm(sys::SOC::ADC);  
}

void ADC::start(Listener& li) //static method
{
 adc.li=&li;
}

void ADC::trigger()  //static method
{
 sys::reg::ADC.SWTRIG=(1<<1);
}

void ADC::onADC() //the interrupt handler
{
 unsigned res=sys::reg::ADC.RESULT;
 if (adc.li) adc.li->onValue(res);
}
