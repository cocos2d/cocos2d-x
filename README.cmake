
# CMake Build Instructions

NB. Depending on your host system your Generator flag -G may be different

Typical -G options
For using gcc and clang from a makefile

## Tips
- Build Cocos2d-X v4 need CMake 3.1 or above.
- Using CMake-GUI or ccmake in console instead cmake to generate project file can config build options before generation.
- Set build directory out of Cocos2D-x source direcotry is a good idea.
- $BUILD_ROOT means Cocos2D-X build directory
- $SOURCE_ROOT means Cocos2D-X source directory

## Windows
```
cd $BUILD_ROOT
cmake -G"Visual Studio 12 2013" $SOURCE_ROOT
cmake --build . --config <Debug|Release>
```

## MacOSX
```
cd $BUILD_ROOT
cmake -G"Xcode" $SOURCE_ROOT
cmake --build . --config <Debug|Release>
```

## Linux
```
cd $BUILD_ROOT
cmake $SOURCE_ROOT
cmake --build . --config <Debug|Release>
```

## iOS
- CMake generate seperate Xcode project for simulator and devices, control with option:IOS_PLATFORM=[SIMULATOR|OS], simulator is default.
```
cd $BUILD_ROOT
cmake -GXoce -DCMAKE_TOOLCHAIN_FILE="$SOURCE_ROOT/cmake/ios.toolchain.cmake" $SOURCE_ROOT
cmake --build . --config <Debug|Release>
```

## Android(Experimental)
- CMake generate seperate Makefile project for different ABI.
- NDK path can set by ANDROID_NDK.
- More option details in android.toolchain.cmake.
```
cd $BUILD_ROOT
cmake -G"Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE="$SOURCE_ROOT/cmake/android.toolchain.cmake" $SOURCE_ROOT
cmake --build . --config <Debug|Release>
```

