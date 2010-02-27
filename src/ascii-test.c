/*---------------------
 ascii-test
 (c) H.Buchmann FHNW 2009
 $Id$
-----------------------*/
#include "io/ascii.h"
#include "sys/screen.h"

int main()
{
//  for(unsigned i=0;i<25;++i)
//  {
//   ascii_printf(Screen,"--line %d %s\n",i,fill);
//  }
 char ch='0';
 for(unsigned i=0;i<25;++i)
 {
  for(unsigned k=0;k<80;++k)
  {
   ascii_put(Screen,ch);
  }
  if (ch=='9') ch='0';
     else      ++ch;
 }
 ascii_string(Screen,"last");
}

