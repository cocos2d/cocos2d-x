################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CCCamera.cpp \
../CCConfiguration.cpp \
../CCDirector.cpp \
../CCDrawingPrimitives.cpp \
../CCScheduler.cpp \
../cocos2d.cpp 

OBJS += \
./CCCamera.o \
./CCConfiguration.o \
./CCDirector.o \
./CCDrawingPrimitives.o \
./CCScheduler.o \
./cocos2d.o 

CPP_DEPS += \
./CCCamera.d \
./CCConfiguration.d \
./CCDirector.d \
./CCDrawingPrimitives.d \
./CCScheduler.d \
./cocos2d.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


