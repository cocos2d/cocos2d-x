SHELL_DIR=$(cd "$(dirname "$0")"; pwd)

GAME_PROJECT_DIR=$1
SELECTED_PLUGINS=(${2//:/ })

# if project path is end with '/', delete it
END_CHAR=${GAME_PROJECT_DIR:$((${#GAME_PROJECT_DIR}-1)):1}
if [ ${END_CHAR} = "/" ]; then
    GAME_PROJECT_DIR=${GAME_PROJECT_DIR%/}
fi

# check the game project path
if [ -d "${GAME_PROJECT_DIR}" -a -f "${GAME_PROJECT_DIR}/AndroidManifest.xml" ]; then
    echo "Game project path : ${GAME_PROJECT_DIR}"
    echo "selected plugins  : ${SELECTED_PLUGINS[@]}"
else
    echo "Game project path is wrong.(Not an android project directory)"
    exit 1
fi

getPathForSystem()
{
    START_WITH_CYGWIN=`echo $1 | grep '^/cygdrive/'`
    if [ -z "${START_WITH_CYGWIN}" ]; then
        echo "$1"
    else
        RET=${START_WITH_CYGWIN#/cygdrive/}
        RET=${RET/\//:/}
        echo "${RET}"
    fi
}

pushd ${SHELL_DIR}/../

source ./config.sh

# check publish directory 
if [ -d "${TARGET_ROOT}" ]; then
    # add protocols name to build
    export NEED_PUBLISH="protocols":$2
    
    # Modify mk file
    MK_FILE_PATH="${GAME_PROJECT_DIR}"/jni/Android.mk
    ${SHELL_DIR}/modifyMk.sh "${MK_FILE_PATH}"
    
    # Modify Application.mk file (add stl & rtti configuration)
    APP_MK_FILE_PATH="${GAME_PROJECT_DIR}"/jni/Application.mk
    ${SHELL_DIR}/modifyAppMk.sh "${APP_MK_FILE_PATH}"
    
    # Combin ForRes directory to the res directory of game project
    GAME_RES_DIR="${GAME_PROJECT_DIR}"/res
    ${SHELL_DIR}/modifyRes.sh "${GAME_RES_DIR}"
    
    # get system dir
    SYS_TARGET_ROOT=$(getPathForSystem ${TARGET_ROOT})
    SYS_SHELL_DIR=$(getPathForSystem ${SHELL_DIR})
    SYS_PROJ_DIR=$(getPathForSystem ${GAME_PROJECT_DIR})
    
    # Modify .project file (link publish directory to the game project)
    PROJECT_FILE_PATH="${SYS_PROJ_DIR}"/.project
    python ${SYS_SHELL_DIR}/modifyProject.py "${PROJECT_FILE_PATH}" "${SYS_TARGET_ROOT}"
    
    # Modify .classpath file (link jar files for game project)
    CLASSPATH_FILE="${SYS_PROJ_DIR}"/.classpath
    python ${SYS_SHELL_DIR}/modifyClassPath.py "${CLASSPATH_FILE}" "${NEED_PUBLISH}" "${SYS_TARGET_ROOT}"
    
    # Modify AndroidManifest.xml file (add permission & add activity info)
    MANIFEST_FILE="${SYS_PROJ_DIR}"/AndroidManifest.xml
    python ${SYS_SHELL_DIR}/modifyManifest.py "${MANIFEST_FILE}" "$2" "${SYS_TARGET_ROOT}"
else
    echo "PLZ run the publish.sh script first"
    popd
    exit 1
fi

popd

exit 0
