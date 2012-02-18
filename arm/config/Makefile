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

export CPPFLAGS=-I../src -I../../src

#------------------------------------------ <source files>
add your sources here 
SRC=

#------------------------------------------ <applications>

#------------------------------- the rules made with make rules
include make.rules

#-------------------------------------- <admin>
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
	
