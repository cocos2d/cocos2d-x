TOP		=	../..

include $(TOP)/linux.config.mk


TARGET		=	cocos2dx-test
VISIBILITY	=	

INCLUDES	=	-I.. \
			-I$(TOP)/cocos2dx/include \
			-I$(TOP)/cocos2dx \
			-I$(TOP)/cocos2dx/platform \
			-I$(TOP)/CocosDenshion/include \
			-I$(TOP)/chipmunk/include/chipmunk \
			-I$(TOP)

OBJECTS		=	../tests/AccelerometerTest/AccelerometerTest.o \
			../tests/ActionManagerTest/ActionManagerTest.o \
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
			../tests/BugsTest/Bug-624.o \
			../tests/BugsTest/Bug-886.o \
			../tests/BugsTest/Bug-899.o \
			../tests/BugsTest/Bug-914.o \
			../tests/BugsTest/Bug-458/Bug-458.o \
			../tests/BugsTest/Bug-458/QuestionContainerSprite.o \
			../tests/BugsTest/BugsTest.o \
			../tests/ChipmunkTest/Bounce.o \
			../tests/ChipmunkTest/Joints.o \
			../tests/ChipmunkTest/LogoSmash.o \
			../tests/ChipmunkTest/MagnetsElectric.o \
			../tests/ChipmunkTest/OneWay.o \
			../tests/ChipmunkTest/Planet.o \
			../tests/ChipmunkTest/Player.o \
			../tests/ChipmunkTest/Plink.o \
			../tests/ChipmunkTest/Pump.o \
			../tests/ChipmunkTest/PyramidStack.o \
			../tests/ChipmunkTest/PyramidTopple.o \
			../tests/ChipmunkTest/Query.o \
			../tests/ChipmunkTest/Sensors.o \
			../tests/ChipmunkTest/Simple.o \
			../tests/ChipmunkTest/Springies.o \
			../tests/ChipmunkTest/Tank.o \
			../tests/ChipmunkTest/TheoJansen.o \
			../tests/ChipmunkTest/Tumble.o \
			../tests/ChipmunkTest/UnsafeOps.o \
			../tests/ChipmunkTest/cocos2dChipmunkDemo.o \
			../tests/ChipmunkTest/drawSpace.o \
			../tests/ClickAndMoveTest/ClickAndMoveTest.o \
			../tests/CocosDenshionTest/CocosDenshionTest.o \
			../tests/CocosNodeTest/CocosNodeTest.o \
			../tests/CurlTest/CurlTest.o \
			../tests/CurrentLanguageTest/CurrentLanguageTest.o \
			../tests/DirectorTest/DirectorTest.o \
			../tests/DrawPrimitivesTest/DrawPrimitivesTest.o \
			../tests/EaseActionsTest/EaseActionsTest.o \
			../tests/EffectsAdvancedTest/EffectsAdvancedTest.o \
			../tests/EffectsTest/EffectsTest.o \
			../tests/FontTest/FontTest.o \
			../tests/HiResTest/HiResTest.o \
			../tests/IntervalTest/IntervalTest.o \
			../tests/KeypadTest/KeypadTest.o \
			../tests/LabelTest/LabelTest.o \
			../tests/LayerTest/LayerTest.o \
			../tests/MenuTest/MenuTest.o \
			../tests/MotionStreakTest/MotionStreakTest.o \
			../tests/ParallaxTest/ParallaxTest.o \
			../tests/ParticleTest/ParticleTest.o \
			../tests/PerformanceTest/PerformanceNodeChildrenTest.o \
			../tests/PerformanceTest/PerformanceParticleTest.o \
			../tests/PerformanceTest/PerformanceSpriteTest.o \
			../tests/PerformanceTest/PerformanceTest.o \
			../tests/PerformanceTest/PerformanceTextureTest.o \
			../tests/PerformanceTest/PerformanceTouchesTest.o \
			../tests/ProgressActionsTest/ProgressActionsTest.o \
			../tests/RenderTextureTest/RenderTextureTest.o \
			../tests/RotateWorldTest/RotateWorldTest.o \
			../tests/SceneTest/SceneTest.o \
			../tests/SchedulerTest/SchedulerTest.o \
			../tests/SpriteTest/SpriteTest.o \
			../tests/TextInputTest/TextInputTest.o \
			../tests/Texture2dTest/Texture2dTest.o \
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

STATICLIBS	=	 -L$(TOP)/lib/linux/$(OUTDIRSUFFIX) -lbox2d -lchipmunk
SHAREDLIBS	=	-L$(TOP)/lib/linux/$(OUTDIRSUFFIX) -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,$(TOP)/lib/linux/$(OUTDIRSUFFIX)

####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)

####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core
