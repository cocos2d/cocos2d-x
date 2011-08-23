################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../platform/android/jni/IMEJni.cpp \
../platform/android/jni/JniHelper.cpp \
../platform/android/jni/MessageJni.cpp \
../platform/android/jni/SensorJni.cpp \
../platform/android/jni/SystemInfoJni.cpp \
../platform/android/jni/TouchesJni.cpp 

OBJS += \
./platform/android/jni/IMEJni.o \
./platform/android/jni/JniHelper.o \
./platform/android/jni/MessageJni.o \
./platform/android/jni/SensorJni.o \
./platform/android/jni/SystemInfoJni.o \
./platform/android/jni/TouchesJni.o 

CPP_DEPS += \
./platform/android/jni/IMEJni.d \
./platform/android/jni/JniHelper.d \
./platform/android/jni/MessageJni.d \
./platform/android/jni/SensorJni.d \
./platform/android/jni/SystemInfoJni.d \
./platform/android/jni/TouchesJni.d 


# Each subdirectory must supply rules for building sources it contributes
platform/android/jni/%.o: ../platform/android/jni/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


