#-------------------
#Makefile for host
#(c) H.Buchmann FHNW 2011
#$Id$
#-------------------
#where to look for the sources
VPATH=../src:../../src
#where to include
CPPFLAGS=-I../src -I../../src

#TODO VPATH and CPPFLAGS contains the same information 
#     with different format only
#     generate automatically the values for VPATH and CPPFLAGS
#     see http://www.gnu.org/software/make/manual/html_node/index.html#toc_Functions
#         8 Functions for Transforming Text
#how to compile
CFLAGS=-std=c99

#----------------------------- applications
stdio-test:	stdio-test.o stdio.o stdout.o io/ascii.o

stdio-test.o:	stdio-test.c stdio.h stdout.h

#----------------------------- minimalistic 
stdio.o:	stdio.c stdio.h
stdout.o:	stdout.c stdout.h io/ascii.h
io/ascii.o:	io/ascii.c io/ascii.h
