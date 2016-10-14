#!/bin/bash
#------------------------------
#sloccount.sh
#(c) H.Buchmann FNNW 2016
#${1}: source directory
#${2}: data directory
#------------------------------
function usage()
{
 echo "usage ${0} source-dir data-dir"
 exit 1
}

[[ ! -d ${1} ]] && { usage; }
[[ ! -d ${2} ]] && { usage; }
#generate
#sloccount --datadir ${2} -- ${1}

#get info
#sloccount --filecount --details --cached --datadir ${2}
sloccount  --cached --datadir ${2}
#count directories without .git
#find ${1} -type d -not -wholename '*.git*'  | wc -l
