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
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPEN)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
// bada don't support libcurl
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
#include "CurlTest/CurlTest.h"
#endif
#endif
#endif
#include "UserDefaultTest/UserDefaultTest.h"
#include "BugsTest/BugsTest.h"
#include "Texture2dTest/Texture2dTest.h"
#include "FontTest/FontTest.h"
#include "CurrentLanguageTest/CurrentLanguageTest.h"
#include "TextureCacheTest/TextureCacheTest.h"
#include "NodeTest/NodeTest.h"
#include "ShaderTest/ShaderTest.h"
#include "ExtensionsTest/ExtensionsTest.h"
#include "MutiTouchTest/MutiTouchTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#include "ClippingNodeTest/ClippingNodeTest.h"
#include "ChipmunkTest/ChipmunkTest.h"
#endif
#include "FileUtilsTest/FileUtilsTest.h"
#include "SpineTest/SpineTest.h"
#include "TexturePackerEncryptionTest/TextureAtlasEncryptionTest.h"
#include "DataVisitorTest/DataVisitorTest.h"
#include "ConfigurationTest/ConfigurationTest.h"
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
    TEST_LABEL,
    TEST_TEXT_INPUT,
    TEST_SPRITE,
    TEST_SCHEDULER,
    TEST_RENDERTEXTURE,
    TEST_TEXTURE2D,
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    TEST_CHIPMUNK,
#endif
    TEST_BOX2D,
    TEST_BOX2DBED,
    TEST_EFFECT_ADVANCE,
    TEST_ACCELEROMRTER,
    TEST_KEYPAD,
    TEST_COCOSDENSHION,
    TEST_PERFORMANCE,
    TEST_ZWOPTEX,
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
    TEST_CURL,
#endif
#endif
    TEST_USERDEFAULT,
    TEST_BUGS,
    TEST_FONTS,
    TEST_CURRENT_LANGUAGE,
    TEST_TEXTURECACHE,
    TEST_EXTENSIONS,
    TEST_SHADER,
    TEST_MUTITOUCH,
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    TEST_CLIPPINGNODE,
#endif
    TEST_FILEUTILS,
    TEST_SPINE,
    TEST_TEXTUREPACKER_ENCRYPTION,
    TEST_DATAVISTOR,
	TEST_CONFIGURATION,

	// last one
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
    "LabelTest",
    "TextInputTest",
    "SpriteTest",
    "SchedulerTest",
    "RenderTextureTest",
    "Texture2DTest",
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    "ChipmunkTest",
#endif
    "Box2dTest",
    "Box2dTestBed",
    "EffectAdvancedTest",
    "Accelerometer",
    "KeypadTest",
    "CocosDenshionTest",
    "PerformanceTest",
    "ZwoptexTest",
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPTEN)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
    "CurlTest",
#endif
#endif
#endif
    "UserDefaultTest",
    "BugsTest",
    "FontTest",
    "CurrentLanguageTest",
    "TextureCacheTest",
    "ExtensionsTest",
    "ShaderTest",
    "MutiTouchTest",
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
    "ClippingNodeTest",
#endif
    "FileUtilsTest",
    "SpineTest",
    "TexturePackerEncryption",
    "DataVistorTest",
	"ConfigurationTest"
};

#endif
