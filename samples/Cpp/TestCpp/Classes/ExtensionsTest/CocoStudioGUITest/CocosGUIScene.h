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
#include "cocos-ext.h"
#include "../../testBasic.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class CocosGUITestScene : public TestScene
{
public:
	CocosGUITestScene(bool bPortrait = false);
    virtual ~CocosGUITestScene();
	virtual void runThisTest();
    
	// The CallBack for back to the main menu scene
	virtual void MainMenuCallback(CCObject* pSender);
    
    void toCocosGUIExampleScene(CCObject* pSender);
    
    void load(CCObject* pSender, int count);
    void loadTextureCallBack(CCObject *obj);
    
    void menuCallback(CCObject* pSender);
    
    UILayer* ul;
    
    CCLabelTTF* m_pLabel;
    
    CCMenu* m_pItemMenu;
};

#endif /* defined(__TestCpp__CocosGUIScene__) */
