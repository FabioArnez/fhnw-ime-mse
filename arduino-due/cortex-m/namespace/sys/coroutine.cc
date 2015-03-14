//--------------------------
//coroutine
//(c) H.Buchmann FHNW 2015
//--------------------------
IMPLEMENTATION(sys_coroutine,$Id$)
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
 
 void Coroutine::transfer(Status** from,Status* to)
 {
 asm volatile
 (
  "@------------------------------------- transfer\n" 
  "     push {r0-r12,lr}\n"
  "	str sp,[r0]\n"
  "	mov sp,r1\n"
  "	pop {r0-r12,pc}\n"
   :
   :
  );
 }
}
