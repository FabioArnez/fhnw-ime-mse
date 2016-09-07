#pragma once
//----------------------------
//stream output to stdout
//(c) H.Buchmann FHNW 2016
//----------------------------
#include "samples.h"
#include <iostream>
namespace sound
{
//a Player writing the samples to an output stream
 class Stream:public Player    
 {
  public:
   Stream(unsigned fs,std::ostream& out);
   void sample(double v);

  private:
   typedef short int Sample;  
   std::ostream& out;
 };
}
