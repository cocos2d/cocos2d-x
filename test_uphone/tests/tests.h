#ifndef _TESTS_H_
#define _TESTS_H_

#include "ActionsTest/ActionsTest.h"

enum
{
    TEST_TEXTURE2D = 0,
    TEST_SPRITE,
    TEST_LAYER,
    TEST_SCENE,
    TEST_FONT,
    TEST_MENU,
    TEST_ACTIONS,
    TEST_ACTIONS_MANAGER,
    TEST_INTERVAL,
    TEST_TOUCHES,
    TEST_PROGRESS_ACTIONS,
    TESTS_COUNT,
};

const std::string g_aTestNames[TESTS_COUNT] = {
    "Texture2dTest",
    "SpriteTest",
    "LayerTest",
    "SceneTest",
    "FontTest",
    "MenuTest",
    "ActionsTest",
    "ActionManagerTest",
    "IntervalTest",
    "TouchesTest",
    "ProgressActionsTest",
};

#endif
