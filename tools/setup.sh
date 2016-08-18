#!/bin/bash
#------------------
#setup.sh
#(c) H.Buchmann FHNW 2014
#------------------
SIGNATURE=.fbea039d-9be0-40a3-97df-d613a339aa98
#we are somewhere below SIGNATURE

#find HOME_BASE
BIN_HOME=$(dirname ${0})
pushd ${BIN_HOME} > /dev/null
#echo "----------------- $(pwd)"
while [ true ]
do
 if [[ $(pwd) = "/" ]]; then
  echo "SIGNATURE=${SIGNATURE} not found"
  exit 1
 fi
	
# echo "********************** $(pwd)"
 if [[ -f ${SIGNATURE} ]]; then
  HOME_BASE=$(pwd)/
  break
 fi
 cd ..
done
popd > /dev/null
#echo ${HOME_BASE}
