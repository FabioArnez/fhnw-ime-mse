//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2015
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys-tick-4.h"
/*----------------------------------- objectives
 - the driver SysTick
 - Demo4 the client of the driver
*/

class Demo4:SysTick::Listener
{
 static Demo4 demo;
 unsigned tick=0;
//----------------------- implementation SysTick::Listener
 void onTick();
 Demo4();
 
};

Demo4 Demo4::demo;

void Demo4::onTick()  //called in normal thread background
{
 sys::msg<<"tick "<<(tick++)<<"\n";
}

Demo4::Demo4()
{
 sys::msg<<"\n" __FILE__ "\n";
 SysTick::listenFast((1<<24)-1,*this);
 sys::Event::loop();  //must be last call
}
