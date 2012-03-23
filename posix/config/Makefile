#-------------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------------
CC=gcc
CFLAGS=-g -std=c99 
LDLIBS=-lm

#posix files will be searched normally
export CPPFLAGS:=-iquote ../src -iquote ../../src 
 
#-------------------------- where to look for the files
VPATH=../src:../../src

SRC=cpu-demo.c \
cpu-demo-ops.c \
stdio-test.c \
samples.c \
function-parameter.c \
pointer.c \
mmap.c \
primes.c


cpu-demo: 	cpu-demo.o cpu-demo-ops.o
samples:	samples.o
function-parameter:	function-parameter.o
pointer:	pointer.o
mmap:		mmap.o
primes: 	primes.o

include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
