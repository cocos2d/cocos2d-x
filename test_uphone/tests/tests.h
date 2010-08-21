#ifndef _TESTS_H_
#define _TESTS_H_

#include "ActionsTest/ActionsTest.h"
#include "TransitionsTest/TransitionsTest.h"
#include "ProgressActionsTest/ProgressActionsTest.h"

enum
{
    TEST_ACTIONS = 0,
    TEST_TRANSITIONS,
    TEST_PROGRESS_ACTIONS,
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
