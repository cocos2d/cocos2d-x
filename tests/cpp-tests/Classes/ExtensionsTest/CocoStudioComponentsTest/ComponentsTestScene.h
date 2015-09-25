#ifndef __COMPONENTSTESTSCENE_H__
#define __COMPONENTSTESTSCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "BaseTest.h"

DEFINE_TEST_SUITE(CocoStudioComponentsTests);

class CocoStudioComponentsTest : public TestCase
{
public:
    CREATE_FUNC(CocoStudioComponentsTest);

    virtual bool init() override;

    cocos2d::Node* createGameScene();
};

#endif  // __HELLOWORLD_SCENE_H__
