/****************************************************************************
 Copyright(c) 2016 cocos2d - x.org
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http ://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files(the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions :
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ui/UITabControl.h"
#include "UITabControlTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITabControlTests::UITabControlTests()
{
    ADD_TEST_CASE(UITabControlTest);
}


UITabControlTest::UITabControlTest()
{
}

UITabControlTest::~UITabControlTest()
{

}

bool UITabControlTest::init()
{

    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        auto displayText = Text::create();
        displayText->setPosition(VisibleRect::bottom() + Vec2(0, 50));
        _uiLayer->addChild(displayText);

        auto tab = TabControl::create();
        tab->setContentSize(Size(200.f, 200.f));
        tab->setHeaderHeight(20.f);
        tab->setHeaderWidth(70.f);
        tab->setHeaderSelectedZoom(.1f);
        tab->setHeaderDockPlace(TabControl::Dock::TOP);

        auto header1 = TabHeader::create();
        header1->setTitleText("background");
        header1->loadTextureBackGround("cocosui/check_box_normal_disable.png");
        auto header2 = TabHeader::create("cross", "cocosui/check_box_normal_disable.png", "cocosui/check_box_active.png");
        auto header3 = TabHeader::create("press&cross", "cocosui/check_box_normal.png",
            "cocosui/check_box_normal_press.png",
            "cocosui/check_box_active.png",
            "cocosui/check_box_normal_disable.png",
            "cocosui/check_box_active_disable.png");

        auto container1 = Layout::create();
        container1->setOpacity(255);
        container1->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        container1->setBackGroundColor(Color3B::GRAY);
        container1->setBackGroundColorOpacity(255);
        auto container2 = Layout::create();
        container2->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        container2->setOpacity(255);
        container2->setBackGroundColor(Color3B::BLUE);
        container2->setBackGroundColorOpacity(255);
        auto container3 = Layout::create();
        container3->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        container3->setOpacity(255);
        container3->setBackGroundColor(Color3B::RED);
        container3->setBackGroundColorOpacity(255);

        tab->insertTab(0, header1, container1);
        tab->insertTab(1, header2, container2);
        tab->insertTab(2, header3, container3);

        tab->setSelectTab(2);
        
        _uiLayer->addChild(tab);
        tab->setPosition(Vec2(widgetSize.width * .5f, widgetSize.height * .5f));

        tab->setTabChangedEventListener(
            [displayText](int index, TabControl::EventType evtType)
        {
            displayText->retain();
            char display[20];
            sprintf(display, "tab %d selected", index);
            displayText->setString(display);
            displayText->release();
        }
            );

        return true;
    }
    return false;
}

