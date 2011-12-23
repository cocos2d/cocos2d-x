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

#copy eclipse configures
move_eclipse_configures_into(){
        for file in `ls -a $HELLOWORLD_ROOT/Linux/ | grep -E '\..*project' `
		do
			cp $HELLOWORLD_ROOT/Linux/$file $APP_DIR/Linux/
	    	done

	sed -i "s/HelloWorld/$APP_NAME/" $APP_DIR/Linux/.project

	sed -i "s:\.\./\.\./\.\./:$COCOS2DX_ROOT:;s:helloworld:$APP_NAME:" $APP_DIR/Linux/.cproject
}

move_files_into_linux
move_eclipse_configures_into
