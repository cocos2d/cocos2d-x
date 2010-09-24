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
#include "ChipmunkTest/cocos2dChipmunkDemo.h"
#include "IntervalTest/IntervalTest.h"
#include "AtlasTest/AtlasTest.h"
#include "SpriteTest/SpriteTest.h"
#include "SchedulerTest/SchedulerTest.h"
#include "RenderTextureTest/RenderTextureTest.h"
#include "Box2DTest/Box2dTest.h"
#include "Box2DTestBed/Box2dView.h"
#include "EffectsAdvancedTest/EffectsAdvancedTest.h"
#include "HiResTest/HiResTest.h"

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
    TEST_ATLAS,
    TEST_SPRITE,
    TEST_SCHEDULER,
    TEST_RENDERTEXTURE,
    TEST_BOX2D,
    TEST_BOX2DBED,
    TEST_EFFECT_ADVANCE,
    TEST_HIRES,

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
    "AtlasTest",
    "SpriteTest",
    "SchdulerTest",
    "RenderTextureTest",
    "Box2dTest",
    "Box2dTestBed",
    "EffectAdvancedTest",
    "HiResTest",
};

#endif
