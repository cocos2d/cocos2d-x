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

#ifndef __TestCpp__UIScene_Editor__
#define __TestCpp__UIScene_Editor__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

#define UI_SCENE_EDITOR_CREATE_FUNC(UIScene_Editor) \
public: \
static Scene* sceneWithTitle(const char * title) \
{ \
    Scene* pScene = Scene::create(); \
    UIScene_Editor* uiLayer = new UIScene_Editor(); \
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

class UIScene_Editor : public Layer
{
public:
    UIScene_Editor();
    ~UIScene_Editor();
    
    bool init();
    virtual void previousCallback(Ref* sender, TouchEventType type);
    virtual void nextCallback(Ref* sender, TouchEventType type);
    
    void toGUIEditorTestScene(Ref* sender, TouchEventType type);
    
    /** Title label of the scene.*/
    CC_SYNTHESIZE_READONLY(Text*, _sceneTitle, SceneTitle)
    
    UI_SCENE_EDITOR_CREATE_FUNC(UIScene_Editor);
    
protected:
    Layer* _touchGroup;
    Layout* _layout;
};

#endif /* defined(__TestCpp__UIScene_Editor__) */
