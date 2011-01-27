/*------------------------------
  minimal stdio
  (c) H.Buchmann FHNW 2011
  demonstrates -variable parameters
  TODO more specifiers 
  $Id$
  ------------------------------*/
#include "stdio.h" 
#include "io/ascii.h"
#include "stdout.h"

void printf(const char* fmt,...)  
{
 va_list lst;
 va_start(lst,fmt);
 unsigned i=0; /* index in fmt */ 
 unsigned status=0;
 for(;;)
 {
  char ch=fmt[i++];
  if (ch=='\0') break;
  switch(status)
  {
   case 0: /* normal char */
    if (ch=='%'){status=1;break;}
    ascii_put(stdout,ch);
   break;
   case 1: /* what kind of output */
    switch(ch)
    {
     case 'd': /* decimal */
      ascii_unsigned_dec(stdout,va_arg(lst,unsigned));
     break;
     case 'x': /* hex */
      ascii_unsigned_hex(stdout,va_arg(lst,unsigned));
     break;
     case 's':
      ascii_string(stdout,va_arg(lst,char*)); 
     break;
     case '%':
      ascii_put(stdout,'%');
     break;
     default:
      ascii_put(stdout,'?');
     break;
    }
   status=0;
   break;
  }
 }
 va_end(lst); 
}
