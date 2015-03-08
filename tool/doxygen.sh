#--------------------------
#doxygen.sh 
#(c) H.Buchmann FHNW 2015
# ${1} the doxygen configfile
#--------------------------
[[ ! -e ${1} ]] &&
{
 echo "no configuration doxyfile"
 exit 1
}
DOXYGEN_CONFIG=$(realpath ${1})
SIGNATURE=.fbea039d-9be0-40a3-97df-d613a339aa98
while [ ! -e ${SIGNATURE} ]
do
 [[ ${PWD} = "/" ]] &&
 {
  echo "not in repository"
  exit 1
 } 
 cd ..
done
REPO_HOME=${PWD}
doxygen ${DOXYGEN_CONFIG}
