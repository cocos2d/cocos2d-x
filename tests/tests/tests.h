#ifndef _TESTS_H_
#define _TESTS_H_

#include "ActionsTest/ActionsTest.h"
#include "TransitionsTest/TransitionsTest.h"
#include "ProgressActionsTest/ProgressActionsTest.h"
#include "EffectsTest/EffectsTest.h"
#include "ClickAndMoveTest/ClickAndMoveTest.h"
#include "RotateWorldTest/RotateWorldTest.h"
#include "ParticleTest/ParticleTest.h"
#include "EaseActionsTest/EaseActionsTest.h"
#include "MotionStreakTest/MotionStreakTest.h"
#include "DrawPrimitivesTest/DrawPrimitivesTest.h"
#include "CocosNodeTest/CocosNodeTest.h"
#include "TouchesTest/TouchesTest.h"
#include "MenuTest/MenuTest.h"
#include "ActionManagerTest/ActionManagerTest.h"
#include "LayerTest/LayerTest.h"
#include "SceneTest/SceneTest.h"
#include "ParallaxTest/ParallaxTest.h"
#include "TileMapTest/TileMapTest.h"
#include "IntervalTest/IntervalTest.h"
#include "LabelTest/LabelTest.h"

// havn't implement on wophone and airplay
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WOPHONE) && (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
#include "TextInputTest/TextInputTest.h"
#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_WOPHONE) && (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)

#include "SpriteTest/SpriteTest.h"
#include "SchedulerTest/SchedulerTest.h"
#include "RenderTextureTest/RenderTextureTest.h"
#include "Box2DTest/Box2dTest.h"
#include "Box2DTestBed/Box2dView.h"
#include "EffectsAdvancedTest/EffectsAdvancedTest.h"
#include "HiResTest/HiResTest.h"
#include "AccelerometerTest/AccelerometerTest.h"
#include "KeypadTest/KeypadTest.h"
#include "PerformanceTest/PerformanceTest.h"
#include "ZwoptexTest/ZwoptexTest.h"
#include "CocosDenshionTest/CocosDenshionTest.h"
#include "CurlTest/CurlTest.h"
#include "UserDefaultTest/UserDefaultTest.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
	#include "ChipmunkTest/cocos2dChipmunkDemo.h"
#else
#ifdef AIRPLAYUSECHIPMUNK
#if	(AIRPLAYUSECHIPMUNK == 1)
	#include "ChipmunkTest/cocos2dChipmunkDemo.h"
#endif
#endif
#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)

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
    TEST_CHIPMUNK,
    TEST_LABEL,
    // havn't implement on wophone and airplay
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WOPHONE) && (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
    TEST_TEXT_INPUT,
#endif
    TEST_SPRITE,
    TEST_SCHEDULER,
    TEST_RENDERTEXTURE,
    TEST_BOX2D,
    TEST_BOX2DBED,
    TEST_EFFECT_ADVANCE,
    TEST_HIRES,
    TEST_ACCELEROMRTER,
    TEST_KEYPAD,
	TEST_COCOSDENSHION,
    TEST_PERFORMANCE,
    TEST_ZWOPTEX,
	TEST_CURL,
	TEST_USERDEFAULT,

    TESTS_COUNT,
};

const std::string g_aTestNames[TESTS_COUNT] = {
    "ActionsTest",
    "TransitionsTest",
    "ProgressActionsTest",
    "EffectsTest",
    "ClickAndMoveTest",
    "RotateWorldTest",
    "ParticleTest",
    "EaseActionsTest",
    "MotionStreakTest",
    "DrawPrimitivesTest",
    "CocosNodeTest",
    "TouchesTest",
    "MenuTest",
    "ActionManagerTest",
    "LayerTest",
    "SceneTest",
    "ParallaxTest",
    "TileMapTest",
    "IntervalTest",
    "ChipmunkTest",
    "LabelTest",
    // havn't implement on wophone and airplay
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WOPHONE) && (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
    "TextInputTest",
#endif
    "SpriteTest",
    "SchdulerTest",
    "RenderTextureTest",
    "Box2dTest",
    "Box2dTestBed",
    "EffectAdvancedTest",
    "HiResTest",
    "Accelerometer",
    "KeypadTest",
	"CocosDenshionTest",
    "PerformanceTest",
    "ZwoptexTest",
	"CurlTest",
	"UserDefaultTest"
};

#endif
