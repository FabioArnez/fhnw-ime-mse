/*------------------------
 screen the basic output
 (c) H.Buchmann FHNW 2009
 $Id$
 www.osdever.net/FreeVGA/vga/
--------------------------*/
#include "sys/screen.h"
#include "sys/sys.h"

/* TODO intensive testing scroll eol etc. */
/* TODO cursor control */
#define CRTADDRESS 0x3d4
#define CRTVALUE   0x3d5

typedef struct
{
 char ch;
 char attr;
} __attribute__((packed)) Char;
                                     /* the video ram */
static volatile Char* video=(volatile Char*)0xb8000; 

static const unsigned COL=80;            /* of screen */  
static const unsigned ROW=25;            /* of screen */
static const unsigned TAB= 8;
                                              /* screen status */
static unsigned row=0;                           /* 0<=row<ROW */
static unsigned col=0;                           /* 0<=col<COL */
static volatile Char* pos;     /* cursor position current line */

static volatile Char* lin;             /* begin of current line */
static unsigned tab=0;

static void scroll() //row==ROW
{
 volatile Char* dst=video;
 volatile Char* src=video+COL;
 for(unsigned r=1;r<ROW;++r)
 {
  for(unsigned c=0;c<COL;++c)
  {
   *dst++=*src++;
  }
 }
 lin=dst;
 for(unsigned c=0;c<COL;++c) dst++->ch=' ';
 --row;
}

static void cursor()
{
 pos->ch='_';
}

static void put(char ch) 
{
/* 0<=col<COL 0<=row<ROW pos-tab<TAB*/
 pos->ch=ch;
 ++pos;
 ++col;
 if (col==COL)
    {
     tab=0;
     col=0;
     ++row;
     lin=pos;
     if (row==ROW) scroll();
     return;
    }
 if (col==tab) tab+=TAB;
 cursor();
}

static void newln()
{
 lin+=COL;
 tab=0;
 col=0;
 ++row;
 if (row==ROW) scroll();
 pos=lin;
 cursor();
}

static void tabulator()
{
 tab+=TAB;
 while(pos<tab) put(' ');
}

static Out out={put,newln,tabulator};

void screen_init()
{
/* disable cursor */
 sys_outb(0x0a,CRTADDRESS);
 sys_outb((1<<5),CRTVALUE);
 
 volatile Char*v=video;
 for(unsigned r=0;r<ROW;++r)
 {
  for(unsigned c=0;c<COL;++c)
  {
   v->ch=' ';
   v->attr=7;
   ++v;
  }
 }
 pos=video;
 lin=video;
 cursor();
}


Out* Screen=&out;

