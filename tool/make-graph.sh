#----------------------
#make-graph.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#parameters 1: classpath
#           2: all-files
#         [3]: files optional
#----------------------
if [ -z ${1}  -o -z ${2} ]
   then echo "usage ${0} classpath allfiles [files]"
        exit 1
fi
java -cp ${1} dep.Graph ${2} ${3}

