/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "CCAnimation.h"
#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "CCSpriteFrame.h"
#include "CCDirector.h"

NS_CC_BEGIN

AnimationFrame* AnimationFrame::create(SpriteFrame* spriteFrame, float delayUnits, const ValueMap& userInfo)
{
    auto ret = new AnimationFrame();
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
: _spriteFrame(NULL)
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
	auto frame = new AnimationFrame();
    frame->initWithSpriteFrame(_spriteFrame->clone(),
							   _delayUnits,
							   _userInfo);

	frame->autorelease();
	return frame;
}

// implementation of Animation

Animation* Animation::create(void)
{
    Animation *pAnimation = new Animation();
    pAnimation->init();
    pAnimation->autorelease();

    return pAnimation;
} 

Animation* Animation::createWithSpriteFrames(const Vector<SpriteFrame*>& frames, float delay/* = 0.0f*/)
{
    Animation *pAnimation = new Animation();
    pAnimation->initWithSpriteFrames(frames, delay);
    pAnimation->autorelease();

    return pAnimation;
}

Animation* Animation::create(const Vector<AnimationFrame*>& arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops /* = 1 */)
{
    Animation *pAnimation = new Animation();
    pAnimation->initWithAnimationFrames(arrayOfAnimationFrameNames, delayPerUnit, loops);
    pAnimation->autorelease();
    return pAnimation;
}

bool Animation::init()
{
    _loops = 1;
    _delayPerUnit = 0.0f;
    
    return true;
}

bool Animation::initWithSpriteFrames(const Vector<SpriteFrame*>& frames, float delay/* = 0.0f*/)
{
    _loops = 1;
    _delayPerUnit = delay;

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
    SpriteFrame *pFrame = SpriteFrame::createWithTexture(texture, rect);
    addSpriteFrame(pFrame);
}

void Animation::addSpriteFrameWithTexture(Texture2D *pobTexture, const Rect& rect)
{
    SpriteFrame *pFrame = SpriteFrame::createWithTexture(pobTexture, rect);
    addSpriteFrame(pFrame);
}

float Animation::getDuration(void) const
{
    return _totalDelayUnits * _delayPerUnit;
}

Animation* Animation::clone() const
{
	// no copy constructor	
	auto a = new Animation();
    a->initWithAnimationFrames(_frames, _delayPerUnit, _loops);
    a->setRestoreOriginalFrame(_restoreOriginalFrame);
	a->autorelease();
	return a;
}

NS_CC_END