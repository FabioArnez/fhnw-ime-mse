#------------------------
#run.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#accessible from work
#------------------------
if [ -z ${1} ]
  then echo "usage ${0} imageFile"
       exit 1
fi

if [ ! -f ${1} ]
   then echo "File ${1} dont exists"
        exit 1
fi

../../../qemu/bin/qemu-system-arm -M realview-eb -kernel ${1} -nographic
stty echo
