//--------------------------
//coroutine test
//(c) H.Buchmann FHNW 2015
//--------------------------
#include "sys/coroutine.h"

namespace sys
{
 Coroutine::Main Coroutine::Main::main;

 Coroutine* Coroutine::cur=&Coroutine::Main::main;

 void Coroutine::start(Coroutine* c)
 {
  c->run();
 }

 Coroutine::Coroutine(unsigned char ws[],unsigned size)
 :s((Status*)(ws+size-sizeof(Status)))
 {
  s->reg0=this;
  for(unsigned i=0;i<12;++i) s->reg1_12[i]=i;
  s->lr=start;
 }

 void Coroutine::transfer(Coroutine& to)
 {
  Coroutine* c=cur;
  cur=&to;
  transfer(&(c->s),cur->s);
 }
}
