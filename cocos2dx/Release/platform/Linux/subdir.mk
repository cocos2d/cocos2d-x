################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../platform/Linux/CCAplication_linux.cpp \
../platform/Linux/CCEGLView_linux.cpp \
../platform/Linux/CCFileUtils_Linux.cpp \
../platform/Linux/CCImage_Linux.cpp 

OBJS += \
./platform/Linux/CCAplication_linux.o \
./platform/Linux/CCEGLView_linux.o \
./platform/Linux/CCFileUtils_Linux.o \
./platform/Linux/CCImage_Linux.o 

CPP_DEPS += \
./platform/Linux/CCAplication_linux.d \
./platform/Linux/CCEGLView_linux.d \
./platform/Linux/CCFileUtils_Linux.d \
./platform/Linux/CCImage_Linux.d 


# Each subdirectory must supply rules for building sources it contributes
platform/Linux/%.o: ../platform/Linux/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


