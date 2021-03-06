#!/bin/bash
#---------------------------
#install-first-time.sh
#(c) H.Buchmann FHNW 2016
#---------------------------
SIGNATURE=.fbea039d-9be0-40a3-97df-d613a339aa98

function resources_help()
{
cat <<EOF
Downwload from Moodle:
 resources.tar.gz 
into repo
EOF
exit 1
}


#check if we are in repo
[[ ! -e ${SIGNATURE} ]] && { echo "you are not in repo"; exit 1; }


#check if resources.tar.gz exists
[[ ! -f resources.tar.gz  ]] && resources_help

tar -xzvf resources.tar.gz

##install 98-openocd.rules you must bee root
[[ ! -f /etc/udev/rules.d/98-openocd.rules ]] && \
	sudo cp resources/98-openocd.rules /etc/udev/rules.d/

##install toolchain
TOOLCHAIN=gcc-6.2.0-arm-64bit
##extract
[[ ! -d resources/${TOOLCHAIN} ]] && \
	tar -xvzf resources/${TOOLCHAIN}.tar.gz  -C resources/
##link to tc
[[ ! -e tc ]] && ln -s resources/${TOOLCHAIN} tc

##install openocd
OPENOCD=openocd
[[ ! -d resources/${OPENOCD} ]] && \
	tar -xvzf resources/${OPENOCD}.tar.gz  -C resources/
[[ ! -e openocd ]] && ln -s resources/${OPENOCD} openocd

##create work
## an existing work will be deleted
[[ -d work ]] && rm -rf work
mkdir work
./tools/makefile.sh
##step into work
pushd work > /dev/null
make namespace
popd  > /dev/null
