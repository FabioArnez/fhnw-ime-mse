#-------------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#-------------------------

#----------------------- your comments and notes





#---------------------------------------------------<setup>
CXX=g++
CC=${CXX}

OPTIMIZE=2
CFLAGS=-O${OPTIMIZE} -g -std=c99 
CXXFLAGS=-O${OPTIMIZE} -std=c++11
LDLIBS=-lm -lpthread -lasound

#posix files will be searched normally
CPPFLAGS:=-I../src -I ../../src 
export CPPFLAGS
#-------------------------- how to link
#%:	%.o;${CXX} ${LDFLAGS} ${^} ${LOADLIBES} ${LDLIBS} -o${@}

#-------------------------- how to assemble
%.o:	%.S ;${CC} -c -o${@} ${^}
#%.o:	%.cc;${CXX} ${CXXFLAGS} -c -o${@} ${<}
#%.o:	%.c ;${CC}  ${CFLAGS}   -c -o${@} ${<}
#-------------------------- where to look for the files
SRC_PATH=../src:../../src
VPATH=${SRC_PATH}

#---------------------------------------------------<source files>
SRC= \
hello-world.cc \
sound-demo.cc sound/samples.cc  sound/sine.cc sound/noise.cc sound/alsa.cc sound/stream.cc \
cpu-demo.S cpu-demo-app.cc \
primes.cc \
thread-demo-1.cc thread-demo-2.cc thread-demo-3.cc \
common-access-1.cc 
#common-access-2.cc common-access-3.cc common-access-4.cc \
#thread.cc \
#hello-world.c \
#cpu-demo-ops.S \
#stdio-test.c \
#sound-demo.cc \
#sound/samples.cc  sound/alsa.cc sound/stream.cc \
#timer.cc \
#function-parameter.c \
#pointer.c \
#mmap.c \
#primes.c \
#critical-section-0.c \
#critical-section-2.c \
#critical-section-3.c \
#critical-section-4.c \
#pthread-mutex.c \
#pthread-semaphore.c \
#pthread-trigger.c \
#ioport.c \
#atomic.c \
#pthread-demo.c \
#sys-call.S \
#cpu-demo.c \

#---------------------------------------------------<applications>
sound-demo:	sound-demo.o sound/samples.o sound/alsa.o sound/stream.o sound/sine.o sound/noise.o timer.o
hello-world:	hello-world.o
cpu-demo-app:	cpu-demo-app.o cpu-demo.o 

primes: 	primes.o
thread-demo-1:	thread-demo-1.o
thread-demo-2:	thread-demo-2.o
thread-demo-3:	thread-demo-3.o thread.o
common-access-1: common-access-1.o 
#common-access-2: common-access-2.o thread.o
#common-access-3: common-access-3.o thread.o
#common-access-4: common-access-4.o thread.o
#hello-world:	hello-world.o
#cpu-demo: 	cpu-demo.o cpu-demo-ops.o
#sound:		sound.o
#function-parameter:	function-parameter.o
#pointer:	pointer.o
#mmap:		mmap.o
#primes: 	primes.o
#critical-section-0:	critical-section-0.o
#critical-section-2:	critical-section-2.o
#critical-section-3:	critical-section-3.o
#critical-section-4:	critical-section-4.o
#atomic: 	atomic.o
#pthread-mutex:	pthread-mutex.o
#pthread-semaphore:	pthread-semaphore.o
#pthread-trigger:	pthread-trigger.o
#ioport: 	ioport.o
#pthread-demo:	pthread-demo.o
#sys-call:	sys-call.o

include make.rules

#---------------------------------------------------<admin>
.PHONY projects:
.PHONY rules:
projects:	rules
rules:	${SRC}
	sh ../../tools/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
