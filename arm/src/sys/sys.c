/*-----------------------------
 reg status and system control registers
 see [RealViewEmulationBaseboard] 4.3
 (c) H.Buchmann FHNW 2012
 $Id$
 ------------------------------*/ 
/* test */
#if 1
#include "sys/sys.h"
#include "stdio.h"
int main()
{
 printf("MCI        =%x\n"
        "CONFIGDATA =%x\n"
	"FLAGS      =%x FLAGSSET =%x\n"
        "OSCRESET   =%x\n"
        "PLDCTL     =%x\n"
        ,&SYS.MCI
	,SYS.CONFIGDATA
	,&SYS.FLAGS,&SYS.FLAGSSET
	,SYS.OSCRESET
	,SYS.PLDCTL);
 return 0;
}
#endif
