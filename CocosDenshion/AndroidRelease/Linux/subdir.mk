################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Linux/FmodAudioPlayer.cpp \
../Linux/SimpleAudioEngine.cpp 

OBJS += \
./Linux/FmodAudioPlayer.o \
./Linux/SimpleAudioEngine.o 

CPP_DEPS += \
./Linux/FmodAudioPlayer.d \
./Linux/SimpleAudioEngine.d 


# Each subdirectory must supply rules for building sources it contributes
Linux/%.o: ../Linux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -I"/home/laschweinski/git/cocos2d-x/CocosDenshion/include" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


