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

#ifndef __TestCpp__UIDragPanelTest__
#define __TestCpp__UIDragPanelTest__

#include "../UIScene.h"

class UIDragPanelTest : public UIScene
{
public:
    UIDragPanelTest();
    ~UIDragPanelTest();
    bool init();
    void berthToLeftBottomEvent(CCObject* pSender);
    void berthToLeftTopEvent(CCObject* pSender);
    void berthToRightBottomEvent(CCObject* pSender);
    void berthToRightTopEvent(CCObject* pSender);
    void berthToLeftEvent(CCObject* pSender);
    void berthToTopEvent(CCObject* pSender);
    void berthToRightEvent(CCObject* pSender);
    void berthToBottomEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIDragPanelTest)
    UILabel *m_pDisplayValueLabel;
};

class UIDragPanelTest_Bounce : public UIScene
{
public:
    UIDragPanelTest_Bounce();
    ~UIDragPanelTest_Bounce();
    bool init();
    void bounceToLeftBottomEvent(CCObject* pSender);
    void bounceToRightBottomEvent(CCObject* pSender);
    void bounceToLeftTopEvent(CCObject* pSender);
    void bounceToRightTopEvent(CCObject* pSender);
    void bounceToLeftEvent(CCObject* pSender);
    void bounceToTopEvent(CCObject* pSender);
    void bounceToRightEvent(CCObject* pSender);
    void bounceToBottomEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIDragPanelTest_Bounce)
    UILabel *m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UIDragPanelTest__) */
