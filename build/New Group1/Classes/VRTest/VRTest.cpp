/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "VRTest.h"

USING_NS_CC;

VRTests::VRTests()
{
    ADD_TEST_CASE(VRTest1);
};

//------------------------------------------------------------------
//
// VRTest1
//
//------------------------------------------------------------------

VRTest1::VRTest1()
{
    auto size = Director::getInstance()->getVisibleSize();

    auto image = Sprite::create("Images/background.png");
    image->setPosition(size/2);
    addChild(image);

    auto button = MenuItemFont::create("Enable / Disable VR", [](Ref* ref){

        auto glview = Director::getInstance()->getOpenGLView();
        auto vrimpl = glview->getVR();
        if (vrimpl)
        {
            glview->setVR(nullptr);
        }
        else
        {
            auto genericvr = new VRGenericRenderer;
            glview->setVR(genericvr);
        }
    });
    button->setFontSizeObj(16);
    auto menu = Menu::create(button, nullptr);
    addChild(menu);

    menu->setPosition(size / 6 );
}

std::string VRTest1::title() const
{
    return "Testing Generic VR";
}

std::string VRTest1::subtitle() const
{
    return "Enable / Disable it with the button";
}



