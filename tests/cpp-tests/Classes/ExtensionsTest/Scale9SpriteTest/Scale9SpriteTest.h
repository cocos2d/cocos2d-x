/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013      Surith Thekkiam

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

#include "testBasic.h"
#include "BaseTest.h"


class S9SpriteTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class S9SpriteTestDemo : public BaseTest
{
public:
    virtual void onEnter() override;
    
	virtual void restartCallback(Ref* sender);
	virtual void nextCallback(Ref* sender);
	virtual void backCallback(Ref* sender);
};
    
// S9BatchNodeBasic

class S9BatchNodeBasic : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9BatchNodeBasic);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheet

class S9FrameNameSpriteSheet : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheet);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetRotated

class S9FrameNameSpriteSheetRotated : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetRotated);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9BatchNodeScaledNoInsets

class S9BatchNodeScaledNoInsets : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9BatchNodeScaledNoInsets);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetScaledNoInsets

class S9FrameNameSpriteSheetScaledNoInsets : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetScaledNoInsets);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetRotatedScaledNoInsets

class S9FrameNameSpriteSheetRotatedScaledNoInsets : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetRotatedScaledNoInsets);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


// S9BatchNodeScaleWithCapInsets

class S9BatchNodeScaleWithCapInsets : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9BatchNodeScaleWithCapInsets);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetInsets

class S9FrameNameSpriteSheetInsets : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetInsets);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetInsetsScaled

class S9FrameNameSpriteSheetInsetsScaled : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetInsetsScaled);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetRotatedInsets

class S9FrameNameSpriteSheetRotatedInsets : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetRotatedInsets);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9_TexturePacker

class S9_TexturePacker : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9_TexturePacker);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class S9FrameNameSpriteSheetRotatedInsetsScaled : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetRotatedInsetsScaled);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class S9FrameNameSpriteSheetRotatedSetCapInsetLater : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9FrameNameSpriteSheetRotatedSetCapInsetLater);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

// S9CascadeOpacityAndColor

class S9CascadeOpacityAndColor : public S9SpriteTestDemo
{
public:
    CREATE_FUNC(S9CascadeOpacityAndColor);

    virtual void onEnter() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};
