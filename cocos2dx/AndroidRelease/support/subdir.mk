################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../support/CCArray.cpp \
../support/CCPointExtension.cpp \
../support/CCProfiling.cpp \
../support/CCUserDefault.cpp \
../support/TransformUtils.cpp \
../support/base64.cpp \
../support/ccUtils.cpp 

OBJS += \
./support/CCArray.o \
./support/CCPointExtension.o \
./support/CCProfiling.o \
./support/CCUserDefault.o \
./support/TransformUtils.o \
./support/base64.o \
./support/ccUtils.o 

CPP_DEPS += \
./support/CCArray.d \
./support/CCPointExtension.d \
./support/CCProfiling.d \
./support/CCUserDefault.d \
./support/TransformUtils.d \
./support/base64.d \
./support/ccUtils.d 


# Each subdirectory must supply rules for building sources it contributes
support/%.o: ../support/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


