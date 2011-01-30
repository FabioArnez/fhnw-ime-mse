#------------------------
#run.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#accessible from work
#------------------------
QEMU=../../../qemu
${QEMU}/bin/qemu-system-arm -kernel ${1} -nographic
stty echo

