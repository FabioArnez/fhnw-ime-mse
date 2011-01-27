#-----------------
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id: Makefile 239 2011-01-17 14:47:22Z hans.buchmann $
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
uart:		uart.o
uart.o: 	uart.S

#--------------------------- hexadecimal output
hex:		hex.o
hex.o:		hex.S

#--------------------------- first c
first-c:	sys/bigBang.o first-c.o
first-c.o:	first-c.c

#--------------------------- signal test
sys/bigBang:	sys/bigBang.o sys/deb.o

#--------------------------- system
sys/bigBang.o:	sys/bigBang.S
sys/deb.o:	sys/deb.c sys/deb.h
