################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../keypad_dispatcher/CCKeypadDelegate.cpp \
../keypad_dispatcher/CCKeypadDispatcher.cpp 

OBJS += \
./keypad_dispatcher/CCKeypadDelegate.o \
./keypad_dispatcher/CCKeypadDispatcher.o 

CPP_DEPS += \
./keypad_dispatcher/CCKeypadDelegate.d \
./keypad_dispatcher/CCKeypadDispatcher.d 


# Each subdirectory must supply rules for building sources it contributes
keypad_dispatcher/%.o: ../keypad_dispatcher/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


