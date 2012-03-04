#pragma once
/*---------------------------
 lcd
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
extern void lcd_init();
typedef unsigned short Color;
/* color scheme 5 6 5
bit  0.. 4 RED
bit  5..10 GREEN
bit 11..15 BLUE
*/

extern void lcd_pixel(unsigned x,unsigned y, Color c);
  
/* TODO more graphic primitives */

extern unsigned lcd_char(unsigned x,unsigned y,Color c,char ch);
/* returns witdh of character in pixel */
