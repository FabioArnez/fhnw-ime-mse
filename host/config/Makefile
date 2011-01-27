#-------------------
#Makefile for host
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------

#where to look for the sources
VPATH=../src:../../src
CPPFLAGS=-I../src -I../../src
CFLAGS=-std=c99

stdio-test:	stdio-test.o stdio.o stdout.o io/ascii.o


stdio-test.o:	stdio-test.c stdio.h stdout.h

#----------------------------- minimalistic 
stdio.o:	stdio.c stdio.h
stdout.o:	stdout.c stdout.h io/ascii.h
io/ascii.o:	io/ascii.c io/ascii.h
