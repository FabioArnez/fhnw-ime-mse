#-------------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------------
VPATH=../src:../../src

#posix files will be searched normally
export CPPFLAGS:=-iquote../src -iquote../../src

SRC=cpu-demo.c \
cpu-demo-ops.c \
stdio-test.c


cpu-demo: cpu-demo.o cpu-demo-ops.o

include make.rules

#-------------------------------------- admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
