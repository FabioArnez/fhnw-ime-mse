//----------------------------
//stream output to stdout
//(c) H.Buchmann FHNW 2016
//----------------------------
#include "stream.h"
namespace sound
{
 Stream::Stream(unsigned fs,std::ostream& out)
 :Player(fs)
 ,out(out)
 {
 }

 void Stream::sample(double v)
 {
  union
  {
   Sample out;
   char   bytes[0];
  } s;

  s.out=0x7fff*v;
  out.write(s.bytes,sizeof(s));
 }

}
