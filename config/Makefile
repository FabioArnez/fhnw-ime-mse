#--------------------
#Makefile for sos
#(c) H.Buchmann FHNW 2009
#$Id$
#Makefike docu see:
#http://www.gnu.org/software/make/manual/html_node/index.html
#TODO make library from sys files
#TODO make better rules
#--------------------
#we are in work: *** all accesses made relative to work ***

TC=/home/buchmann/devel/tools/target/host/gcc-4.5/
#------------------------------------------------ configuration
SRC_HOME=../src
PACKAGES=sys sys/boot io       # subdirs of src 
VPATH=${SRC_HOME}              # where to look for source files
CPPFLAGS=-I${SRC_HOME} 
CFLAGS=-O3 -std=gnu99          # compiler options
CC=${TC}/bin/gcc
                               # c99 dont enable asm
#CC=gcc-4 you can use it with cygwin

#--------------------- pattern for link
#creates an image file suitable for cdrom booting
%:	%.o
	ld $^ -Map $@.map --script ../config/iso.ld -o$@ && \
	objcopy --output-target binary $@ iso/boot.img && \
	mkisofs -R \
	        -b boot.img \
		-no-emul-boot \
		-boot-load-size 4 \
		-boot-info-table \
		-o boot.iso iso

#the system modules
SYSTEM=sys/boot/big-bang.o sys/start.o sys/screen.o

#------------------------------------------------ the images
clock-demo:	${SYSTEM} \
	sys/pit.o sys/pic.o \
	sys/trap.o sys/trap0.o \
	io/kbd.o io/ascii.o \
	clock-demo.o

sys/boot/big-bang:	sys/boot/big-bang.o
hello-world:	hello-world.o  sys/boot/big-bang.o
ascii-test:	${SYSTEM} io/ascii.o ascii-test.o 
out-test:	sys/boot/big-bang.o sys/start.o io/out.o out-test.o
pit-demo:	${SYSTEM} sys/pit.o io/ascii.o io/kbd.o pit-demo.o
pic-devel:	${SYSTEM} sys/pic.o sys/trap.o sys/trap0.o io/ascii.o io/kbd.o pic-devel.o
kbc-demo:	${SYSTEM} sys/kbc.o sys/deb.o sys/pit.o io/kbd.o sys/pic.o sys/trap.o sys/trap0.o io/ascii.o kbc-demo.o 
#kbc-demo:	sys/start.o sys/screen.o sys/deb.o io/ascii.o kbc-demo.o 
apic-test:	${SYSTEM} apic-test.o sys/apic.o io/ascii.o 
apic-devel:	${SYSTEM} sys/trap.o sys/trap0.o io/ascii.o io/kbd.o apic-devel.o
trap-devel:	${SYSTEM} sys/trap.o sys/trap0.o io/ascii.o trap-devel.o
apic-demo:	${SYSTEM}  io/ascii.o apic-demo.o
irq-demo:	${SYSTEM} io/ascii.o irq-demo.o
kbd-demo:	${SYSTEM} sys/kbc.o io/ascii.o io/kbd.o kbd-demo.o
scancode-demo:	${SYSTEM} io/ascii.o scancode-demo.o 

#------------------------------------------------ the modules
sys/boot/big-bang.o:	sys/boot/big-bang.S
sys/boot/deb0.o:	sys/boot/deb0.S
io/out.o:	io/out.c io/out.h
io/ascii.o:	io/ascii.c io/ascii.h
sys/apic.o:	sys/apic.c sys/apic.h sys/screen.h sys/io.h io/ascii.h
sys/deb.o:	sys/deb.c sys/deb.h io/ascii.h sys/screen.h
sys/trap.o:	sys/trap.c sys/trap.h
sys/pic.o:	sys/pic.c sys/pic.h sys/trap.h sys/screen.h sys/io.h io/ascii.h
sys/trap0.o:	sys/trap0.S sys/trap.c sys/trap.h
sys/screen.o:	sys/screen.c sys/screen.h io/ascii.h
sys/start.o:	sys/start.c sys/screen.h
sys/kbc.o:      sys/kbc.c sys/kbc.h sys/screen.h sys/trap.h sys/pic.h io/ascii.h 

out-test.o:	out-test.c io/out.h
scancode-demo.o:	scancode-demo.c io/ascii.h sys/io.h
hello-world.o:	hello-world.c 
ascii-test.o:	ascii-test.c io/ascii.h sys/screen.h
kbd-demo.o:	kbd-demo.c io/ascii.h io/kbd.h sys/screen.h
irq-demo.o:	irq-demo.c io/ascii.h sys/screen.h
apic-demo.o:	apic-demo.c sys/io.h io/ascii.h sys/screen.h
trap-devel.o:	trap-devel.c io/ascii.h sys/trap.h sys/screen.h
apic-devel.o:	apic-devel.c io/ascii.h sys/trap.h sys/screen.h io/kbd.h sys/io.h
kbc-demo.o:	kbc-demo.c io/ascii.h sys/screen.h sys/io.h sys/kbc.h sys/deb.h
pic-devel.o:	pic-devel.c io/ascii.h io/kbd.h sys/screen.h sys/trap.h sys/io.h
pit-demo.o:	pit-demo.c io/ascii.h io/kbd.h sys/screen.h sys/pit.h sys/io.h 
clock-demo.o: clock-demo.c sys/screen.h io/ascii.h \
  io/ascii.h sys/pit.h sys/pic.h sys/trap.h \
  sys/io.h io/kbd.h sys/io.h
  
.PHONY: clean
clean:
	rm -f *.o $(foreach p,${PACKAGES},${p}/*.o)
