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

#include "UILayoutTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UILayoutTests::UILayoutTests()
{
    ADD_TEST_CASE(UILayoutTest);
    ADD_TEST_CASE(UILayoutTest_Color);
    ADD_TEST_CASE(UILayoutTest_Gradient);
    ADD_TEST_CASE(UILayoutTest_BackGroundImage);
    ADD_TEST_CASE(UILayoutTest_BackGroundImage_Scale9);
    ADD_TEST_CASE(UILayoutTest_Layout_Linear_Vertical);
    ADD_TEST_CASE(UILayoutTest_Layout_Linear_Horizontal);
    ADD_TEST_CASE(UILayoutTest_Layout_Relative_Align_Parent);
    ADD_TEST_CASE(UILayoutTest_Layout_Relative_Location);
    ADD_TEST_CASE(UILayoutTest_Layout_Scaled_Widget);
    ADD_TEST_CASE(UILayoutComponentTest);
    ADD_TEST_CASE(UILayoutComponent_Berth_Test);
    ADD_TEST_CASE(UILayoutComponent_Berth_Stretch_Test);
}

// UILayoutTest

UILayoutTest::UILayoutTest()
{
}

UILayoutTest::~UILayoutTest()
{
}

bool UILayoutTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout", "fonts/Marker Felt.ttf", 30 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81)) ;
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                                  layout->getContentSize().height - button->getContentSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(layout->getContentSize().width - button_scale9->getContentSize().width / 2.0f,
                                         button_scale9->getContentSize().height / 2.0f));
        
        layout->addChild(button_scale9);
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Color

UILayoutTest_Color::UILayoutTest_Color()
{
}

UILayoutTest_Color::~UILayoutTest_Color()
{
}

bool UILayoutTest_Color::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout color render", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with color render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B(128, 128, 128));
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                                  layout->getContentSize().height - button->getContentSize().height / 2.0f));
        
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(layout->getContentSize().width - button_scale9->getContentSize().width / 2.0f,
                                         button_scale9->getContentSize().height / 2.0f));
        
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UILayoutTest_Gradient

UILayoutTest_Gradient::UILayoutTest_Gradient()
{    
}

UILayoutTest_Gradient::~UILayoutTest_Gradient()
{
}

bool UILayoutTest_Gradient::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout gradient render", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with gradient render
        Layout* layout = Layout::create();
        layout->setBackGroundColorType(Layout::BackGroundColorType::GRADIENT);
        layout->setBackGroundColor(Color3B(64, 64, 64), Color3B(192, 192, 192));
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                                  layout->getContentSize().height - button->getContentSize().height / 2.0f));
        
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(layout->getContentSize().width - button_scale9->getContentSize().width / 2.0f,
                                         button_scale9->getContentSize().height / 2.0f));
        
        layout->addChild(button_scale9);        
        
        return true;
    }
    return false;
}

// UILayoutTest_BackGroundImage

UILayoutTest_BackGroundImage::UILayoutTest_BackGroundImage()
{
}

UILayoutTest_BackGroundImage::~UILayoutTest_BackGroundImage()
{
}

bool UILayoutTest_BackGroundImage::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout background image", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setClippingEnabled(true);
        layout->setBackGroundImage("cocosui/Hello.png");
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                                  layout->getContentSize().height - button->getContentSize().height / 2.0f));
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(layout->getContentSize().width - button_scale9->getContentSize().width / 2.0f,
                                         button_scale9->getContentSize().height / 2.0f));
        
        layout->addChild(button_scale9);        

        _layout = layout;

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UILayoutTest_BackGroundImage::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0, 0));
        this->addChild(pMenu1, 10);
        
        return true;
    }
    return false;
}

void UILayoutTest_BackGroundImage::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData textureFile = _layout->getRenderFile();
    CCLOG("textureFile  Name : %s, Type: %d", textureFile.file.c_str(), textureFile.type);
}

// UILayoutTest_BackGroundImage_Scale9

UILayoutTest_BackGroundImage_Scale9::UILayoutTest_BackGroundImage_Scale9()
{
}

UILayoutTest_BackGroundImage_Scale9::~UILayoutTest_BackGroundImage_Scale9()
{
}

bool UILayoutTest_BackGroundImage_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout background image scale9", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout with background image
        Layout* layout = Layout::create();
        layout->setBackGroundImageScale9Enabled(true);
        layout->setBackGroundImage("cocosui/green_edit.png");
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                                  layout->getContentSize().height - button->getContentSize().height / 2.0f));
        
        layout->addChild(button);
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        titleButton->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
        layout->addChild(titleButton);
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        button_scale9->setPosition(Vec2(layout->getContentSize().width - button_scale9->getContentSize().width / 2.0f,
                                         button_scale9->getContentSize().height / 2.0f));
        layout->addChild(button_scale9);
        
        return true;
    }
    return false;
}

// UILayoutTest_Layout_Linear_Vertical

UILayoutTest_Layout_Linear_Vertical::UILayoutTest_Layout_Linear_Vertical()
{
}

UILayoutTest_Layout_Linear_Vertical::~UILayoutTest_Layout_Linear_Vertical()
{
}

bool UILayoutTest_Layout_Linear_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout Linear Vertical", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(Layout::Type::VERTICAL);
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
        lp1->setMargin(Margin(0.0f, 5.0f, 0.0f, 10.0f));
        
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
        lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
        lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Linear_Horizontal

UILayoutTest_Layout_Linear_Horizontal::UILayoutTest_Layout_Linear_Horizontal()
{
}

UILayoutTest_Layout_Linear_Horizontal::~UILayoutTest_Layout_Linear_Horizontal()
{
}

bool UILayoutTest_Layout_Linear_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout Linear Horizontal", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(Layout::Type::HORIZONTAL);
        layout->setClippingEnabled(true);
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                  (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                  (widgetSize.height - backgroundSize.height) / 2.0f +
                                  (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        layout->addChild(button);
        
        LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
        button->setLayoutParameter(lp1);
        lp1->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        lp1->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* titleButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        titleButton->setTitleText("Title Button");
        layout->addChild(titleButton);
        
        LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
        titleButton->setLayoutParameter(lp2);
        lp2->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        Button* button_scale9 = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
        button_scale9->setScale9Enabled(true);
        button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
        layout->addChild(button_scale9);
        
        LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
        button_scale9->setLayoutParameter(lp3);
        lp3->setGravity(LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
        
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Relative_Align_Parent

UILayoutTest_Layout_Relative_Align_Parent::UILayoutTest_Layout_Relative_Align_Parent()
{
}

UILayoutTest_Layout_Relative_Align_Parent::~UILayoutTest_Layout_Relative_Align_Parent()
{
}

bool UILayoutTest_Layout_Relative_Align_Parent::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout Relative Align Parent", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(Layout::Type::RELATIVE);
        layout->setContentSize(Size(280, 150));
        layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B::GREEN);
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        // top left
        Button* button_TopLeft = Button::create("cocosui/animationbuttonnormal.png",
                                                "cocosui/animationbuttonpressed.png");
        layout->addChild(button_TopLeft);
        
        RelativeLayoutParameter* rp_TopLeft = RelativeLayoutParameter::create();
        rp_TopLeft->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
        button_TopLeft->setLayoutParameter(rp_TopLeft);
        
        
        // top center horizontal
        Button* button_TopCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                  "cocosui/animationbuttonpressed.png");
        layout->addChild(button_TopCenter);
        
        RelativeLayoutParameter* rp_TopCenter = RelativeLayoutParameter::create();
        rp_TopCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        button_TopCenter->setLayoutParameter(rp_TopCenter);
        
        
        // top right
        Button* button_TopRight = Button::create("cocosui/animationbuttonnormal.png",
                                                 "cocosui/animationbuttonpressed.png");
        layout->addChild(button_TopRight);
        
        RelativeLayoutParameter* rp_TopRight = RelativeLayoutParameter::create();
        rp_TopRight->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
        button_TopRight->setLayoutParameter(rp_TopRight);
        
        
        // left center
        Button* button_LeftCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                   "cocosui/animationbuttonpressed.png");
        layout->addChild(button_LeftCenter);
        
        RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
        rp_LeftCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        button_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        // center
        Button* buttonCenter = Button::create("cocosui/animationbuttonnormal.png",
                                              "cocosui/animationbuttonpressed.png");
        layout->addChild(buttonCenter);
        
        RelativeLayoutParameter* rpCenter = RelativeLayoutParameter::create();
        rpCenter->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
        buttonCenter->setLayoutParameter(rpCenter);
        
        
        // right center
        Button* button_RightCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                    "cocosui/animationbuttonpressed.png");
        layout->addChild(button_RightCenter);
        
        RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
        rp_RightCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        button_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
        // left bottom
        Button* button_LeftBottom = Button::create("cocosui/animationbuttonnormal.png",
                                                   "cocosui/animationbuttonpressed.png");
        layout->addChild(button_LeftBottom);
        
        RelativeLayoutParameter* rp_LeftBottom = RelativeLayoutParameter::create();
        rp_LeftBottom->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM);
        button_LeftBottom->setLayoutParameter(rp_LeftBottom);
        
        
        // bottom center
        Button* button_BottomCenter = Button::create("cocosui/animationbuttonnormal.png",
                                                     "cocosui/animationbuttonpressed.png");
        layout->addChild(button_BottomCenter);
        
        RelativeLayoutParameter* rp_BottomCenter = RelativeLayoutParameter::create();
        rp_BottomCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        button_BottomCenter->setLayoutParameter(rp_BottomCenter);
        
        
        // right bottom
        Button* button_RightBottom = Button::create("cocosui/animationbuttonnormal.png",
                                                    "cocosui/animationbuttonpressed.png");
        layout->addChild(button_RightBottom);
        
        RelativeLayoutParameter* rp_RightBottom = RelativeLayoutParameter::create();
        rp_RightBottom->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM);
        button_RightBottom->setLayoutParameter(rp_RightBottom);
        
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Relative_Location

UILayoutTest_Layout_Relative_Location::UILayoutTest_Layout_Relative_Location()
{
}

UILayoutTest_Layout_Relative_Location::~UILayoutTest_Layout_Relative_Location()
{
}

bool UILayoutTest_Layout_Relative_Location::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout Relative Location", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(Layout::Type::RELATIVE);
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                (widgetSize.height - backgroundSize.height) / 2.0f +
                                (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        // center
        ImageView* imageView_Center = ImageView::create("cocosui/scrollviewbg.png");
        layout->addChild(imageView_Center);
        
        RelativeLayoutParameter* rp_Center = RelativeLayoutParameter::create();
        rp_Center->setRelativeName("rp_Center");
        rp_Center->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
        imageView_Center->setLayoutParameter(rp_Center);
        
        
        // above center
        ImageView* imageView_AboveCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_AboveCenter);
        
        RelativeLayoutParameter* rp_AboveCenter = RelativeLayoutParameter::create();
        rp_AboveCenter->setRelativeToWidgetName("rp_Center");
        rp_AboveCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_CENTER);
        imageView_AboveCenter->setLayoutParameter(rp_AboveCenter);
        
        
        // below center
        ImageView* imageView_BelowCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_BelowCenter);
        
        RelativeLayoutParameter* rp_BelowCenter = RelativeLayoutParameter::create();
        rp_BelowCenter->setRelativeToWidgetName("rp_Center");
        rp_BelowCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER);
        imageView_BelowCenter->setLayoutParameter(rp_BelowCenter);
        
        
        // left center
        ImageView* imageView_LeftCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_LeftCenter);
        
        RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
        rp_LeftCenter->setRelativeToWidgetName("rp_Center");
        rp_LeftCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_CENTER);
        imageView_LeftCenter->setLayoutParameter(rp_LeftCenter);
        
        
        
        // right center
        ImageView* imageView_RightCenter = ImageView::create("cocosui/switch-mask.png");
        layout->addChild(imageView_RightCenter);
        
        RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
        rp_RightCenter->setRelativeToWidgetName("rp_Center");
        rp_RightCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER);
        imageView_RightCenter->setLayoutParameter(rp_RightCenter);
        
        
        return true;
    }
    
    return false;
}

// UILayoutTest_Layout_Relative_Location

UILayoutTest_Layout_Scaled_Widget::UILayoutTest_Layout_Scaled_Widget()
{
}

UILayoutTest_Layout_Scaled_Widget::~UILayoutTest_Layout_Scaled_Widget()
{
}

bool UILayoutTest_Layout_Scaled_Widget::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add the alert
        Text* alert = Text::create("Layout Scaled Widget", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 4.5f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        
        // Create the layout
        Layout* layout = Layout::create();
        layout->setLayoutType(Layout::Type::HORIZONTAL);
        layout->setContentSize(Size(280, 150));
        Size backgroundSize = background->getContentSize();
        layout->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                 (backgroundSize.width - layout->getContentSize().width) / 2.0f,
                                 (widgetSize.height - backgroundSize.height) / 2.0f +
                                 (backgroundSize.height - layout->getContentSize().height) / 2.0f));
        _uiLayer->addChild(layout);
        
        ImageView* imageView_Center1 = ImageView::create("cocosui/scrollviewbg.png");
        imageView_Center1->setScale(0.5);
        layout->addChild(imageView_Center1);
        
        ImageView* imageView_Center2 = ImageView::create("cocosui/scrollviewbg.png");
        imageView_Center2->setScale(1.2);
        layout->addChild(imageView_Center2);
        
        ImageView* imageView_Center3 = ImageView::create("cocosui/scrollviewbg.png");
        imageView_Center3->setScale(0.8);
        layout->addChild(imageView_Center3);
        
        return true;
    }
    
    return false;
}


bool UILayoutComponentTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        _baseLayer = LayerColor::create();
        _baseLayer->setColor(Color3B(50, 100, 0));
        _baseLayer->setOpacity(100);
        _baseLayer->setContentSize(Size(200, 200));
        _uiLayer->addChild(_baseLayer);

        Button* button = Button::create("cocosui/animationbuttonnormal.png");
        CCLOG("content size should be greater than 0:  width = %f, height = %f", button->getContentSize().width,
            button->getContentSize().height);
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(CC_CALLBACK_2(UILayoutComponentTest::touchEvent, this));
        button->setZoomScale(0.4f);
        button->setPressedActionEnabled(true);
        _uiLayer->addChild(button);

        return true;
    }
    return false;
}

void UILayoutComponentTest::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        break;

    case Widget::TouchEventType::MOVED:
        break;

    case Widget::TouchEventType::ENDED:
        {
            Size widgetSize = _widget->getContentSize();
            Size layerSize = _baseLayer->getContentSize();
            if (layerSize.width == widgetSize.width && layerSize.height == widgetSize.height)
                _baseLayer->setContentSize(Size(200, 200));
            else
                _baseLayer->setContentSize(widgetSize);
            Helper::doLayout(_baseLayer);
         }
        break;

    case Widget::TouchEventType::CANCELED:
        break;

    default:
        break;
    }
}

bool UILayoutComponent_Berth_Test::init()
{
    if (UILayoutComponentTest::init())
    {
        Sprite* leftTopSprite = Sprite::create("cocosui/CloseSelected.png");
        LayoutComponent* leftTop = LayoutComponent::bindLayoutComponent(leftTopSprite);
        leftTop->setHorizontalEdge(LayoutComponent::HorizontalEdge::Left);
        leftTop->setVerticalEdge(LayoutComponent::VerticalEdge::Top);
        _baseLayer->addChild(leftTopSprite);

        Sprite* leftBottomSprite = Sprite::create("cocosui/CloseSelected.png");
        LayoutComponent* leftBottom = LayoutComponent::bindLayoutComponent(leftBottomSprite);
        leftBottom->setHorizontalEdge(LayoutComponent::HorizontalEdge::Left);
        leftBottom->setVerticalEdge(LayoutComponent::VerticalEdge::Bottom);
        _baseLayer->addChild(leftBottomSprite);

        Sprite* rightTopSprite = Sprite::create("cocosui/CloseSelected.png");
        LayoutComponent* rightTop = LayoutComponent::bindLayoutComponent(rightTopSprite);
        rightTop->setHorizontalEdge(LayoutComponent::HorizontalEdge::Right);
        rightTop->setVerticalEdge(LayoutComponent::VerticalEdge::Top);
        _baseLayer->addChild(rightTopSprite);

        Sprite* rightBottomSprite = Sprite::create("cocosui/CloseSelected.png");
        LayoutComponent* rightBottom = LayoutComponent::bindLayoutComponent(rightBottomSprite);
        rightBottom->setHorizontalEdge(LayoutComponent::HorizontalEdge::Right);
        rightBottom->setVerticalEdge(LayoutComponent::VerticalEdge::Bottom);
        _baseLayer->addChild(rightBottomSprite);

        ui::Helper::doLayout(_baseLayer);

        return true;
    }
    return false;
}

bool UILayoutComponent_Berth_Stretch_Test::init()
{
    if (UILayoutComponentTest::init())
    {
        ImageView* leftTopSprite = ImageView::create("cocosui/CloseSelected.png");
        leftTopSprite->ignoreContentAdaptWithSize(false);
        LayoutComponent* leftTop = LayoutComponent::bindLayoutComponent(leftTopSprite);
        leftTop->setHorizontalEdge(LayoutComponent::HorizontalEdge::Left);
        leftTop->setVerticalEdge(LayoutComponent::VerticalEdge::Top);
        leftTop->setStretchWidthEnabled(true);
        leftTop->setStretchHeightEnabled(true);
        _baseLayer->addChild(leftTopSprite);
        leftTop->setSize(leftTopSprite->getContentSize());
        leftTop->setLeftMargin(0);
        leftTop->setTopMargin(0);

        ImageView* leftBottomSprite = ImageView::create("cocosui/CloseSelected.png");
        leftBottomSprite->ignoreContentAdaptWithSize(false);
        LayoutComponent* leftBottom = LayoutComponent::bindLayoutComponent(leftBottomSprite);
        leftBottom->setHorizontalEdge(LayoutComponent::HorizontalEdge::Left);
        leftBottom->setVerticalEdge(LayoutComponent::VerticalEdge::Bottom);
        leftBottom->setStretchWidthEnabled(true);
        leftBottom->setStretchHeightEnabled(true);
        _baseLayer->addChild(leftBottomSprite);
        leftBottom->setSize(leftBottomSprite->getContentSize());
        leftBottom->setLeftMargin(0);
        leftBottom->setBottomMargin(0);

        ImageView* rightTopSprite = ImageView::create("cocosui/CloseSelected.png");
        rightTopSprite->ignoreContentAdaptWithSize(false);
        LayoutComponent* rightTop = LayoutComponent::bindLayoutComponent(rightTopSprite);
        rightTop->setHorizontalEdge(LayoutComponent::HorizontalEdge::Right);
        rightTop->setVerticalEdge(LayoutComponent::VerticalEdge::Top);
        rightTop->setStretchWidthEnabled(true);
        rightTop->setStretchHeightEnabled(true);
        _baseLayer->addChild(rightTopSprite);
        rightTop->setSize(rightTopSprite->getContentSize());
        rightTop->setTopMargin(0);
        rightTop->setRightMargin(0);

        ImageView* rightBottomSprite = ImageView::create("cocosui/CloseSelected.png");
        rightBottomSprite->ignoreContentAdaptWithSize(false);
        LayoutComponent* rightBottom = LayoutComponent::bindLayoutComponent(rightBottomSprite);
        rightBottom->setHorizontalEdge(LayoutComponent::HorizontalEdge::Right);
        rightBottom->setVerticalEdge(LayoutComponent::VerticalEdge::Bottom);
        rightBottom->setStretchWidthEnabled(true);
        rightBottom->setStretchHeightEnabled(true);
        _baseLayer->addChild(rightBottomSprite);
        rightBottom->setSize(rightBottomSprite->getContentSize());
        rightBottom->setBottomMargin(0);
        rightBottom->setRightMargin(0);

        ui::Helper::doLayout(_baseLayer);

        return true;
    }
    return false;
}
