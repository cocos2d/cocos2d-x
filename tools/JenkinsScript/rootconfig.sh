#old=NDK_ROOT_LOCAL=/home/james/Software/android/android-ndk-r8b
#new=$ANDROID_NDK
#echo $new
#sed 's/old/new/g' build_native.sh
#sed -i '3,4d' build_native.sh
#sed -i '3 i\ i love you cdy' build_native.sh
NDK_ROOT=$($CYGWIN/bin/cygpath.exe $ANDROID_NDK)
#COCOS2DX_ROOT=$($CYGWIN/bin/cygpath.exe $cd)
echo $NDK_ROOT
CUR=$(pwd)
cd ../../..
tmp=$(pwd)
COCOS2DX=$($CYGWIN/bin/cygpath.exe $tmp)
echo $COCOS2DX
var1=NDK_ROOT_LOCAL=
_NDK_ROOT=${var1}${NDK_ROOT}

var2=COCOS2DX_ROOT_LOCAL=
_COCOS2DX_ROOT=${var2}${COCOS2DX}
echo $_NDK_ROOT
echo $_COCOS2DX_ROOT

sed -i '3,4d' $CUR/build_native.sh
sed -i '13d' $CUR/project.properties
sed -i "3 i\\$_NDK_ROOT" $CUR/build_native.sh
sed -i "4 i\\$_COCOS2DX_ROOT" $CUR/build_native.sh