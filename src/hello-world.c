/*---------------------
 hello-world
 (c) H.Buchmann FHNW 2011
 $Id$
-----------------------*/
#include <stdio.h> /* the external functions */
int main()
{
 printf("-Hello World- date='%s' file='%s'\n",
                 __DATE__,  /* predefined macro for date when compiled */
	         __FILE__); /* predefined macro for file name */
} 
