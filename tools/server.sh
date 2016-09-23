#!/bin/bash
#----------------------
#flash.sh
#(c) H.Buchmann FHNW 2016
#----------------------
. $(dirname ${0})/openocd.sh
echo "connect: telnet localhost 4444"
${OPENOCD_BIN} -d2 \
-c init \
-c reset \
-c halt
