#-----------------------
#Makefile
#(c) H.Buchmann FHNW 2011
#$Id$
#TODO setup for 64 bit check with grub
#-----------------------
CC=gcc -m32
CFLAGS="-std=c99"
VPATH=../src
#------------- link pattern
# settings 32 bit architecture
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

first:		first.o
first.o:	first.S
