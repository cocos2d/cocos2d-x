################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cocoa/CCAffineTransform.cpp \
../cocoa/CCAutoreleasePool.cpp \
../cocoa/CCData.cpp \
../cocoa/CCGeometry.cpp \
../cocoa/CCNS.cpp \
../cocoa/CCObject.cpp \
../cocoa/CCSet.cpp \
../cocoa/CCZone.cpp 

OBJS += \
./cocoa/CCAffineTransform.o \
./cocoa/CCAutoreleasePool.o \
./cocoa/CCData.o \
./cocoa/CCGeometry.o \
./cocoa/CCNS.o \
./cocoa/CCObject.o \
./cocoa/CCSet.o \
./cocoa/CCZone.o 

CPP_DEPS += \
./cocoa/CCAffineTransform.d \
./cocoa/CCAutoreleasePool.d \
./cocoa/CCData.d \
./cocoa/CCGeometry.d \
./cocoa/CCNS.d \
./cocoa/CCObject.d \
./cocoa/CCSet.d \
./cocoa/CCZone.d 


# Each subdirectory must supply rules for building sources it contributes
cocoa/%.o: ../cocoa/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


