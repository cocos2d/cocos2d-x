################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/Box2dView.cpp \
/home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/GLES-Render.cpp \
/home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/Test.cpp \
/home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/TestEntries.cpp 

OBJS += \
./tests/Box2DTestBed/Box2dView.o \
./tests/Box2DTestBed/GLES-Render.o \
./tests/Box2DTestBed/Test.o \
./tests/Box2DTestBed/TestEntries.o 

CPP_DEPS += \
./tests/Box2DTestBed/Box2dView.d \
./tests/Box2DTestBed/GLES-Render.d \
./tests/Box2DTestBed/Test.d \
./tests/Box2DTestBed/TestEntries.d 


# Each subdirectory must supply rules for building sources it contributes
tests/Box2DTestBed/Box2dView.o: /home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/Box2dView.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I../../ -I../../../cocos2dx/platform/third_party/linux -I../../../cocos2dx/include -I../../../cocos2dx -I../../../cocos2dx/platform -I../../../CocosDenshion/include -I../../..//chipmunk/include/chipmunk -I../../../Box2D -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/Box2DTestBed/GLES-Render.o: /home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/GLES-Render.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I../../ -I../../../cocos2dx/platform/third_party/linux -I../../../cocos2dx/include -I../../../cocos2dx -I../../../cocos2dx/platform -I../../../CocosDenshion/include -I../../..//chipmunk/include/chipmunk -I../../../Box2D -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/Box2DTestBed/Test.o: /home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/Test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I../../ -I../../../cocos2dx/platform/third_party/linux -I../../../cocos2dx/include -I../../../cocos2dx -I../../../cocos2dx/platform -I../../../CocosDenshion/include -I../../..//chipmunk/include/chipmunk -I../../../Box2D -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tests/Box2DTestBed/TestEntries.o: /home/laschweinski/git/cocos2d-x/tests/tests/Box2DTestBed/TestEntries.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -I../../ -I../../../cocos2dx/platform/third_party/linux -I../../../cocos2dx/include -I../../../cocos2dx -I../../../cocos2dx/platform -I../../../CocosDenshion/include -I../../..//chipmunk/include/chipmunk -I../../../Box2D -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


