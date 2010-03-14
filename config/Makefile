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
out-test:	sys/boot/big-bang.o sys/start.o io/out.o out-test.o
screen-test:	${SYSTEM} screen-test.o
ascii-test:	${SYSTEM} io/ascii.o ascii-test.o 
pit-demo:	${SYSTEM} sys/pit.o io/ascii.o io/kbd.o pit-demo.o
pic-devel:	${SYSTEM} sys/pic.o sys/trap.o sys/trap0.o io/ascii.o io/kbd.o pic-devel.o
trap-demo:	${SYSTEM} sys/pic.o sys/deb.o sys/trap.o sys/trap0.o io/ascii.o trap-demo.o 
common-access:	${SYSTEM} sys/pic.o sys/deb.o sys/trap.o sys/trap0.o io/ascii.o common-access.o 
common-access-2:${SYSTEM} sys/pic.o sys/deb.o sys/trap.o sys/trap0.o io/ascii.o common-access-2.o 
apic-test:	${SYSTEM} apic-test.o
apic-devel:	${SYSTEM} sys/pic.o sys/trap.o sys/trap0.o io/ascii.o io/kbd.o apic-devel.o
trap-devel:	${SYSTEM} sys/trap.o sys/trap0.o io/ascii.o trap-devel.o
apic-demo:	${SYSTEM} io/ascii.o apic-demo.o
irq-demo:	${SYSTEM} io/ascii.o irq-demo.o
kbd-demo:	${SYSTEM} io/ascii.o io/kbd.o kbd-demo.o
scancode-demo:	${SYSTEM} io/ascii.o scancode-demo.o 
cpu-trap:	${SYSTEM} cpu-trap.o sys/trap.o sys/trap0.o io/ascii.o
vga-demo:	${SYSTEM} vga-demo.o 
#------------------------------------------------ the modules
apic-demo.o: apic-demo.c sys/screen.h io/ascii.h \
  io/ascii.h sys/sys.h
apic-devel.o: apic-devel.c sys/screen.h io/ascii.h \
  io/ascii.h sys/sys.h io/kbd.h sys/trap.h \
  sys/pic.h sys/trap.h
apic-test.o: apic-test.c sys/apic.h sys/trap.h \
  sys/sys.h
ascii-test.o: ascii-test.c io/ascii.h sys/screen.h \
  io/ascii.h
calling-an-image.o: calling-an-image.c
clock-demo.o: clock-demo.c sys/screen.h io/ascii.h \
  io/ascii.h sys/pit.h sys/pic.h sys/trap.h \
  sys/sys.h io/kbd.h
hello-world.o: hello-world.c
irq-demo.o: irq-demo.c io/ascii.h sys/screen.h \
  io/ascii.h
kbc-demo.o: kbc-demo.c sys/screen.h io/ascii.h \
  io/ascii.h sys/pic.h sys/trap.h sys/sys.h
kbd-demo.o: kbd-demo.c io/kbd.h io/ascii.h \
  sys/screen.h io/ascii.h
mp-config.o: mp-config.c
out-test.o: out-test.c io/out.h
pic-devel.o: pic-devel.c sys/screen.h io/ascii.h \
  io/ascii.h sys/sys.h sys/trap.h io/kbd.h \
  sys/pic.h sys/trap.h
pit-basic-demo.o: pit-basic-demo.c sys/screen.h \
  io/ascii.h io/ascii.h sys/sys.h io/kbd.h
pit-demo.o: pit-demo.c sys/screen.h io/ascii.h \
  io/ascii.h sys/sys.h io/kbd.h sys/pit.h
scancode-demo.o: scancode-demo.c io/ascii.h \
  sys/screen.h io/ascii.h sys/sys.h
screen-test.o: screen-test.c sys/screen.h io/ascii.h
trap-demo.o: trap-demo.c sys/screen.h io/ascii.h \
  io/ascii.h sys/pic.h sys/trap.h sys/sys.h \
  sys/deb.h
common-access.o: common-access.c sys/screen.h io/ascii.h \
  io/ascii.h sys/pic.h sys/trap.h sys/sys.h \
  sys/deb.h
common-access-2.o: common-access-2.c sys/screen.h io/ascii.h \
  io/ascii.h sys/pic.h sys/trap.h sys/sys.h \
  sys/deb.h

trap-devel.o: trap-devel.c sys/screen.h io/ascii.h \
  io/ascii.h sys/trap.h
sys/apic.o: sys/apic.c sys/apic.h sys/pic.h \
  sys/trap.h sys/sys.h io/ascii.h \
  sys/screen.h
sys/deb.o: sys/deb.c sys/deb.h sys/sys.h
sys/kbc.o: sys/kbc.c sys/kbc.h sys/sys.h \
  sys/pic.h sys/trap.h sys/screen.h \
  io/ascii.h
sys/pic.o: sys/pic.c sys/pic.h sys/trap.h \
  sys/screen.h io/ascii.h sys/sys.h
sys/pit.o: sys/pit.c sys/pit.h sys/sys.h
sys/screen.o: sys/screen.c sys/screen.h io/ascii.h \
  sys/sys.h
sys/start.o: sys/start.c sys/screen.h io/ascii.h
sys/trap.o: sys/trap.c sys/trap.h sys/screen.h \
  io/ascii.h sys/trap0.h
sys/trap0.o: sys/trap0.S
sys/boot/big-bang.o: sys/boot/big-bang.S
io/ascii.o: io/ascii.c io/ascii.h
kbd.o: io/kbd.c io/kbd.h sys/sys.h
out.o: io/out.c io/out.h
cpu-trap.o: cpu-trap.c sys/trap.h
vga-demo.o: vga-demo.c sys/sys.h


.PHONY: clean
clean:
	rm -f *.o $(foreach p,${PACKAGES},${p}/*.o)

rules:
	gcc ${CPPFLAGS} -MM \
	../src/*.{c,S} $(foreach p,${PACKAGES},../src/${p}/*.{c,S})
 
