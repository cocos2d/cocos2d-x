################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../platform/CCCommon.cpp \
../platform/CCFileUtils.cpp \
../platform/CCGL.cpp \
../platform/CCImage.cpp \
../platform/CCSAXParser.cpp \
../platform/CCStdC.cpp \
../platform/CCThread.cpp \
../platform/platform.cpp 

OBJS += \
./platform/CCCommon.o \
./platform/CCFileUtils.o \
./platform/CCGL.o \
./platform/CCImage.o \
./platform/CCSAXParser.o \
./platform/CCStdC.o \
./platform/CCThread.o \
./platform/platform.o 

CPP_DEPS += \
./platform/CCCommon.d \
./platform/CCFileUtils.d \
./platform/CCGL.d \
./platform/CCImage.d \
./platform/CCSAXParser.d \
./platform/CCStdC.d \
./platform/CCThread.d \
./platform/platform.d 


# Each subdirectory must supply rules for building sources it contributes
platform/%.o: ../platform/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


