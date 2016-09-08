#!/bin/bash
#--------------------------
#create-toolchain.sh
#(c) H.Buchmann 2016
#--------------------------
#we are in repo
TOOLCHAIN=gcc-6.2.0-arm-64bit
tar --transform "s,^.,${TOOLCHAIN}," -czvf ${TOOLCHAIN}.tar.gz -C tc .
