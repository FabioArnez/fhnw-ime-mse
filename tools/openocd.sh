. $(dirname ${0})/setup.sh
OPENOCD=${HOME_BASE}/openocd
OPENOCD_SCRIPTS=${OPENOCD}/scripts
OPENOCD_BIN="${OPENOCD}/bin/openocd -s ${OPENOCD_SCRIPTS} -f ${OPENOCD_SCRIPTS}/arduino-zero.cfg"
