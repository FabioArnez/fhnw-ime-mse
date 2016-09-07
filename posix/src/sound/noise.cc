//----------------------------
//sine.h a sine wave generator
//(c) H.Buchmann FHNW 2016
//----------------------------
#include "noise.h"
#include <random>
namespace sound
{
 Noise::Noise(Player& p,double dur_Sec)
 :Generator(p)
 {
  std::random_device dev;  //too slow
//  std::default_random_engine dev;
  std::uniform_real_distribution<double> random(-0.5,0.5);
  for(double t=0;t<dur_Sec;t+=dt)
  {
   p.sample(random(dev));
  }
 }
}
