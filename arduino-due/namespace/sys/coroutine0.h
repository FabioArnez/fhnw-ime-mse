#pragma once
//------------------------
//coroutine0
//(c) H.Buchmann FHNW 2015
//------------------------
INTERFACE(sys_coroutine0,$Id$)
namespace sys
{
 class Coroutine0
 {
  protected:
   virtual void run()=0;

   Coroutine0();
   Coroutine0(unsigned workspace[],unsigned size);
   struct Status;
   Status* status=0;
   static void callInit(Coroutine0* c){c->run();}
//done in assembler

   static void transfer(Status** from,Status* to);
  private:   
   static Status* init(Coroutine0* c,
                       unsigned*   top, //of stack
		       void (*call)(Coroutine0*));       
 };

 struct Coroutine0::Status
 {
  struct Init
  {
   Coroutine0* c0;
   unsigned reg1_12[12];
   void (*init)(Coroutine0*);
  };
  union
  {
   struct
   {
    unsigned reg0_12[13]; 
    unsigned lr;      //the link register
   } run;
   Init init;
  };
  void show(const char msg[]);
  void show() __attribute__((noinline));
 };

}

