//----------------------------
//sine.h a sine wave generator
//(c) H.Buchmann FHNW 2016
//----------------------------
#include "sine.h"
namespace sound
{
 Sine::Sine(Player& p,double f_Hz,double dur_Sec)
 :Generator(p)
 {
  double sin_,cos_;
  sincos(2*PI*f_Hz/p.fs,&sin_,&cos_);            //calculated only once
  double x0=0.875;
  double y0=0.0;
  for(double t=0;t<=dur_Sec;t+=dt)
  {   
   p.sample(x0);
   double x1=x0*cos_ - y0*sin_;               //next sample 
   double y1=x0*sin_ + y0*cos_;
   x0=x1;
   y0=y1;
  }
 }

}
