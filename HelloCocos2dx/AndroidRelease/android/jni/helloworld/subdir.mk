################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../android/jni/helloworld/main.cpp 

OBJS += \
./android/jni/helloworld/main.o 

CPP_DEPS += \
./android/jni/helloworld/main.d 


# Each subdirectory must supply rules for building sources it contributes
android/jni/helloworld/%.o: ../android/jni/helloworld/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/CocosDenshion/include" -I"/home/laschweinski/git/cocos2d-x/HelloCocos2dx/Classes" -I/home/laschweinski/git/cocos2d-x/cocos2dx/include -I/home/laschweinski/git/cocos2d-x/cocos2dx/platform -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


