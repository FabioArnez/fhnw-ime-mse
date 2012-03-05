#pragma once
/*------------------------------------
  font.h
  (c) H.Buchmann FHNW 2012
  $Id$
  generated with font/Font.java
--------------------------------------*/
typedef struct
{
 unsigned wi_pix; /* width in pixel  */
 unsigned he_pix; /* height in pixel */
 const unsigned* pix; 
} Glyph;

extern void font_init();
extern void font_glyph(char ch,Glyph* g);
