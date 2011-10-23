function check_vars()
{
    if [ -z ${ANDROID_NDK_ROOT:+x} ]
    then
	echo "Error! Variable ANDROID_NDK_ROOT is not set"
	exit 1
    else
	echo "ANDROID_NDK_ROOT = " $ANDROID_NDK_ROOT
    fi

    if [ -z "${ANDROID_SDK_ROOT:+x}" ]
    then
	echo "Error! Variable ANDROID_SDK_ROOT is not set"
	exit 1
    else
	echo "ANDROID_SDK_ROOT = " $ANDROID_SDK_ROOT
    fi

    if [ -z "${COCOS2DX_ROOT:+x}" ]
    then
	echo "Error! Variable COCOS2DX_ROOT is not set"
	exit 1
    else
	echo "COCOS2DX_ROOT = " $COCOS2DX_ROOT
    fi
}
