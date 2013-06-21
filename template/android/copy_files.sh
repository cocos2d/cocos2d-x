#!/bin/bash
# check the args
# $1: root of cocos2dx $2: app name $3: ndk root $4:pakcage path

APP_NAME=$2
COCOS2DX_ROOT=$1
APP_DIR=$COCOS2DX_ROOT/$APP_NAME
HELLOWORLD_ROOT=$COCOS2DX_ROOT/samples/Cpp/HelloCpp
COCOSJAVALIB_ROOT=$COCOS2DX_ROOT/cocos2dx/platform/android/java
NDK_ROOT=$3
PACKAGE_PATH=$4
NEED_BOX2D=$5
NEED_CHIPMUNK=$6
NEED_LUA=$7

# xxx.yyy.zzz -> xxx/yyy/zzz
convert_package_path_to_dir(){
    PACKAGE_PATH_DIR=`echo $1 | sed -e "s/\./\//g"`
}

copy_cpp_h(){
    mkdir $APP_DIR/Classes
    for file in $COCOS2DX_ROOT/template/android/Classes/*
    do
        cp $file $APP_DIR/Classes
    done
}

# copy resources
copy_resouces(){
    mkdir $APP_DIR/Resources
    
    for file in $HELLOWORLD_ROOT/Resources/iphone/*
    do
        cp -rf $file $APP_DIR/Resources
    done
}

# from HelloWorld copy src and jni to APP_DIR
copy_src_and_jni(){
    cp -rf $HELLOWORLD_ROOT/proj.android/jni $APP_DIR/proj.android
    cp -rf $HELLOWORLD_ROOT/proj.android/src $APP_DIR/proj.android
    
    # replace Android.mk
    sh $COCOS2DX_ROOT/template/android/gamemk.sh $APP_DIR/proj.android/jni/Android.mk $NEED_BOX2D $NEED_CHIPMUNK $NEED_LUA

    if [ $NEED_LUA = "true" ]; then
        # copy lua script
        cp "$COCOS2DX_ROOT"/scripting/lua/script/* "$APP_DIR"/Resources
    fi
}

# copy build_native.sh and replace something
copy_build_native(){
    # here should use # instead of /, why??
    sed "s#__cocos2dxroot__#$COCOS2DX_ROOT#;s#__ndkroot__#$NDK_ROOT#;s#__projectname__#$APP_NAME#" $COCOS2DX_ROOT/template/android/build_native.sh > $APP_DIR/proj.android/build_native.sh
    chmod u+x $APP_DIR/proj.android/build_native.sh
}

# copy debugger script and replace templated parameters
copy_ndkgdb(){
    sed "s#__projectname__#$APP_NAME#;s#__packagename__#$PACKAGE_PATH#" $COCOS2DX_ROOT/template/android/ndkgdb.sh > $APP_DIR/proj.android/ndkgdb.sh
    chmod u+x $APP_DIR/proj.android/ndkgdb.sh
}

# copy .project and .classpath and replace project name
modify_project_classpath(){
    sed "s/HelloCpp/$APP_NAME/" $COCOS2DX_ROOT/template/android/.project > $APP_DIR/proj.android/.project
    cp -f $COCOS2DX_ROOT/template/android/.classpath $APP_DIR/proj.android
}

# replace AndroidManifext.xml and change the activity name
# use sed to replace the specified line
modify_androidmanifest(){
    sed "s/HelloCpp/$APP_NAME/;s/org\.cocos2dx\.hellocpp/$PACKAGE_PATH/" $HELLOWORLD_ROOT/proj.android/AndroidManifest.xml > $APP_DIR/proj.android/AndroidManifest.xml
}

# modify HelloCpp.java
modify_applicationdemo(){
    convert_package_path_to_dir $PACKAGE_PATH
    
    # rename APP_DIR/android/src/org/cocos2dx/hellocpp/HelloCpp.java to 
    # APP_DIR/android/src/org/cocos2dx/hellocpp/$APP_NAME.java, change hellocpp to game
    sed "s/HelloCpp/$APP_NAME/;s/org\.cocos2dx\.hellocpp/$PACKAGE_PATH/;s/hellocpp/game/" $APP_DIR/proj.android/src/org/cocos2dx/hellocpp/HelloCpp.java > $APP_DIR/proj.android/src/$PACKAGE_PATH_DIR/$APP_NAME.java    
    rm -fr $APP_DIR/proj.android/src/org/cocos2dx/hellocpp
}

modify_layout(){
    rm -f $APP_DIR/proj.android/res/layout/main.xml
}

# android.bat of android 4.0 don't create res/drawable-hdpi res/drawable-ldpi and res/drawable-mdpi.
# These work are done in ADT
copy_icon(){
    if [ ! -d $APP_DIR/proj.android/res/drawable-hdpi ]; then
        cp -r $HELLOWORLD_ROOT/proj.android/res/drawable-hdpi $APP_DIR/proj.android/res
        cp -r $HELLOWORLD_ROOT/proj.android/res/drawable-ldpi $APP_DIR/proj.android/res
        cp -r $HELLOWORLD_ROOT/proj.android/res/drawable-mdpi $APP_DIR/proj.android/res
    fi
}

copy_cpp_h
copy_resouces
copy_src_and_jni
copy_build_native
copy_ndkgdb
#modify_project_classpath
modify_androidmanifest
modify_applicationdemo
modify_layout
copy_icon
