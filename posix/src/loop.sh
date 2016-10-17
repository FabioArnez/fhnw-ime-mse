#!/bin/bash
#-----------------------------
#loop.sh
#(c) H.Buchmann FHNW 2012
#using simply cpu-time
#-----------------------------
echo "starting ${0} PID=${$}"
COUNT=0
while [ true ]
do
 COUNT=$((COUNT+1))  # do something 
done

