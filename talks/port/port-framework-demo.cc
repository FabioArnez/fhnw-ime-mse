//----------------------
//port-framework-demo using sys/pin
//(c) H.Buchmann FHNW 2016
//----------------------
IMPLEMENTATION(port_demo,$Id$)
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/pin.h"
class App
{
 static App app;
 App();
 sys::Pin::Output led;
 void menu();
};


App App::app;


void App::menu()
{
 while(true)
 {
  sys::msg<<"(c)clear (s)et (t)oggle:";
  switch(sys::deb::get())
  {
   case 'c':
    led&=false;
   break;
   case 's':
    led|=true;
   break;
   case 't':
    led^=true;
   break;
  }
  sys::msg<<"\n";
 }
}

App::App()
:led(sys::Pin::PA17,false)
{
 sys::msg<<"Port Demo\n";
 menu();
}


