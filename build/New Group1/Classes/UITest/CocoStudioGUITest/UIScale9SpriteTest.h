/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef __cocos2d_tests__UIScale9SpriteTest__
#define __cocos2d_tests__UIScale9SpriteTest__
#include "UIScene.h"

DEFINE_TEST_SUITE(UIScale9SpriteTests);

class UIScale9SpriteTest : public UIScene
{
public:
    CREATE_FUNC(UIScale9SpriteTest);

    UIScale9SpriteTest();
    ~UIScale9SpriteTest();

    virtual bool init() override;
};

class UIScale9SpriteHierarchialTest : public UIScene
{
public:
    CREATE_FUNC(UIScale9SpriteHierarchialTest);

    UIScale9SpriteHierarchialTest();
    ~UIScale9SpriteHierarchialTest();

    virtual bool init() override;
};

class UIScale9SpriteTouchTest : public UIScene
{
public:
    CREATE_FUNC(UIScale9SpriteTouchTest);

    UIScale9SpriteTouchTest();
    ~UIScale9SpriteTouchTest();

    virtual bool init() override;
};

// S9BatchNodeBasic

class UIS9BatchNodeBasic : public UIScene
{
public:
    CREATE_FUNC(UIS9BatchNodeBasic);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheet

class UIS9FrameNameSpriteSheet : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheet);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetRotated

class UIS9FrameNameSpriteSheetRotated : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotated);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetCroppedSimple

class UIS9FrameNameSpriteSheetCroppedSimple : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetCroppedSimple);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetCroppedRotatedSimple

class UIS9FrameNameSpriteSheetCroppedRotatedSimple : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetCroppedRotatedSimple);
    
    virtual bool init() override;
};


// S9FrameNameSpriteSheetCropped

class UIS9FrameNameSpriteSheetCropped : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetCropped);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetCroppedRotated

class UIS9FrameNameSpriteSheetCroppedRotated : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetCroppedRotated);
    
    virtual bool init() override;
};

// S9BatchNodeScaledNoInsets

class UIS9BatchNodeScaledNoInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9BatchNodeScaledNoInsets);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetScaledNoInsets

class UIS9FrameNameSpriteSheetScaledNoInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetScaledNoInsets);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetRotatedScaledNoInsets

class UIS9FrameNameSpriteSheetRotatedScaledNoInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedScaledNoInsets);
    
    virtual bool init() override;
};


// S9BatchNodeScaleWithCapInsets

class UIS9BatchNodeScaleWithCapInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9BatchNodeScaleWithCapInsets);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetInsets

class UIS9FrameNameSpriteSheetInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetInsets);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetInsetsScaled

class UIS9FrameNameSpriteSheetInsetsScaled : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetInsetsScaled);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetRotatedInsets

class UIS9FrameNameSpriteSheetRotatedInsets : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedInsets);
    
    virtual bool init() override;
};

// S9_TexturePacker

class UIS9_TexturePacker : public UIScene
{
public:
    CREATE_FUNC(UIS9_TexturePacker);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class UIS9FrameNameSpriteSheetRotatedInsetsScaled : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedInsetsScaled);
    
    virtual bool init() override;
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class UIS9FrameNameSpriteSheetRotatedSetCapInsetLater : public UIScene
{
public:
    CREATE_FUNC(UIS9FrameNameSpriteSheetRotatedSetCapInsetLater);
    
    virtual bool init() override;
};

// S9CascadeOpacityAndColor

class UIS9CascadeOpacityAndColor : public UIScene
{
public:
    CREATE_FUNC(UIS9CascadeOpacityAndColor);
    
    virtual bool init() override;
};

// Scale9Sprite ZOrder

class UIS9ZOrder : public UIScene
{
public:
    CREATE_FUNC(UIS9ZOrder);
    
    virtual bool init() override;
};

// Scale9Sprite Flip

class UIS9Flip : public UIScene
{
public:
    CREATE_FUNC(UIS9Flip);
    
    virtual bool init() override;
};

class UIS9ChangeAnchorPoint : public UIScene
{
public:
    CREATE_FUNC(UIS9ChangeAnchorPoint);
    
    virtual bool init() override;
};

class UIS9NinePatchTest : public UIScene
{
public:
    CREATE_FUNC(UIS9NinePatchTest);

    virtual bool init() override;
};

class UIS9BatchTest: public UIScene
{
public:
    CREATE_FUNC(UIS9BatchTest);
    
    virtual bool init() override;
};

class UIS9ToggleRenderingTypeTest: public UIScene
{
public:
    CREATE_FUNC(UIS9ToggleRenderingTypeTest);
    
    virtual bool init() override;
};

class UIS9GlobalZOrderTest: public UIScene
{
public:
    CREATE_FUNC(UIS9GlobalZOrderTest);
    
    virtual bool init() override;
};

class UIS9EnableScale9FalseTest: public UIScene
{
public:
    CREATE_FUNC(UIS9EnableScale9FalseTest);
    
    virtual bool init() override;
};

class UIS9GrayStateOpacityTest: public UIScene
{
public:
    CREATE_FUNC(UIS9GrayStateOpacityTest);
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

    virtual bool init() override;
};

#endif /* defined(__cocos2d_tests__UIScale9SpriteTest__) */
