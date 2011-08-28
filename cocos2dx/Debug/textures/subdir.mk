################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../textures/CCTexture2D.cpp \
../textures/CCTextureAtlas.cpp \
../textures/CCTextureCache.cpp \
../textures/CCTexturePVR.cpp 

OBJS += \
./textures/CCTexture2D.o \
./textures/CCTextureAtlas.o \
./textures/CCTextureCache.o \
./textures/CCTexturePVR.o 

CPP_DEPS += \
./textures/CCTexture2D.d \
./textures/CCTextureAtlas.d \
./textures/CCTextureCache.d \
./textures/CCTexturePVR.d 


# Each subdirectory must supply rules for building sources it contributes
textures/%.o: ../textures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


