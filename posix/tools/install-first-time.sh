#!/bin/bash
#---------------------------
#install-first-time.sh
#(c) H.Buchmann FHNW 2016
#---------------------------
SIGNATURE=.fbea039d-9be0-40a3-97df-d613a339aa98

#check if we are in repo
[[ ! -e ${SIGNATURE} ]] && { echo "you are not in repo"; exit 1; }
pushd posix >/dev/null
#create work
# an existing work will be deleted
[[ -d work ]] && rm -rf work
mkdir work
pushd work >/dev/null
#link to config/Makfile
ln -s ../config/Makefile

#create empty make.rules
touch make.rules

make rules

popd >/dev/null
popd >/dev/null
