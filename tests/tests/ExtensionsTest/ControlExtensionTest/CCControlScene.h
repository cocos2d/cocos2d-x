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

#include "cocos2d.h"

// 'scene' is an autorelease object.


// 'layer' is an autorelease object.
CCControlScene *controlLayer = CCControlScene::node();
controlLayer->getSceneTitleLabel()->setString(title);

// add layer as a child to scene
scene->addChild(controlLayer);

// return the scene
return scene;

#define CONTROL_SCENE_NODE_FUNC(scene) \
static scene* sceneWithTitle(const char * title) \
{ \
    scene *pRet = new scene(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
    } \
    else \
    { \
        CC_SAFE_DELETE(pRet); \
    } \
    return pRet; \
}

class CCControlScene : public cocos2d::CCLayer
{
public:
    ~CCControlScene();
    bool init();

    /**
     * Returns a CCScene that contains the CCControl example layer.
     *
     * @param title The title of the scene.
     */
    static cocos2d::CCScene* sceneWithTitle(const char * title);

    // Menu Callbacks
    void previousCallback(cocos2d::CCNode* sender);
    void restartCallback(cocos2d::CCNode* sender);
    void nextCallback(cocos2d::CCNode* sender);

    /** Title label of the scene. */
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, m_pSceneTitleLabel, SceneTitleLabel)

    LAYER_NODE_FUNC(CCControlScene);
};
