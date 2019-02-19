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
// Bug-886
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=886
//

#include "Bug-886.h"

USING_NS_CC;

bool Bug886Layer::init()
{
    if(BugsTestBase::init())
    {
        // ask director the the window size
        //        auto size = [[Director sharedDirector] winSize];
        
        auto sprite = Sprite::create("Images/bugs/bug886.jpg");
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(Vec2::ZERO);
        sprite->setScaleX(0.6f);
        addChild(sprite);

        auto sprite2 = Sprite::create("Images/bugs/bug886.png");
        sprite2->setAnchorPoint(Vec2::ZERO);
        sprite2->setScaleX(0.6f);
        sprite2->setPosition(sprite->getContentSize().width * 0.6f + 10, 0);
        addChild(sprite2);

        return true;
    }

    return false;
}
