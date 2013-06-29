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
#ifdef CC_KEYBOARD_SUPPORT
#include "KeyboardTest/KeyboardTest.h"
#endif
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

#endif
