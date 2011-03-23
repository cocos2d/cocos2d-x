# check the args
# $0: root of cocos2dx $1: app name

APP_NAME=$2
APP_DIR=$1/$2
HELLOWORLD_ROOT=$1/HelloWorld

check_arguments(){
    if [ $# != 2 ]; then
        echo usage $0 root_of_cocos2dx appname
        exit -1
    fi
}

# make director andorid and copy all files and directories into it
move_files_into_android(){
    mkdir $APP_DIR/android

    for file in $APP_DIR/*
    do
        if [ -d $file ]; then
            if [ $file != $APP_DIR/android ]; then
                mv -f $file $APP_DIR/android
            fi
        fi

        if [ -f $file ]; then
            mv $file $APP_DIR/android
        fi
    done
}

copy_cpp_h_from_helloworld(){
    for file in `ls $HELLOWORLD_ROOT/* | grep -E '.*\.[cpp|h]' `
    do
        if [ -f $file ];then
            cp $file $APP_DIR
        fi
    done
}

# make director assets and copy resources
copy_resouces_into_asserts(){
    mkdir $APP_DIR/android/assets
    
    for file in $HELLOWORLD_ROOT/Resource/*
    do
        cp $file $APP_DIR/android/assets
    done
}

# from HelloWorld copy src and jni to APP_DIR
copy_src_and_jni(){
    cp -rf $HELLOWORLD_ROOT/android/jni $APP_DIR/android
    cp -rf $HELLOWORLD_ROOT/android/src $APP_DIR/android
}

# replace AndroidManifext.xml and change the activity name
# use sed to replace the specified line
modify_androidmanifest(){
    cp -f $HELLOWORLD_ROOT/android/AndroidManifest.xml $APP_DIR/android
    sed "s/ApplicationDemo/$APP_NAME/" $APP_DIR/android/AndroidManifest.xml > $APP_DIR/android/tempfile
    mv $APP_DIR/android/tempfile $APP_DIR/android/AndroidManifest.xml
}


# rename APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java 
# and change some content
modify_applicationdemo(){
    sed "s/ApplicationDemo/$APP_NAME/" $APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java > $APP_DIR/android/src/org/cocos2dx/application/tempfile.java
    rm -f $APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java
    mv $APP_DIR/android/src/org/cocos2dx/application/tempfile.java $APP_DIR/android/src/org/cocos2dx/application/$APP_NAME.java
}

check_arguments $1 $2
move_files_into_android
copy_cpp_h_from_helloworld
copy_resouces_into_asserts
copy_src_and_jni
modify_androidmanifest
modify_applicationdemo
