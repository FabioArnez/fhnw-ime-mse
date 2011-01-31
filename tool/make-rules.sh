#------------------------
#make-rules.sh
#(c) H.Buchmann FHNW 2011
#$Id$
#------------------------
echo ${CPPFLAGS}
rm -rf make.rules
for src in ${*}
do
cat<<EOF | cpp -MM -MT${src%.*}.o ${CPPFLAGS} >> make.rules
 #include "${src}" 
EOF
done


# echo "gcc -MM -MT${src} ${CPPFLAGS} ${src}"
