#!/bin/bash
#--------------------------
#create-resources.sh
#(c) H.Buchmann 2016
#--------------------------
#we are in repo
RESOURCES="./gcc-6.2.0-arm-64bit.tar.gz ./98-openocd.rules ./openocd.tar.gz"
tar --transform "s,^.,resources," -czvf resources.tar.gz -C resources ${RESOURCES}
