//-----------------------------
//sys-tick an event driven driver
//(c) H.Buchmann FHNW 2015
//-----------------------------
IMPLEMENTATION(sys_tick,$Id$)
#include "sys-tick-4.h"
#include "sys/soc.h"
#include "sys/reg/scs.h"  //for SYSTICK
#include "sys/deb/deb.h"
#include "sys/msg.h"
SysTick SysTick::sysTick; //the instance



void SysTick::listen(unsigned time,unsigned clockSourceBit,Listener& li)
{
 sys::reg::SCS.SYSTICK.CSR=0; //disable
 sysTick.li=&li;
 sys::reg::SCS.SYSTICK.RVR=time; //TODO check 0<time<2^24
 sys::reg::SCS.SYSTICK.CSR=(1<<0) | //enable
                           (1<<1) | //enable interrupt
	           clockSourceBit |
			       0;
}

void SysTick::onTick()    //the handler static
{
 sysTick.signal();        //called in interrupt foreground
}

SysTick::SysTick()
:sys::Event(this)
{
 sys::SOC::install(sys::SOC::SYSTICK,onTick);
 sys::SOC::arm(sys::SOC::SYSTICK);
}

void SysTick::onEvent(sys::Event&)
{
 if (li) li->onTick();  //call in normal thread background
}

