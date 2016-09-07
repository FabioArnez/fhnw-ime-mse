#pragma once
//----------------------------
//noise.h a white nois generator
//(c) H.Buchmann FHNW 2016
//----------------------------
#include "samples.h"
namespace sound
{
 class Noise:Generator
 {
  public:
   Noise(Player&,double dur_Sec);
 };
}
