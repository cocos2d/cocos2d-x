/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
CopyRight (c) 2013-2016 Chukong Technologies Inc.
 
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
#include "2d/CCAnimation.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTexture2D.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

AnimationFrame* AnimationFrame::create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo)
{
    auto ret = new (std::nothrow) AnimationFrame();
    if (ret && ret->initWithSpriteFrame(spriteFrame, delayUnits, userInfo))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

AnimationFrame::AnimationFrame()
: _spriteFrame(nullptr)
, _delayUnits(0.0f)
{

}

bool AnimationFrame::initWithSpriteFrame(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo)
{
    setSpriteFrame(spriteFrame);
    setDelayUnits(delayUnits);
    setUserInfo(userInfo);

    return true;
}

AnimationFrame::~AnimationFrame()
{    
    CCLOGINFO( "deallocing AnimationFrame: %p", this);

    CC_SAFE_RELEASE(_spriteFrame);
}

AnimationFrame* AnimationFrame::clone() const
{
    // no copy constructor
    auto frame = new (std::nothrow) AnimationFrame();
    frame->initWithSpriteFrame(_spriteFrame->clone(),
                               _delayUnits,
                               _userInfo);

    frame->autorelease();
    return frame;
}

// implementation of Animation

Animation* Animation::create()
{
    Animation *animation = new (std::nothrow) Animation();
    animation->init();
    animation->autorelease();

    return animation;
} 

Animation* Animation::createWithSpriteFrames(const Vector<SpriteFrame*>& frames, float delay/* = 0.0f*/, unsigned int loops/* = 1*/)
{
    Animation *animation = new (std::nothrow) Animation();
    animation->initWithSpriteFrames(frames, delay, loops);
    animation->autorelease();

    return animation;
}

Animation* Animation::create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops /* = 1 */)
{
    Animation *animation = new (std::nothrow) Animation();
    animation->initWithAnimationFrames(arrayOfAnimationFrameNames, delayPerUnit, loops);
    animation->autorelease();
    return animation;
}

bool Animation::init()
{
    _loops = 1;
    _delayPerUnit = 0.0f;
    
    return true;
}

bool Animation::initWithSpriteFrames(const Vector<SpriteFrame*>& frames, float delay/* = 0.0f*/, unsigned int loops/* = 1*/)
{
    _delayPerUnit = delay;
    _loops = loops;

    for (auto& spriteFrame : frames)
    {
        auto animFrame = AnimationFrame::create(spriteFrame, 1, ValueMap());
        _frames.pushBack(animFrame);
        _totalDelayUnits++;
    }

    return true;
}

bool Animation::initWithAnimationFrames(const Vector<AnimationFrame*>& arrayOfAnimationFrames, float delayPerUnit, unsigned int loops)
{
    _delayPerUnit = delayPerUnit;
    _loops = loops;

    setFrames(arrayOfAnimationFrames);

    for (auto& animFrame : _frames)
    {
        _totalDelayUnits += animFrame->getDelayUnits();
    }
    return true;
}

Animation::Animation()
: _totalDelayUnits(0.0f)
, _delayPerUnit(0.0f)
, _duration(0.0f)
, _restoreOriginalFrame(false)
, _loops(0)
{

}

Animation::~Animation(void)
{
    CCLOGINFO("deallocing Animation: %p", this);
}

void Animation::addSpriteFrame(SpriteFrame* spriteFrame)
{
    AnimationFrame *animFrame = AnimationFrame::create(spriteFrame, 1.0f, ValueMap());
    _frames.pushBack(animFrame);

    // update duration
    _totalDelayUnits++;
}

void Animation::addSpriteFrameWithFile(const std::string& filename)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    SpriteFrame *frame = SpriteFrame::createWithTexture(texture, rect);
    addSpriteFrame(frame);
}

void Animation::addSpriteFrameWithTexture(Texture2D *pobTexture, const Rect& rect)
{
    SpriteFrame *frame = SpriteFrame::createWithTexture(pobTexture, rect);
    addSpriteFrame(frame);
}

float Animation::getDuration(void) const
{
    return _totalDelayUnits * _delayPerUnit;
}

Animation* Animation::clone() const
{
    // no copy constructor    
    auto a = new (std::nothrow) Animation();
    a->initWithAnimationFrames(_frames, _delayPerUnit, _loops);
    a->setRestoreOriginalFrame(_restoreOriginalFrame);
    a->autorelease();
    return a;
}

NS_CC_END
