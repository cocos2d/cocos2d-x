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
    virtual void onEnter();
    
	virtual void restartCallback(Object* sender);
	virtual void nextCallback(Object* sender);
	virtual void backCallback(Object* sender);
};
    
// S9BatchNodeBasic

class S9BatchNodeBasic : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheet

class S9FrameNameSpriteSheet : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetRotated

class S9FrameNameSpriteSheetRotated : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9BatchNodeScaledNoInsets

class S9BatchNodeScaledNoInsets : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetScaledNoInsets

class S9FrameNameSpriteSheetScaledNoInsets : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetRotatedScaledNoInsets

class S9FrameNameSpriteSheetRotatedScaledNoInsets : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};


// S9BatchNodeScaleWithCapInsets

class S9BatchNodeScaleWithCapInsets : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetInsets

class S9FrameNameSpriteSheetInsets : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetInsetsScaled

class S9FrameNameSpriteSheetInsetsScaled : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetRotatedInsets

class S9FrameNameSpriteSheetRotatedInsets : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9_TexturePacker

class S9_TexturePacker : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class S9FrameNameSpriteSheetRotatedInsetsScaled : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9FrameNameSpriteSheetRotatedInsetsScaled

class S9FrameNameSpriteSheetRotatedSetCapInsetLater : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};

// S9CascadeOpacityAndColor

class S9CascadeOpacityAndColor : public S9SpriteTestDemo
{
public:
    virtual void onEnter();
    
    virtual std::string title();
    virtual std::string subtitle();
};