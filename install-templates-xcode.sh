#!/bin/bash

echo 'cocos2d-x template installer'

COCOS2D_VER='2.1rc0-x-2.1.4'
BASE_TEMPLATE_DIR="/Library/Application Support/Developer/Shared/Xcode"
BASE_TEMPLATE_USER_DIR="$HOME/Library/Application Support/Developer/Shared/Xcode"

force=
user_dir=

usage(){
cat << EOF
usage: $0 [options]

Install / update templates for ${COCOS2D_VER}

OPTIONS:
   -f	force overwrite if directories exist
   -h	this help
   -u	install in user's Library directory instead of global directory
EOF
}

while getopts "fhu" OPTION; do
	case "$OPTION" in
		f)
			force=1
			;;
		h)
			usage
			exit 0
			;;
		u)
			user_dir=1
			;;
	esac
done

# Make sure only root can run our script
if [[ ! $user_dir  && "$(id -u)" != "0" ]]; then
	echo ""
	echo "Error: This script must be run as root in order to copy templates to ${BASE_TEMPLATE_DIR}" 1>&2
	echo ""
	echo "Try running it with 'sudo', or with '-u' to install it only you:" 1>&2
	echo "   sudo $0" 1>&2
	echo "or:" 1>&2
	echo "   $0 -u" 1>&2
exit 1
fi

# Make sure root and user_dir is not executed at the same time
if [[ $user_dir && "$(id -u)" == "0" ]]; then
	echo ""
	echo "Error: Do not run this script as root with the '-u' option." 1>&2
	echo ""
	echo "Either use the '-u' option or run it as root, but not both options at the same time." 1>&2
	echo ""
	echo "RECOMMENDED WAY:" 1>&2
	echo " $0 -u -f" 1>&2
	echo ""
exit 1
fi

copy_files(){
    # SRC_DIR="${SCRIPT_DIR}/${1}"
	rsync -r --exclude=.svn "$1" "$2"
}

check_dst_dir(){
	if [[ -d $DST_DIR ]];  then
		if [[ $force ]]; then
			echo "removing old libraries: ${DST_DIR}"
			rm -rf "${DST_DIR}"
		else
			echo "templates already installed. To force a re-install use the '-f' parameter"
			exit 1
		fi
	fi

	echo ...creating destination directory: $DST_DIR
	mkdir -p "$DST_DIR"
}

# copy_base_mac_files(){
#	echo ...copying cocos2dx files
#	copy_files cocos2dx "$LIBS_DIR"

#	echo ...copying CocosDenshion files
#	copy_files CocosDenshion "$LIBS_DIR"
# }

copy_base_files(){
	echo ...copying cocos2dx files
	copy_files cocos2dx "$LIBS_DIR"


	echo ...copying CocosDenshion files
	copy_files CocosDenshion "$LIBS_DIR"
}

copy_cocos2d_files(){
	echo ...copying cocos2d files
	copy_files cocos2dx "$LIBS_DIR"
	copy_files licenses/LICENSE_cocos2d-x.txt "$LIBS_DIR"
}

copy_cocosdenshion_files(){
	echo ...copying CocosDenshion files
	copy_files CocosDenshion "$LIBS_DIR"
    # copy_files licenses/LICENSE_CocosDenshion.txt "$LIBS_DIR"
}

copy_extensions_files(){
    echo ...copying extension files
    copy_files extensions "$LIBS_DIR"
}

# copy_cocosdenshionextras_files(){
#	echo ...copying CocosDenshionExtras files
#	copy_files CocosDenshion/CocosDenshionExtras "$LIBS_DIR"
# }

# copy_fontlabel_files(){
#	echo ...copying FontLabel files
#	copy_files external/FontLabel "$LIBS_DIR"
#    copy_files licenses/LICENSE_FontLabel.txt "$LIBS_DIR"
# }

# copy_cocoslive_files(){
#	echo ...copying cocoslive files
#	copy_files cocoslive "$LIBS_DIR"

#	echo ...copying TouchJSON files
#	copy_files external/TouchJSON "$LIBS_DIR"
#    copy_files licenses/LICENSE_TouchJSON.txt "$LIBS_DIR"
# }

print_template_banner(){
	echo ''
	echo ''
	echo ''
	echo "$1"
	echo '----------------------------------------------------'
	echo ''
}

# Xcode4 templates
copy_xcode4_project_templates(){
    TEMPLATE_DIR="$HOME/Library/Developer/Xcode/Templates/cocos2d-x/"

	print_template_banner "Installing Xcode 4 cocos2d-x iOS template"

	DST_DIR="$TEMPLATE_DIR"
    check_dst_dir

	LIBS_DIR="$DST_DIR""lib_cocos2dx.xctemplate/libs/"
    mkdir -p "$LIBS_DIR"
    copy_cocos2d_files

	LIBS_DIR="$DST_DIR""lib_cocosdenshion.xctemplate/libs/"
    mkdir -p "$LIBS_DIR"
    copy_cocosdenshion_files

    echo ...copying websockets files
	LIBS_DIR="$DST_DIR""lib_websockets.xctemplate/libs/libwebsockets"
	mkdir -p "$LIBS_DIR"
	copy_files external/libwebsockets/ios "$LIBS_DIR"

    LIBS_DIR="$DST_DIR""lib_extensions.xctemplate/libs/"
    mkdir -p "$LIBS_DIR"
    copy_extensions_files

	echo ...copying template files
	copy_files template/xcode4/ "$DST_DIR"

	echo done!

	print_template_banner "Installing Xcode 4 Chipmunk iOS template"


	LIBS_DIR="$DST_DIR""lib_chipmunk.xctemplate/libs/"
    mkdir -p "$LIBS_DIR"

	echo ...copying Chipmunk files
	copy_files external/chipmunk "$LIBS_DIR"
    copy_files licenses/LICENSE_chipmunk.txt "$LIBS_DIR"

	echo done!

	print_template_banner "Installing Xcode 4 Box2d iOS template"


	LIBS_DIR="$DST_DIR""lib_box2d.xctemplate/libs/"
	mkdir -p "$LIBS_DIR"

	echo ...copying Box2D files
	copy_files external/Box2D "$LIBS_DIR"
	copy_files licenses/LICENSE_box2d.txt "$LIBS_DIR"

	echo done!


	print_template_banner "Installing Xcode 4 lua iOS template"
	
	
	LIBS_DIR="$DST_DIR""lib_lua.xctemplate/libs/"
	mkdir -p "$LIBS_DIR"
	
	echo ...copying lua files
	copy_files scripting/lua "$LIBS_DIR"
	copy_files licenses/LICENSE_lua.txt "$LIBS_DIR"
	copy_files licenses/LICENSE_tolua++.txt "$LIBS_DIR"
	
	echo done!
	
	print_template_banner "Installing Xcode 4 JS iOS template"
	
	LIBS_DIR="$DST_DIR""lib_js.xctemplate/libs/javascript"
	mkdir -p "$LIBS_DIR"
	
	echo ...copying js files
	copy_files scripting/javascript/bindings "$LIBS_DIR"
	copy_files licenses/LICENSE_js.txt "$LIBS_DIR"

	echo done!


	echo ...copying spidermonkey files

	LIBS_DIR="$DST_DIR""lib_spidermonkey.xctemplate/libs/javascript"
	mkdir -p "$LIBS_DIR"
	copy_files scripting/javascript/spidermonkey-ios "$LIBS_DIR"	

	echo done!

    # Move File Templates to correct position
	# DST_DIR="$HOME/Library/Developer/Xcode/Templates/File Templates/cocos2d/"
	# OLD_DIR="$HOME/Library/Developer/Xcode/Templates/cocos2d/"

	# print_template_banner "Installing Xcode 4 CCNode file templates..."

    # check_dst_dir

	# mv -f "$OLD_DIR""/CCNode class.xctemplate" "$DST_DIR"

	echo done!

}

copy_xcode4_project_templates
