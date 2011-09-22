################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include android/jni/helloworld/subdir.mk
-include Classes/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libHelloWorld.so

# Tool invocations
libHelloWorld.so: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	arm-linux-androideabi-g++ -L"../../..//cocos2dx/proj.linux/AndroidRelease" -L"../../..//CocosDenshion/proj.linux/AndroidRelease" -shared -o "libHelloWorld.so" $(OBJS) $(USER_OBJS) $(LIBS) -Wl,-rpath,../../..//cocos2dx/proj.linux/AndroidRelease -Wl,-rpath,/home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Linux/../../cocos2dx/proj.linux/AndroidRelease  -Wl,-rpath,/home/laschweinski/git/cocos2dx-ming/cocos2d-x/HelloWorld/Linux/../../CocosDenshion/proj.linux/AndroidRelease -Wl,-rpath,../../..//CocosDenshion/proj.linux/AndroidRelease
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(LIBRARIES)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) libHelloWorld.so
	-@echo ' '

post-build:
	-@echo 'move required lib into android/libs automatically'
	-sh ../postCompiled.sh AndroidRelease HelloWorld ../../../
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
