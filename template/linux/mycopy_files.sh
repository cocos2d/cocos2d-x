# check the args
# $1: root of cocos2dx $2: app name $3: ndk root $4:pakcage path

APP_NAME=$2
COCOS2DX_ROOT=$1
APP_DIR=$COCOS2DX_ROOT/$APP_NAME
HELLOWORLD_ROOT=$COCOS2DX_ROOT/HelloWorld
NDK_ROOT=$3
PACKAGE_PATH=$4

# invoke android template
sh $(dirname "$0")/../android/copy_files.sh $1 $2 $3 $4

#copy linux's
move_files_into_linux(){
   mkdir $APP_DIR/Linux
   for file in `ls $HELLOWORLD_ROOT/Linux/* | grep -E '.*\.[cpp|h]' `
    do
        if [ -f $file ];then
            cp $file $APP_DIR/Linux
        fi
    done
}

# set resources path to Resources in AppDelegate.cpp, when #925 is resolved, it should be deleted
change_resources_path(){
    sed "s/CCFileUtils::setResourcePath(\"\.\.\\/Resource\/\")/CCFileUtils::setResourcePath(\"\.\.\\/Resources\/\")/" $APP_DIR/Classes/AppDelegate.cpp > $APP_DIR/Classes/temp.cpp
    rm -f $APP_DIR/Classes/AppDelegate.cpp
    mv $APP_DIR/Classes/temp.cpp $APP_DIR/Classes/AppDelegate.cpp
}

#copy eclipse configures
move_eclipse_configures_into(){
        for file in `ls -a $HELLOWORLD_ROOT/Linux/ | grep -E '\..*project' `
		do
			cp $HELLOWORLD_ROOT/Linux/$file $APP_DIR/Linux/
	    	done

	sed -i "s/HelloWorld/$APP_NAME/" $APP_DIR/Linux/.project

	sed -i "s/HelloWorld/$APP_NAME/" $APP_DIR/Linux/.cproject
}

move_files_into_linux
change_resources_path
move_eclipse_configures_into
