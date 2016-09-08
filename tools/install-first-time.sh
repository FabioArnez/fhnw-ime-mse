#!/bin/bash
#---------------------------
#install-first-time.sh
#(c) H.Buchmann FHNW 2016
#---------------------------
SIGNATURE=.fbea039d-9be0-40a3-97df-d613a339aa98

#check if we are in repo
[[ ! -e ${SIGNATURE} ]] && { echo "you are not in repo"; exit 1; }

TOOLCHAIN=gcc-6.2.0-arm-64bit
#install toolchain

#extract
[[ ! -d resources/${TOOLCHAIN} ]] && tar -xvzf resources/${TOOLCHAIN}.tar.gz  -C resources/
#link
[[ ! -e tc ]] && ln -s resources/${TOOLCHAIN} tc

#create work
# an existing work will be deleted
[[ -d work ]] && rm -rf work
mkdir work
./tools/makefile.sh
#step into work
pushd work > /dev/null
make namespace
popd  > /dev/null
