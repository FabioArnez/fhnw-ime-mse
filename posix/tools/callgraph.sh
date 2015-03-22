#-------------------
#callgraph.sh
#(c) H.Buchmann FHNW 2015
#see http://stackoverflow.com/questions/5373714/generate-calling-graph-for-c-code
# ${1} cc file 
# ${2} options
#-------------------
clang++ -std=c++11 ${2} -S -emit-llvm ${1} -o- | \
opt  -analyze -std-link-opts -dot-callgraph 
c++filt<callgraph.dot 
