################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include touch_dispatcher/subdir.mk
-include tileMap_parallax_nodes/subdir.mk
-include textures/subdir.mk
-include text_input_node/subdir.mk
-include support/zip_support/subdir.mk
-include support/image_support/subdir.mk
-include support/subdir.mk
-include sprite_nodes/subdir.mk
-include script_support/subdir.mk
-include platform/subdir.mk
-include platform/Linux/subdir.mk
-include particle_nodes/subdir.mk
-include misc_nodes/subdir.mk
-include menu_nodes/subdir.mk
-include layers_scenes_transitions_nodes/subdir.mk
-include label_nodes/subdir.mk
-include keypad_dispatcher/subdir.mk
-include effects/subdir.mk
-include cocoa/subdir.mk
-include base_nodes/subdir.mk
-include actions/subdir.mk
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
all: libcocos2dx-base.so

# Tool invocations
libcocos2dx-base.so: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -shared -o "libcocos2dx-base.so" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(LIBRARIES)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) libcocos2dx-base.so
	-@echo ' '

post-build:
	-@echo 'move all libs into the specific folder'
	-sh ../../post.sh cocos2dx-base cocos2d
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
