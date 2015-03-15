//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2015
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
/*----------------------------------- objectives
 -introducing Event
 -introducing Event::Listener
 -signal()
 -onEvent(...)
*/

class Demo1:sys::Event::Listener
{
 static Demo1 demo;
 sys::Event event;
//----------------------- implementation Event::Listener
 void onEvent(sys::Event&);
 Demo1();
};

Demo1 Demo1::demo;

void Demo1::onEvent(sys::Event&)
{
 sys::msg<<"onEvent\n";
// event.signal(); //called via sys::Event::loop()
}

Demo1::Demo1()
:event(this) //
{
 sys::msg<<"\n"__FILE__"\n";
 event.signal();
 sys::Event::loop();  //must be last call
}
