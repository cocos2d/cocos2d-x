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
//  Bug-Child.h
//  cocos2d_tests
//
//  Created by NiTe Luo on 5/12/14.
//
//

#ifndef __Bug_Child__
#define __Bug_Child__

#include "BugsTest.h"

class BugChild : public BugsTestBase
{
public:
    CREATE_FUNC(BugChild);

    virtual bool init() override;
    virtual std::string title() const override { return "BugChild";}
    
    void switchChild(cocos2d::Ref* sender);
    
protected:
    
    cocos2d::Sprite* parent1;
    cocos2d::Sprite* parent2;
    
    cocos2d::Sprite* child;
    
    cocos2d::Menu* menu;
};

class BugCameraMask : public BugsTestBase
{
public:
    CREATE_FUNC(BugCameraMask);
    
    virtual bool init() override;
    
    virtual std::string title() const override { return "BugCameraMask";}
    void switchSpriteFlag(cocos2d::Ref* sender);
    void updateSpriteMaskLabel();
    Node* _sprite;
    cocos2d::Label* _spriteMaskLabel;
};

#endif /* defined(__Bug_Child__) */
