SHELL_DIR=$(cd "$(dirname "$0")"; pwd)

type gawk >/dev/null 2>&1 || { echo >&2 "gawk is required, PLZ install it first."; exit 1; }

pushd ${SHELL_DIR}

# include the config
source ./config.sh

# show dialog for continue
python ./toolsForGame/main.py ${PLUGINS_CAN_SELECT}

popd
