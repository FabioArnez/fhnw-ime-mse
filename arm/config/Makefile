#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#------------------------------------------ 
# SETUP
#------------------------------------------

VPATH=../src:../../src
PREFIX=arm-fhnw-eabi
CC=../tc/bin/${PREFIX}-gcc
CXX=../tc/bin/${PREFIX}-g++
CFLAGS=-std=gnu99 -O2

#------------------------------------------ see sys/boot/big-bang.S
STACK_SIZE_WORD=32
IRQ_STACK_SIZE_WORD=32

#------------------------------------------ assembler pattern
%.o:	%.S;$(CC) ${CPPFLAGS} ${CFLAGS} -c -o ${@} ${<}

export CPPFLAGS=-I../src -I../../src
CPPFLAGS+=-DSTACK_SIZE_WORD=${STACK_SIZE_WORD}
CPPFLAGS+=-DIRQ_STACK_SIZE_WORD=${IRQ_STACK_SIZE_WORD}

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
accessing-hardware.c \
undef-trap-demo.c \
sys/boot/big-bang-exceptions.S \
sys/boot/big-bang-call-undef.S \
sys/boot/big-bang-call-c.S \
undef-trap-demo-exceptions.c \
undef-trap-demo-call-undef.c \
undef-trap-demo-call-c.c \
uart-trap-demo.c \
timer-trap-demo.c \
sys/sys.c

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
cpu-demo: cpu-demo.o cpu-demo-ops.o hex.o sys/deb.o sys/boot/big-bang.o \
	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
hello-world: hello-world.o sys/boot/big-bang.o \
     	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
accessing-hardware:	accessing-hardware.o sys/deb.o hex.o sys/boot/big-bang.o \
	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
uart-trap-demo: 	uart-trap-demo.o hex.o sys/sys.o sys/deb.o\
	sys/boot/big-bang.o io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
timer-trap-demo:	timer-trap-demo.o hex.o sys/sys.o sys/deb.o\
	sys/boot/big-bang.o io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
undef-trap-demo-exceptions:	undef-trap-demo-exceptions.o \
	sys/sys.o sys/deb.o\
	sys/boot/big-bang-exceptions.o \
	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
undef-trap-demo-call-undef:	undef-trap-demo-call-undef.o \
	sys/sys.o sys/deb.o\
	sys/boot/big-bang-call-undef.o \
	io/ascii.o io/uart.o sys/start.o stdio.o stdout.o
undef-trap-demo-call-c:	undef-trap-demo-call-c.o \
	sys/sys.o sys/deb.o\
	sys/boot/big-bang-call-c.o \
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
	
