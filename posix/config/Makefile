#-------------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------------
CC=gcc
OPTIMIZE=2
CFLAGS=-O${OPTIMIZE} -g -std=c99 
LDLIBS=-lm -lpthread

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
primes.c \
pthread.c \
pthread-mutex.c \
pthread-semaphore.c \
pthread-trigger.c


cpu-demo: 	cpu-demo.o cpu-demo-ops.o
samples:	samples.o
function-parameter:	function-parameter.o
pointer:	pointer.o
mmap:		mmap.o
primes: 	primes.o
pthread:	pthread.o
pthread-mutex:	pthread-mutex.o
pthread-semaphore:	pthread-semaphore.o
pthread-trigger:	pthread-trigger.o

include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
