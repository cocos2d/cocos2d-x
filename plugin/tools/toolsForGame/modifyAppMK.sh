# Modify mk file
MK_FILE_PATH=$1
TEMP_FILE_PATH=$(dirname ${MK_FILE_PATH})/tempAppMK.txt

STL_CFG="gnustl_static"
CPP_FLAG="-frtti"

# check if mk file existed or not
if [ -f ${MK_FILE_PATH} ]; then
    gawk '
    BEGIN { addSTL = 1; addRTTI = 1; }
    {
        if (match($0, /^([\s]*[^#]*)APP_STL[\s]*/))
        {
            printf "APP_STL := gnustl_static\n";
            addSTL = 0;
        } else
        if (match($0, /^([\s]*[^#]*)-frtti/))
        {
            printf "%s\n",$0;
            addRTTI = 0;
        } else
        {
            printf "%s\n",$0;
        }
    }
    END {
        if (addSTL)
        {
            printf "APP_STL := gnustl_static\n";
        }
        
        if (addRTTI)
        {
            printf "APP_CPPFLAGS += -frtti\n";
        }
    }' "${MK_FILE_PATH}" > "${TEMP_FILE_PATH}"
    cp -rf ${TEMP_FILE_PATH} ${MK_FILE_PATH}
    rm -rf ${TEMP_FILE_PATH}
else
    echo "APP_STL := ${STL_CFG}" > ${MK_FILE_PATH}
    echo "APP_CPPFLAGS += ${CPP_FLAG}" >> ${MK_FILE_PATH}
fi

exit 0
