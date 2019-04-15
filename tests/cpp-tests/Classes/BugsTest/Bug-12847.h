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

#ifndef __cocos2d_tests__Bug_12847__
#define __cocos2d_tests__Bug_12847__

#include "BugsTest.h"

class Bug12847Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug12847Layer);
    
    Bug12847Layer();
    virtual ~Bug12847Layer();

    virtual bool init() override;
    virtual std::string title() const override { return "Bug1287";}
    
protected:
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
private:
    
    cocos2d::Sprite* sprite1;
    cocos2d::Sprite* sprite2;
    cocos2d::Sprite* sprite3;
    cocos2d::Sprite* sprite4;

    cocos2d::Director::Projection _projection = cocos2d::Director::Projection::_3D;
};

#endif /* defined(__cocos2d_tests__Bug_12847__) */
