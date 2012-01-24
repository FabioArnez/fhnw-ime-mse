#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2010
#$Id$
#we are in work
#------------------------------------------ 
# SETUP
#------------------------------------------

VPATH=../src:../../src
PREFIX=../tc/bin/arm-fhnw-eabi
#------------------------- the tool names 
CC=${PREFIX}-gcc
LD=${PREFIX}-ld
OBJCOPY=${PREFIX}-objcopy
CXX=${PREFIX}-g++

CFLAGS=-std=gnu99 -O2
export CPPFLAGS=-I../src -I../../src
#the defines

CPPFLAGS+=-DIRQ_STACK_SIZE_WORD=0x20 \
	-DSTACK_SIZE_WORD=0x100

LDFLAGS=-nostdlib -Wl,--script=../config/ram.ld -Wl,-Map -Wl,${@}.map
       # |        |----- the linker script
       # |-------------- no standard libs 

#------------------------------------------ the source files
#add your sources here 
SRC=first.S \
sys/boot/big-bang.S \
sys/deb.c \
sys/start.c \
hello-world.c \
stdio.c \
stdout.c \
io/ascii.c \
io/uart.c \
sys-id.c

SYSTEM=sys/boot/big-bang.o sys/start.o sys/deb.o \
	stdio.o stdout.o io/ascii.o io/uart.o
#------------------------------------------ THE APPLICATIONS

#--------------------------- very first
first:		first.o
	${LD} first.o -o first --script=../config/ram.ld && \
	${OBJCOPY} -O binary first first.img

#--------------------------- big-bang-test
sys/boot/big-bang:	sys/boot/big-bang.o sys/deb.o
hello-world:	hello-world.o sys/boot/big-bang.o sys/start.o sys/deb.o \
	stdio.o stdout.o io/ascii.o io/uart.o

sys-id: sys-id.o ${SYSTEM}

#------------------------------- the rules made with make rules
include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
	
