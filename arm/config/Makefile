#-----------------
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#-----------------
STACK_SIZE_WORD=32

VPATH=../src:../../src

PREFIX=arm-fhnw-eabi
CC=../tc/bin/${PREFIX}-gcc
CXX=../tc/bin/${PREFIX}-g++
CFLAGS=-std=c99
CPPFLAGS=-DSTACK_SIZE_WORD=${STACK_SIZE_WORD} \
 -I../src -I../../src


LDFLAGS=-nostdlib -Wl,--script=../config/ram.ld -Wl,-Map -Wl,${@}.map
       # |        |----- the linker script
       # |-------------- no standard libs 

#--------------------------- very first
first:		first.o
first.o:	first.S

#--------------------------- uart
uart-0:		uart-0.o
uart-0.o: 	uart-0.S

#--------------------------- hexadecimal output
hex:		hex.o
hex.o:		hex.S

#--------------------------- first c
first-c:	sys/bigBang.o first-c.o
first-c.o:	first-c.c

#--------------------------- test
sys/bigBang:	sys/bigBang.o sys/deb.o
uart-test:	uart-test.o io/uart.o sys/start.o sys/bigBang.o
uart-test.o:	uart-test.c io/uart.h

#--------------------------- system
sys/bigBang.o:	sys/bigBang.S
sys/deb.o:	sys/deb.c sys/deb.h
sys/start.o:	sys/start.c
io/uart.o:	io/uart.c

