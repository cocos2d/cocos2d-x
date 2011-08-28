################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../layers_scenes_transitions_nodes/CCLayer.cpp \
../layers_scenes_transitions_nodes/CCScene.cpp \
../layers_scenes_transitions_nodes/CCTransition.cpp \
../layers_scenes_transitions_nodes/CCTransitionPageTurn.cpp \
../layers_scenes_transitions_nodes/CCTransitionRadial.cpp 

OBJS += \
./layers_scenes_transitions_nodes/CCLayer.o \
./layers_scenes_transitions_nodes/CCScene.o \
./layers_scenes_transitions_nodes/CCTransition.o \
./layers_scenes_transitions_nodes/CCTransitionPageTurn.o \
./layers_scenes_transitions_nodes/CCTransitionRadial.o 

CPP_DEPS += \
./layers_scenes_transitions_nodes/CCLayer.d \
./layers_scenes_transitions_nodes/CCScene.d \
./layers_scenes_transitions_nodes/CCTransition.d \
./layers_scenes_transitions_nodes/CCTransitionPageTurn.d \
./layers_scenes_transitions_nodes/CCTransitionRadial.d 


# Each subdirectory must supply rules for building sources it contributes
layers_scenes_transitions_nodes/%.o: ../layers_scenes_transitions_nodes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I"/home/laschweinski/git/cocos2d-x/cocos2dx" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libfreetype2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/include" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libpng" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libxml2" -I"/home/laschweinski/git/cocos2d-x/cocos2dx/platform/third_party/linux/libjpeg" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


