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
// havn't implement on marmalade
//#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#include "TextInputTest/TextInputTest.h"
//#endif
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
#include "DirectorTest/DirectorTest.h"
#include "BugsTest/BugsTest.h"
#include "Texture2dTest/Texture2dTest.h"
#include "FontTest/FontTest.h"
#include "CurrentLanguageTest/CurrentLanguageTest.h"
#include "TextureCacheTest/TextureCacheTest.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
	#include "ChipmunkTest/cocos2dChipmunkDemo.h"
#else
#ifdef MARMALADEUSECHIPMUNK
#if	(MARMALADEUSECHIPMUNK == 1)
	#include "ChipmunkTest/cocos2dChipmunkDemo.h"
#endif
#endif
#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)

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
    TEST_TEXT_INPUT,
    TEST_SPRITE,
    TEST_SCHEDULER,
    TEST_RENDERTEXTURE,
    TEST_TEXTURE2D,
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
    TEST_DIRECTOR,
    TEST_BUGS,
	TEST_FONTS,
	TEST_CURRENT_LANGUAGE,
	TEST_TEXTURECACHE,

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
    "TextInputTest",
    "SpriteTest",
    "SchdulerTest",
    "RenderTextureTest",
    "Texture2DTest",
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
	"UserDefaultTest",
    "DirectorTest",
    "BugsTest",
	"FontTest",
	"CurrentLanguageTest",
	"TextureCacheTest"
};

#endif
