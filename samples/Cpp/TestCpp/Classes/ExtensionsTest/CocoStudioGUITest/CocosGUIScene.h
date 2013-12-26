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

#ifndef __TestCpp__CocosGUIScene__
#define __TestCpp__CocosGUIScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../testBasic.h"
#include "gui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace gui;

class CocosGUITestMainLayer : public Layer
{
public:
    virtual void onEnter();
    
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    
	Point _beginPos;
    Menu* _itemMenu;
    
	int _testcount;
};

class CocosGUITestScene : public TestScene
{
public:
    virtual void runThisTest();
};

/*
class CocosGUITestScene : public TestScene
{
public:
	CocosGUITestScene(bool portrait = false);
    virtual ~CocosGUITestScene();
	virtual void runThisTest();
    
	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(Object* sender);    
    
    void load(Object* pSender, int count);
    void loadTextureCallBack(Object *obj);
    
    void menuCallback(Object* pSender);
    
    UILayer* _ul;
    
    LabelTTF* _label;
    
    Menu* _itemMenu;
};
 */

#endif /* defined(__TestCpp__CocosGUIScene__) */
