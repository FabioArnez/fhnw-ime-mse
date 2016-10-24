#!/bin/bash
#----------------------
#server.sh
#(c) H.Buchmann FHNW 2016
#----------------------
. $(dirname ${0})/openocd.sh
echo "connect: telnet localhost 4444/gdb localhost:3333"

ELF=${1%%.bin}
IMAGE=
[[ ! -z ${ELF} ]] && {
	make ${ELF}
	[[ ${?} -ne 0 ]] && exit ${?}
	IMAGE=${ELF}.bin
		     }
if [[ -f ${IMAGE} ]]; then
   	${OPENOCD_BIN} -d2 \
	-c init \
	-c halt \
	-c "program ${IMAGE} 0x4000"
else
   	${OPENOCD_BIN} -d2 \
	-c init \
	-c halt 
fi



