################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../base_nodes/CCAtlasNode.cpp \
../base_nodes/CCNode.cpp 

OBJS += \
./base_nodes/CCAtlasNode.o \
./base_nodes/CCNode.o 

CPP_DEPS += \
./base_nodes/CCAtlasNode.d \
./base_nodes/CCNode.d 


# Each subdirectory must supply rules for building sources it contributes
base_nodes/%.o: ../base_nodes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


