#-----------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#TODO setup for 64 bit check with grub
#     make system without grub use sys/boot/iso-big-bang.S
#-----------------------
#------------------------------------------ 
# SETUP
#------------------------------------------
CC=gcc -m32
CFLAGS=-std=gnu99 #for asm volatile
CFLAGS+=-fno-stack-protector

VPATH=../src:../../src

CPPFLAGS=-I../src -I../../src

#------------------------------ link pattern
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
#------------------------------------------ 
# THE RULES
#------------------------------------------

#------------------------------- very first
first:		first.o
first.o:	first.S

hex:		hex.o
hex.o:		hex.S


#------------------------------- applications
sys/boot/grub-big-bang:	sys/boot/grub-big-bang.o sys/start.o sys/deb.o
stdio-test:	stdio-test.o sys/boot/grub-big-bang.o \
	io/ascii.o io/screen.o sys/start.o stdio.o stdout.o 


#------------------------------- the modules
sys/boot/grub-big-bang.o:	sys/boot/grub-big-bang.S
sys/deb.o:	sys/deb.c sys/deb.h
sys/start.o:	sys/start.c
io/screen.o:	io/screen.c io/screen.h sys/sys.h
stdout.o:	stdout.c stdout.h io/screen.h io/ascii.h sys/sys.h 
