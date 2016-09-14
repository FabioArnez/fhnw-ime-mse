#!/bin/bash
#----------------------
#flash.sh
#(c) H.Buchmann FHNW 2016
#----------------------
. $(dirname ${0})/openocd.sh

cd ${HOME_BASE}/work
ELF=${1%%.bin}
IMAGE=${ELF}.bin
[[ ! -e ${IMAGE} ]] && { echo "usage ${0} file"; exit 1; }
${OPENOCD_BIN} -d2 \
-c init \
-c halt \
-c "program ${IMAGE} 0x4000" \
-c reset \
-c exit
