/*-----------------------------
 stdout
 (c) H.Buchmann FHNW 2011
 $Id$
-------------------------------*/
#include "stdout.h"
#include "io/ascii.h"
#include "io/uart.h"

static void newln()
{
 uart_out('\n');
}

static void tab()
{
 uart_out('\t');
}

void stdout_init()
{
}

Out stdout_={uart_out,newln,tab};
Out* stdout=&stdout_;

