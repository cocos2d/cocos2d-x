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
#include "CCString.h"
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
    return true;
}

AnimationCache::AnimationCache()
: _animations(NULL)
{
}

AnimationCache::~AnimationCache()
{
    CCLOGINFO("deallocing AnimationCache: %p", this);
}

void AnimationCache::addAnimation(Animation *animation, const std::string& name)
{
    _animations.setObject(animation, name);
}

void AnimationCache::removeAnimation(const std::string& name)
{
    if (name.size()==0)
        return;

    _animations.removeObjectForKey(name);
}

Animation* AnimationCache::getAnimation(const std::string& name)
{
    return _animations.getObjectForKey(name);
}

void AnimationCache::parseVersion1(const ValueDict& animations)
{
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();

    for (auto iter = animations.cbegin(); iter != animations.cend(); ++iter)
    {
        const ValueDict& animationDict = iter->second.asDict();
        const ValueArray& frameNames = animationDict.at("frames").asArray();
        float delay = animationDict.at("delay").asFloat();
        Animation* animation = nullptr;

        if ( frameNames.empty() )
        {
            CCLOG("cocos2d: AnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", iter->first.c_str());
            continue;
        }

        Vector<AnimationFrame*> frames(frameNames.size());

        for (auto& frameName : frameNames)
        {
            SpriteFrame* spriteFrame = frameCache->getSpriteFrameByName(frameName.asString());

            if ( ! spriteFrame ) {
                CCLOG("cocos2d: AnimationCache: Animation '%s' refers to frame '%s' which is not currently in the SpriteFrameCache. This frame will not be added to the animation.", iter->first.c_str(), frameName.asString().c_str());

                continue;
            }

            AnimationFrame* animFrame = AnimationFrame::create(spriteFrame, 1, ValueDict());
            frames.addObject(animFrame);
        }

        if ( frames.count() == 0 )
        {
            CCLOG("cocos2d: AnimationCache: None of the frames for animation '%s' were found in the SpriteFrameCache. Animation is not being added to the Animation Cache.", iter->first.c_str());
            continue;
        }
        else if ( frames.count() != frameNames.size() )
        {
            CCLOG("cocos2d: AnimationCache: An animation in your dictionary refers to a frame which is not in the SpriteFrameCache. Some or all of the frames for the animation '%s' may be missing.", iter->first.c_str());
        }

        animation = Animation::create(frames, delay, 1);

        AnimationCache::getInstance()->addAnimation(animation, iter->first.c_str());
    }
}

void AnimationCache::parseVersion2(const ValueDict& animations)
{
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();

    for (auto iter = animations.cbegin(); iter != animations.cend(); ++iter)
    {
        std::string name = iter->first;
        const ValueDict& animationDict = iter->second.asDict();

        const Value& loops = animationDict.at("loops");
        bool restoreOriginalFrame = animationDict.at("restoreOriginalFrame").asBool();

        const ValueArray& frameArray = animationDict.at("frames").asArray();

        if ( frameArray.empty() )
        {
            CCLOG("cocos2d: AnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", name.c_str());
            continue;
        }

        // Array of AnimationFrames
        Vector<AnimationFrame*> array(frameArray.size());

        for (auto& obj : frameArray)
        {
            const ValueDict& entry = obj.asDict();
            std::string spriteFrameName = entry.at("spriteframe").asString();
            SpriteFrame *spriteFrame = frameCache->getSpriteFrameByName(spriteFrameName);

            if( ! spriteFrame ) {
                CCLOG("cocos2d: AnimationCache: Animation '%s' refers to frame '%s' which is not currently in the SpriteFrameCache. This frame will not be added to the animation.", name.c_str(), spriteFrameName.c_str());

                continue;
            }

            float delayUnits = entry.at("delayUnits").asFloat();
            const Value& userInfo = entry.at("notification");

            AnimationFrame *animFrame = AnimationFrame::create(spriteFrame, delayUnits, userInfo.asDict());

            array.addObject(animFrame);
        }

        float delayPerUnit = animationDict.at("delayPerUnit").asFloat();
        Animation *animation = Animation::create(array, delayPerUnit, loops.getType() != Value::Type::NONE ? loops.asInt() : 1);

        animation->setRestoreOriginalFrame(restoreOriginalFrame);

        AnimationCache::getInstance()->addAnimation(animation, name);
    }
}

void AnimationCache::addAnimationsWithDictionary(const ValueDict& dictionary)
{
    if ( dictionary.find("animations") == dictionary.end() )
    {
        CCLOG("cocos2d: AnimationCache: No animations were found in provided dictionary.");
        return;
    }
    
    const Value& animations = dictionary.at("animations");
    unsigned int version = 1;

    if( dictionary.find("properties") != dictionary.end() )
    {
        const ValueDict& properties = dictionary.at("properties").asDict();
        version = properties.at("format").asInt();
        const ValueArray& spritesheets = properties.at("spritesheets").asArray();

        std::for_each(spritesheets.cbegin(), spritesheets.cend(), [](const Value& value){
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(value.asString());
        });
    }

    switch (version) {
        case 1:
            parseVersion1(animations.asDict());
            break;
        case 2:
            parseVersion2(animations.asDict());
            break;
        default:
            CCASSERT(false, "Invalid animation format");
    }
}

/** Read an NSDictionary from a plist file and parse it automatically for animations */
void AnimationCache::addAnimationsWithFile(const std::string& plist)
{
    CCASSERT( plist.size()>0, "Invalid texture file name");

    std::string path = FileUtils::getInstance()->fullPathForFilename(plist);
    ValueDict dict =  FileUtils::getInstance()->fileToValueDict(path);

    CCASSERT( !dict.empty(), "CCAnimationCache: File could not be found");

    addAnimationsWithDictionary(dict);
}


NS_CC_END