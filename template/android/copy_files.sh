#!/bin/bash
# check the args
# $1: root of cocos2dx $2: app name $3: ndk root $4:pakcage path

APP_NAME=$2
COCOS2DX_ROOT=$1
APP_DIR=$COCOS2DX_ROOT/$APP_NAME
HELLOWORLD_ROOT=$COCOS2DX_ROOT/HelloWorld
NDK_ROOT=$3
PACKAGE_PATH=$4
NEED_BOX2D=$5
NEED_CHIPMUNK=$6
NEED_LUA=$7

# xxx.yyy.zzz -> xxx/yyy/zzz
convert_package_path_to_dir(){
    PACKAGE_PATH_DIR=`echo $1 | sed -e "s/\./\//g"`
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
    mkdir $APP_DIR/Classes
    for file in `ls $HELLOWORLD_ROOT/Classes/* | grep -E '.*\.(cpp|h|mk)' `
    do
        if [ -f $file ];then
            cp $file $APP_DIR/Classes
        fi
    done
}

# copy resources
copy_resouces(){
    mkdir $APP_DIR/Resources
    
    for file in $HELLOWORLD_ROOT/Resources/*
    do
        cp -rf $file $APP_DIR/Resources
    done
}

# from HelloWorld copy src and jni to APP_DIR
copy_src_and_jni(){
    cp -rf $HELLOWORLD_ROOT/android/jni $APP_DIR/android
    cp -rf $HELLOWORLD_ROOT/android/src $APP_DIR/android
    
    # repalce Android.mk and Application.mk
    sh $COCOS2DX_ROOT/template/android/classesmk.sh $APP_DIR/Classes/Android.mk $NEED_BOX2D $NEED_CHIPMUNK $NEED_LUA
    sh $COCOS2DX_ROOT/template/android/gamestaticmk.sh $APP_DIR/android/jni/Android.mk $NEED_BOX2D $NEED_CHIPMUNK $NEED_LUA
    sh $COCOS2DX_ROOT/template/android/gamemk.sh $APP_DIR/android/jni/helloworld/Android.mk $NEED_BOX2D $NEED_CHIPMUNK $NEED_LUA
    sh $COCOS2DX_ROOT/template/android/application.sh $APP_DIR/android/jni/Application.mk $NEED_BOX2D $NEED_CHIPMUNK $NEED_LUA
}

# copy build_native.sh and replace something
copy_build_native(){
    # here should use # instead of /, why??
    sed "s#__cocos2dxroot__#$COCOS2DX_ROOT#;s#__ndkroot__#$NDK_ROOT#;s#__projectname__#$APP_NAME#" $COCOS2DX_ROOT/template/android/build_native.sh > $APP_DIR/android/build_native.sh
    chmod u+x $APP_DIR/android/build_native.sh
}

# replace AndroidManifext.xml and change the activity name
# use sed to replace the specified line
modify_androidmanifest(){
    sed "s/ApplicationDemo/$APP_NAME/;s/org\.cocos2dx\.application/$PACKAGE_PATH/" $HELLOWORLD_ROOT/android/AndroidManifest.xml > $APP_DIR/android/AndroidManifest.xml
}

# modify ApplicationDemo.java
modify_applicationdemo(){
    convert_package_path_to_dir $PACKAGE_PATH
    
    # rename APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java to 
    # APP_DIR/android/src/org/cocos2dx/application/$APP_NAME.java, change helloworld to game
    sed "s/ApplicationDemo/$APP_NAME/;s/helloworld/game/;s/org\.cocos2dx\.application/$PACKAGE_PATH/" $APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java > $APP_DIR/android/src/$PACKAGE_PATH_DIR/$APP_NAME.java    
    rm -fr $APP_DIR/android/src/org/cocos2dx/application
    
    # load need .so
    CONTENT=
    if [ $NEED_BOX2D = "true" ];then
        CONTENT=$CONTENT'System.loadLibrary("box2d");'
    fi

    if [ $NEED_CHIPMUNK = "true" ]; then
        CONTENT=$CONTENT'System.loadLibrary("chipmunk");'
    fi

    if [ $NEED_LUA = "true" ]; then
        CONTENT=$CONTENT'System.loadLibrary("lua");'
    fi
    
    sed -i -e "s/System.loadLibrary(\"cocosdenshion\")\;/System.loadLibrary(\"cocosdenshion\")\;$CONTENT/" $APP_DIR/android/src/$PACKAGE_PATH_DIR/$APP_NAME.java
}

modify_layout(){
    cp $HELLOWORLD_ROOT/android/res/layout/helloworld_demo.xml $APP_DIR/android/res/layout
    sed "s/helloworld_gl_surfaceview/game_gl_surfaceview/" $APP_DIR/android/res/layout/helloworld_demo.xml > $APP_DIR/android/res/layout/game_demo.xml
    rm -f $APP_DIR/android/res/layout/main.xml
    rm -f $APP_DIR/android/res/layout/helloworld_demo.xml
}

# android.bat of android 4.0 don't create res/drawable-hdpi res/drawable-ldpi and res/drawable-mdpi.
# These work are done in ADT
copy_icon(){
    if [ ! -d $APP_DIR/android/res/drawable-hdpi ]; then
        cp -r $HELLOWORLD_ROOT/android/res/drawable-hdpi $APP_DIR/android/res
        cp -r $HELLOWORLD_ROOT/android/res/drawable-ldpi $APP_DIR/android/res
        cp -r $HELLOWORLD_ROOT/android/res/drawable-mdpi $APP_DIR/android/res
    fi
}


move_files_into_android
copy_cpp_h_from_helloworld
copy_resouces
copy_src_and_jni
copy_build_native
modify_androidmanifest
modify_applicationdemo
modify_layout
copy_icon
