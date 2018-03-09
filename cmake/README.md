
# CMake Guide

CMake is an open-source, cross-platform family of tools designed to build, test and package software. CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.

## Requirement

1. Open your terminal, input `cmake --version`, if the cmake version is lower than 3.1, please upgrade

2. You should use out-of-source build, that is said you need to create a different directory from `cocos2d-x` to execute cmake command.

## Step by Step

### Build in Linux

```sh
cd cocos2d-x
mkdir linux-build && cd linux-build
cmake ..
make
``` 

Execute `make help` to see all build targets, `make <target>` build specified target

### Generate Visual Studio project

```sh
cd cocos2d-x
mkdir win32-build && cd win32-build
cmake .. -G"Visual Studio 15 2017" -Tv141
```

Execute `cmake --build .` to compile, or open `Cocos2d-x.sln` in Explorer to use the generated project. 

### Generate macOS Project

```sh
cd cocos2d-x
mkdir mac-build && cd msc-build
cmake .. -GXcode
open Cocos2d-x.xcodeproj
```

### Generate iOS Project

```sh
cd cocos2d-x
mkdir ios-build && cd ios-build
cmake .. -GXcode -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake
open Cocos2d-x.xcodeproj
```

### CMake in Android Studio

We use the Gradle to Android applacition, and Gradle use cmake to build the native code, see the [property](https://github.com/cocos2d/cocos2d-x/blob/84be684e3858393a6f3efc50e3f95d4e0ac92a20/tests/cpp-empty-test/proj.android/gradle.properties#L38): `PROP_NDK_MODE`, it control the way of native build

```sh
# android cmake support
# uncomment it, native code will build by cmake
# keep comment, native code will build by ndkBuild
PROP_NDK_MODE=cmake
```

If you want to add cmake build arguments, please add it at [externalNativeBuild](https://github.com/cocos2d/cocos2d-x/blob/84be684e3858393a6f3efc50e3f95d4e0ac92a20/tests/cpp-empty-test/proj.android/app/build.gradle#L25) block of [app/build.gradle] file.

## Prebuilt feature

To solve the problem that compiling engine sources spends too long time, we add the feature of pre-builds libs. Using this feature you only need build engine sources once for a specific environment.

### Example

This is an example of build cpp libs once, and use it in different cpp project.

```sh
cocos new -l cpp -p my.pack.app1 test_app1
mkdir app1_build && cd app1_build
cmake ../test_app1 -DGEN_COCOS_PREBUILT=ON
make prebuilt
```

Close option `GEN_COCOS_PREBUILT` and open `USE_COCOS_PREBUILT` to use prebuilt in the same project

```sh
cmake ../test_app1 -DGEN_COCOS_PREBUILT=OFF -DUSE_COCOS_PREBUILT=ON
make TemplateCpp
open bin/TemplateCpp.app
```

Add `-DUSE_COCOS_PREBUILT=ON` to use prebuilt libs in another cmake build.

```sh
cocos new -l cpp -p my.pack.app2 test_app2
mkdir app2_build && cd app2_build
cmake ../test_app2 -DUSE_COCOS_PREBUILT=ON
make TemplateCpp
open bin/TemplateCpp.app
```
> Any other cpp project can use prebuilt in this way

Using this feature on Android exists a little difference, for CMake can't find system environment when build in Gradle. So you need to [supply a path](https://github.com/cocos2d/cocos2d-x/blob/c087be314c2c56a757bf66163b173746b5d6ad34/tests/cpp-empty-test/proj.android/app/build.gradle#L34) as the location of prebuilt libs.

## Build Options

### CMake Common

1. __`-G`__, generate native build project you specified, for example

    * `-GXcode` generate Xcode project files.
    * `-GVisual Studio 15 2017` generate Visual Studio 2017 project, the default toolset is v141, add `-T` option to specify toolset, like this `-Tv140`

1. __`CMAKE_BUILD_TYPE`__, specify the build mode, Debug or Release

    * `-DCMAKE_BUILD_TYPE=Release` to generate the Release mode project, the default build mode is Debug

1. __`-H -B`__, `-H` specify the CMake project Home directory, `-B` specify CMake-generated project binary directory. for example

    * `-H..\cocos2d-x -Bmsvc_build` the generated native project's location will be `msvc_build` directory.

1. __`--build  <dir>`__, build a CMake-generated project binary tree, for example

    * `cmake --build ./msvc_build`, cmake will sellect corresponding build tools.

### Cocos2d-x Options

1. __`GEN_COCOS_PREBUILT`__, control the project have the feature to generate pre-build libraries or not. Default value is `OFF`

    * `-DGEN_COCOS_PREBUILT=ON`, will add target prebuilt, build this target will generate prebuilt libraries

1. __`USE_COCOS_PREBUILT`__, control the project have the feature to use pre-build libraries or not. Default value is `OFF`

    * `-DUSE_COCOS_PREBUILT=ON`, will disable libraries target, and make app target use prebuilt libraries

1. __`COCOS_PREBUILT_ROOT`__, a path means the prebuilt libraries root location, it's not optional for Android Project on Android Studio, optional for other supported platforms. the default value is $cocos2dx_root/prebuilt if the cmake can access to cocos2d-x environment variable. for example

    * `arguments "-DCOCOS_PREBUILT_ROOT=/Users/laptop/cocos-prebuilt"` set this value on [cmake block](https://github.com/cocos2d/cocos2d-x/blob/84be684e3858393a6f3efc50e3f95d4e0ac92a20/tests/cpp-empty-test/proj.android/app/build.gradle#L31) of build.gradle file.

1. Any options in [SelectModule.cmake](./Modules/SelectModule.cmake) can be set manually. Do it if you know what you're doing.

## Useful Links

* Official website: [cmake.org](https://cmake.org/)

* Documentation: [cmake.org/documentation](https://cmake.org/documentation/)

* CMake FAQ: [Wiki/CMake_FAQ](https://cmake.org/Wiki/CMake_FAQ)