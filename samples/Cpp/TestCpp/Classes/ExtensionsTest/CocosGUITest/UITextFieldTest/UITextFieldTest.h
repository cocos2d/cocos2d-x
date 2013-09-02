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

#ifndef __TestCpp__UITextFieldTest__
#define __TestCpp__UITextFieldTest__

#include "../UIScene.h"

class UITextFieldTest : public UIScene
{
public:
    UITextFieldTest();
    ~UITextFieldTest();
    bool init();
    void attachWithIMEEvent(CCObject* pSender);
    void detachWithIMEEvent(CCObject* pSender);
    void insertTextEvent(CCObject* pSender);
    void deleteBackwardEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextFieldTest)
    UILabel* m_pDisplayValueLabel;
};

class UITextFieldTest_MaxLength : public UIScene
{
public:
    UITextFieldTest_MaxLength();
    ~UITextFieldTest_MaxLength();
    bool init();
    void attachWithIMEEvent(CCObject* pSender);
    void detachWithIMEEvent(CCObject* pSender);
    void insertTextEvent(CCObject* pSender);
    void deleteBackwardEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextFieldTest_MaxLength)
    UILabel* m_pDisplayValueLabel;
};

class UITextFieldTest_Password : public UIScene
{
public:
    UITextFieldTest_Password();
    ~UITextFieldTest_Password();
    bool init();
    void attachWithIMEEvent(CCObject* pSender);
    void detachWithIMEEvent(CCObject* pSender);
    void insertTextEvent(CCObject* pSender);
    void deleteBackwardEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UITextFieldTest_Password)
    UILabel* m_pDisplayValueLabel;
};
#endif /* defined(__TestCpp__UITextFieldTest__) */
