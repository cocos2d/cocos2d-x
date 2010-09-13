/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "ccMacros.h"
#include "CCTextureCache.h"
#include "CCSpriteFrameCache.h"
#include "CCSpriteFrame.h"
#include "CCSprite.h"
#include "support/TransformUtils.h"
#include "CCXFileUtils.h"
#include "NSString.h"

namespace   cocos2d {

static CCSpriteFrameCache *pSharedSpriteFrameCache = NULL;

CCSpriteFrameCache* CCSpriteFrameCache::sharedSpriteFrameCache(void)
{
	if (! pSharedSpriteFrameCache)
	{
		pSharedSpriteFrameCache = new CCSpriteFrameCache();
        pSharedSpriteFrameCache->init();
	}

	return pSharedSpriteFrameCache;
}

void CCSpriteFrameCache::purgeSharedSpriteFrameCache(void)
{
	CCX_SAFE_RELEASE_NULL(pSharedSpriteFrameCache);
}

bool CCSpriteFrameCache::init(void)
{
	m_pSpriteFrames= new NSDictionary<std::string, CCSpriteFrame*>();
	return true;
}

CCSpriteFrameCache::~CCSpriteFrameCache(void)
{
	m_pSpriteFrames->release();
}

void CCSpriteFrameCache::addSpriteFramesWithDictionary(NSDictionary<std::string, NSObject*> *dictionary, CCTexture2D *pobTexture)
{
	/*
	Supported Zwoptex Formats:
		enum {
			ZWTCoordinatesListXMLFormat_Legacy = 0
			ZWTCoordinatesListXMLFormat_v1_0,
		};
	*/

	NSDictionary<std::string, NSObject*> *metadataDict = (NSDictionary<std::string, NSObject*>*)dictionary->objectForKey(std::string("metadata"));
	NSDictionary<std::string, NSObject*> *framesDict = (NSDictionary<std::string, NSObject*>*)dictionary->objectForKey(std::string("frames"));
	int format = 0;

	// get the format
	if(metadataDict != NULL) 
	{
		format = atoi(valueForKey("format", metadataDict));
	}

	// check the format
	if(format < 0 || format > 1) 
	{
		NSAssert(0, "cocos2d: WARNING: format is not supported for CCSpriteFrameCache addSpriteFramesWithDictionary:texture:");
		return;
	}

	framesDict->begin();
	std::string key = "";
	NSDictionary<std::string, NSObject*> *frameDict = NULL;
	while( frameDict = (NSDictionary<std::string, NSObject*>*)framesDict->next(&key) )
	{
		CCSpriteFrame *spriteFrame = m_pSpriteFrames->objectForKey(key);
		if (spriteFrame)
		{
			continue;
		}
		
		if(format == 0) 
		{
			float x = (float)atof(valueForKey("x", frameDict));
			float y = (float)atof(valueForKey("y", frameDict));
			float w = (float)atof(valueForKey("width", frameDict));
			float h = (float)atof(valueForKey("height", frameDict));
			float ox = (float)atof(valueForKey("offsetX", frameDict));
			float oy = (float)atof(valueForKey("offsetY", frameDict));
			int ow = atoi(valueForKey("originalWidth", frameDict));
			int oh = atoi(valueForKey("originalHeight", frameDict));
			// check ow/oh
			if(!ow || !oh)
			{
				CCLOG("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
			}
			// abs ow/oh
			ow = abs(ow);
			oh = abs(oh);
			// create frame
			spriteFrame = CCSpriteFrame::frameWithTexture(pobTexture, CGRectMake(x, y, w, h), CGPointMake(ox, oy), CGSizeMake((float)ow, (float)oh));
		} 
		else if(format == 1) 
		{
			/** @todo
			CGRect frame = CGRectFromString([frameDict objectForKey:@"frame"]);
			CGPoint offset = CGPointFromString([frameDict objectForKey:@"offset"]);
			CGSize sourceSize = CGSizeFromString([frameDict objectForKey:@"sourceSize"]);
			
			// create frame
			spriteFrame = [CCSpriteFrame frameWithTexture:texture rect:frame offset:offset originalSize:sourceSize];
			*/
		}
		// add sprite frame
		m_pSpriteFrames->setObject(spriteFrame, key);
	}
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture)
{
	const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
	NSDictionary<std::string, NSObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);

	return addSpriteFramesWithDictionary(dict, pobTexture);
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist)
{
	const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
	NSDictionary<std::string, NSObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);
	
	string texturePath = string(pszPlist);

	// remove .xxx
	size_t startPos = texturePath.find_last_of("."); 
	texturePath = texturePath.erase(startPos);

	// append .png
	texturePath = texturePath.append(".png");

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(texturePath.c_str());

	return addSpriteFramesWithDictionary(dict, pTexture);
}

void CCSpriteFrameCache::addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName)
{
	m_pSpriteFrames->setObject(pobFrame, std::string(pszFrameName));
}

void CCSpriteFrameCache::removeSpriteFrames(void)
{
	m_pSpriteFrames->removeAllObjects();
}

void CCSpriteFrameCache::removeUnusedSpriteFrames(void)
{
	m_pSpriteFrames->begin();
	std::string key = "";
	CCSpriteFrame *spriteFrame = NULL;
	while( spriteFrame = m_pSpriteFrames->next(&key) )
	{
		if( spriteFrame->retainCount() == 1 ) 
		{
			CCLOG("cocos2d: CCSpriteFrameCache: removing unused frame: %s", key.c_str());
			m_pSpriteFrames->removeObjectForKey(key);
		}
	}
	m_pSpriteFrames->end();
}


void CCSpriteFrameCache::removeSpriteFrameByName(const char *pszName)
{
	m_pSpriteFrames->removeObjectForKey(std::string(pszName));
}

CCSpriteFrame* CCSpriteFrameCache::spriteFrameByName(const char *pszName)
{
	CCSpriteFrame *frame = m_pSpriteFrames->objectForKey(std::string(pszName));
	if( ! frame )
	{
		CCLOG("cocos2d: CCSpriteFrameCache: Frame '%s' not found", pszName);
	}
	return frame;
}

CCSprite* CCSpriteFrameCache::createSpriteWithFrameName(const char *pszName)
{
	CCSpriteFrame *frame = m_pSpriteFrames->objectForKey(std::string(pszName));
	return CCSprite::spriteWithSpriteFrame(frame);
}
const char * CCSpriteFrameCache::valueForKey(const char *key, NSDictionary<std::string, NSObject*> *dict)
{
	if (dict)
	{
		NSString *pString = (NSString*)dict->objectForKey(std::string(key));
		return pString ? pString->m_sString.c_str() : "";
	}
	return "";
}
}//namespace   cocos2d 
