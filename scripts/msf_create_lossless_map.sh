#! /bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "${DIR}/.."

source "${DIR}/apollo_base.sh"
echo $APOLLO_BIN_PREFIX
DIR_NAME=$1
ZONE_ID=$2
IN_FOLDER=$3

function create_lossless_map() {
$APOLLO_BIN_PREFIX/modules/localization/msf/lossless_map_creator \
      --use_plane_inliers_only true \
      --pcd_folders $1 \
      --pose_files $2 \
      --map_folder $IN_FOLDER \
      --zone_id $ZONE_ID \
      --coordinate_type UTM \
      --map_resolution_type single
}
# create_lossless_map "${DIR_NAME}/pcd" "${DIR_NAME}/pcd/corrected_poses.txt"
create_lossless_map "${DIR_NAME}" "${DIR_NAME}/corrected_poses.txt"
