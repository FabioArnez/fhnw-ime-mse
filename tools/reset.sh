#!/bin/bash
#----------------------
#reset.sh
#(c) H.Buchmann FHNW 2016
#----------------------
. $(dirname ${0})/openocd.sh

cd ${HOME_BASE}/work
${OPENOCD_BIN} -d2 \
-c init \
-c halt \
-c reset \
-c exit
