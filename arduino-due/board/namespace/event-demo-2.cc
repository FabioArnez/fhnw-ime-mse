//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2015
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
/*----------------------------------- objectives
 polling
*/

class Demo2:sys::Event::Listener
{
 static Demo2 demo;
 sys::Event event;
//----------------------- implementation Event::Listener
 void onEvent(sys::Event&);
 Demo2();
};

Demo2 Demo2::demo;

void Demo2::onEvent(sys::Event&)
{
 if (sys::deb::avail())
    {
     sys::msg<<"key '"<<sys::deb::get()<<"' pressed\n";
    }
 event.signal();      //retrigger
}

Demo2::Demo2()
:event(this) //
{
 sys::msg<<"\n"__FILE__"\n";
 event.signal();      //trigger onEvent
 sys::Event::loop();  //must be last call
}
