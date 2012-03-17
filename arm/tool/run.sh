#------------------------
#run.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#accessible from work
#------------------------
if [ -z ${1} ]
  then echo "usage ${0} imageFile"
       exit 1
fi

if [ ! -f ${1} ]
   then echo "File ${1} dont exists"
        exit 1
fi
#MACHINE=versatileab
MACHINE=realview-eb
QEMU=../../../qemu/bin/
#QEMU=
${QEMU}qemu-system-arm -M ${MACHINE} -kernel ${1} -serial stdio -sdl -display sdl
#gdb --args ${QEMU}qemu-system-arm -M ${MACHINE} -kernel ${1} -serial stdio -sdl -display sdl
#-chardev pipe,id=console,path=console
#-nographic
stty echo
