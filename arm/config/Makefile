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
          -DUNDEF_STACK_SIZE_WORD=0x20 \
	  -DSTACK_SIZE_WORD=0x100 

LDFLAGS=-nostdlib -Wl,--script=../config/ram.ld -Wl,-Map -Wl,${@}.map
       # |        |----- the linker script
       # |-------------- no standard libs 

#------------------------------------------ assembler pattern
%.o:	%.S;$(CC) ${CPPFLAGS} ${CFLAGS} -c -o ${@} ${<}

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
sys/stack.c \
undef-trap-demo.c \
gic-test.c sys/gic.c \
io/lcd.c lcd-demo.c \
io/font.c \
io/screen.c \
ascii-test.c \
cpu-demo-ops.S cpu-demo.c \
sys/arm.c \
timer-trap-demo-hw.c \
timer-trap-demo-polling.c \
timer-trap-demo-irq.c \
common-access.c


SYSTEM=sys/stack.o sys/arm.o sys/deb.o stdio.o io/ascii.o stdout.o io/uart.o sys/boot/big-bang.o sys/start.o
#------------------------------------------ <applications>
hello-world:	hello-world.o ${SYSTEM}
accessing-hardware:	accessing-hardware.o ${SYSTEM}
timer-test:	timer-test.o sys/timer.o ${SYSTEM}

cpu-demo:	cpu-demo.o cpu-demo-ops.o ${SYSTEM}

#-----------------------------------------undef-trap-demo
undef-trap-demo:	undef-trap-demo.o ${SYSTEM}

#-----------------------------------------timer-trap-demo
timer-trap-demo-hw:		timer-trap-demo-hw.o sys/timer.o ${SYSTEM}
timer-trap-demo-polling:	timer-trap-demo-polling.o sys/timer.o ${SYSTEM}
timer-trap-demo-irq:		timer-trap-demo-irq.o sys/timer.o ${SYSTEM}

#-----------------------------------------common-access
common-access: 	common-access.o sys/timer.o ${SYSTEM}

#-----------------------------------------gic generic interrupt controller
gic-test:	gic-test.o sys/sys.o sys/gic.o sys/deb.o ${SYSTEM}

#-----------------------------------------lcd
lcd-demo:	lcd-demo.o io/lcd.o io/font.o  ${SYSTEM}
lcd-demo-0:	lcd-demo-0.o sys/deb.o ${SYSTEM}
ascii-test:	ascii-test.o io/screen.o io/lcd.o io/font.o ${SYSTEM}

#------------------------------- the rules made with make rules
include make.rules

#-------------------------------------- <admin>
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
	
