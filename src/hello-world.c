/*---------------------
 hello-world
 (c) H.Buchmann FHNW 2009
 $Id$
-----------------------*/
/* the video ram */
volatile unsigned short* video=(volatile unsigned short*)0xb8000;
#define WIDTH 80              /* of screen */  
#define HEIGHT 25             /* of screen */

int main()
{
 unsigned char ch='A';
 while(1)
 { 
  volatile unsigned short* v=video;
  for(unsigned r=0;r<HEIGHT;r++)
  {
   for(unsigned c=0;c<WIDTH;c++)
   {
    *v++=0x0700|ch;  
    if (ch=='Z') ch='A';
       else      ++ch;
   }
  }
 }
}

