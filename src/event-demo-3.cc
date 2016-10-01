//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2016
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
/*----------------------------------- objectives
 all in once
 App is an Event
      is an Event::Listener
*/

class App:sys::Event
         ,sys::Event::Listener
{
 static App app;
//----------------------- implementation Event::Listener
 void onEvent(sys::Event&);
 App();
};

App App::app;

void App::onEvent(sys::Event&)
{
 signal();
 if (!sys::deb::avail()) return;
 sys::msg<<"you pressed '"<<sys::deb::get()<<"'\n";
}

App::App()
:sys::Event(*this,"App")
{
 sys::msg<<"\n" __FILE__ "\n";
 signal();
 sys::Event::loop();  //must be last call
}
