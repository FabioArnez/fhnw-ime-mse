#-------------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------------
CC=gcc
CXX=g++
#-------------------- uncomment if you are using clang
#CC=clang
#CXX=clang++

OPTIMIZE=2
CFLAGS=-O${OPTIMIZE} -g -std=c99 
CXXFLAGS=-O${OPTIMIZE} -std=c++11
LDLIBS=-lm -lpthread -lasound

#posix files will be searched normally
export CPPFLAGS:=-I../src -I ../../src 

#-------------------------- how to link
%:	%.o;${CXX} ${LDFLAGS} ${^} ${LOADLIBES} ${LDLIBS} -o${@}

#-------------------------- where to look for the files
VPATH=../src:../../src

SRC= \
hello-world.c \
cpu-demo.c \
cpu-demo-ops.c \
stdio-test.c \
samples-demo.cc \
sound/samples.cc  sound/alsa.cc \
tim.cc\
function-parameter.c \
pointer.c \
mmap.c \
primes.c \
critical-section-0.c \
critical-section-2.c \
critical-section-3.c \
critical-section-4.c \
pthread-mutex.c \
pthread-semaphore.c \
pthread-trigger.c \
ioport.c \
atomic.c \
pthread-demo.c \
sys-call.S

hello-world:	hello-world.o
cpu-demo: 	cpu-demo.o cpu-demo-ops.o
samples-demo:	samples-demo.o sound/alsa.o sound/samples.o tim.o
sound:		sound.o
function-parameter:	function-parameter.o
pointer:	pointer.o
mmap:		mmap.o
primes: 	primes.o
critical-section-0:	critical-section-0.o
critical-section-2:	critical-section-2.o
critical-section-3:	critical-section-3.o
critical-section-4:	critical-section-4.o
atomic: 	atomic.o
pthread-mutex:	pthread-mutex.o
pthread-semaphore:	pthread-semaphore.o
pthread-trigger:	pthread-trigger.o
ioport: 	ioport.o
pthread-demo:	pthread-demo.o
sys-call:	sys-call.o

include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
