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
//  Bug-15594.cpp
//  cocos2d_tests
//
//  Created by Ricardo Quesada on 5/24/16.
//
//

// https://github.com/cocos2d/cocos2d-x/pull/15594

#include "Bug-15594.h"


USING_NS_CC;

bool Bug15594Layer::init()
{
    if (BugsTestBase::init())
    {
        auto sprite3d = Sprite3D::create("Images/bugs/bug15594.c3t", "Images/bugs/bug15594.jpg");
        addChild(sprite3d);
        auto size = Director::getInstance()->getWinSize();
        sprite3d->setPosition(size/2);

        auto animation = Animation3D::create("Images/bugs/bug15594.c3t");
        auto animate = Animate3D::create(animation);
        auto repeat = RepeatForever::create(animate);
        sprite3d->runAction(repeat);
        return true;
    }

    return false;
}
