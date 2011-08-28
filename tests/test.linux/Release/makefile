################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include tests/subdir.mk
-include tests/ZwoptexTest/subdir.mk
-include tests/UserDefaultTest/subdir.mk
-include tests/TransitionsTest/subdir.mk
-include tests/TouchesTest/subdir.mk
-include tests/TileMapTest/subdir.mk
-include tests/Texture2dTest/subdir.mk
-include tests/TextInputTest/subdir.mk
-include tests/SpriteTest/subdir.mk
-include tests/SchedulerTest/subdir.mk
-include tests/SceneTest/subdir.mk
-include tests/RotateWorldTest/subdir.mk
-include tests/RenderTextureTest/subdir.mk
-include tests/ProgressActionsTest/subdir.mk
-include tests/ParallaxTest/subdir.mk
-include tests/MotionStreakTest/subdir.mk
-include tests/MenuTest/subdir.mk
-include tests/LayerTest/subdir.mk
-include tests/LabelTest/subdir.mk
-include tests/KeypadTest/subdir.mk
-include tests/IntervalTest/subdir.mk
-include tests/HiResTest/subdir.mk
-include tests/FontTest/subdir.mk
-include tests/EffectsTest/subdir.mk
-include tests/EffectsAdvancedTest/subdir.mk
-include tests/EaseActionsTest/subdir.mk
-include tests/DrawPrimitivesTest/subdir.mk
-include tests/DirectorTest/subdir.mk
-include tests/CurrentLanguageTest/subdir.mk
-include tests/CurlTest/subdir.mk
-include tests/CocosNodeTest/subdir.mk
-include tests/CocosDenshionTest/subdir.mk
-include tests/ClickAndMoveTest/subdir.mk
-include tests/ChipmunkTest/subdir.mk
-include tests/BugsTest/subdir.mk
-include tests/BugsTest/Bug-458/subdir.mk
-include tests/Box2DTestBed/subdir.mk
-include tests/Box2DTest/subdir.mk
-include tests/ActionsTest/subdir.mk
-include tests/ActionManagerTest/subdir.mk
-include tests/AccelerometerTest/subdir.mk
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
all: cocos2dx-test

# Tool invocations
cocos2dx-test: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L"/home/laschweinski/git/cocos2d-x/lib/linux/Release" -o "cocos2dx-test" $(OBJS) $(USER_OBJS) $(LIBS) -Wl,-rpath,../../lib/linux/Release/
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) cocos2dx-test
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
