plugin_name=$1
TARGET_DIR=$2/${plugin_name}
PLUGIN_ROOT=$3

ANDROID_PROJ_DIR=${PLUGIN_ROOT}/${plugin_name}/proj.android
echo target dir is ${TARGET_DIR}
echo android project dir is ${ANDROID_PROJ_DIR}

#create directory for plugin
mkdir -p ${TARGET_DIR}

###############################
# functions used
###############################
getLibraryFileName()
{
    #get the library file name created by ndk build
    #fine line with LOCAL_MODULE_FILENAME
    DEFINED_FILENAME_LINE=`cat ./jni/Android.mk | grep LOCAL_MODULE_FILENAME`
    
    if [ -n "${DEFINED_FILENAME_LINE}" ]; then
        LIB_FILENAME=${DEFINED_FILENAME_LINE#*\=}
    else
        DEFINED_MODULE_LINE=`cat ./jni/Android.mk | grep LOCAL_MODULE `
        LIB_FILENAME=${DEFINED_MODULE_LINE#*\=}
        LIB_FILENAME=lib${LIB_FILENAME}
    fi
    
    LIB_FILENAME=`echo ${LIB_FILENAME} | sed 's/ //g'`
    LIB_FILENAME=${LIB_FILENAME}.a
    echo ${LIB_FILENAME}
}

getPathForAnt()
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

echo
echo "Publish plugin for android"

pushd ${ANDROID_PROJ_DIR}

#check local.properties file
LOACL_FILE_NAME=local.properties
if [ -f ${LOACL_FILE_NAME} ]; then
    DEFINED_SDK_DIR=`grep sdk.dir= ./${LOACL_FILE_NAME}`
    if [ -z "${DEFINED_SDK_DIR}" ]; then
        ANT_SDK_DIR="$(getPathForAnt ${INPUT_SDK_PATH})"
        echo "sdk.dir=${ANT_SDK_DIR}" >> ${LOACL_FILE_NAME}
    fi
    
    DEFINED_PLUGIN_DIR=`grep plugin.dir= ./${LOACL_FILE_NAME}`
    if [ -z "${DEFINED_PLUGIN_DIR}" ]; then
        ANT_PLUGIN_ROOT_DIR="$(getPathForAnt ${PLUGIN_ROOT})"
        echo "plugin.dir=${ANT_PLUGIN_ROOT_DIR}" >> ${LOACL_FILE_NAME}
    fi
else
    ANT_SDK_DIR="$(getPathForAnt ${INPUT_SDK_PATH})"
    echo "sdk.dir=${ANT_SDK_DIR}" > ${LOACL_FILE_NAME}
    ANT_PLUGIN_ROOT_DIR="$(getPathForAnt ${PLUGIN_ROOT})"
    echo "plugin.dir=${ANT_PLUGIN_ROOT_DIR}" >> ${LOACL_FILE_NAME}
fi

#invoke ant build of plugin
${ANT_PATH}/ant -q clean
${ANT_PATH}/ant -q plugin-publish

#copy .jar files to target directory
mkdir -p ${TARGET_DIR}/android
cp -rf ${ANDROID_PROJ_DIR}/bin/*.jar ${TARGET_DIR}/android
if [ -d ${ANDROID_PROJ_DIR}/sdk ]; then
    cp -rf ${ANDROID_PROJ_DIR}/sdk/*.jar ${TARGET_DIR}/android
fi

#copy android depend on project to publish directory
if [ -d "${ANDROID_PROJ_DIR}/DependProject" ]; then
    cp -rf "${ANDROID_PROJ_DIR}/DependProject" "${TARGET_DIR}/android"
fi

#copy ForManifest.xml file to publish directory
if [ -f "${ANDROID_PROJ_DIR}/ForManifest.xml" ]; then
    cp -rf "${ANDROID_PROJ_DIR}/ForManifest.xml" "${TARGET_DIR}/android"
fi

#copy ForRes directory to publish directory
if [ -d "${ANDROID_PROJ_DIR}/ForRes" ]; then
    cp -rf "${ANDROID_PROJ_DIR}/ForRes" "${TARGET_DIR}/android"
fi

#copy ForAssets directory to publish directory
if [ -d "${ANDROID_PROJ_DIR}/ForAssets" ]; then
    cp -rf "${ANDROID_PROJ_DIR}/ForAssets" "${TARGET_DIR}/android"
fi

#Build C++ code
BUILD_NATIVE_SCRIPT=${ANDROID_PROJ_DIR}/build_native.sh
if [ -f $BUILD_NATIVE_SCRIPT ]; then

    echo "Build C++ code"

    #create include directory
    mkdir -p ${TARGET_DIR}/include
    cp -rf ${PLUGIN_ROOT}/${plugin_name}/include/* ${TARGET_DIR}/include

    #copy android include files
    ADNROID_SOURCE_DIR=${PLUGIN_ROOT}/${plugin_name}/platform/android
    if [ -d ${ADNROID_SOURCE_DIR} ]; then
        HAVE_HEADER_FILE=`find ${ADNROID_SOURCE_DIR} -name "*.h"`
        if [ -n "${HAVE_HEADER_FILE}" ]; then
            cp -rf ${ADNROID_SOURCE_DIR}/*.h "${TARGET_DIR}/android"
        fi
    fi

    #invoke ndk build for plugin project
    ./build_native.sh
    LIB_FILE="$(getLibraryFileName)"
    cp -rf "${ANDROID_PROJ_DIR}/obj/local/armeabi/${LIB_FILE}" "${TARGET_DIR}/android"

    #generate mk file for prebuild
    ${PLUGIN_ROOT}/tools/toolsForPublish/genPrebuildMK.sh ${ANDROID_PROJ_DIR}/jni/Android.mk ${TARGET_DIR}/android/Android.mk
fi

popd
