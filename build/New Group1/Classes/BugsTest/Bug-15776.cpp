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

//
//  Bug-15776.cpp
//  cocos2d_tests
//
//  Created by Ricardo Quesada on 6/17/16.
//
//

#include "Bug-15776.h"


USING_NS_CC;


//
// IMPORTANT:
// THIS TEST WILL CRASH ON TextureCache::addImage()
// THIS IS NOT A BUG
// It is expected to crash there
//
bool Bug15776Layer::init()
{
    if (BugsTestBase::init())
    {
        cocos2d::Image *cocos2dxImage = new cocos2d::Image();
        cocos2dxImage->initWithImageData(nullptr, 0);
        // should not crash. invalid cocos2dImage
        auto texture2d = Director::getInstance()->getTextureCache()->addImage(cocos2dxImage, "unused");
        return texture2d;
    }

    return false;
}

std::string Bug15776Layer::title() const
{
    return "Testing Issue #15776";
}

std::string Bug15776Layer::subtitle() const
{
    return "It should crash on TextureCache::addImage()";
}
