CC      = gcc
CXX     = g++
TARGET	= cocos2dx-test
CCFLAGS = -Wall -g #-O2 
CXXFLAGS = -Wall -g #-O2 
VISIBILITY = 
LIBS = 

COCOS2DX_PATH = ../../../cocos2dx
INCLUDES =  -I../ \
			-I../../ \
			-I../Classes \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/include/ \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I../../../CocosDenshion/include \
			-I../../../extensions/ \
			-I../../../external/ \
			-I../../../external/chipmunk/include/chipmunk \





#CCFLAGS += -fno-tree-scev-cprop
#CXXFLAGS = -fno-tree-scev-cprop

DEFINES = -DLINUX
#DEFINES += -D__LP64__

OBJECTS = ../Classes/AccelerometerTest/AccelerometerTest.o \
			../Classes/ActionManagerTest/ActionManagerTest.o \
			../Classes/ActionsEaseTest/ActionsEaseTest.o \
			../Classes/ActionsProgressTest/ActionsProgressTest.o \
			../Classes/ActionsTest/ActionsTest.o \
			../Classes/Box2DTest/Box2dTest.o \
			../Classes/Box2DTestBed/Box2dView.o \
			../Classes/Box2DTestBed/GLES-Render.o \
			../Classes/Box2DTestBed/Test.o \
			../Classes/Box2DTestBed/TestEntries.o \
			../Classes/BugsTest/Bug-1159.o \
			../Classes/BugsTest/Bug-1174.o \
			../Classes/BugsTest/Bug-350.o \
			../Classes/BugsTest/Bug-422.o \
			../Classes/BugsTest/Bug-458/Bug-458.o \
			../Classes/BugsTest/Bug-458/QuestionContainerSprite.o \
			../Classes/BugsTest/Bug-624.o \
			../Classes/BugsTest/Bug-886.o \
			../Classes/BugsTest/Bug-899.o \
			../Classes/BugsTest/Bug-914.o \
			../Classes/BugsTest/BugsTest.o \
			../Classes/ChipmunkAccelTouchTest/ChipmunkAccelTouchTest.o \
			../Classes/ClickAndMoveTest/ClickAndMoveTest.o \
			../Classes/CocosDenshionTest/CocosDenshionTest.o \
			../Classes/CurlTest/CurlTest.o \
			../Classes/CurrentLanguageTest/CurrentLanguageTest.o \
			../Classes/DrawPrimitivesTest/DrawPrimitivesTest.o \
			../Classes/EffectsAdvancedTest/EffectsAdvancedTest.o \
			../Classes/EffectsTest/EffectsTest.o \
			../Classes/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.o \
			../Classes/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.o \
			../Classes/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.o \
			../Classes/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.o \
			../Classes/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.o \
			../Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.o \
			../Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.o \
			../Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.o \
			../Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.o \
			../Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.o \
			../Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.o \
			../Classes/ExtensionsTest/ExtensionsTest.o \
			../Classes/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.o \
			../Classes/FontTest/FontTest.o \
			../Classes/IntervalTest/IntervalTest.o \
			../Classes/KeypadTest/KeypadTest.o \
			../Classes/LabelTest/LabelTest.o \
			../Classes/LayerTest/LayerTest.o \
			../Classes/MenuTest/MenuTest.o \
			../Classes/MotionStreakTest/MotionStreakTest.o \
			../Classes/MutiTouchTest/MutiTouchTest.o \
			../Classes/NodeTest/NodeTest.o \
			../Classes/ParallaxTest/ParallaxTest.o \
			../Classes/ParticleTest/ParticleTest.o \
			../Classes/PerformanceTest/PerformanceNodeChildrenTest.o \
			../Classes/PerformanceTest/PerformanceParticleTest.o \
			../Classes/PerformanceTest/PerformanceSpriteTest.o \
			../Classes/PerformanceTest/PerformanceTest.o \
			../Classes/PerformanceTest/PerformanceTextureTest.o \
			../Classes/PerformanceTest/PerformanceTouchesTest.o \
			../Classes/RenderTextureTest/RenderTextureTest.o \
			../Classes/RotateWorldTest/RotateWorldTest.o \
			../Classes/SceneTest/SceneTest.o \
			../Classes/SchedulerTest/SchedulerTest.o \
			../Classes/ShaderTest/ShaderTest.o \
			../Classes/SpriteTest/SpriteTest.o \
			../Classes/TextInputTest/TextInputTest.o \
			../Classes/Texture2dTest/Texture2dTest.o \
			../Classes/TextureCacheTest/TextureCacheTest.o \
			../Classes/TileMapTest/TileMapTest.o \
			../Classes/TouchesTest/Ball.o \
			../Classes/TouchesTest/Paddle.o \
			../Classes/TouchesTest/TouchesTest.o \
			../Classes/TransitionsTest/TransitionsTest.o \
			../Classes/UserDefaultTest/UserDefaultTest.o \
			../Classes/ZwoptexTest/ZwoptexTest.o \
			../Classes/controller.o \
			../Classes/testBasic.o \
			../Classes/AppDelegate.o \
			./main.o 

					
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../../../cocos2dx/platform/third_party/linux/libraries
endif
STATICLIBS = 
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libcurl.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \
				../../../lib/linux/Debug/libbox2d.a \
				../../../lib/linux/Debug/libchipmunk.a \
#				$(STATICLIBS_DIR)/libGLEW.a \

SHAREDLIBS = 
ifeq ($(LBITS),64)
SHAREDLIBS_DIR = ../../../CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = ../../../CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

SHAREDLIBS += -lglfw -lGL
#SHAREDLIBS += -lGLEW
SHAREDLIBS += -L../../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../../lib/linux/Debug/ 
SHAREDLIBS += -Wl,-rpath,$(SHAREDLIBS_DIR)
SHAREDLIBS += -Wl,-rpath,../../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib
SHAREDLIBS += -L../../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -lGLEW

SHAREDLIBS += -Wl,-rpath,$(STATICLIBS_DIR)
SHAREDLIBS += -L$(STATICLIBS_DIR) -lcurl


####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS) $(LIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
