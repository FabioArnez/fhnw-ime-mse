//------------------------
//co-demo
//(c) H.Buchmann FHNW 2015
//------------------------
#include "sys/msg.h"
#include "co/coroutine.h"
#include "sys/deb/deb.h"

class Co:public co::Coroutine
{
 public:
  Co(const char id[],Co* next)
  :Coroutine(ws,WS),id(id),next(next){}
 private:
  static const unsigned WS=0x400;
  unsigned char ws[WS];
  const char*const id;
  Co*const next;
  void run();
};

void Co::run()
{
 while(true)
 {
  sys::msg<<id<<"\t"<<this<<"\n";
  co::Coroutine::transfer(*next);
 }
}

class Demo
{
 static Demo demo;
 Co c1;
 Co c2;
 Co c3;
 Demo();
};


Demo Demo::demo;

Demo::Demo()
:c1("c1",&c2)
,c2("c2",&c3)
,c3("c3",&c1)
{
 sys::msg<<"Co-Demo\n";
 co::Coroutine::transfer(c1);
 sys::msg<<"done\n";
}
