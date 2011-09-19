# check the args
# $1: root of cocos2dx $2: app name $3: ndk root $4:pakcage path

APP_NAME=$2
COCOS2DX_ROOT=$1
APP_DIR=`pwd`/$5
HELLOWORLD_ROOT=$COCOS2DX_ROOT/HelloWorld
NDK_ROOT=$3
PACKAGE_PATH=$4
projName=$5

echo $APP_DIR $5

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
    rm -r $APP_DIR/android/asset
}

#copy linux's
move_files_into_linux(){
   mkdir $APP_DIR/Linux
   for file in `ls $HELLOWORLD_ROOT/Linux/* | grep -E '.*\.[cpp|h]' `
    do
        if [ -f $file ];then
            cp $file $APP_DIR/Linux
        fi
    done

    cp $HELLOWORLD_ROOT/Linux/postCompiled.sh $APP_DIR/Linux
}

#copy eclipse configures
move_eclipse_configures_into(){
    for file in `ls -a $HELLOWORLD_ROOT/Linux/ | grep -E '\..*project' `
	do
		cp $HELLOWORLD_ROOT/Linux/$file $APP_DIR/Linux/
    	done
	mv $APP_DIR/Linux/.project $APP_DIR/Linux/.project1
	sed "s/HelloWorld/$projName/" $APP_DIR/Linux/.project1 > $APP_DIR/Linux/.project
	rm $APP_DIR/Linux/.project1
}

#copy main sources
copy_cpp_h_from_helloworld(){
    mkdir $APP_DIR/Classes
    for file in `ls $HELLOWORLD_ROOT/Classes/* | grep -E '.*\.[cpp|h]' `
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
    sed "s/ApplicationDemo/$APP_NAME/;s/helloworld/game/;s/org\.cocos2dx\.application/$PACKAGE_PATH/" $APP_DIR/android/src/org/cocos2dx/application/ApplicationDemo.java > $APP_DIR/android/src/$PACKAGE_PATH_DIR/tempfile.java    
    rm -fr $APP_DIR/android/src/org/cocos2dx/application
    mv $APP_DIR/android/src/$PACKAGE_PATH_DIR/tempfile.java $APP_DIR/android/src/$PACKAGE_PATH_DIR/$APP_NAME.java
    
    
}

modify_layout(){
    cp $HELLOWORLD_ROOT/android/res/layout/helloworld_demo.xml $APP_DIR/android/res/layout
    sed "s/helloworld_gl_surfaceview/game_gl_surfaceview/" $APP_DIR/android/res/layout/helloworld_demo.xml > $APP_DIR/android/res/layout/game_demo.xml
    rm -f $APP_DIR/android/res/layout/main.xml
    rm -f $APP_DIR/android/res/layout/helloworld_demo.xml
}


move_files_into_android
move_files_into_linux
move_eclipse_configures_into
copy_cpp_h_from_helloworld
copy_resouces
copy_src_and_jni
copy_build_native
modify_androidmanifest
modify_applicationdemo
modify_layout
