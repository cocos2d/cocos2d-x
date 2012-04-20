/*
 * CCControlScene.h
 *
 * Copyright (c) 2011 Yannick Loriot
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef __CCCONTROLSCENE_H__
#define __CCCONTROLSCENE_H__

#include "cocos2d.h"
#include "cocos2dExt.h"

USING_NS_CC;


#define CONTROL_SCENE_NODE_FUNC(controlScene) \
public: \
static CCScene* sceneWithTitle(const char * title) \
{ \
    CCScene* pScene = CCScene::node(); \
    controlScene* controlLayer = new controlScene(); \
    if (controlLayer && controlLayer->init()) \
    { \
        controlLayer->autorelease(); \
        controlLayer->getSceneTitleLabel()->setString(title); \
        pScene->addChild(controlLayer); \
    } \
    else \
    { \
        CC_SAFE_DELETE(controlLayer); \
    } \
    return pScene; \
}


class CCControlScene : public cocos2d::CCLayer
{
public:
    CCControlScene();
    ~CCControlScene();
    bool init();
    // Menu Callbacks
    void toExtensionsMainLayer(cocos2d::CCObject* sender);
    void previousCallback(cocos2d::CCObject* sender);
    void restartCallback(cocos2d::CCObject* sender);
    void nextCallback(cocos2d::CCObject* sender);

    /** Title label of the scene. */
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, m_pSceneTitleLabel, SceneTitleLabel)

    CONTROL_SCENE_NODE_FUNC(CCControlScene);
};

#endif /* __CCCONTROLSCENE_H__ */
