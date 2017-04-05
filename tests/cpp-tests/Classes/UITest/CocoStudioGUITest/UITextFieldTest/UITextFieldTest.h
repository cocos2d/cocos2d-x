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

DEFINE_TEST_SUITE(UITextFieldTests);

class UITextFieldTest : public UIScene
{
public:
    CREATE_FUNC(UITextFieldTest);

    UITextFieldTest();
    ~UITextFieldTest();
    virtual bool init() override;
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UITextFieldTest_MaxLength : public UIScene
{
public:
    CREATE_FUNC(UITextFieldTest_MaxLength);

    UITextFieldTest_MaxLength();
    ~UITextFieldTest_MaxLength();
    virtual bool init() override;
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UITextFieldTest_Password : public UIScene
{
public:
    CREATE_FUNC(UITextFieldTest_Password);

    UITextFieldTest_Password();
    ~UITextFieldTest_Password();
    virtual bool init() override;
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UITextFieldTest_LineWrap : public UIScene
{
public:
    CREATE_FUNC(UITextFieldTest_LineWrap);

    UITextFieldTest_LineWrap();
    ~UITextFieldTest_LineWrap();
    virtual bool init() override;
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UITextFieldTest_TrueTypeFont : public UIScene
{
public:
    CREATE_FUNC(UITextFieldTest_TrueTypeFont);

    UITextFieldTest_TrueTypeFont();
    ~UITextFieldTest_TrueTypeFont();
    virtual bool init() override;
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};

class UITextFieldTest_PlaceHolderColor : public UIScene
{
public:
    CREATE_FUNC(UITextFieldTest_PlaceHolderColor);

    UITextFieldTest_PlaceHolderColor();
    ~UITextFieldTest_PlaceHolderColor();
    virtual bool init() override;
    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);
    
protected:
    
    cocos2d::ui::Text* _displayValueLabel;
};
#endif /* defined(__TestCpp__UITextFieldTest__) */
