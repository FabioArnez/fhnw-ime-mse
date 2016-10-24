//----------------------
//gdb-demo
//(c) H.Buchmann FHNW 2016
//----------------------
IMPLEMENTATION(gdb_demo,$Id$)
#include "sys/msg.h"
class App
{
 static App app;
 App();
 void method();
 unsigned minor=0; //initial value
 unsigned major=0;
};

App App::app;


void App::method()
{
 sys::msg<<'x';
 ++minor;
 if (minor==0x1000)
    {
     ++major;
     minor=0;
    }
}

App::App()
{
 while(true)
 {
  method();
 }
}


