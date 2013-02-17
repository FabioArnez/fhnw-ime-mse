#-------------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------------
CC=g++
CXX=g++
CC=clang
CXX=clang++

OPTIMIZE=2
CFLAGS=-O${OPTIMIZE} -g -std=c99 
CXXFLAGS=-O${OPTIMIZE}
LDLIBS=-lm -lpthread -lasound

#posix files will be searched normally
export CPPFLAGS:=-iquote ../src -iquote ../../src 
#-------------------------- how to link
%:	%.o;${CXX} ${LDFLAGS} ${^} ${LOADLIBES} ${LDLIBS} -o${@}

#-------------------------- where to look for the files
VPATH=../src:../../src

SRC=cpu-demo.c \
cpu-demo-ops.c \
stdio-test.c \
samples.cc \
function-parameter.c \
pointer.c \
mmap.c \
primes.c \
pthread.c \
pthread-mutex.c \
pthread-semaphore.c \
pthread-trigger.c \
ioport.c \
atomic.c 

cpu-demo: 	cpu-demo.o cpu-demo-ops.o
samples:	samples.o
sound:		sound.o
function-parameter:	function-parameter.o
pointer:	pointer.o
mmap:		mmap.o
primes: 	primes.o
pthread:	pthread.o
atomic: 	atomic.o
pthread-mutex:	pthread-mutex.o
pthread-semaphore:	pthread-semaphore.o
pthread-trigger:	pthread-trigger.o
ioport: 	ioport.o

include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
