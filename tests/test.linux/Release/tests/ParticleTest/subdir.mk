################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2d-x/tests/tests/ParticleTest/ParticleTest.cpp 

OBJS += \
./tests/ParticleTest/ParticleTest.o 

CPP_DEPS += \
./tests/ParticleTest/ParticleTest.d 


# Each subdirectory must supply rules for building sources it contributes
tests/ParticleTest/ParticleTest.o: /home/laschweinski/git/cocos2d-x/tests/tests/ParticleTest/ParticleTest.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I/usr/include/cocos2dx -I/usr/include/cocos2dx/platform -I/usr/include/cocos2dx/include -I"/home/laschweinski/git/cocos2d-x/tests" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


