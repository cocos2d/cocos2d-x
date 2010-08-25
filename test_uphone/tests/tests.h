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
//     TEST_TEXTURE2D,
//     TEST_SPRITE,
//     TEST_LAYER,
//     TEST_SCENE,
//     TEST_FONT,
//     TEST_MENU,
//     TEST_ACTIONS_MANAGER,
//     TEST_INTERVAL,
//     TEST_TOUCHES,
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
//     "Texture2dTest",
//     "SpriteTest",
//     "LayerTest",
//     "SceneTest",
//     "FontTest",
//     "MenuTest",
//     "ActionManagerTest",
//     "IntervalTest",
//     "TouchesTest",
};

#endif
