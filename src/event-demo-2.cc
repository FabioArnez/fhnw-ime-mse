//-------------------------
//event-demo
//(c) H.Buchmann FHNW 2016
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
/*----------------------------------- objectives
 - polling
*/

class App:sys::Event::Listener
{
 static App app;
 sys::Event event;
//----------------------- implementation Event::Listener
 void onEvent(sys::Event&);
 App();
};

App App::app;

void App::onEvent(sys::Event&)
{
 event.signal();
 if (!sys::deb::avail()) return;
 sys::msg<<"you pressed '"<<sys::deb::get()<<"'\n";
}

App::App()
:event(*this,"App")
{
 sys::msg<<"\n" __FILE__ "\n";
 event.signal();
 sys::Event::loop();  //must be last call
}
