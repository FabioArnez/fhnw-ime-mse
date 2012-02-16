/*-----------------------
 mmap you must be root
 (c) H.Buchmann FHNW 2009
 $Id$
-------------------------*/
/*TODO call with parameter
  mmap type start size
   type:  u: unsigned s:short b:byte
   start: start address
   size:  in types
*/  
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char** args)
{
 unsigned offset=0x000f0000;    /* the location of the BIOS */
 unsigned len=0x100*sizeof(unsigned);
 int id=open("/dev/mem",O_RDONLY);
                                /* the memory */
 if (id<0)
    {
     perror("open");
     return 1;
    }
 unsigned* m=mmap(0,              /* normally 0 (only hint) */
                  len,                            /* length */
                  PROT_READ,            /* only for reading */
	          MAP_SHARED,
	          id,                         /* the device */
                  offset);                    /* the offset */               
 if (m==0)
    {
     perror("mmap");
     return 1;
    }
 fwrite(m,1,len,stdout);
}
