LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_logic_static

LOCAL_MODULE_FILENAME := libgame_logic

LOCAL_SRC_FILES := \
tests/AccelerometerTest/AccelerometerTest.cpp \
tests/ActionManagerTest/ActionManagerTest.cpp \
tests/ActionsTest/ActionsTest.cpp \
tests/ActionsEaseTest/ActionsEaseTest.cpp \
tests/ActionsProgressTest/ActionsProgressTest.cpp \
tests/Box2dTest/Box2dTest.cpp \
tests/Box2DTestBed/Box2dView.cpp \
tests/Box2DTestBed/GLES-Render.cpp \
tests/Box2DTestBed/Test.cpp \
tests/Box2DTestBed/TestEntries.cpp \
tests/BugsTest/Bug-1159.cpp \
tests/BugsTest/Bug-1174.cpp \
tests/BugsTest/Bug-350.cpp \
tests/BugsTest/Bug-422.cpp \
tests/BugsTest/Bug-624.cpp \
tests/BugsTest/Bug-886.cpp \
tests/BugsTest/Bug-899.cpp \
tests/BugsTest/Bug-914.cpp \
tests/BugsTest/BugsTest.cpp \
tests/BugsTest/Bug-458/Bug-458.cpp \
tests/BugsTest/Bug-458/QuestionContainerSprite.cpp \
tests/ChipmunkAccelTouchTest/ChipmunkAccelTouchTest.cpp \
tests/ClickAndMoveTest/ClickAndMoveTest.cpp \
tests/CocosDenshionTest/CocosDenshionTest.cpp \
tests/CurlTest/CurlTest.cpp \
tests/CurrentLanguageTest/CurrentLanguageTest.cpp \
tests/DirectorTest/DirectorTest.cpp \
tests/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
tests/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
tests/EffectsTest/EffectsTest.cpp \
tests/ExtensionsTest/ExtensionsTest.cpp \
tests/ExtensionsTest/NotificationCenterTest.cpp \
tests/FontTest/FontTest.cpp \
tests/HiResTest/HiResTest.cpp \
tests/IntervalTest/IntervalTest.cpp \
tests/KeypadTest/KeypadTest.cpp \
tests/LabelTest/LabelTest.cpp \
tests/LayerTest/LayerTest.cpp \
tests/NodeTest/NodeTest.cpp \
tests/TextInputTest/TextInputTest.cpp \
tests/MenuTest/MenuTest.cpp \
tests/MotionStreakTest/MotionStreakTest.cpp \
tests/ParallaxTest/ParallaxTest.cpp \
tests/ParticleTest/ParticleTest.cpp \
tests/PerformanceTest/PerformanceNodeChildrenTest.cpp \
tests/PerformanceTest/PerformanceParticleTest.cpp \
tests/PerformanceTest/PerformanceSpriteTest.cpp \
tests/PerformanceTest/PerformanceTest.cpp \
tests/PerformanceTest/PerformanceTextureTest.cpp \
tests/PerformanceTest/PerformanceTouchesTest.cpp \
tests/RenderTextureTest/RenderTextureTest.cpp \
tests/RotateWorldTest/RotateWorldTest.cpp \
tests/SceneTest/SceneTest.cpp \
tests/SchedulerTest/SchedulerTest.cpp \
tests/ShaderTest/ShaderTest.cpp \
tests/SpriteTest/SpriteTest.cpp \
tests/TextureCacheTest/TextureCacheTest.cpp \
tests/Texture2dTest/Texture2dTest.cpp \
tests/TileMapTest/TileMapTest.cpp \
tests/TouchesTest/Ball.cpp \
tests/TouchesTest/Paddle.cpp \
tests/TouchesTest/TouchesTest.cpp \
tests/TransitionsTest/TransitionsTest.cpp \
tests/UserDefaultTest/UserDefaultTest.cpp \
tests/ZwoptexTest/ZwoptexTest.cpp \
tests/controller.cpp \
tests/testBasic.cpp \
AppDelegate.cpp

LOCAL_STATIC_LIBRARIES := png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_STATIC_LIBRARIES += curl_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                   
LOCAL_SHARED_LIBRARIES := cocosdenshion_shared box2d_shared chipmunk_shared
            
include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx/platform/third_party/android/modules/libcurl)
$(call import-module,cocos2dx/platform/third_party/android/modules/libpng)
$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)
$(call import-module,cocos2dx/platform/third_party/android/modules/libjpeg)
