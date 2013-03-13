#pragma once
/*-----------------------
  clock.h
  (c) H.Buchmann FHNW 2013
 ------------------------*/
#include "io/lcd.h"

typedef struct
{
 unsigned hh;
 unsigned mm;
 unsigned ss;
} Time;

typedef struct
{
 Time   time;
 Pixel  pos;
} Clock;

extern void clock_init();

extern void clock_create(Clock*const      clock,
                         const Time*const time,
                         unsigned x,unsigned y);  /* position on screen */

extern void clock_show(const Clock*const clock);

extern void clock_tick(Clock*const clock);
