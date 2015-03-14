//------------------------
//coroutine
//(c) H.Buchmann FHNW 2015
//------------------------
IMPLEMENTATION(sys_coroutine,$Id$)
#include "sys/coroutine.h"
namespace sys
{
 Coroutine::Main Coroutine::Main::main;
 volatile Coroutine* Coroutine::cur=&Coroutine::Main::main;

 void Coroutine::transfer(Coroutine& to)
 {
  sys::msg<<"transfer "<<(void*)cur<<" -> "<<(void*)&to<<"\n";
  cur->status->show("cur");
  to.status->show("to");
  Coroutine* c=cur;
  cur=&to;
  Coroutine0::transfer(&(c->status),cur->status);
 }
}

