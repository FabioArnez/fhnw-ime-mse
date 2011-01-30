#-----------------
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#-----------------
#------------------------------------------ 
# SETUP
#------------------------------------------
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



#------------------------------------------ 
# THE RULES
#------------------------------------------

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
first-c:	sys/boot/bigBang.o first-c.o
first-c.o:	first-c.c

#--------------------------- test
uart-test:	uart-test.o io/uart.o sys/start.o sys/boot/bigBang.o
uart-test.o:	uart-test.c io/uart.h
stdio-test:	stdio-test.o io/uart.o io/ascii.o stdio.o stdout.o sys/start.o sys/bigBang.o

#--------------------------- system
sys/bigBang.o:	sys/bigBang.S
sys/deb.o:	sys/deb.c sys/deb.h
sys/start.o:	sys/start.c
io/uart.o:	io/uart.c
stdout.o:	stdout.c stdout.h io/ascii.h io/uart.h
stdio.o:	stdio.c stdio.h stdout.h
