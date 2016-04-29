SHELL_DIR=$(cd "$(dirname "$0")"; pwd)

pushd ${SHELL_DIR}

source ./config.sh

if [ -d ${TARGET_ROOT} ]; then
    rm -rf ${TARGET_ROOT}
fi
mkdir -p ${TARGET_ROOT}

#check the environment
./toolsForPublish/checkEnvironment.sh
source ./toolsForPublish/environment.sh

# output the number of plugins
if [ $1 ]; then
    plugins=(${1//:/ })
else
    plugins=(`echo ${ALL_PLUGINS[@]}`)
fi

length=${#plugins[@]}
echo
echo Now have ${length} plugins
echo

#publish protocols
echo
echo Now publish protocols
echo ---------------------------------
./toolsForPublish/publishPlugin.sh "protocols" ${TARGET_ROOT} ${PLUGIN_ROOT}
echo ---------------------------------

#publish plugins
for plugin_name in ${plugins[@]}
do
    echo
    echo Now publish ${plugin_name}
    echo ---------------------------------
    ./toolsForPublish/publishPlugin.sh "plugins/"${plugin_name} ${TARGET_ROOT} ${PLUGIN_ROOT}
    echo ---------------------------------
done

echo

popd
