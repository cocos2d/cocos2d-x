EXECUTABLE = TestCpp

SOURCES = ../Classes/AccelerometerTest/AccelerometerTest.cpp \
	../Classes/ActionManagerTest/ActionManagerTest.cpp \
	../Classes/ActionsEaseTest/ActionsEaseTest.cpp \
	../Classes/ActionsProgressTest/ActionsProgressTest.cpp \
	../Classes/ActionsTest/ActionsTest.cpp \
	../Classes/Box2DTest/Box2dTest.cpp \
	../Classes/Box2DTestBed/Box2dView.cpp \
	../Classes/Box2DTestBed/GLES-Render.cpp \
	../Classes/Box2DTestBed/Test.cpp \
	../Classes/Box2DTestBed/TestEntries.cpp \
	../Classes/BugsTest/Bug-1159.cpp \
	../Classes/BugsTest/Bug-1174.cpp \
	../Classes/BugsTest/Bug-350.cpp \
	../Classes/BugsTest/Bug-422.cpp \
	../Classes/BugsTest/Bug-458/Bug-458.cpp \
	../Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp \
	../Classes/BugsTest/Bug-624.cpp \
	../Classes/BugsTest/Bug-886.cpp \
	../Classes/BugsTest/Bug-899.cpp \
	../Classes/BugsTest/Bug-914.cpp \
	../Classes/BugsTest/BugsTest.cpp \
	../Classes/ChipmunkTest/ChipmunkTest.cpp \
	../Classes/ClickAndMoveTest/ClickAndMoveTest.cpp \
	../Classes/ClippingNodeTest/ClippingNodeTest.cpp \
	../Classes/CocosDenshionTest/CocosDenshionTest.cpp \
	../Classes/CurrentLanguageTest/CurrentLanguageTest.cpp \
	../Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
	../Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
	../Classes/EffectsTest/EffectsTest.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/AnimationsTest/AnimationsTestLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.cpp \
	../Classes/ExtensionsTest/CocosBuilderTest/TimelineCallbackTest/TimelineCallbackTestLayer.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp \
	../Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp \
	../Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp \
	../Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp \
	../Classes/ExtensionsTest/ExtensionsTest.cpp \
	../Classes/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.cpp \
	../Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp \
	../Classes/ExtensionsTest/ComponentsTest/ComponentsTestScene.cpp \
	../Classes/ExtensionsTest/ComponentsTest/EnemyController.cpp \
	../Classes/ExtensionsTest/ComponentsTest/GameOverScene.cpp \
	../Classes/ExtensionsTest/ComponentsTest/PlayerController.cpp \
	../Classes/ExtensionsTest/ComponentsTest/ProjectileController.cpp \
	../Classes/ExtensionsTest/ComponentsTest/SceneController.cpp \
	../Classes/ExtensionsTest/ArmatureTest/ArmatureScene.cpp \
	../Classes/ExtensionsTest/Scale9SpriteTest/Scale9SpriteTest.cpp \
	../Classes/FontTest/FontTest.cpp \
	../Classes/IntervalTest/IntervalTest.cpp \
	../Classes/KeypadTest/KeypadTest.cpp \
	../Classes/LabelTest/LabelTest.cpp \
	../Classes/LayerTest/LayerTest.cpp \
	../Classes/MenuTest/MenuTest.cpp \
	../Classes/MotionStreakTest/MotionStreakTest.cpp \
	../Classes/MutiTouchTest/MutiTouchTest.cpp \
	../Classes/NodeTest/NodeTest.cpp \
	../Classes/ParallaxTest/ParallaxTest.cpp \
	../Classes/ParticleTest/ParticleTest.cpp \
	../Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp \
	../Classes/PerformanceTest/PerformanceParticleTest.cpp \
	../Classes/PerformanceTest/PerformanceSpriteTest.cpp \
	../Classes/PerformanceTest/PerformanceTest.cpp \
	../Classes/PerformanceTest/PerformanceTextureTest.cpp \
	../Classes/PerformanceTest/PerformanceTouchesTest.cpp \
	../Classes/RenderTextureTest/RenderTextureTest.cpp \
	../Classes/RotateWorldTest/RotateWorldTest.cpp \
	../Classes/SceneTest/SceneTest.cpp \
	../Classes/SchedulerTest/SchedulerTest.cpp \
	../Classes/ShaderTest/ShaderTest.cpp \
	../Classes/SpriteTest/SpriteTest.cpp \
	../Classes/TextInputTest/TextInputTest.cpp \
	../Classes/Texture2dTest/Texture2dTest.cpp \
	../Classes/TextureCacheTest/TextureCacheTest.cpp \
	../Classes/TileMapTest/TileMapTest.cpp \
	../Classes/TouchesTest/Ball.cpp \
	../Classes/TouchesTest/Paddle.cpp \
	../Classes/TouchesTest/TouchesTest.cpp \
	../Classes/TransitionsTest/TransitionsTest.cpp \
	../Classes/UserDefaultTest/UserDefaultTest.cpp \
	../Classes/ZwoptexTest/ZwoptexTest.cpp \
	../Classes/FileUtilsTest/FileUtilsTest.cpp \
	../Classes/DataVisitorTest/DataVisitorTest.cpp \
	../Classes/ConfigurationTest/ConfigurationTest.cpp \
	../Classes/controller.cpp \
	../Classes/testBasic.cpp \
	../Classes/AppDelegate.cpp \
	../Classes/BaseTest.cpp \
	../Classes/VisibleRect.cpp \
	main.cpp

RESOURCE_PATH = ../Resources

RESOURCES := $(shell (cd $(RESOURCE_PATH); find . -type f ! -name '* *'))

SHAREDLIBS = -lcocos2d -lcocosdenshion
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so

include ../../../../cocos2dx/proj.emscripten/cocos2dx.mk

INCLUDES +=  -I../ \
    -I../../ \
    -I../Classes \
    -I$(COCOS_ROOT)/CocosDenshion/include \
    -I$(COCOS_ROOT)/extensions/ \
    -I$(COCOS_ROOT)/external/ \
    -I$(COCOS_ROOT)/external/chipmunk/include/chipmunk

STATICLIBS += \
    $(LIB_DIR)/libextension.a \
    $(LIB_DIR)/libbox2d.a \
    $(LIB_DIR)/libchipmunk.a

DEFINES += -DCC_ENABLE_CHIPMUNK_INTEGRATION=1

####### Build rules
$(TARGET).js: $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS) $(LIBS)

$(TARGET).data: $(CORE_MAKEFILE_LIST) $(patsubst %,$(RESOURCE_PATH)/%,$(RESOURCES))
	@mkdir -p $(@D)
	$(eval RESTMP := $(shell mktemp -d /tmp/cocos-emscripten.XXXXXX))
	# Always need a font path, so ensure that it is created first.
	mkdir -p $(RESTMP)/fonts
	(cd $(RESOURCE_PATH) && tar cf - $(RESOURCES)) | (cd $(RESTMP) && tar xvf -)
	(cd $(RESTMP); python $(PACKAGER) $(EXECUTABLE).data $(patsubst %,--preload %,$(RESOURCES)) --preload fonts --pre-run > $(EXECUTABLE).data.js)
	mv $(RESTMP)/$(EXECUTABLE).data $@
	mv $(RESTMP)/$(EXECUTABLE).data.js $@.js
	# Copy the assets as individual files to the output directory in addition
	# to building the .data file so that async texture loading works.
	cp -av $(RESOURCE_PATH)/* $(shell dirname $@)
	rm -rf $(RESTMP)

$(BIN_DIR)/$(HTMLTPL_FILE): $(HTMLTPL_DIR)/$(HTMLTPL_FILE) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	@cp -Rf $(HTMLTPL_DIR)/* $(BIN_DIR)
	@sed -i -e "s/JS_APPLICATION/$(EXECUTABLE)/g" $(BIN_DIR)/$(HTMLTPL_FILE)

####### Compile
$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
