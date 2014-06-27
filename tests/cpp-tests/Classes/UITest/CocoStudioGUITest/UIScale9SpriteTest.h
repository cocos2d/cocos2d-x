/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __cocos2d_tests__UIScale9SpriteTest__
#define __cocos2d_tests__UIScale9SpriteTest__
#include "UIScene.h"

class UIScale9SpriteTest : public UIScene
{
public:
    UIScale9SpriteTest();
    ~UIScale9SpriteTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScale9SpriteTest)
};

class UIScale9SpriteHierarchialTest : public UIScene
{
public:
    UIScale9SpriteHierarchialTest();
    ~UIScale9SpriteHierarchialTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScale9SpriteHierarchialTest)
};

class UIScale9SpriteTouchTest : public UIScene
{
public:
    UIScale9SpriteTouchTest();
    ~UIScale9SpriteTouchTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UIScale9SpriteTouchTest)
};


#endif /* defined(__cocos2d_tests__UIScale9SpriteTest__) */
