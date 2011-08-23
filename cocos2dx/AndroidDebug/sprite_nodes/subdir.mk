################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sprite_nodes/CCAnimation.cpp \
../sprite_nodes/CCAnimationCache.cpp \
../sprite_nodes/CCSprite.cpp \
../sprite_nodes/CCSpriteBatchNode.cpp \
../sprite_nodes/CCSpriteFrame.cpp \
../sprite_nodes/CCSpriteFrameCache.cpp 

OBJS += \
./sprite_nodes/CCAnimation.o \
./sprite_nodes/CCAnimationCache.o \
./sprite_nodes/CCSprite.o \
./sprite_nodes/CCSpriteBatchNode.o \
./sprite_nodes/CCSpriteFrame.o \
./sprite_nodes/CCSpriteFrameCache.o 

CPP_DEPS += \
./sprite_nodes/CCAnimation.d \
./sprite_nodes/CCAnimationCache.d \
./sprite_nodes/CCSprite.d \
./sprite_nodes/CCSpriteBatchNode.d \
./sprite_nodes/CCSpriteFrame.d \
./sprite_nodes/CCSpriteFrameCache.d 


# Each subdirectory must supply rules for building sources it contributes
sprite_nodes/%.o: ../sprite_nodes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


