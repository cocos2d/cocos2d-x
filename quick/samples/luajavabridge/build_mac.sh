DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ ! -d "$DIR/test/LuaJavaBridge" ]; then
    $DIR/create_test_project.sh
fi

$DIR/test/LuaJavaBridge/frameworks/runtime-src/proj.android/build_apk.sh -bldm release