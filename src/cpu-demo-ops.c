/*-------------------------
 cpu-demo-ops.c 
 (c) H.Buchmann FHNW 2011
 $Id$
 the c language implementation 
---------------------------*/
#include "cpu-demo-ops.h" /* how the functions look like */

/* the implememtation */
unsigned op(unsigned x,unsigned y)
{
 return x+y;
}

void copy(unsigned* dst,unsigned* src)
{
 *dst=*src;
}