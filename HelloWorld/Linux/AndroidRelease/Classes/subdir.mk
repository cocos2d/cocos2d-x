################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Classes/AppDelegate.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Classes/HelloWorldScene.cpp 

OBJS += \
./Classes/AppDelegate.o \
./Classes/HelloWorldScene.o 

CPP_DEPS += \
./Classes/AppDelegate.d \
./Classes/HelloWorldScene.d 


# Each subdirectory must supply rules for building sources it contributes
Classes/AppDelegate.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Classes/AppDelegate.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -I"../../..//cocos2dx" -I"../../..//CocosDenshion/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Classes" -I../../..//cocos2dx/include -I../../..//cocos2dx/platform -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Classes/HelloWorldScene.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Classes/HelloWorldScene.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -I"../../..//cocos2dx" -I"../../..//CocosDenshion/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Classes" -I../../..//cocos2dx/include -I../../..//cocos2dx/platform -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


