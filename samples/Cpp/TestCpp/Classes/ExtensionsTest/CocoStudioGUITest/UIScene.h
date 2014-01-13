/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TestCpp__UIScene__
#define __TestCpp__UIScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "gui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

#define UI_SCENE_CREATE_FUNC(UIScene) \
public: \
static Scene* sceneWithTitle(const char * title) \
{ \
    Scene* pScene = Scene::create(); \
    UIScene* uiLayer = new UIScene(); \
    if (uiLayer && uiLayer->init()) \
    { \
        uiLayer->autorelease(); \
        uiLayer->getSceneTitle()->setText(title); \
        pScene->addChild(uiLayer); \
    } \
    else \
    { \
        CC_SAFE_DELETE(uiLayer); \
    } \
    return pScene; \
}

class UIScene : public Layer
{
public:
    UIScene();
    ~UIScene();
    bool init();
    // Menu Callbacks
    void toCocosGUITestScene(Object* sender, TouchEventType type);
    virtual void previousCallback(Object* sender, TouchEventType type);
    virtual void restartCallback(Object* sender, TouchEventType type);
    virtual void nextCallback(Object* sender, TouchEventType type);
    
    /** Title label of the scene. */    
    CC_SYNTHESIZE_READONLY(gui::Text*, _sceneTitle, SceneTitle)
    
    UI_SCENE_CREATE_FUNC(UIScene);
    
protected:
    // a selector callback
    void menuCloseCallback(Object* pSender, TouchEventType type);
    
protected:
    Layer* _uiLayer;
    Layout* _widget;
};

#endif /* defined(__TestCpp__UIScene__) */
