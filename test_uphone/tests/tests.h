#ifndef _TESTS_H_
#define _TESTS_H_

#include "ActionsTest/ActionsTest.h"
#include "TransitionsTest/TransitionsTest.h"

enum
{
    TEST_ACTIONS = 0,
    TEST_TRANSITIONS,
//     TEST_TEXTURE2D,
//     TEST_SPRITE,
//     TEST_LAYER,
//     TEST_SCENE,
//     TEST_FONT,
//     TEST_MENU,
//     TEST_ACTIONS_MANAGER,
//     TEST_INTERVAL,
//     TEST_TOUCHES,
//     TEST_PROGRESS_ACTIONS,
    TESTS_COUNT,
};

const std::string g_aTestNames[TESTS_COUNT] = {
    "ActionsTest",
    "TransitionsTest",
//     "Texture2dTest",
//     "SpriteTest",
//     "LayerTest",
//     "SceneTest",
//     "FontTest",
//     "MenuTest",
//     "ActionManagerTest",
//     "IntervalTest",
//     "TouchesTest",
//     "ProgressActionsTest",
};

#endif
