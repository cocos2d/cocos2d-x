# Modify mk file
MK_FILE_PATH=$1
TEMP_FILE_PATH=$(dirname ${MK_FILE_PATH})/temp.txt
SELECTED_PLUGINS=(${NEED_PUBLISH//:/ })

###############################
# functions used
###############################
getStaticModuleName()
{
    #get the library file name created by ndk build
    #find line with LOCAL_MODULE
    _FUN_DEFINED_LINE=`grep 'LOCAL_MODULE[ :]' ${TARGET_ROOT}/$1/android/Android.mk`
    
    if [ -n "${_FUN_DEFINED_LINE}" ]; then
        _FUN_LIB_FILENAME=${_FUN_DEFINED_LINE#*\=}
    fi
    
    _FUN_LIB_FILENAME=`echo ${_FUN_LIB_FILENAME} | sed 's/ //g'`
    echo ${_FUN_LIB_FILENAME}
}

# check if mk file existed or not
if [ -f ${MK_FILE_PATH} ]; then
    ADD_MODULE_STR=""
    ADD_IMPORT_STR=""
    for plugin_name in ${SELECTED_PLUGINS[@]}
    do
        PLUGIN_MK_FILE=${TARGET_ROOT}/${plugin_name}/android/Android.mk
        if [ ! -f "${PLUGIN_MK_FILE}" ]; then
            continue
        fi

        PLUGIN_MODULE_NAME="$(getStaticModuleName ${plugin_name})"
        HAVE_PLUGIN=`grep "^\([\s]*[^#]*\)${PLUGIN_MODULE_NAME}" ${MK_FILE_PATH}`
        if [ "${HAVE_PLUGIN}" ]; then
            # already have this plugin
            echo "Plugin ${plugin_name} have added in Android.mk"
            continue
        else
            if [ -z "${ADD_MODULE_STR}" ]; then
                ADD_MODULE_STR=${PLUGIN_MODULE_NAME}
            else
                ADD_MODULE_STR="${ADD_MODULE_STR} ${PLUGIN_MODULE_NAME}"
            fi
            
            NEW_LINE="\$(call import-module,${plugin_name}/android)"
            if [ -z "${ADD_IMPORT_STR}" ]; then
                ADD_IMPORT_STR=${NEW_LINE}
            else
                ADD_IMPORT_STR="${ADD_IMPORT_STR}:${NEW_LINE}"
            fi
        fi
    done

    # Modify the mk file if necessary
    if [ "${ADD_MODULE_STR}" ]; then
        gawk '
            {
                ModuleStr="'"$ADD_MODULE_STR"'";
                ImportStr="'"$ADD_IMPORT_STR"'";
                if (match($0, /^([\s]*[^#]*)LOCAL_WHOLE_STATIC_LIBRARIES/) && ! PROC1)
                {
                    PROC1 = 1;
                    if (match($0, /\\$/))
                    {
                        printf "%s\n",$0;
                        printf "%s \\\n",ModuleStr;
                    } else
                    {
                        printf "%s \\\n",$0;
                        printf "%s\n",ModuleStr;
                    }
                } else
                if (match($0, /^([\s]*[^#]*)call[\s]*import-module/) && ! PROC2)
                {
                    printf $0;
                    split(ImportStr,arr,":")
                    for (j=0; j<length(arr); j++)
                    {
                        oneStr=arr[j];
                        printf "%s\n",oneStr;
                    }
                    PROC2 = 1;
                } else
                if (match($0, /^([\s]*[^#]*)include[ \t]+\$\(BUILD_(SHARED|STATIC)_LIBRARY\)/) && ! PROC1)
                {
                    PROC1 = 1;
                    printf "\nLOCAL_WHOLE_STATIC_LIBRARIES := %s\n\n",ModuleStr;
                    printf "%s\n",$0;
                } else {
                    printf "%s\n",$0;
                }
            }
            END {
                if (! PROC1)
                {
                    printf "\nLOCAL_WHOLE_STATIC_LIBRARIES := %s\n",ModuleStr;
                }
                
                if (! PROC2)
                {
                    split(ImportStr,arr,":")
                    for (j=0; j<length(arr); j++)
                    {
                        oneStr=arr[j];
                        printf "%s\n",oneStr;
                    }
                }
            }' ${MK_FILE_PATH} > ${TEMP_FILE_PATH}
        cp -rf ${TEMP_FILE_PATH} ${MK_FILE_PATH}
        rm -rf ${TEMP_FILE_PATH}
    fi
else
    echo "Can't find Android.mk file"
fi

exit 0

