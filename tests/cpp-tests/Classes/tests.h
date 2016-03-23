#ifndef _TESTS_H_
#define _TESTS_H_

#if CC_ENABLE_BOX2D_INTEGRATION
#include "Box2DTest/Box2dTest.h"
#include "Box2DTestBed/Box2dView.h"
#endif
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
#include "ChipmunkTest/ChipmunkTest.h"
#include "ClippingNodeTest/ClippingNodeTest.h"
#endif
#include "NewAudioEngineTest/NewAudioEngineTest.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_EMSCRIPEN)
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
// bada don't support libcurl
#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
#include "CurlTest/CurlTest.h"
#endif
#endif
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JNITest/JNITest.h"
#endif

// sort them alphabetically. thanks
#include "ActionManagerTest/ActionManagerTest.h"
#include "ActionsEaseTest/ActionsEaseTest.h"
#include "ActionsProgressTest/ActionsProgressTest.h"
#include "ActionsTest/ActionsTest.h"
#include "AllocatorTest/AllocatorTest.h"
#include "BillBoardTest/BillBoardTest.h"
#include "BugsTest/BugsTest.h"
#include "Camera3DTest/Camera3DTest.h"
#include "ClickAndMoveTest/ClickAndMoveTest.h"
#include "CocosDenshionTest/CocosDenshionTest.h"
#include "CocosStudio3DTest/CocosStudio3DTest.h"
#include "ConfigurationTest/ConfigurationTest.h"
#include "ConsoleTest/ConsoleTest.h"
#include "CurrentLanguageTest/CurrentLanguageTest.h"
#include "DataVisitorTest/DataVisitorTest.h"
#include "DownloaderTest/DownloaderTest.h"
#include "DrawPrimitivesTest/DrawPrimitivesTest.h"
#include "EffectsAdvancedTest/EffectsAdvancedTest.h"
#include "EffectsTest/EffectsTest.h"
#include "ExtensionsTest/ExtensionsTest.h"
#include "FileUtilsTest/FileUtilsTest.h"
#include "FontTest/FontTest.h"
#include "InputTest/MouseTest.h"
#include "IntervalTest/IntervalTest.h"
#include "LabelTest/LabelTest.h"
#include "LabelTest/LabelTestNew.h"
#include "LayerTest/LayerTest.h"
#include "LightTest/LightTest.h"
#include "MaterialSystemTest/MaterialSystemTest.h"
#include "MenuTest/MenuTest.h"
#include "MotionStreakTest/MotionStreakTest.h"
#include "MutiTouchTest/MutiTouchTest.h"
#include "NavMeshTest/NavMeshTest.h"
#include "NewEventDispatcherTest/NewEventDispatcherTest.h"
#include "NewRendererTest/NewRendererTest.h"
#include "NodeTest/NodeTest.h"
#include "OpenURLTest/OpenURLTest.h"
#include "ParallaxTest/ParallaxTest.h"
#include "Particle3DTest/Particle3DTest.h"
#include "ParticleTest/ParticleTest.h"
#include "Physics3DTest/Physics3DTest.h"
#include "PhysicsTest/PhysicsTest.h"
#include "ReleasePoolTest/ReleasePoolTest.h"
#include "RenderTextureTest/RenderTextureTest.h"
#include "RotateWorldTest/RotateWorldTest.h"
#include "Scene3DTest/Scene3DTest.h"
#include "SceneTest/SceneTest.h"
#include "SchedulerTest/SchedulerTest.h"
#include "ShaderTest/ShaderTest.h"
#include "ShaderTest/ShaderTest2.h"
#include "SpineTest/SpineTest.h"
#include "Sprite3DTest/Sprite3DTest.h"
#include "SpritePolygonTest/SpritePolygonTest.h"
#include "SpriteTest/SpriteTest.h"
#include "TerrainTest/TerrainTest.h"
#include "TextInputTest/TextInputTest.h"
#include "Texture2dTest/Texture2dTest.h"
#include "TextureCacheTest/TextureCacheTest.h"
#include "TexturePackerEncryptionTest/TextureAtlasEncryptionTest.h"
#include "TileMapTest/TileMapTest.h"
#include "TileMapTest/TileMapTest2.h"
#include "TouchesTest/TouchesTest.h"
#include "TransitionsTest/TransitionsTest.h"
#include "UITest/UITest.h"
#include "UnitTest/UnitTest.h"
#include "UserDefaultTest/UserDefaultTest.h"
#include "VibrateTest/VibrateTest.h"
#include "ZwoptexTest/ZwoptexTest.h"
#include "SpriteFrameCacheTest/SpriteFrameCacheTest.h"

#endif
