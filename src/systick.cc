//------------------------
//systick
//(c) H.Buchmann FHNW 2016
///[1] ARMv6-M Architecture Reference Manual. 
//    This documentation defines the ARMv6-M Microcontroller architecture
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//------------------------
IMPLEMENTATION(systick,$Id$)
#include "systick.h" //the public part

SysTick SysTick::sysTick_;

SysTick& SysTick::get()
{
 return sysTick_;
}

SysTick::SysTick()
:sys::Event(*this,"SysTick")
{
}

void SysTick::start(unsigned delta,Listener& li)
{
 
 this->li=&li;
 SYST.RVR=(delta<(1<<24))?delta:((1<<24)-1);
 SYST.CSR=(1<<0) | //start
          (1<<1) | //enable interrupt
             0;
}

void SysTick::sysTick() //the trap call back in foreground
{
 sysTick_.signal(); 
}

void SysTick::onEvent(Event&) //the call back in background
{
 if (li) li->onTick();
}
