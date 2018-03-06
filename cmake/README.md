
## CMake

CMake is an open-source, cross-platform family of tools designed to build, test and package software. CMake is used to control the software compilation process using simple platform and compiler independent configuration files, and generate native makefiles and workspaces that can be used in the compiler environment of your choice.

### Links

* Official website: [cmake.org](https://cmake.org/)

* Documentation: [cmake.org/documentation](https://cmake.org/documentation/)

* CMake FAQ: [Wiki/CMake_FAQ](https://cmake.org/Wiki/CMake_FAQ)

## CMake in Cocos2d-x

1. CMake in Cocos2d-x support platform iOS, Android, macOS, Linux, Win32.

1. open the terminal `cmake --version`, if the cmake version is lower than 3.1, please install the latest stable cmake

2. you should use out-of-source build, that is said you need to create a different directory from `$cocos2dx_root` to execute cmake command.

## Build Options

### CMake Common

1. __`-G`__, generate native build project you specified, for example

    * `-GXcode` Generate Xcode project files.
    * `-GVisual Studio 15 2017` generate Visual Studio 2017 project, the default toolset is v141, add `-T` option to specify toolset, like this `-Tv140`

1. __`CMAKE_BUILD_TYPE`__, specify the build mode, Debug or Release

    * `-DCMAKE_BUILD_TYPE=Release` to generate the Release mode project, the default build mode is Debug

1. __`-H -B`__, `-H` specify the CMake project Home directory, `-B` specify CMake-generated project binary directory. for example

    * `-H..\cocos2d-x -Bmsvc_build` the generated native project's location will be `msvc_build` directory.

1. __`--build  <dir>`__, Build a CMake-generated project binary tree, for example

    * `cmake --build ./msvc_build`, cmake will sellect corresponding build tools.

### Cocos2d-x Options

1. __`GEN_COCOS_PREBUILT`__, control the project have the feature to generate pre-build libs or not. Default value is `OFF`

    * `-DGEN_COCOS_PREBUILT=ON`, will add target prebuilt, build this target will generate prebuilt libs

1. __`USE_COCOS_PREBUILT`__, control the project have the feature to use pre-build libs or not. Default value is `OFF`

    * `-DUSE_COCOS_PREBUILT=ON`, will disable libs target, and make app target use prebuilt libs

1. __`COCOS_PREBUILT_ROOT`__, a path means the prebuilt libs root location, it's not optional for Android Project on Android Studio, optional for other supported platforms. the default value is $cocos2dx_root/prebuilt if the cmake can access to cocos2d-x environment variable. for example

    * `arguments "-DCOCOS_PREBUILT_ROOT=/Users/laptop/cocos-prebuilt"` set this value on [app/build.gradle](./../tests/cpp-empty-test/proj.android/app/build.gradle)

1. Any options in [SelectModule.cmake](./Modules/SelectModule.cmake) can be set manually. Do it if you know what you're doing.

## Build Examples

### Generate Xcode Project for macOS platform

```sh
cmake -H$COCOS_TEMPLATES_ROOT/.. -Bbuild_mac -GXcode
cd build_mac
open Cocos2d-x.xcodeproj
```

### Generate Xcode Project for iOS platform

```sh
cd build_ios
cmake -DCMAKE_TOOLCHAIN_FILE=$COCOS_TEMPLATES_ROOT/../cmake/ios.toolchain.cmake -DIOS_PLATFORM=SIMULATOR64 -H$COCOS_TEMPLATES_ROOT/.. -Bbuild_ios_sim64 -GXcode
cd build_ios_sim64
open Cocos2d-x.xcodeproj
```

### using CMake in Android Studio

see the Gradle properties: `PROP_NDK_MODE`, it control the way of build Native

```sh
# android cmake support
# uncomment it, native code will build by cmake
# keep comment, native code will build by ndkBuild
PROP_NDK_MODE=cmake
```

add arguments in externalNativeBuild block of [app/build.gradle](./../tests/cpp-empty-test/proj.android/app/build.gradle) file.

### Generate Visual Studio project

```sh
cmake -H"..\cocos2d-x\" -Bmsvc_build -G"Visual Studio 15 2017" -Tv141 -DCMAKE_BUILD_TYPE=Debug
```

execute `cmake --build ./msvc_build` or open `Cocos2d-x.sln` in Explorer to use the generated native project.

## TODO

1. support cocos simulator App
1. better support package iOS/MacOS App
1. improve and refactor if neeeded
1. support MinGW on Windows
