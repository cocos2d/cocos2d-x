LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := tests

LOCAL_SRC_FILES := tests.cpp \
../../../tests/AccelerometerTest/AccelerometerTest.cpp \
../../../tests/ActionManagerTest/ActionManagerTest.cpp \
../../../tests/ActionsTest/ActionsTest.cpp \
../../../tests/AtlasTest/AtlasTest.cpp \
../../../tests/Box2DTest/Box2dTest.cpp \
../../../tests/Box2DTestBed/Box2dView.cpp \
../../../tests/Box2DTestBed/GLES-Render.cpp \
../../../tests/Box2DTestBed/Test.cpp \
../../../tests/Box2DTestBed/TestEntries.cpp \
../../../tests/ChipmunkTest/Bounce.cpp \
../../../tests/ChipmunkTest/Joints.cpp \
../../../tests/ChipmunkTest/LogoSmash.cpp \
../../../tests/ChipmunkTest/MagnetsElectric.cpp \
../../../tests/ChipmunkTest/OneWay.cpp \
../../../tests/ChipmunkTest/Planet.cpp \
../../../tests/ChipmunkTest/Player.cpp \
../../../tests/ChipmunkTest/Plink.cpp \
../../../tests/ChipmunkTest/Pump.cpp \
../../../tests/ChipmunkTest/PyramidStack.cpp \
../../../tests/ChipmunkTest/PyramidTopple.cpp \
../../../tests/ChipmunkTest/Query.cpp \
../../../tests/ChipmunkTest/Sensors.cpp \
../../../tests/ChipmunkTest/Simple.cpp \
../../../tests/ChipmunkTest/Springies.cpp \
../../../tests/ChipmunkTest/TheoJansen.cpp \
../../../tests/ChipmunkTest/Tumble.cpp \
../../../tests/ChipmunkTest/UnsafeOps.cpp \
../../../tests/ChipmunkTest/cocos2dChipmunkDemo.cpp \
../../../tests/ChipmunkTest/drawSpace.cpp \
../../../tests/ClickAndMoveTest/ClickAndMoveTest.cpp \
../../../tests/CocosNodeTest/CocosNodeTest.cpp \
../../../tests/DrawPrimitivesTest/DrawPrimitivesTest.cpp \
../../../tests/EaseActionsTest/EaseActionsTest.cpp \
../../../tests/EffectsAdvancedTest/EffectsAdvancedTest.cpp \
../../../tests/EffectsTest/EffectsTest.cpp \
../../../tests/HiResTest/HiResTest.cpp \
../../../tests/IntervalTest/IntervalTest.cpp \
../../../tests/KeypadTest/KeypadTest.cpp \
../../../tests/LayerTest/LayerTest.cpp \
../../../tests/MenuTest/MenuTest.cpp \
../../../tests/MotionStreakTest/MotionStreakTest.cpp \
../../../tests/ParallaxTest/ParallaxTest.cpp \
../../../tests/ParticleTest/ParticleTest.cpp \
../../../tests/ProgressActionsTest/ProgressActionsTest.cpp \
../../../tests/RenderTextureTest/RenderTextureTest.cpp \
../../../tests/RotateWorldTest/RotateWorldTest.cpp \
../../../tests/SceneTest/SceneTest.cpp \
../../../tests/SchedulerTest/SchedulerTest.cpp \
../../../tests/SpriteTest/SpriteTest.cpp \
../../../tests/TileMapTest/TileMapTest.cpp \
../../../tests/TouchesTest/Ball.cpp \
../../../tests/TouchesTest/Paddle.cpp \
../../../tests/TouchesTest/TouchesTest.cpp \
../../../tests/TransitionsTest/TransitionsTest.cpp \
../../../tests/controller.cpp \
../../../tests/testBasic.cpp \
../../../AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../cocos2dx \
                   $(LOCAL_PATH)/../cocos2dx/include \
                   $(LOCAL_PATH)/../../../tests \
                   $(LOCAL_PATH)/../../.. \
                   $(LOCAL_PATH)/../chipmunk/include/chipmunk \
                   $(LOCAL_PATH)/../
                   
LOCAL_LDLIBS := -lGLESv1_CM \
                -L$(LOCAL_PATH)/../../libs/armeabi -lcocos2d -llog \
                -lbox2d -lchipmunk
            
include $(BUILD_SHARED_LIBRARY)
                   