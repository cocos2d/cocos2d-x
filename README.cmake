
CMake Build Instructions

NB. Depending on your host system your Generator flag -G may be different

Typical -G options
For using gcc and clang from a makefile

msys2 = "MSYS Makefiles"
windows = "MinGW Makefiles"
nix and mac = "Unix Makefiles"

For using and editor such as Visual Studio or xcode or sublime text there are different flags

To like all available flags for your system run

cmake --help


More Examples

mac build Instructions

cd cocos2d-x
mkdir macbuild && cd macbuild
cmake -G "Unix Makefile" -DBUILD_CPP_TESTS=OFF -DBUILD_LUA_LIBS=OFF ..

Android Build Instructions

cd cocos2d-x
mkdir androidbuild && cd androidbuild
cmake -G"MSYS Makefiles" -DANDROID_NDK=/path/to/android-ndk-r9d -DANDROID_NATIVE_API_LEVEL=android-9 -DCMAKE_TOOLCHAIN_FILE=../cmake/android.toolchain.cmake ..

mingw64 with msys2 build Instructions

cd cocos2d-x
mkdir mingwbuild && cd mingwbuild
cmake -G "MSYS Makefile" -DBUILD_CPP_TESTS=OFF -DBUILD_LUA_LIBS=OFF ..

todo: structure this document in markdown with better examples and more details