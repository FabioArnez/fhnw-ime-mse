#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#TODO setup for 64 bit check with grub
#     make system without grub use sys/boot/iso-big-bang.S
#     look for a more elegant solution for making the rules
#------------------------------------------ 
# SETUP
#------------------------------------------
CC=gcc -m32
CFLAGS=-std=gnu99 #for asm volatile
CFLAGS+=-fno-stack-protector

VPATH=../src:../../src
export CPPFLAGS=-I../src -I../../src

#------------------------------------------ link pattern
# .settings 32 bit architecture
#     objcopy: creating binary image
# genisoimage: creating cd iso image appropriate for grub
%:	%.o;\
ld  -o${@} \
    --build-id=none \
    -m elf_i386 \
    --script=../config/grub.ld \
    -Map ${@}.map ${^} && \
objcopy --output-target=binary ${@} ../iso/${@} && \
genisoimage -R \
           -b stage2_eltorito \
	   -no-emul-boot \
	   -boot-load-size 4 \
	   -boot-info-table \
       -o ../sos.iso ../iso	

#------------------------------------------ the source files
SRC=first.S \
hex.S \
io/screen.c \
sys/start.c \
sys/boot/grub-big-bang.S \
sys/deb.c \
stdio-test.c\
io/ascii.c \
stdout.c

#------------------------------------------ THE APPLICATIONS
#------------------------------- very first
first:		first.o
hex:		hex.o

#------------------------------- applications
sys/boot/grub-big-bang:	sys/boot/grub-big-bang.o sys/start.o sys/deb.o
stdio-test:	stdio-test.o sys/boot/grub-big-bang.o \
     	io/ascii.o io/screen.o sys/start.o stdio.o stdout.o 


#------------------------------- the rules made with make rules
include make.rules

#------------------------------------------ making the rules
#
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}
