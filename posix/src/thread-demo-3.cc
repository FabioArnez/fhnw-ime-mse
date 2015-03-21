//---------------------------
//thread-demo-3
//(c) H.Buchmann FHNW 2015
// make it with
//    g++ -std=c++11 -llpthread ../src/thread-demo-1.cc -o thread-demo-1
//---------------------------
#include <iostream>
#include "thread.h"
/*------------------------------- objectives
 - using templates
 - java like: the interface Runnable
*/

class Run:public Thread,
          private Thread::Runnable
{
 public:
  Run(const char*const id);
 private:
  const char*const id;
//implementation Thread::Runnable
  void run();
};

Run::Run(const char*const id)
:Thread((Thread::Runnable&)*this)
,id(id)
{
}

void Run::run()
{
 while(true)
 {
  std::cerr<<id<<"\n";
 }
}

int main(int argc,char** args)
{
 Run run1("run1"); 
 Run run2("run2"); 
 
 run1.start();
 run2.start();
//TODO check cpu usage (sysmonitor)
 run1.join();
 run2.join();
 return 0;
}
