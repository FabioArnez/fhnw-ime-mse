//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2015
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
/*----------------------------------- objectives
 all in once
 Demo is an Event
      is an Event::Listener
*/

class Demo3:sys::Event
           ,sys::Event::Listener
{
 static Demo3 demo;
//----------------------- implementation Event::Listener
 void onEvent(sys::Event&);
 Demo3();
};

Demo3 Demo3::demo;

void Demo3::onEvent(sys::Event&)
{
 if (sys::deb::avail())
    {
     sys::msg<<"key '"<<sys::deb::get()<<"' pressed\n";
    }
 signal();      //retrigger
}

Demo3::Demo3()
:sys::Event(this) //
{
 sys::msg<<"\n"__FILE__"\n";
 signal();      //trigger onEvent
 sys::Event::loop();  //must be last call
}
