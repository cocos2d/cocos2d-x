#ifndef _TESTS_H_
#define _TESTS_H_

#include "ActionsTest/ActionsTest.h"
#include "TransitionsTest/TransitionsTest.h"
#include "ActionsProgressTest/ActionsProgressTest.h"
#include "EffectsTest/EffectsTest.h"
#include "ClickAndMoveTest/ClickAndMoveTest.h"
#include "RotateWorldTest/RotateWorldTest.h"
#include "ParticleTest/ParticleTest.h"
#include "ActionsEaseTest/ActionsEaseTest.h"
#include "MotionStreakTest/MotionStreakTest.h"
#include "DrawPrimitivesTest/DrawPrimitivesTest.h"
#include "TouchesTest/TouchesTest.h"
#include "MenuTest/MenuTest.h"
#include "ActionManagerTest/ActionManagerTest.h"
#include "LayerTest/LayerTest.h"
#include "SceneTest/SceneTest.h"
#include "ParallaxTest/ParallaxTest.h"
#include "TileMapTest/TileMapTest.h"
#include "IntervalTest/IntervalTest.h"
#include "LabelTest/LabelTest.h"
#include "TextInputTest/TextInputTest.h"
#include "SpriteTest/SpriteTest.h"
#include "SchedulerTest/SchedulerTest.h"
#include "RenderTextureTest/RenderTextureTest.h"
#include "Box2DTest/Box2dTest.h"
#include "Box2DTestBed/Box2dView.h"
#include "EffectsAdvancedTest/EffectsAdvancedTest.h"
#include "AccelerometerTest/AccelerometerTest.h"
#include "KeypadTest/KeypadTest.h"
#include "PerformanceTest/PerformanceTest.h"
#include "ZwoptexTest/ZwoptexTest.h"
#include "CocosDenshionTest/CocosDenshionTest.h"
#include "CurlTest/CurlTest.h"
#include "UserDefaultTest/UserDefaultTest.h"
#include "BugsTest/BugsTest.h"
#include "Texture2dTest/Texture2dTest.h"
#include "FontTest/FontTest.h"
#include "CurrentLanguageTest/CurrentLanguageTest.h"
#include "TextureCacheTest/TextureCacheTest.h"
#include "NodeTest/NodeTest.h"
#include "ShaderTest/ShaderTest.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    #include "ChipmunkTest/ChipmunkTest.h"
#else
#ifdef MARMALADEUSECHIPMUNK
#if    (MARMALADEUSECHIPMUNK == 1)
    #include "ChipmunkTest/ChipmunkTest.h"
#endif
#endif
#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)

#include "ExtensionsTest/ExtensionsTest.h"
#include "MutiTouchTest/MutiTouchTest.h"

enum
{
    TEST_ACTIONS = 0,
    TEST_TRANSITIONS,
    TEST_PROGRESS_ACTIONS,
    TEST_EFFECTS,
    TEST_CLICK_AND_MOVE,
    TEST_ROTATE_WORLD,
    TEST_PARTICLE,
    TEST_EASE_ACTIONS,
    TEST_MOTION_STREAK,
    TEST_DRAW_PRIMITIVES,
    TEST_COCOSNODE,
    TEST_TOUCHES,
    TEST_MENU,
    TEST_ACTION_MANAGER,
    TEST_LAYER,
    TEST_SCENE,
    TEST_PARALLAX,
    TEST_TILE_MAP,
    TEST_INTERVAL,
    TEST_CHIPMUNKACCELTOUCH,
    TEST_LABEL,
    TEST_TEXT_INPUT,
    TEST_SPRITE,
    TEST_SCHEDULER,
    TEST_RENDERTEXTURE,
    TEST_TEXTURE2D,
    TEST_BOX2D,
    TEST_BOX2DBED,
    TEST_EFFECT_ADVANCE,
    TEST_ACCELEROMRTER,
    TEST_KEYPAD,
    TEST_COCOSDENSHION,
    TEST_PERFORMANCE,
    TEST_ZWOPTEX,
    TEST_CURL,
    TEST_USERDEFAULT,
    TEST_BUGS,
    TEST_FONTS,
    TEST_CURRENT_LANGUAGE,
    TEST_TEXTURECACHE,
    TEST_EXTENSIONS,
    TEST_SHADER,
    TEST_MUTITOUCH,
    TESTS_COUNT,    
};

const std::string g_aTestNames[TESTS_COUNT] = {
    "ActionsTest",
    "TransitionsTest",
    "ActionsProgressTest",
    "EffectsTest",
    "ClickAndMoveTest",
    "RotateWorldTest",
    "ParticleTest",
    "ActionsEaseTest",
    "MotionStreakTest",
    "DrawPrimitivesTest",
    "NodeTest",
    "TouchesTest",
    "MenuTest",
    "ActionManagerTest",
    "LayerTest",
    "SceneTest",
    "ParallaxTest",
    "TileMapTest",
    "IntervalTest",
    "ChipmunkAccelTouchTest",
    "LabelTest",
    "TextInputTest",
    "SpriteTest",
    "SchdulerTest",
    "RenderTextureTest",
    "Texture2DTest",
    "Box2dTest",
    "Box2dTestBed",
    "EffectAdvancedTest",
    "Accelerometer",
    "KeypadTest",
    "CocosDenshionTest",
    "PerformanceTest",
    "ZwoptexTest",
    "CurlTest",
    "UserDefaultTest",
    "BugsTest",
    "FontTest",
    "CurrentLanguageTest",
    "TextureCacheTest",
    "ExtensionsTest",
    "ShaderTest",
    "MutiTouchTest"
};

#endif
