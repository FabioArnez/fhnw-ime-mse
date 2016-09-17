//------------------------
//cpu-demo for arduino
//(c) H.Buchmann FHNW 2016
//------------------------
IMPLEMENTATION(cpu_demo,$Id$)
#include "sys/msg.h"
#include "cpu-demo.h"
#include "io/ascii/write.h"
class App
{
 static App app;
 App();
};

App App::app;

App::App()
{
 OpsTest<io::ascii::Writer> opsTest(sys::msg);
}
