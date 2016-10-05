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

#include "MainScene.h"

USING_NS_CC;

CreatorTests::CreatorTests()
{
    ADD_TEST_CASE(CreatorTest1);
};

//------------------------------------------------------------------
//
// CreatorTest1
//
//------------------------------------------------------------------

CreatorTest1::CreatorTest1()
{
    MainScene_init();
    auto scene = MainScene_create();
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
