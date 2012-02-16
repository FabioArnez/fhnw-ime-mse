/*---------------------
  samples.c
  generates sine samples for stdout
  sound using sox/play
  ./samples | play -q -r44000 -e floating-point -8 -traw - 

  TODO reading parameter 
       sine/cos generated with cordic
       see [CORDIC]
  (c) H.Buchmann FHNW 2011
  $Id$
-----------------------*/
#define _GNU_SOURCE
#include <math.h>
#include <unistd.h>
#include <time.h>

/* wait dont works properly */
static void wait(long nanoSec)
{
 if (nanoSec==0) return;
 struct timespec delta={tv_sec:0,tv_nsec:nanoSec};
 nanosleep(&delta,0);
}

static void samples(double fS,/* sampling frequency Hz */
                    double f,          /* frequency Hz */
		    double dur)        /* duration sec */
{
 double dt=dur/fS;
 double cos_;
 double sin_;
 sincos(2*M_PI*f/fS,&sin_,&cos_);
 double x0=0.875; /* cosine */
 double y0=0.0; /* sine */
 for(double t=0;t<=dur;t+=dt)
 {
  int ret=write(STDOUT_FILENO,&x0,sizeof(x0));
  double x1=x0*cos_ - y0*sin_;
  double y1=x0*sin_ + y0*cos_;
  x0=x1;
  y0=y1;
  for(unsigned i=0;i<30000;++i)     /* set the value manually */
  {
   volatile unsigned v=i; /* preventing optimizer to optimize loop away */
  }
 }
}

int main(int argc,char** args)
{
 samples(44000,  /* Hz  */
         440,    /* Hz  */
	 2);     /* sec */
 return 0;
}
