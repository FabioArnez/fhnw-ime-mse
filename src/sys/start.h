#pragma once
/*-------------------------
start for non posix systems
(c) H.Buchmann FHNW 2009
$Id$
see big-bang
--------------------------*/
/* possible to include in assembler file */
#if __ASSEMBLER__ == 1
 .global _start
#else
 extern void _start();
#endif
