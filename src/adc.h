#pragma once
//----------------------------
//adc.h the driver event driven
//(c) H.Buchmann FHNW 2016
//----------------------------
INTERFACE(adc,$Id$)
#include "sys/reg/adc.h" //the hardware 
#include "sys/soc.h"     //the system on chip
#include "sys/event.h"   //the framework

class ADC
{
 public:
  struct Listener
  {
   virtual void onValue(unsigned v)=0; //the call back
  };
  
  static void start(Listener& li);
  static void trigger();
  
  static void onADC(); //the interrupt hander
 private:
  static ADC adc; //the singelton
  ADC();          //private constructor singelton
  Listener*  li=0;
};
