/*---------------------------
  lcd-demo
  (c) H.Buchmann FHNW 2012
  $Id$
-----------------------------*/
#include "io/lcd.h"
int main()
{
 lcd_init();
 for(unsigned x=0;x<100;++x)
 {
  lcd_pixel(x,x,0xffff);
 }
 unsigned x=0;
 for(char ch=' ';ch<0x80;++ch)
 {
  x+=lcd_char(x,0,0xffff,ch);;
 }
 return 0;
}
