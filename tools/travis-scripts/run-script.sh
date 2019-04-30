#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../..
CPU_CORES=4

function do_retry()
{
	cmd=$@
	retry_times=5
	retry_wait=3
	c=0
	while [ $c -lt $((retry_times+1)) ]; do
		c=$((c+1))
		echo "Executing \"$cmd\", try $c"
		$cmd && return $?
		if [ ! $c -eq $retry_times ]; then
			echo "Command failed, will retry in $retry_wait secs"
			sleep $retry_wait
		else
			echo "Command failed, giving up."
			return 1
		fi
	done
}

function build_linux()
{
    echo "Building tests ..."
    cd $COCOS2DX_ROOT/build
    mkdir -p linux-build
    cd linux-build
    cmake ../..
    cmake --build .
}

function build_linux_clang_tidy()
{
    echo "Building clang tidy test on Linux ..."
    cd $COCOS2DX_ROOT/build
    mkdir -p clang-tidy-build
    cd clang-tidy-build
    cmake ../.. -DCMAKE_EXPORT_COMPILE_COMMANDS=on
    python $(dirname $(dirname $(readlink -f `which clang-tidy`)))/share/clang/run-clang-tidy.py
}

function build_mac()
{
    NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`

    xcodebuild -project $COCOS2DX_ROOT/build/cocos2d_tests.xcodeproj -scheme "build all tests Mac" -jobs $NUM_OF_CORES -arch x86_64 build | xcpretty
    ##xcpretty has a bug, some xcodebuid fails return value would be treated as 0.
    xcodebuild -project $COCOS2DX_ROOT/build/cocos2d_tests.xcodeproj -scheme "build all tests Mac" -jobs $NUM_OF_CORES -arch x86_64 build
}

function build_ios()
{
    NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`

    xcodebuild -project $COCOS2DX_ROOT/build/cocos2d_tests.xcodeproj -scheme "build all tests iOS" -jobs $NUM_OF_CORES  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build | xcpretty
    #the following commands must not be removed
    xcodebuild -project $COCOS2DX_ROOT/build/cocos2d_tests.xcodeproj -scheme "build all tests iOS" -jobs $NUM_OF_CORES  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
}

function build_mac_cmake()
{
    NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`
    
    # pushd $COCOS2DX_ROOT
    # python -u tools/cocos2d-console/bin/cocos.py --agreement n new -l cpp -p my.pack.qqqq cocos_new_test
    # popd
    # cd $COCOS2DX_ROOT/cocos_new_test
    cd $COCOS2DX_ROOT
    mkdir -p mac_cmake_build
    cd mac_cmake_build
    cmake .. -GXcode
    # cmake --build .
    xcodebuild -project Cocos2d-x.xcodeproj -alltargets -jobs $NUM_OF_CORES build  | xcpretty
    #the following commands must not be removed
    xcodebuild -project Cocos2d-x.xcodeproj -alltargets -jobs $NUM_OF_CORES build
    exit 0
}

function build_ios_cmake()
{
    NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`

    # pushd $COCOS2DX_ROOT
    # python -u tools/cocos2d-console/bin/cocos.py --agreement n new -l cpp -p my.pack.qqqq cocos_new_test
    # popd
    # cd $COCOS2DX_ROOT/cocos_new_test
    cd $COCOS2DX_ROOT
    mkdir -p ios_cmake_build
    cd ios_cmake_build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=$COCOS2DX_ROOT/cmake/ios.toolchain.cmake -GXcode -DIOS_PLATFORM=SIMULATOR64
    # too much logs on console when "cmake --build ."
    # cmake --build .
    xcodebuild -project Cocos2d-x.xcodeproj -alltargets -jobs $NUM_OF_CORES  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build  | xcpretty
    #the following commands must not be removed
    xcodebuild -project Cocos2d-x.xcodeproj -alltargets -jobs $NUM_OF_CORES  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
    exit 0
}

function build_android_cpp_ndk-build()
{
    # Build all samples
    echo "Building Android samples ..."
    source ../environment.sh

    # build cpp-empty-test
    # pushd $COCOS2DX_ROOT/tests/cpp-empty-test
    # cocos compile -p android --android-studio
    # popd

    # build cpp-tests
    pushd $COCOS2DX_ROOT/tests/cpp-tests/proj.android
    do_retry ./gradlew assembleRelease -PPROP_BUILD_TYPE=ndk-build --parallel --info
    popd

    # build js-tests
    # should uncomon it when building time not exceed time limit
    # pushd $COCOS2DX_ROOT/tests/js-tests
    # cocos compile -p android
    # popd
}

function build_android_cpp_cmake()
{
    # Build all samples
    echo "Building Android samples ..."
    source ../environment.sh

    # build cpp-tests
    pushd $COCOS2DX_ROOT/tests/cpp-tests/proj.android
    do_retry ./gradlew assembleRelease -PPROP_BUILD_TYPE=cmake --parallel --info
    popd
}

function build_android_lua_ndk-build()
{
    # Build all samples
    echo "Building Android samples lua ..."
    source ../environment.sh

    # build lua-tests
    pushd $COCOS2DX_ROOT/tests/lua-tests/project/proj.android
    do_retry ./gradlew assembleDebug -PPROP_BUILD_TYPE=ndk-build --parallel --info
    popd

}

function build_android_lua_cmake()
{
    # Build all samples
    echo "Building Android samples lua ..."
    source ../environment.sh

    # build lua-tests
    pushd $COCOS2DX_ROOT/tests/lua-tests/project/proj.android
    do_retry ./gradlew assembleDebug -PPROP_BUILD_TYPE=cmake --parallel --info
    popd

}

function build_android_js_cmake()
{
    # Build all samples
    echo "Building Android samples js ..."
    source ../environment.sh

    # build lua-tests
    pushd $COCOS2DX_ROOT/tests/js-tests/project/proj.android
    do_retry ./gradlew assembleDebug -PPROP_BUILD_TYPE=cmake --parallel --info
    popd

}

function genernate_binding_codes()
{
    if [ $TRAVIS_OS_NAME == "linux" ]; then
        # print some log for libstdc++6
        strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBC
        ls -l /usr/lib/x86_64-linux-gnu/libstdc++*
        dpkg-query -W libstdc++6
        ldd $COCOS2DX_ROOT/tools/bindings-generator/libclang/libclang.so
    fi

    if [ "$TRAVIS_OS_NAME" == "osx" ]; then
        eval "$(pyenv init -)"
    fi
    which python

    source ../environment.sh

    # Generate binding glue codes

    echo "Create auto-generated luabinding glue codes."
    pushd "$COCOS2DX_ROOT/tools/tolua"
    python ./genbindings.py
    popd

    # We don't support building js projects for linux platform,
    # therefore, don't generate js-binding code for it.
    if [ $TRAVIS_OS_NAME != "linux" ] || [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
        echo "Create auto-generated jsbinding glue codes."
        pushd "$COCOS2DX_ROOT/tools/tojs"
        python ./genbindings.py
        popd
    fi
}

# generate cocos_files.json and check diff
function update_cocos_files()
{
    # Don't exit on non-zero return value
    set +e

    COCOSFILE_PATH="$COCOS2DX_ROOT/templates/cocos2dx_files.json"
    echo "Updates cocos_files.json"
    $COCOS2DX_ROOT/tools/travis-scripts/generate-template-files.py
    git diff FETCH_HEAD --stat --exit-code "$COCOSFILE_PATH"
    COCOSFILE_DIFF_RETVAL=$?

    if [ $LUA_DIFF_RETVAL -eq 0 ] && [ $JS_DIFF_RETVAL -eq 0 ] && [ $COCOSFILE_DIFF_RETVAL -eq 0 ]; then
        echo
        echo "No differences in generated files"
        echo "Exiting with success."
        echo
        exit 0
    else
        echo
        echo "Generated files differ from HEAD. Continuing."
        echo
    fi

    # Exit on error
    set -e
}

function generate_pull_request_for_binding_codes_and_cocosfiles()
{
    COCOS_ROBOT_REMOTE="https://${GH_USER}:${GH_PASSWORD}@github.com/${GH_USER}/cocos2d-x.git"
    LUA_AUTO_GENERATE_SCRIPT_PATH="$COCOS2DX_ROOT/cocos/scripting/lua-bindings/auto"
    JS_AUTO_GENERATE_SCRIPT_PATH="$COCOS2DX_ROOT/cocos/scripting/js-bindings/auto"
    ELAPSEDSECS=`date +%s`
    COCOS_BRANCH="update_lua_bindings_$ELAPSEDSECS"
    COMMITTAG="[ci skip][AUTO]: updating luabinding & jsbinding & cocos_file.json automatically"
    PULL_REQUEST_REPO="https://api.github.com/repos/cocos2d/cocos2d-x/pulls"

    pushd "$COCOS2DX_ROOT"
    #Set git user for cocos2d-lua repo
    git config user.email ${GH_EMAIL}
    git config user.name ${GH_USER}#Set remotes
    git remote add upstream "$COCOS_ROBOT_REMOTE" 2> /dev/null > /dev/null

    # Run status to record the output in the log
    git status

    echo
    echo Comparing with origin HEAD ...
    echo
    git fetch origin "$TRAVIS_BRANCH"

    # Don't exit on non-zero return value
    set +e
    git diff FETCH_HEAD --stat --exit-code "$LUA_AUTO_GENERATE_SCRIPT_PATH"
    LUA_DIFF_RETVAL=$?

    git diff FETCH_HEAD --stat --exit-code "$JS_AUTO_GENERATE_SCRIPT_PATH"
    JS_DIFF_RETVAL=$?

    # generate cocos_files.json and check diff
    update_cocos_files

    # Exit on error
    set -e

    git add -f --all "$LUA_AUTO_GENERATE_SCRIPT_PATH"
    git add -f --all "$JS_AUTO_GENERATE_SCRIPT_PATH"
    git add -f --all "$COCOSFILE_PATH"
    git checkout -b "$COCOS_BRANCH"
    git commit -m "$COMMITTAG"

    echo "Pushing to Robot's repo ..."
    git push -fq upstream "$COCOS_BRANCH" 2> /dev/null

    echo "Sending Pull Request to base repo ..."
    curl --user "${GH_USER}:${GH_PASSWORD}" --request POST --data "{ \"title\": \"$COMMITTAG\", \"body\": \"\", \"head\": \"${GH_USER}:${COCOS_BRANCH}\", \"base\": \"${TRAVIS_BRANCH}\"}" "${PULL_REQUEST_REPO}" 2> /dev/null > /dev/null

    popd
}

function run_pull_request()
{
    # linux
    if [ $BUILD_TARGET == 'linux' ]; then
        genernate_binding_codes
        build_linux
    fi

    # linux_clang_tidy_test
    if [ $BUILD_TARGET == 'linux_clang_tidy' ]; then
        build_linux_clang_tidy
    fi

    # android
    if [ $BUILD_TARGET == 'android_cpp_ndk-build' ]; then
        build_android_cpp_ndk-build
    fi

    # android
    if [ $BUILD_TARGET == 'android_cpp_cmake' ]; then
        build_android_cpp_cmake
    fi

    # android_lua
    if [ $BUILD_TARGET == 'android_lua_ndk-build' ]; then
        genernate_binding_codes
        build_android_lua_ndk-build
    fi

    # android_lua
    if [ $BUILD_TARGET == 'android_lua_cmake' ]; then
        genernate_binding_codes
        build_android_lua_cmake
    fi

    # android_js
    if [ $BUILD_TARGET == 'android_js_cmake' ]; then
        genernate_binding_codes
        build_android_js_cmake
    fi

    if [ $BUILD_TARGET == 'mac' ]; then
        genernate_binding_codes
        build_mac
    fi

    if [ $BUILD_TARGET == 'ios' ]; then
        genernate_binding_codes
        build_ios
    fi

    if [ $BUILD_TARGET == 'mac_cmake' ]; then
        genernate_binding_codes
        build_mac_cmake
    fi

    if [ $BUILD_TARGET == 'ios_cmake' ]; then
        genernate_binding_codes
        build_ios_cmake
    fi
}

function run_after_merge()
{
    echo "Building merge commit ..."
    # Re-generation of the javascript bindings can perform push of the new
    # version back to github.  We don't do this for pull requests, or if
    # GH_USER/GH_EMAIL/GH_PASSWORD environment variables are not set correctly
    # by the encoded variables in the .travis.yml file.  (e.g. if cloned repo's
    # want to use travis).
    if [ -z "${GH_EMAIL}" ]; then
        echo "GH_EMAIL not set"
        exit 1
    fi
    if [ -z "${GH_USER}" ]; then
        echo "GH_USER not set"
        exit 1
    fi
    if [ -z "${GH_PASSWORD}" ]; then
        echo "GH_USER not set"
        exit 1
    fi

    genernate_binding_codes
    generate_pull_request_for_binding_codes_and_cocosfiles
}

# build pull request
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then

    echo "Building pull request ..."

    if [ "$BUILD_TARGET" == "android_cocos_new_cpp_test" ]; then
        source ../environment.sh
        pushd $COCOS2DX_ROOT
        update_cocos_files
        python -u tools/cocos2d-console/bin/cocos.py --agreement n new -l cpp -p my.pack.qqqq cocos_new_test
        popd
        pushd $COCOS2DX_ROOT/cocos_new_test/proj.android
        do_retry ./gradlew build
        popd
        exit 0
    fi

    if [ "$BUILD_TARGET" == "linux_cocos_new_lua_test" ]; then
        genernate_binding_codes
        pushd $COCOS2DX_ROOT
        update_cocos_files
        python -u tools/cocos2d-console/bin/cocos.py --agreement n new -l lua -p my.pack.qqqq cocos_new_test
        popd

        echo "Building tests ..."
        cd $COCOS2DX_ROOT/cocos_new_test
        mkdir -p linux-build
        cd linux-build
        cmake ..
        cmake --build .
        exit 0
    fi

    run_pull_request
fi

# run after merging
# - make cocos robot to send PR to cocos2d-x for new binding codes
# - generate cocos_files.json for template
if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
    # only one job need to send PR, linux virtual machine has better performance
    if [ $TRAVIS_OS_NAME == "linux" ] && [ x$GEN_BINDING_AND_COCOSFILE == x"true" ]; then
        run_after_merge
    fi
fi
