#pragma once
/*--------------------
 deb(ug)
 (c) H.Buchmann FHNW 2009
 $Id$
----------------------*/
extern void deb_signal0() __attribute__((noreturn)); 
                                    /* writes signal at and returns */
extern void deb_signal1() __attribute__((noreturn)); 

extern void deb_reset() __attribute__((noreturn)); 
