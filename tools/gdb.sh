#!/bin/bash
#----------------------
#gdb.sh
#(c) H.Buchmann FHNW 2016
#we are in work
#----------------------
. $(dirname ${0})/openocd.sh
echo "-------------- ${HOME_BASE}"
ELF=${1%%.bin}
[[ ! -f ${ELF} ]] && { echo "usage ${0} application (ELF file)" ; exit 1 ; }
GDB=${TOOLCHAIN}-gdb
${GDB} -x ../config/gdb.init ${ELF}
