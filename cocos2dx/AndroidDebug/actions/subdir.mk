################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../actions/CCAction.cpp \
../actions/CCActionCamera.cpp \
../actions/CCActionEase.cpp \
../actions/CCActionGrid.cpp \
../actions/CCActionGrid3D.cpp \
../actions/CCActionInstant.cpp \
../actions/CCActionInterval.cpp \
../actions/CCActionManager.cpp \
../actions/CCActionPageTurn3D.cpp \
../actions/CCActionProgressTimer.cpp \
../actions/CCActionTiledGrid.cpp 

OBJS += \
./actions/CCAction.o \
./actions/CCActionCamera.o \
./actions/CCActionEase.o \
./actions/CCActionGrid.o \
./actions/CCActionGrid3D.o \
./actions/CCActionInstant.o \
./actions/CCActionInterval.o \
./actions/CCActionManager.o \
./actions/CCActionPageTurn3D.o \
./actions/CCActionProgressTimer.o \
./actions/CCActionTiledGrid.o 

CPP_DEPS += \
./actions/CCAction.d \
./actions/CCActionCamera.d \
./actions/CCActionEase.d \
./actions/CCActionGrid.d \
./actions/CCActionGrid3D.d \
./actions/CCActionInstant.d \
./actions/CCActionInterval.d \
./actions/CCActionManager.d \
./actions/CCActionPageTurn3D.d \
./actions/CCActionProgressTimer.d \
./actions/CCActionTiledGrid.d 


# Each subdirectory must supply rules for building sources it contributes
actions/%.o: ../actions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-androideabi-g++ -DANDROID -DUSE_FILE32API -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libjpeg" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/android/libxml2" -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


