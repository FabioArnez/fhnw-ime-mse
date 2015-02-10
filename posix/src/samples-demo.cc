//----------------------
//samples-demo
//(c) H.Buchmann FHNW 2015
// ./samples-demo | play -e signed-integer -q -r 44000 -b 16 -t raw -
//----------------------
#include "sound/alsa.h"
#include "sound/samples.h"
#include "tim.h"
#include <thread>
#include <chrono>
#include <iostream>

class Wait:public sound::Player
{
 public:
  Wait(sound::Player& p);
  ~Wait();
  void sample(double v);
 private:
  unsigned cnt=0;
  Player& p; //the delegate
};

Wait::Wait(sound::Player& p)
:Player(p.fs)
,p(p)
{
}

Wait::~Wait()
{
 std::cerr<<"~Wait "<<cnt<<"\n";
}

void Wait::sample(double v)
{
 ++cnt;
#if 0
 for(unsigned i=0;i<4096;++i)
 {
//  volatile unsigned c=i;
 }
#endif
// p.sample(v);
}

int main(int argc,char** args)
{
 Time t;
 sound::Alsa   pl0(44000,4096);
// Stream pl0(44000,std::cout);
 Wait pl(pl0);
 sound::Noise(pl0,2);
 return 0;
}
