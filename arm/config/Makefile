#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#------------------------------------------ 

#------------------------------------------ <setup>
PREFIX=../tc/bin/arm-fhnw-eabi
CC=${PREFIX}-gcc
LD=${PREFIX}-ld
OBJCOPY=${PREFIX}-objcopy
CXX=${PREFIX}-g++

CFLAGS=-std=gnu99 -O2

CPPFLAGS+=-DIRQ_STACK_SIZE_WORD=0x20 \
	-DSTACK_SIZE_WORD=0x100

LDFLAGS=-nostdlib -Wl,--script=../config/ram.ld -Wl,-Map -Wl,${@}.map
       # |        |----- the linker script
       # |-------------- no standard libs 


VPATH=../src:../../src

export CPPFLAGS+=-I../src -I../../src

#------------------------------------------ <source files>
SRC=hello-world.c \
stdio.c io/ascii.c stdout.c \
io/uart.c \
sys/boot/big-bang.S sys/start.c \
accessing-hardware.c \
sys/timer.c timer-test.c \
sys/deb.c sys/sys.c \
undef-trap-demo-call-undef.c sys/boot/big-bang-call-undef.S \
undef-trap-demo-call-c.c sys/boot/big-bang-call-c.S \
gic-test.c sys/gic.c \
io/lcd.c lcd-demo.c \
io/font.c 

SYSTEM=stdio.o io/ascii.o stdout.o io/uart.o sys/boot/big-bang.o sys/start.o
#------------------------------------------ <applications>
hello-world:	hello-world.o ${SYSTEM}
accessing-hardware:	accessing-hardware.o ${SYSTEM}
timer-test:	timer-test.o sys/timer.o ${SYSTEM}

#-----------------------------------------undef-trap-demo
undef-trap-demo-call-undef:	undef-trap-demo-call-undef.o  sys/boot/big-bang-call-undef.o\
	sys/sys.o sys/deb.o stdio.o io/ascii.o stdout.o io/uart.o sys/start.o

undef-trap-demo-call-c:	undef-trap-demo-call-c.o  sys/boot/big-bang-call-c.o\
	sys/sys.o sys/deb.o stdio.o io/ascii.o stdout.o io/uart.o sys/start.o

#-----------------------------------------gic generic interrupt controller
gic-test:	gic-test.o sys/sys.o sys/gic.o sys/deb.o ${SYSTEM}

#-----------------------------------------lcd
lcd-demo:	lcd-demo.o io/lcd.o io/font.o sys/gic.o ${SYSTEM}
lcd-demo-0:	lcd-demo-0.o sys/gic.o sys/deb.o ${SYSTEM}

#------------------------------- the rules made with make rules
include make.rules

#-------------------------------------- <admin>
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
	
