#pragma once
//--------------------------
//coroutine test
//(c) H.Buchmann FHNW 2015
//--------------------------
INTERFACE(sys_coroutine,$Id$)
#include "sys/msg.h"
namespace sys
{
 class Coroutine
 {
  public:
   static void transfer(Coroutine& to);

  protected:
   Coroutine(unsigned char ws[],unsigned size);
   virtual void run()=0;

  private:
   struct Status
   {
    Coroutine* reg0;
    unsigned reg1_12[12];
    void (*lr)(Coroutine*);  
   };
   Status* s;
   Coroutine():s(0){}
   static void start(Coroutine*);
   static void transfer(Status** from,Status* to) __attribute__((naked));
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
