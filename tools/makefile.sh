#!/bin/bash
#-----------------------------
#makefile.sh
#creates makefile from projects.xml
#(c) H.Buchmann FHNW 2016
#-----------------------------
. $(dirname ${0})/setup.sh
java -jar ${HOME_BASE}/tools/projects.jar makefile ../config/projects.xml ${HOME_BASE}
