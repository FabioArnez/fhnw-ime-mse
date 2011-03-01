#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#------------------------------------------ 
# SETUP
#------------------------------------------
STACK_SIZE_WORD=32
VPATH=../src:../../src
PREFIX=arm-fhnw-eabi
CC=../tc/bin/${PREFIX}-gcc
CXX=../tc/bin/${PREFIX}-g++
CFLAGS=-std=c99

#------------------------------------------ assembler pattern
%.o:	%.S;$(CC) ${CPPFLAGS} ${CFLAGS} -c -o ${@} ${<}

export CPPFLAGS=-DSTACK_SIZE_WORD=${STACK_SIZE_WORD} -I../src -I../../src

LDFLAGS=-nostdlib -Wl,--script=../config/ram.ld -Wl,-Map -Wl,${@}.map
       # |        |----- the linker script
       # |-------------- no standard libs 

#------------------------------------------ the source files
#add your sources here 
SRC=first.S \
hex.S \
io/ascii.c \
sys/start.c \
sys/boot/big-bang.S \
sys/deb.c \
io/ascii.c \
io/uart.c \
stdio-test.c \
stdout.c \
stdio.c \
cpu-demo.c \
cpu-demo-ops.S \
hello-world.c \
accessing-hardware.c



#------------------------------------------ THE APPLICATIONS

##--------------------------- very first
first:		first.o
#--------------------------- uart
uart-0:		uart-0.o
#--------------------------- hexadecimal output
hex:		hex.o

#------------------------------- applications
sys/boot/big-bang:	sys/boot/big-bang.o sys/start.o sys/deb.o
stdio-test:	stdio-test.o sys/boot/big-bang.o \
     	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o 
cpu-demo: cpu-demo.o cpu-demo-ops.o sys/boot/big-bang.o \
	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
hello-world: hello-world.o sys/boot/big-bang.o \
     	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
accessing-hardware:	accessing-hardware.o sys/boot/big-bang.o \
	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
#------------------------------- the rules made with make rules
include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
	
