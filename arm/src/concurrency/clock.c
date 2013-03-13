/*-----------------------
  clock.c
  (c) H.Buchmann FHNW 2013
 ------------------------*/
#include "clock.h"
#include "sys/deb.h"


/* #define CLOCK_TEST */ /* uncomment for testing */

static const char*const Digits[]=
{
  "00","01","02","03","04","05","06","07","08","09",
  "10","11","12","13","14","15","16","17","18","19",
  "20","21","22","23","24","25","26","27","28","29",
  "30","31","32","33","34","35","36","37","38","39",
  "40","41","42","43","44","45","46","47","48","49",
  "50","51","52","53","54","55","56","57","58","59"
};

void clock_init()
{
 lcd_init();
}

void clock_create(Clock*const      clock,
                  const Time*const time,
                  unsigned x,unsigned y)  /* position on screen */
{
 clock->time=*time; /* copy */
 clock->pos=lcd_pixel(x,y);
}

static unsigned digits(const Pixel at,unsigned v)
{
 const char*const d=Digits[v];
 unsigned dx= lcd_char(at,   WHITE,d[0]);
          dx+=lcd_char(at+dx,WHITE,d[1]);
 return dx;
}

void clock_show(const Clock*const clock)
{
 Pixel at=clock->pos;
 at+=digits(at,clock->time.hh);
 at+=lcd_char(at,WHITE,':');
 at+=digits(at,clock->time.mm);
 at+=lcd_char(at,WHITE,':');
 digits(at,clock->time.ss);
}

void clock_tick(Clock*const clock)
{
 Time*const t=&clock->time;
 ++t->ss;
 if (t->ss<60) return;
 t->ss=0;
 ++t->mm;
 if (t->mm<60) return;
 t->mm=0;
 ++t->hh;
 if (t->hh<24) return;
 t->hh=0;
}

#ifdef CLOCK_TEST
Time t={23,59,59};
Clock clock;

int main()
{
 clock_init(); /* the module */
 clock_create(&clock,&t,50,50);
 while(1)
 {
  clock_show(&clock);
  deb_in();
  clock_tick(&clock);
 }
}
#endif
