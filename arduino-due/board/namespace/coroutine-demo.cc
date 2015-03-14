//--------------------------
//coroutine-demo
//(c) H.Buchmann FHNW 2015
//--------------------------
IMPLEMENTATION(coroutine_demo,$Id$)
#include "sys/coroutine.h"
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/soc.h"

class Coroutine:public sys::Coroutine
{
 public:
  Coroutine(const char name[],Coroutine& next)
  :sys::Coroutine(workspace,WORKSPACE)
  ,name(name)
  ,next(next)
  {}
  
 private:
  const char*const name;
  static const unsigned WORKSPACE=0x400;
  unsigned char workspace[WORKSPACE];
  sys::Coroutine& next;
  void run();
};


void Coroutine::run()
{
 while(true)
 {
  sys::Coroutine::transfer(next);
  sys::msg<<"--------------- "<<name<<"\n";
 }
}

class Demo
{
 Coroutine c0;
 Coroutine c1;
 Coroutine c2;
 Demo();
 static Demo demo;
};

Demo Demo::demo;

Demo::Demo()
:c0("c0",c1)
,c1("c1",c2)
,c2("c2",c0)
{
 sys::deb::out("\n\n\nCoroutine Demo\n");
 sys::Coroutine::transfer(c0);
 sys::msg<<"-------done\n";
}
