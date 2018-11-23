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

#ifndef __BUG_624_H__
#define __BUG_624_H__

#include "BugsTest.h"

class Bug624Layer : public BugsTestBase
{
public:
    virtual ~Bug624Layer();
    virtual bool init() override;
    void switchLayer(float dt);
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);

    virtual std::string title() const override { return "Bug624";}
    CREATE_FUNC(Bug624Layer);
};

class Bug624Layer2 : public BugsTestBase
{
public:
    virtual ~Bug624Layer2();
    virtual bool init() override;
    void switchLayer(float dt);
    virtual std::string title() const override { return "Bug624-2";}

    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);

    CREATE_FUNC(Bug624Layer2);
};

#endif // __BUG_624_H__
