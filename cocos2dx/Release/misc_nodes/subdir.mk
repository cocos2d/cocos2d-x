################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../misc_nodes/CCMotionStreak.cpp \
../misc_nodes/CCProgressTimer.cpp \
../misc_nodes/CCRenderTexture.cpp \
../misc_nodes/CCRibbon.cpp 

OBJS += \
./misc_nodes/CCMotionStreak.o \
./misc_nodes/CCProgressTimer.o \
./misc_nodes/CCRenderTexture.o \
./misc_nodes/CCRibbon.o 

CPP_DEPS += \
./misc_nodes/CCMotionStreak.d \
./misc_nodes/CCProgressTimer.d \
./misc_nodes/CCRenderTexture.d \
./misc_nodes/CCRibbon.d 


# Each subdirectory must supply rules for building sources it contributes
misc_nodes/%.o: ../misc_nodes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


