#pragma once
//------------------------
//coroutine
//(c) H.Buchmann FHNW 2015
//------------------------
INTERFACE(sys_coroutine,$Id$)
#include "sys/msg.h"
#include "sys/coroutine0.h"
namespace sys
{
 class Coroutine:public Coroutine0
 {
  public:
   Coroutine(unsigned workspace[],unsigned size)
   :Coroutine0(workspace,size)
   {
   }
   
   static void transfer(Coroutine& to);
    
  private:
   Coroutine(){}
   struct Main;
   static Main main;
   static volatile Coroutine* cur;  //TODO: check if volatile is really necessary
 };
 
 struct Coroutine::Main:Coroutine
 {
  void run(){}
  static Main main;
  Main()
  {
//   cur=this;
   sys::msg<<"Main "<<(volatile void*)cur<<"\n";
  }
 };
 
}
