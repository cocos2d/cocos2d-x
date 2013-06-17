SHELL_DIR=$(cd "$(dirname "$0")"; pwd)
pushd ${SHELL_DIR}

# include the config
source ./config.sh

# show dialog for continue
python ./toolsForGame/main.py ${PLUGINS_CAN_SELECT}

popd
