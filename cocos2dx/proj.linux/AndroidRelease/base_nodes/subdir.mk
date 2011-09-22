################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/base_nodes/CCAtlasNode.cpp \
/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/base_nodes/CCNode.cpp 

OBJS += \
./base_nodes/CCAtlasNode.o \
./base_nodes/CCNode.o 

CPP_DEPS += \
./base_nodes/CCAtlasNode.d \
./base_nodes/CCNode.d 


# Each subdirectory must supply rules for building sources it contributes
base_nodes/CCAtlasNode.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/base_nodes/CCAtlasNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

base_nodes/CCNode.o: /home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/base_nodes/CCNode.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I../../ -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2dx-ming/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


