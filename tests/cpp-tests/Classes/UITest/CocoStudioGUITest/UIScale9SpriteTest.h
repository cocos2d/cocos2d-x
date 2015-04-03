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

// S9BatchNodeBasic

class UIS9BatchNodeBasic : public UIScene
{
public:
    CREATE_FUNC(UIS9BatchNodeBasic);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9BatchNodeBasic)
};

// S9FrameNameSpriteSheet

class UIS9FrameNameSpriteSheet : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheet);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheet)

};

// S9FrameNameSpriteSheetRotated

class UIS9FrameNameSpriteSheetRotated : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotated);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetRotated)
};

// S9FrameNameSpriteSheetCropped

class UIS9FrameNameSpriteSheetCropped : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetCropped);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetCropped)
};

// S9FrameNameSpriteSheetCroppedRotated

class UIS9FrameNameSpriteSheetCroppedRotated : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetCroppedRotated);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetCroppedRotated)
};

// S9BatchNodeScaledNoInsets

class UIS9BatchNodeScaledNoInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9BatchNodeScaledNoInsets);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9BatchNodeScaledNoInsets)
};

// S9FrameNameSpriteSheetScaledNoInsets

class UIS9FrameNameSpriteSheetScaledNoInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetScaledNoInsets);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetScaledNoInsets)
};

// S9FrameNameSpriteSheetRotatedScaledNoInsets

class UIS9FrameNameSpriteSheetRotatedScaledNoInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedScaledNoInsets);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedScaledNoInsets)
};


// S9BatchNodeScaleWithCapInsets

class UIS9BatchNodeScaleWithCapInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9BatchNodeScaleWithCapInsets);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9BatchNodeScaleWithCapInsets)
};

// S9FrameNameSpriteSheetInsets

class UIS9FrameNameSpriteSheetInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetInsets);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetInsets)
};

// S9FrameNameSpriteSheetInsetsScaled

class UIS9FrameNameSpriteSheetInsetsScaled : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetInsetsScaled);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetInsetsScaled)
};

// S9FrameNameSpriteSheetRotatedInsets

class UIS9FrameNameSpriteSheetRotatedInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedInsets);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedInsets)
};

// S9_TexturePacker

class UIS9_TexturePacker : public UIScene
{
public:
    CREATE_FUNC(UIS9_TexturePacker);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9_TexturePacker)

};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class UIS9FrameNameSpriteSheetRotatedInsetsScaled : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedInsetsScaled);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedInsetsScaled)
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class UIS9FrameNameSpriteSheetRotatedSetCapInsetLater : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedSetCapInsetLater);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedSetCapInsetLater)
};

// S9CascadeOpacityAndColor

class UIS9CascadeOpacityAndColor : public UIScene
{
public:
    CREATE_FUNC(UIS9CascadeOpacityAndColor);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9CascadeOpacityAndColor)
};

// Scale9Sprite ZOrder

class UIS9ZOrder : public UIScene
{
public:
    CREATE_FUNC(UIS9ZOrder);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9ZOrder)

};

// Scale9Sprite Flip

class UIS9Flip : public UIScene
{
public:
    CREATE_FUNC(UIS9Flip);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9Flip)
};

class UIS9ChangeAnchorPoint : public UIScene
{
public:
    CREATE_FUNC(UIS9ChangeAnchorPoint);
    
    bool init();
protected:
    UI_SCENE_CREATE_FUNC(UIS9ChangeAnchorPoint)
};

#endif /* defined(__cocos2d_tests__UIScale9SpriteTest__) */
