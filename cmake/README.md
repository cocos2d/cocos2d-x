
## CMake Build Instructions

Depending on your host system your Generator flag -G may be different

Typical -G options
For using gcc and clang from a makefile

msys2 = "MSYS Makefiles"
windows = "MinGW Makefiles"
nix and mac = "Unix Makefiles"

For using and editor such as Visual Studio or xcode there are different flags

To like all available flags for your system run

cmake --help


### Build Examples

#### using CMake in macOS terminal

```sh
cmake -H$COCOS_TEMPLATES_ROOT/.. -Bbuild_cocos2dx
cd build_cocos2dx
make all -j 4
```

#### Generate Xcode Project for macOS platform

```sh
cmake -H$COCOS_TEMPLATES_ROOT/.. -Bbuild_mac -GXcode
cd build_mac
open Cocos2d-x.xcodeproj
```

#### Generate Xcode Project for iOS platform

```sh
cd any_dir_you_want
cmake -DCMAKE_TOOLCHAIN_FILE=$COCOS_TEMPLATES_ROOT/../cmake/ios.toolchain.cmake -DIOS_PLATFORM=SIMULATOR64 -H$COCOS_TEMPLATES_ROOT/.. -Bbuild_ios_sim64 -GXcode
cd build_ios_sim64
open Cocos2d-x.xcodeproj
```

#### using CMake in Android Studio

see the Gradle properties: `PROP_NDK_MODE`, it control the way of build Native

```sh
# android cmake support
# uncomment it, native code will build by cmake
# keep comment, native code will build by ndkBuild
# PROP_NDK_MODE=cmake
```

#### TODO

    1. make cmake build support windows
    2. generate Visual Studio project
    3. test cmake build again on Linux 
    4. add examples and more details in this manual
