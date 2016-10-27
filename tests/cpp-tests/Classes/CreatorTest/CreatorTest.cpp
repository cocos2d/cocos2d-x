/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.

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

#include "CreatorTest.h"
#include "../testResource.h"

#include "CreatorTest1.h"
#include "CreatorLabels.h"
#include "CreatorSprites.h"
#include "CreatorUI.h"


USING_NS_CC;

CreatorTests::CreatorTests()
{
    ADD_TEST_CASE(CreatorLabels);
    ADD_TEST_CASE(CreatorSprites);
    ADD_TEST_CASE(CreatorUI);
    ADD_TEST_CASE(CreatorTest1);
};

//------------------------------------------------------------------
//
// CreatorTest1
//
//------------------------------------------------------------------

CreatorTest1::CreatorTest1()
{
    CreatorTest1_init();
    auto scene = CreatorTest1_create();
    addChild(scene);
}

std::string CreatorTest1::title() const
{
    return "Creator Test #1";
}

std::string CreatorTest1::subtitle() const
{
    return "Testing built-in Renderer nodes";
}

//------------------------------------------------------------------
//
// CreatorLabels
//
//------------------------------------------------------------------

CreatorLabels::CreatorLabels()
{
    CreatorLabels_init();
    auto scene = CreatorLabels_create();
    addChild(scene);
}

std::string CreatorLabels::title() const
{
    return "Creator Test #1";
}

std::string CreatorLabels::subtitle() const
{
    return "Testing different labels";
}

//------------------------------------------------------------------
//
// CreatorSprites
//
//------------------------------------------------------------------

CreatorSprites::CreatorSprites()
{
    CreatorSprites_init();
    auto scene = CreatorSprites_create();
    addChild(scene);
}

std::string CreatorSprites::title() const
{
    return "";
}

std::string CreatorSprites::subtitle() const
{
    return "Testing different sprites";
}

//------------------------------------------------------------------
//
// CreatorUI
//
//------------------------------------------------------------------

CreatorUI::CreatorUI()
{
    CreatorUI_init();
    auto scene = CreatorUI_create();
    addChild(scene);
}

std::string CreatorUI::title() const
{
    return "";
}

std::string CreatorUI::subtitle() const
{
    return "Testing different UI components";
}

