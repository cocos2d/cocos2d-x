/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

using namespace std;

NS_CC_BEGIN

CCAnimationCache* CCAnimationCache::s_pSharedAnimationCache = NULL;

CCAnimationCache* CCAnimationCache::sharedAnimationCache(void)
{
    if (! s_pSharedAnimationCache)
	{
		s_pSharedAnimationCache = new CCAnimationCache();
		s_pSharedAnimationCache->init();
	}

	return s_pSharedAnimationCache;
}

void CCAnimationCache::purgeSharedAnimationCache(void)
{
    CC_SAFE_RELEASE_NULL(s_pSharedAnimationCache);
}

bool CCAnimationCache::init()
{
	m_pAnimations = new CCMutableDictionary<std::string, CCAnimation*>();
	return true;
}

CCAnimationCache::CCAnimationCache()
: m_pAnimations(NULL)
{
}

CCAnimationCache::~CCAnimationCache()
{
	CCLOGINFO("cocos2d: deallocing %p", this);
	CC_SAFE_RELEASE(m_pAnimations);
}

void CCAnimationCache::addAnimation(CCAnimation *animation, const char * name)
{
	m_pAnimations->setObject(animation, std::string(name));
}

void CCAnimationCache::removeAnimationByName(const char* name)
{
    if (! name)
	{
		return;
	}

	m_pAnimations->removeObjectForKey(std::string(name));
}

CCAnimation* CCAnimationCache::animationByName(const char* name)
{
	return m_pAnimations->objectForKey(std::string(name));
}

void CCAnimationCache::parseVersion1(CCObjectDictionary* animations)
{
	vector<std::string> animationNames = animations->allKeys();
	CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	for (vector<std::string>::iterator iterName = animationNames.begin(); iterName != animationNames.end(); ++iterName)
	{
		string name = *iterName;
		CCObjectDictionary* animationDict = (CCObjectDictionary*)animations->objectForKey(name);
		CCMutableArray<CCObject*>* frameNames = (CCMutableArray<CCObject*>*)animationDict->objectForKey("frames");
		float delay = (float)atof(valueForKey("delay", animationDict));
		CCAnimation* animation = NULL;

		if ( frameNames == NULL ) {
			CCLOG("cocos2d: CCAnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", name.c_str());
			continue;
		}

		CCMutableArray<CCAnimationFrame*>* frames = new CCMutableArray<CCAnimationFrame*>(frameNames->count());

		for (CCMutableArray<CCObject*>::CCMutableArrayIterator iterFrameName = frameNames->begin(); iterFrameName != frameNames->end(); ++iterFrameName)
		{
			const char* frameName = ((CCString*)(*iterFrameName))->toStdString().c_str();
			CCSpriteFrame* spriteFrame = frameCache->spriteFrameByName(frameName);

			if ( ! spriteFrame ) {
				CCLOG("cocos2d: CCAnimationCache: Animation '%s' refers to frame '%s' which is not currently in the CCSpriteFrameCache. This frame will not be added to the animation.", name.c_str(), frameName);

				continue;
			}

			CCAnimationFrame* animFrame = new CCAnimationFrame();
			animFrame->initWithSpriteFrame(spriteFrame, 1, NULL);
			frames->addObject(animFrame);
			animFrame->release();
		}

		if ( frames->count() == 0 ) {
			CCLOG("cocos2d: CCAnimationCache: None of the frames for animation '%s' were found in the CCSpriteFrameCache. Animation is not being added to the Animation Cache.", name.c_str());
			continue;
		} else if ( frames->count() != frameNames->count() ) {
			CCLOG("cocos2d: CCAnimationCache: An animation in your dictionary refers to a frame which is not in the CCSpriteFrameCache. Some or all of the frames for the animation '%s' may be missing.", name.c_str());
		}

		animation = CCAnimation::animationWithAnimationFrames(frames, delay, 1);

		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, name.c_str());
		frames->release();
	}	
}

void CCAnimationCache::parseVersion2(CCObjectDictionary* animations)
{
	vector<std::string> animationNames = animations->allKeys();
	CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

	for (vector<std::string>::iterator iterName = animationNames.begin(); iterName != animationNames.end(); ++iterName)
	{
		string name = *iterName;
		CCObjectDictionary* animationDict = (CCObjectDictionary*)animations->objectForKey(name);

		int loops = atoi(valueForKey("loops", animationDict));
		bool restoreOriginalFrame = atoi(valueForKey("restoreOriginalFrame", animationDict)) == 0 ? false : true;

		CCMutableArray<CCObject*>* frameArray = (CCMutableArray<CCObject*>*)animationDict->objectForKey("frames");

		if ( frameArray == NULL ) {
			CCLOG("cocos2d: CCAnimationCache: Animation '%s' found in dictionary without any frames - cannot add to animation cache.", name.c_str());
			continue;
		}

		// Array of AnimationFrames
		CCMutableArray<CCAnimationFrame*>* array = new CCMutableArray<CCAnimationFrame*>(frameArray->count());

		for (CCMutableArray<CCObject*>::CCMutableArrayIterator iterFrameName = frameArray->begin(); iterFrameName != frameArray->end(); ++iterFrameName)
		{
			CCObjectDictionary* entry = (CCObjectDictionary*)(*iterFrameName);

			const char* spriteFrameName = valueForKey("spriteframe", entry);
			CCSpriteFrame *spriteFrame = frameCache->spriteFrameByName(spriteFrameName);

			if( ! spriteFrame ) {
				CCLOG("cocos2d: CCAnimationCache: Animation '%s' refers to frame '%s' which is not currently in the CCSpriteFrameCache. This frame will not be added to the animation.", name.c_str(), spriteFrameName);

				continue;
			}

			float delayUnits = (float)atof(valueForKey("delayUnits", entry));
			CCObjectDictionary* userInfo = (CCObjectDictionary*)entry->objectForKey("notification");

			CCAnimationFrame *animFrame = new CCAnimationFrame();
			animFrame->initWithSpriteFrame(spriteFrame, delayUnits, userInfo);

			array->addObject(animFrame);
			animFrame->release();
		}

		float delayPerUnit = (float)atof(valueForKey("delayPerUnit", animationDict));
		CCAnimation *animation = new CCAnimation();
		animation->initWithAnimationFrames(array, delayPerUnit, loops);
		array->release();

		animation->setRestoreOriginalFrame(restoreOriginalFrame);

		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, name.c_str());
		animation->release();
	}
}

void CCAnimationCache::addAnimationsWithDictionary(CCObjectDictionary* dictionary)
{
	CCObjectDictionary* animations = (CCObjectDictionary*)dictionary->objectForKey("animations");

	if ( animations == NULL ) {
		CCLOG("cocos2d: CCAnimationCache: No animations were found in provided dictionary.");
		return;
	}

	unsigned int version = 1;
	CCObjectDictionary* properties = (CCObjectDictionary*)dictionary->objectForKey("properties");
	if( properties )
	{
		version = atoi(valueForKey("format", properties));
	}

	CCMutableArray<CCObject*>* spritesheets = (CCMutableArray<CCObject*>*)properties->objectForKey("spritesheets");

	for( CCMutableArray<CCObject*>::CCMutableArrayIterator iterName = spritesheets->begin(); iterName != spritesheets->end(); ++iterName)
	{
		CCString* name = (CCString*)(*iterName);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(name->toStdString().c_str());
	}

	switch (version) {
		case 1:
			parseVersion1(animations);
			break;
		case 2:
			parseVersion2(animations);
			break;
		default:
			CCAssert(false, "Invalid animation format");
	}
}

const char * CCAnimationCache::valueForKey(const char *key, CCDictionary<std::string, CCObject*> *dict)
{
	if (dict)
	{
		CCString *pString = (CCString*)dict->objectForKey(std::string(key));
		return pString ? pString->m_sString.c_str() : "";
	}
	return "";
}

/** Read an NSDictionary from a plist file and parse it automatically for animations */
void CCAnimationCache::addAnimationsWithFile(const char* plist)
{
	CCAssert( plist, "Invalid texture file name");

	const char* path = CCFileUtils::fullPathFromRelativePath(plist);
	CCObjectDictionary* dict = CCFileUtils::dictionaryWithContentsOfFile(path);

	CCAssert( dict, "CCAnimationCache: File could not be found");

	addAnimationsWithDictionary(dict);
}


NS_CC_END