#------------------------------------------ 
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#TODO setup for 64 bit check with grub
#     make system without grub use sys/boot/iso-big-bang.S
#     look for a more elegant solution for making the rules
#     handle empty file make.rules
#------------------------------------------ 

#------------------------------------------ setup
CC=gcc -m32                    #we are using 32 bit
CFLAGS=-std=gnu99              #for asm volatile
CFLAGS+=-fno-stack-protector   #easy stack handling
VPATH=.:../src:../../src       #where to look for the source files

#------------------------------------------ assembler pattern
%.o:	%.S;$(CC) ${CPPFLAGS} ${CFLAGS} -c -o ${@} ${<}

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

#------------------------------------------ source files
#add here your source files typically c rsp. S files
SRC=vga-demo.c \
sys/boot/grub-big-bang.S \
sys/start.c \
sys/pic.c \
sys/pit.c \
sys/trap.c \
sys/trap0.S \
sys/deb.c \
stdout.c \
stdio.c \
io/screen.c \
io/kbd.c \
kbdc-demo.c \
clock-demo.c 

#------------------------------------------ applications
vga-demo:	vga-demo.o io/screen.o sys/start.o stdout.o sys/boot/grub-big-bang.o
kbdc-demo:	kbdc-demo.o \
	stdout.o stdio.o \
	io/screen.o io/ascii.o \
	sys/start.o sys/boot/grub-big-bang.o
clock-demo:	clock-demo.o \
	stdout.o stdio.o \
	io/screen.o io/ascii.o io/kbd.o \
	sys/start.o sys/deb.o sys/boot/grub-big-bang.o \
	sys/pic.o sys/pit.o sys/trap.o sys/trap0.o 
#------------------------------------------ rules
#at first time using make empty make.rules
include make.rules       # made by make rules

#------------------------------------------ admin
.PHONY rules:
rules:	${SRC}
	sh ../../tool/make-rules.sh ${SRC}

.PHONY clean:
clean:
	rm -rf $(addsuffix *,$(basename ${SRC})) 
