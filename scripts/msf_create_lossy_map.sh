#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${DIR}/.."
source "${DIR}/apollo_base.sh"
echo $APOLLO_BIN_PREFIX
IN_FOLDER=$1
function create_lossy_map() {
	$APOLLO_BIN_PREFIX/modules/localization/msf/lossless_map_to_lossy_map --srcdir $IN_FOLDER/lossless_map --dstdir $IN_FOLDER 
}
create_lossy_map

