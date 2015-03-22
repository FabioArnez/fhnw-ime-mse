//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2015
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys-tick-4.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
#include "sys/led.h"
#include "sys/soc.h"
#include "sys/reg/scs.h"
/*----------------------------------- objectives
*/

class Demo4:SysTick::Listener
           ,sys::Event,sys::Event::Listener
{
 static Demo4 demo;
 static const unsigned COUNT=(1<<24)-1;
 static const unsigned DELTA=1 ;
//----------------------- implementation SysTick::Listener
 void onTick();
 void onEvent(sys::Event&);
 static void onHardFault();
 Demo4();
 
};

Demo4 Demo4::demo;

void Demo4::onTick()  //called in normal thread background
{
 sys::LED::tgl(sys::LED::RX);
 static unsigned tick=0;
 tick++;
 if (tick==(1<<DELTA))
    {
     tick=0;
    }
}

void Demo4::onEvent(sys::Event&)
{
 if (sys::deb::avail())
    {
     sys::deb::get();
     sys::LED::tgl(sys::LED::TX);
    }
 signal();
}

void Demo4::onHardFault()
{
 volatile unsigned* fa=(unsigned*) __builtin_return_address(0);
 unsigned lr=sys::SOC::lr();
 unsigned cfsr=sys::reg::SCS.SCB.CFSR;
 unsigned bfar=sys::reg::SCS.SCB.BFAR;
 sys::deb::hex(lr);sys::deb::newln();
 sys::deb::hex(cfsr);sys::deb::newln();
 sys::deb::hex(bfar);
 while(true){}
}

Demo4::Demo4()
:sys::Event(this)
{
 sys::msg<<"\n"__FILE__"\n";
 sys::SOC::install(sys::SOC::HARD_FAULT,onHardFault);
 SysTick::listenFast(COUNT>>DELTA,*this);
 signal();
 
 sys::Event::loop();  //must be last call
}
