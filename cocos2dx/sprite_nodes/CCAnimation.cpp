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
#include "textures/CCTextureCache.h"
#include "textures/CCTexture2D.h"
#include "ccMacros.h"
#include "sprite_nodes/CCSpriteFrame.h"

NS_CC_BEGIN

AnimationFrame::AnimationFrame()
: _spriteFrame(NULL)
, _delayUnits(0.0f)
, _userInfo(NULL)
{

}

bool AnimationFrame::initWithSpriteFrame(SpriteFrame* spriteFrame, float delayUnits, Dictionary* userInfo)
{
    setSpriteFrame(spriteFrame);
    setDelayUnits(delayUnits);
    setUserInfo(userInfo);

    return true;
}

AnimationFrame::~AnimationFrame()
{    
    CCLOGINFO( "cocos2d: deallocing %p", this);

    CC_SAFE_RELEASE(_spriteFrame);
    CC_SAFE_RELEASE(_userInfo);
}

AnimationFrame* AnimationFrame::clone() const
{
	// no copy constructor
	auto frame = new AnimationFrame();
    frame->initWithSpriteFrame(_spriteFrame->clone(),
							   _delayUnits,
							   _userInfo != NULL ? _userInfo->clone() : NULL);

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

Animation* Animation::createWithSpriteFrames(Array *frames, float delay/* = 0.0f*/)
{
    Animation *pAnimation = new Animation();
    pAnimation->initWithSpriteFrames(frames, delay);
    pAnimation->autorelease();

    return pAnimation;
}

Animation* Animation::create(Array* arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops /* = 1 */)
{
    Animation *pAnimation = new Animation();
    pAnimation->initWithAnimationFrames(arrayOfAnimationFrameNames, delayPerUnit, loops);
    pAnimation->autorelease();
    return pAnimation;
}

bool Animation::init()
{
    return initWithSpriteFrames(NULL, 0.0f);
}

bool Animation::initWithSpriteFrames(Array *pFrames, float delay/* = 0.0f*/)
{
    CCARRAY_VERIFY_TYPE(pFrames, SpriteFrame*);

    _loops = 1;
    _delayPerUnit = delay;
    Array* pTmpFrames = Array::create();
    setFrames(pTmpFrames);

    if (pFrames != NULL)
    {
        Object* pObj = NULL;
        CCARRAY_FOREACH(pFrames, pObj)
        {
            SpriteFrame* frame = static_cast<SpriteFrame*>(pObj);
            AnimationFrame *animFrame = new AnimationFrame();
            animFrame->initWithSpriteFrame(frame, 1, NULL);
            _frames->addObject(animFrame);
            animFrame->release();

            _totalDelayUnits++;
        }
    }

    return true;
}

bool Animation::initWithAnimationFrames(Array* arrayOfAnimationFrames, float delayPerUnit, unsigned int loops)
{
    CCARRAY_VERIFY_TYPE(arrayOfAnimationFrames, AnimationFrame*);

    _delayPerUnit = delayPerUnit;
    _loops = loops;

    setFrames(Array::createWithArray(arrayOfAnimationFrames));

    Object* pObj = NULL;
    CCARRAY_FOREACH(_frames, pObj)
    {
        AnimationFrame* animFrame = static_cast<AnimationFrame*>(pObj);
        _totalDelayUnits += animFrame->getDelayUnits();
    }
    return true;
}

Animation::Animation()
: _totalDelayUnits(0.0f)
, _delayPerUnit(0.0f)
, _duration(0.0f)
, _frames(NULL)
, _restoreOriginalFrame(false)
, _loops(0)
{

}

Animation::~Animation(void)
{
    CCLOGINFO("cocos2d, deallocing %p", this);
    CC_SAFE_RELEASE(_frames);
}

void Animation::addSpriteFrame(SpriteFrame *pFrame)
{
    AnimationFrame *animFrame = new AnimationFrame();
    animFrame->initWithSpriteFrame(pFrame, 1.0f, NULL);
    _frames->addObject(animFrame);
    animFrame->release();

    // update duration
    _totalDelayUnits++;
}

void Animation::addSpriteFrameWithFileName(const char *filename)
{
    Texture2D *texture = TextureCache::getInstance()->addImage(filename);
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