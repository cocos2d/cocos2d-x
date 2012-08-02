CC      = gcc
CXX     = g++
TARGET	= cocos2dx-test
CCFLAGS = -Wall -g #-O2 
CXXFLAGS = -Wall -g #-O2 
VISIBILITY = 
LIBS = 

COCOS2DX_PATH = ../../cocos2dx
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
			-I$(COCOS2DX_PATH)/platform/Linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/include/ \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I../../CocosDenshion/include \
			-I../../chipmunk/include/chipmunk \





#CCFLAGS += -fno-tree-scev-cprop
#CXXFLAGS = -fno-tree-scev-cprop

DEFINES = -DLINUX
#DEFINES += -D__LP64__

OBJECTS = ../tests/AccelerometerTest/AccelerometerTest.o \
			../tests/ActionManagerTest/ActionManagerTest.o \
			../tests/ActionsEaseTest/ActionsEaseTest.o \
			../tests/ActionsProgressTest/ActionsProgressTest.o \
			../tests/ActionsTest/ActionsTest.o \
			../tests/Box2DTest/Box2dTest.o \
			../tests/Box2DTestBed/Box2dView.o \
			../tests/Box2DTestBed/GLES-Render.o \
			../tests/Box2DTestBed/Test.o \
			../tests/Box2DTestBed/TestEntries.o \
			../tests/BugsTest/Bug-1159.o \
			../tests/BugsTest/Bug-1174.o \
			../tests/BugsTest/Bug-350.o \
			../tests/BugsTest/Bug-422.o \
			../tests/BugsTest/Bug-458/Bug-458.o \
			../tests/BugsTest/Bug-458/QuestionContainerSprite.o \
			../tests/BugsTest/Bug-624.o \
			../tests/BugsTest/Bug-886.o \
			../tests/BugsTest/Bug-899.o \
			../tests/BugsTest/Bug-914.o \
			../tests/BugsTest/BugsTest.o \
			../tests/ChipmunkAccelTouchTest/ChipmunkAccelTouchTest.o \
			../tests/ClickAndMoveTest/ClickAndMoveTest.o \
			../tests/CocosDenshionTest/CocosDenshionTest.o \
			../tests/CurlTest/CurlTest.o \
			../tests/CurrentLanguageTest/CurrentLanguageTest.o \
			../tests/DrawPrimitivesTest/DrawPrimitivesTest.o \
			../tests/EffectsAdvancedTest/EffectsAdvancedTest.o \
			../tests/EffectsTest/EffectsTest.o \
			../tests/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.o \
			../tests/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.o \
			../tests/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.o \
			../tests/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.o \
			../tests/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.o \
			../tests/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.o \
			../tests/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.o \
			../tests/ExtensionsTest/ControlExtensionTest/CCControlScene.o \
			../tests/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.o \
			../tests/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.o \
			../tests/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.o \
			../tests/ExtensionsTest/ExtensionsTest.o \
			../tests/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.o \
			../tests/FontTest/FontTest.o \
			../tests/IntervalTest/IntervalTest.o \
			../tests/KeypadTest/KeypadTest.o \
			../tests/LabelTest/LabelTest.o \
			../tests/LayerTest/LayerTest.o \
			../tests/MenuTest/MenuTest.o \
			../tests/MotionStreakTest/MotionStreakTest.o \
			../tests/MutiTouchTest/MutiTouchTest.o \
			../tests/NodeTest/NodeTest.o \
			../tests/ParallaxTest/ParallaxTest.o \
			../tests/ParticleTest/ParticleTest.o \
			../tests/PerformanceTest/PerformanceNodeChildrenTest.o \
			../tests/PerformanceTest/PerformanceParticleTest.o \
			../tests/PerformanceTest/PerformanceSpriteTest.o \
			../tests/PerformanceTest/PerformanceTest.o \
			../tests/PerformanceTest/PerformanceTextureTest.o \
			../tests/PerformanceTest/PerformanceTouchesTest.o \
			../tests/RenderTextureTest/RenderTextureTest.o \
			../tests/RotateWorldTest/RotateWorldTest.o \
			../tests/SceneTest/SceneTest.o \
			../tests/SchedulerTest/SchedulerTest.o \
			../tests/ShaderTest/ShaderTest.o \
			../tests/SpriteTest/SpriteTest.o \
			../tests/TextInputTest/TextInputTest.o \
			../tests/Texture2dTest/Texture2dTest.o \
			../tests/TextureCacheTest/TextureCacheTest.o \
			../tests/TileMapTest/TileMapTest.o \
			../tests/TouchesTest/Ball.o \
			../tests/TouchesTest/Paddle.o \
			../tests/TouchesTest/TouchesTest.o \
			../tests/TransitionsTest/TransitionsTest.o \
			../tests/UserDefaultTest/UserDefaultTest.o \
			../tests/ZwoptexTest/ZwoptexTest.o \
			../tests/controller.o \
			../tests/testBasic.o \
			../AppDelegate.o \
			./main.o 

					
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = ../../cocos2dx/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = ../../cocos2dx/platform/third_party/linux/libraries
endif
STATICLIBS = 
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libcurl.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \
				../../lib/linux/Debug/libbox2d.a \
				../../lib/linux/Debug/libchipmunk.a \
#				$(STATICLIBS_DIR)/libGLEW.a \

SHAREDLIBS = 
ifeq ($(LBITS),64)
SHAREDLIBS_DIR = ../../CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = ../../CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

SHAREDLIBS += -lglfw -lGL
#SHAREDLIBS += -lGLEW
SHAREDLIBS += -L../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../lib/linux/Debug/ 
SHAREDLIBS += -Wl,-rpath,$(SHAREDLIBS_DIR)
SHAREDLIBS += -Wl,-rpath,../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib
SHAREDLIBS += -L../../cocos2dx/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -lGLEW

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
