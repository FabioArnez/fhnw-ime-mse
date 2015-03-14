#pragma once
//--------------------------
//coroutine test
//(c) H.Buchmann FHNW 2015
//--------------------------
#include "sys/msg.h"
namespace co
{
 struct Coroutine
 {
  typedef void (*Run)(Coroutine*);
  struct Status
  {
   Coroutine* reg0;
   unsigned reg1_12[12];
   Run lr;  
  };
  Status* s;
  Coroutine(unsigned char ws[],unsigned size);
  Coroutine():s(0){}
  virtual void run()=0;
  static void start(Coroutine*);
  static void transfer(Coroutine& to);
  static void transfer(Status** from,Status* to);

  static Coroutine* cur;
  struct Main;
 };

 struct Coroutine::Main:Coroutine
 {
  void run(){}
  static Main main;
  Main()
  {
   sys::msg<<"Main="<<(void*)cur<<"\n";  
  }
 };
}
