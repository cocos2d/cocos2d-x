require "luaScript/helper"

require "luaScript/ActionsTest/ActionsTest"
require "luaScript/TransitionsTest/TransitionsTest"
require "luaScript/ActionsProgressTest/ActionsProgressTest"
require "luaScript/EffectsTest/EffectsTest"
require "luaScript/ClickAndMoveTest/ClickAndMoveTest"
require "luaScript/RotateWorldTest/RotateWorldTest"
require "luaScript/ParticleTest/ParticleTest"
require "luaScript/ActionsEaseTest/ActionsEaseTest"
require "luaScript/MotionStreakTest/MotionStreakTest"
require "luaScript/DrawPrimitivesTest/DrawPrimitivesTest"
require "luaScript/NodeTest/NodeTest"
require "luaScript/TouchesTest/TouchesTest"
require "luaScript/SpriteTest/SpriteTest"

require "luaScript/PerformanceTest/PerformanceTest"
require "luaScript/LabelTest/LabelTest"
----------------------------------------------------

-- tests scene
Test_Table =
{
	"TEST_ACTIONS",
    "TEST_TRANSITIONS",
    "TEST_PROGRESS_ACTIONS",
    "TEST_EFFECTS",
    "TEST_CLICK_AND_MOVE",
    "TEST_ROTATE_WORLD",
    "TEST_PARTICLE",
    "TEST_EASE_ACTIONS",
    "TEST_MOTION_STREAK",
--  "TEST_DRAW_PRIMITIVES",
    "TEST_COCOSNODE",
    "TEST_TOUCHES",
--  "TEST_MENU",
--  "TEST_ACTION_MANAGER",
--  "TEST_LAYER",
--  "TEST_SCENE",
--  "TEST_PARALLAX",
--  "TEST_TILE_MAP",
--  "TEST_INTERVAL",
--  "TEST_CHIPMUNKACCELTOUCH",
	"TEST_LABEL",
--  "TEST_TEXT_INPUT",
    "TEST_SPRITE",
--  "TEST_SCHEDULER",
--  "TEST_RENDERTEXTURE",
--  "TEST_TEXTURE2D",
--  "TEST_BOX2D",
--  "TEST_BOX2DBED",
--  "TEST_EFFECT_ADVANCE",
--  "TEST_ACCELEROMRTER",
--  "TEST_KEYPAD",
--  "TEST_COCOSDENSHION",
--  "TEST_PERFORMANCE",
--  "TEST_ZWOPTEX",
--  "TEST_CURL",
--  "TEST_USERDEFAULT",
--  "TEST_BUGS",
--  "TEST_FONTS",
--  "TEST_CURRENT_LANGUAGE",
--  "TEST_TEXTURECACHE",
--  "TEST_EXTENSIONS",
--  "TEST_SHADER",
--  "TEST_MUTITOUCH",
    "TESTS_COUNT"
}

Test_Table = CreateEnumTable(Test_Table)

Test_Name =
{
    [0] = "ActionsTest",
    "TransitionsTest",
    "ActionsProgressTest",
    "EffectsTest",
    "ClickAndMoveTest",
    "RotateWorldTest",
    "ParticleTest",
    "ActionsEaseTest",
    "MotionStreakTest",
--  "DrawPrimitivesTest",
    "NodeTest",
    "TouchesTest",
--  "MenuTest",
--  "ActionManagerTest",
--  "LayerTest",
--  "SceneTest",
--  "ParallaxTest",
--  "TileMapTest",
--  "IntervalTest",
--  "ChipmunkAccelTouchTest",
	"LabelTest",
--  "TextInputTest",
    "SpriteTest",
--  "SchdulerTest",
--  "RenderTextureTest",
--  "Texture2DTest",
--  "Box2dTest",
--  "Box2dTestBed",
--  "EffectAdvancedTest",
--  "Accelerometer",
--  "KeypadTest",
--  "CocosDenshionTest",
--  "PerformanceTest",
--  "ZwoptexTest",
--  "CurlTest",
--  "UserDefaultTest",
--  "BugsTest",
--  "FontTest",
--  "CurrentLanguageTest",
--  "TextureCacheTest",
--  "ExtensionsTest",
--  "ShaderTest",
--  "MutiTouchTest"
}
