/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada
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
#include "CCAnimationCache.h"
#include "ccMacros.h"
#include "CCAnimation.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "cocoa/CCString.h"
#include "platform/CCFileUtils.h"

using namespace std;

NS_CC_BEGIN

AnimationCache* AnimationCache::s_pSharedAnimationCache = NULL;

AnimationCache* AnimationCache::getInstance()
{
    if (! s_pSharedAnimationCache)
    {
        s_pSharedAnimationCache = new AnimationCache();
        s_pSharedAnimationCache->init();
    }

    return s_pSharedAnimationCache;
}

void AnimationCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_pSharedAnimationCache);
}

bool AnimationCache::init()
{
    _animations = new Dictionary();
    return true;
}

AnimationCache::AnimationCache()
: _animations(NULL)
{
}

AnimationCache::~AnimationCache()
{
    CCLOGINFO("cocos2d: deallocing %p", this);
    CC_SAFE_RELEASE(_animations);
}

void AnimationCache::addAnimation(Animation *animation, const char * name)
{
    _animations->setObject(animation, name);
}

void AnimationCache::removeAnimationByName(const char* name)
{
    if (! name)
    {
        return;
    }

    _animations->removeObjectForKey(name);
}

Animation* AnimationCache::animationByName(const char* name)
{
    return (Animation*)_animations->objectForKey(name);
}

void AnimationCache::parseVersion1(Dictionary* animations)
{
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();

    DictElement* pElement = NULL;
    CCDICT_FOREACH(animations, pElement)
    {
        Dictionary* animationDict = static_cast<Dictionary*>(pElement->getObject());
        Array* frameNames = static_cast<Array*>(animationDict->objectForKey("frames"));
        float delay = animationDict->valueForKey("delay")->floatValue();
        Animation* animation = NULL;

        if ( frameNames == NULL ) 
        {
            CCLOG("cocos2d: AnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", pElement->getStrKey());
            continue;
        }

        Array* frames = Array::createWithCapacity(frameNames->count());
        frames->retain();

        Object* pObj = NULL;
        CCARRAY_FOREACH(frameNames, pObj)
        {
            const char* frameName = static_cast<String*>(pObj)->getCString();
            SpriteFrame* spriteFrame = frameCache->getSpriteFrameByName(frameName);

            if ( ! spriteFrame ) {
                CCLOG("cocos2d: AnimationCache: Animation '%s' refers to frame '%s' which is not currently in the SpriteFrameCache. This frame will not be added to the animation.", pElement->getStrKey(), frameName);

                continue;
            }

            AnimationFrame* animFrame = new AnimationFrame();
            animFrame->initWithSpriteFrame(spriteFrame, 1, NULL);
            frames->addObject(animFrame);
            animFrame->release();
        }

        if ( frames->count() == 0 ) {
            CCLOG("cocos2d: AnimationCache: None of the frames for animation '%s' were found in the SpriteFrameCache. Animation is not being added to the Animation Cache.", pElement->getStrKey());
            continue;
        } else if ( frames->count() != frameNames->count() ) {
            CCLOG("cocos2d: AnimationCache: An animation in your dictionary refers to a frame which is not in the SpriteFrameCache. Some or all of the frames for the animation '%s' may be missing.", pElement->getStrKey());
        }

        animation = Animation::create(frames, delay, 1);

        AnimationCache::getInstance()->addAnimation(animation, pElement->getStrKey());
        frames->release();
    }    
}

void AnimationCache::parseVersion2(Dictionary* animations)
{
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();

    DictElement* pElement = NULL;
    CCDICT_FOREACH(animations, pElement)
    {
        const char* name = pElement->getStrKey();
        Dictionary* animationDict = static_cast<Dictionary*>(pElement->getObject());

        const String* loops = animationDict->valueForKey("loops");
        bool restoreOriginalFrame = animationDict->valueForKey("restoreOriginalFrame")->boolValue();

        Array* frameArray = static_cast<Array*>(animationDict->objectForKey("frames"));

        if ( frameArray == NULL ) {
            CCLOG("cocos2d: AnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", name);
            continue;
        }

        // Array of AnimationFrames
        Array* array = Array::createWithCapacity(frameArray->count());
        array->retain();

        Object* pObj = NULL;
        CCARRAY_FOREACH(frameArray, pObj)
        {
            Dictionary* entry = static_cast<Dictionary*>(pObj);

            const char* spriteFrameName = entry->valueForKey("spriteframe")->getCString();
            SpriteFrame *spriteFrame = frameCache->getSpriteFrameByName(spriteFrameName);

            if( ! spriteFrame ) {
                CCLOG("cocos2d: AnimationCache: Animation '%s' refers to frame '%s' which is not currently in the SpriteFrameCache. This frame will not be added to the animation.", name, spriteFrameName);

                continue;
            }

            float delayUnits = entry->valueForKey("delayUnits")->floatValue();
            Dictionary* userInfo = (Dictionary*)entry->objectForKey("notification");

            AnimationFrame *animFrame = new AnimationFrame();
            animFrame->initWithSpriteFrame(spriteFrame, delayUnits, userInfo);

            array->addObject(animFrame);
            animFrame->release();
        }

        float delayPerUnit = animationDict->valueForKey("delayPerUnit")->floatValue();
        Animation *animation = new Animation();
        animation->initWithAnimationFrames(array, delayPerUnit, 0 != loops->length() ? loops->intValue() : 1);
        array->release();

        animation->setRestoreOriginalFrame(restoreOriginalFrame);

        AnimationCache::getInstance()->addAnimation(animation, name);
        animation->release();
    }
}

void AnimationCache::addAnimationsWithDictionary(Dictionary* dictionary)
{
    Dictionary* animations = (Dictionary*)dictionary->objectForKey("animations");

    if ( animations == NULL ) {
        CCLOG("cocos2d: AnimationCache: No animations were found in provided dictionary.");
        return;
    }

    unsigned int version = 1;
    Dictionary* properties = (Dictionary*)dictionary->objectForKey("properties");
    if( properties )
    {
        version = properties->valueForKey("format")->intValue();
        Array* spritesheets = (Array*)properties->objectForKey("spritesheets");

        Object* pObj = NULL;
        CCARRAY_FOREACH(spritesheets, pObj)
        {
            String* name = static_cast<String*>(pObj);
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name->getCString());
        }
    }

    switch (version) {
        case 1:
            parseVersion1(animations);
            break;
        case 2:
            parseVersion2(animations);
            break;
        default:
            CCASSERT(false, "Invalid animation format");
    }
}

/** Read an NSDictionary from a plist file and parse it automatically for animations */
void AnimationCache::addAnimationsWithFile(const char* plist)
{
    CCASSERT( plist, "Invalid texture file name");

    std::string path = FileUtils::getInstance()->fullPathForFilename(plist);
    Dictionary* dict = Dictionary::createWithContentsOfFile(path.c_str());

    CCASSERT( dict, "CCAnimationCache: File could not be found");

    addAnimationsWithDictionary(dict);
}


NS_CC_END