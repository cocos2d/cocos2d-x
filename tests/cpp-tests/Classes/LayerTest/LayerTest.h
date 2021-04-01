/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#ifndef _LAYER_TEST_H_
#define _LAYER_TEST_H_

#include "../BaseTest.h"
#include "cocos/ui/UISlider.h"
#include "../cocos/ui/UIListView.h"

DEFINE_TEST_SUITE(LayerTests);

class LayerTest : public TestCase
{
public:
    virtual std::string title() const override;
protected:
    std::string    _title;
};

class LayerTestCascadingOpacityA : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingOpacityA);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingOpacityB : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingOpacityB);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingOpacityC : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingOpacityC);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingColorA : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingColorA);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingColorB : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingColorB);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class LayerTestCascadingColorC : public LayerTest
{
public:
    CREATE_FUNC(LayerTestCascadingColorC);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


class LayerTest1 : public LayerTest
{
public:
    CREATE_FUNC(LayerTest1);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;

    void updateSize(cocos2d::Vec2 &touchLocation);

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

class LayerTest2 : public LayerTest
{
public:
    CREATE_FUNC(LayerTest2);
    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};


class LayerTestBlend : public LayerTest
{
public:
    CREATE_FUNC(LayerTestBlend);

    LayerTestBlend();
    void newBlend(float dt);
    virtual std::string subtitle() const override;
};

class LayerGradientTest : public LayerTest
{
public:
    CREATE_FUNC(LayerGradientTest);
    LayerGradientTest();
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void toggleItem(cocos2d::Ref *sender);
};

class LayerGradientTest2 : public LayerTest
{
public:
    CREATE_FUNC(LayerGradientTest2);
    LayerGradientTest2();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerIgnoreAnchorPointPos : public LayerTest
{
public:
    CREATE_FUNC(LayerIgnoreAnchorPointPos);
    virtual void onEnter() override;
    void onToggle(cocos2d::Ref* pObject);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerIgnoreAnchorPointRot : public LayerTest
{
public:
    CREATE_FUNC(LayerIgnoreAnchorPointRot);
    virtual void onEnter() override;
    void onToggle(cocos2d::Ref* pObject);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerIgnoreAnchorPointScale : public LayerTest
{
public:
    CREATE_FUNC(LayerIgnoreAnchorPointScale);
    virtual void onEnter() override;
    void onToggle(cocos2d::Ref* pObject);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerExtendedBlendOpacityTest : public LayerTest
{
public:
    CREATE_FUNC(LayerExtendedBlendOpacityTest);
    LayerExtendedBlendOpacityTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class LayerBug3162A : public LayerTest
{
public:
    CREATE_FUNC(LayerBug3162A);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void step(float dt);
    
private:
    cocos2d::LayerColor* _layer[3];
};

class LayerBug3162B : public LayerTest
{
public:
    CREATE_FUNC(LayerBug3162B);
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void step(float dt);
    
private:
    cocos2d::LayerColor* _layer[3];
};

class LayerColorOccludeBug : public LayerTest
{
public:
    CREATE_FUNC(LayerColorOccludeBug);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    cocos2d::LayerColor* _layer;
};

class LayerRadialGradientTest : public LayerTest
{
public:
    CREATE_FUNC(LayerRadialGradientTest);
    virtual void onEnter() override;
    virtual std::string title() const override;
    
    void sliderCallback(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    void listviewCallback(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
private:
    cocos2d::ui::Slider* createSlider();
    cocos2d::ui::ListView* createListView();
    
    cocos2d::LayerRadialGradient* _layer;
    int _currentSeletedItemIndex;
};


#endif
