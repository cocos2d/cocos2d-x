################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Linux/main.cpp 

OBJS += \
./Linux/main.o 

CPP_DEPS += \
./Linux/main.d 


# Each subdirectory must supply rules for building sources it contributes
Linux/%.o: ../Linux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/CocosDenshion/include" -I"/home/laschweinski/git/cocos2d-x/HelloWorld/Classes" -I/home/laschweinski/git/cocos2d-x/cocos2dx/include -I/home/laschweinski/git/cocos2d-x/cocos2dx/platform -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


