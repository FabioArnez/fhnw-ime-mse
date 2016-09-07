#pragma once
//----------------------------
//sine.h a sine wave generator
//(c) H.Buchmann FHNW 2016
//----------------------------
#include "samples.h"
namespace sound
{
 class Sine:Generator //a very simple Player
 {
  public:
   Sine(Player&,double f_Hz,double dur_Sec);
  private:
   static constexpr double PI=4*std::atan(1.0);
 };
}
