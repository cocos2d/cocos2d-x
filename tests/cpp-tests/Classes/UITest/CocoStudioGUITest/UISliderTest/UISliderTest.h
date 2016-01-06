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

#ifndef __TestCpp__UISliderTest__
#define __TestCpp__UISliderTest__

#include "../UIScene.h"

DEFINE_TEST_SUITE(UISliderTests);

class UISliderTest : public UIScene
{
public:
    CREATE_FUNC(UISliderTest);

    UISliderTest();
    ~UISliderTest();
    virtual bool init() override;
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    void printWidgetResources(cocos2d::Ref* sender);
    
protected:
    cocos2d::ui::TextBMFont* _displayValueLabel;
    cocos2d::ui::Slider* _slider;
};

class UISliderTest_Scale9 : public UIScene
{
public:
    CREATE_FUNC(UISliderTest_Scale9);

    UISliderTest_Scale9();
    ~UISliderTest_Scale9();
    virtual bool init() override;
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UISliderTest_Scale9_State_Change : public UIScene
{
public:
    CREATE_FUNC(UISliderTest_Scale9_State_Change);

    UISliderTest_Scale9_State_Change();
    ~UISliderTest_Scale9_State_Change();
    virtual bool init() override;
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

protected:
    cocos2d::ui::Text* _displayValueLabel;
};


class UISliderNormalDefaultTest : public UIScene
{
public:
    CREATE_FUNC(UISliderNormalDefaultTest);

    UISliderNormalDefaultTest();
    ~UISliderNormalDefaultTest();
    virtual bool init() override;
    
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UISliderDisabledDefaultTest : public UIScene
{
public:
    CREATE_FUNC(UISliderDisabledDefaultTest);

    UISliderDisabledDefaultTest();
    ~UISliderDisabledDefaultTest();
    virtual bool init() override;
    
protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UISliderNewEventCallbackTest : public UIScene
{
public:
    CREATE_FUNC(UISliderNewEventCallbackTest);

    UISliderNewEventCallbackTest();
    ~UISliderNewEventCallbackTest();
    virtual bool init() override;

protected:
    cocos2d::ui::Text* _displayValueLabel;
};

class UISliderIssue12249Test : public UIScene
{
public:
    CREATE_FUNC(UISliderIssue12249Test);
    
    UISliderIssue12249Test();
    ~UISliderIssue12249Test();
    virtual bool init() override;
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    
protected:
    cocos2d::ui::TextBMFont* _displayValueLabel;
};
#endif /* defined(__TestCpp__UISliderTest__) */
