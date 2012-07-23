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
   mkdir $APP_DIR/linux
   for file in `ls $HELLOWORLD_ROOT/linux/* | grep -E '.*\.[cpp|h]' `
    do
        if [ -f $file ];then
            cp $file $APP_DIR/linux
        fi
    done
}


#copy eclipse configures
move_eclipse_configures_into(){
        for file in `ls -a $HELLOWORLD_ROOT/linux/ | grep -E '\..*project' `
		do
			cp $HELLOWORLD_ROOT/linux/$file $APP_DIR/linux/
	    	done

	sed -i "s/HelloWorld/$APP_NAME/" $APP_DIR/linux/.project

	sed -i "s/HelloWorld/$APP_NAME/" $APP_DIR/linux/.cproject
}

move_files_into_linux
move_eclipse_configures_into
