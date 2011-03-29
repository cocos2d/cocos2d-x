# check the args
# $1: root of cocos2dx $2: app name $3: ndk root

APP_NAME=$2
COCOS2DX_ROOT=$1
APP_DIR=$COCOS2DX_ROOT/$APP_NAME
HELLOWORLD_ROOT=$COCOS2DX_ROOT/HelloWorld
NDK_ROOT=$3

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
    mkdir $APP_DIR/Classes
    for file in `ls $HELLOWORLD_ROOT/* | grep -E '.*\.[cpp|h]' `
    do
        if [ -f $file ];then
            cp $file $APP_DIR/Classes
        fi
    done
}

# copy resources
copy_resouces(){
    mkdir $APP_DIR/Resource
    
    for file in $HELLOWORLD_ROOT/Resource/*
    do
        cp $file $APP_DIR/Resource
    done
}

# from HelloWorld copy src and jni to APP_DIR
copy_src_and_jni(){
    cp -rf $HELLOWORLD_ROOT/android/jni $APP_DIR/android
    cp -rf $HELLOWORLD_ROOT/android/src $APP_DIR/android
    
    # repalce Android.mk and Application.mk
    cat $COCOS2DX_ROOT/template/android/AndroidTemplate1.mk > $APP_DIR/android/jni/helloworld/Android.mk
    cat $COCOS2DX_ROOT/template/android/Application.mk > $APP_DIR/android/jni/Application.mk
}

# copy build_native.sh and replace something
copy_build_native(){
    # here should use # instead of /, why??
    sed "s#__cocos2dxroot__#$COCOS2DX_ROOT#;s#__ndkroot__#$NDK_ROOT#;s#__projectname__#$APP_NAME#" $COCOS2DX_ROOT/template/android/build_native.sh > $APP_DIR/android/build_native.sh
}

# replace AndroidManifext.xml and change the activity name
# use sed to replace the specified line
modify_androidmanifest(){
    sed "s/ApplicationDemo/$APP_NAME/" $HELLOWORLD_ROOT/android/AndroidManifest.xml > $APP_DIR/android/AndroidManifest.xml
}

# rename APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java 
# and change some content
modify_applicationdemo(){
    sed "s/ApplicationDemo/$APP_NAME/" $APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java > $APP_DIR/android/src/org/cocos2dx/application/tempfile.java
    rm -f $APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java
    mv $APP_DIR/android/src/org/cocos2dx/application/tempfile.java $APP_DIR/android/src/org/cocos2dx/application/$APP_NAME.java
}

move_files_into_android
copy_cpp_h_from_helloworld
copy_resouces
copy_src_and_jni
copy_build_native
modify_androidmanifest
modify_applicationdemo
