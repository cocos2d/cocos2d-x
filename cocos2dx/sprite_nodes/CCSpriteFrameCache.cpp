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

using namespace std;

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
	pSharedSpriteFrameCache->release();
	pSharedSpriteFrameCache = NULL;
}

CCSpriteFrameCache* CCSpriteFrameCache::init(void)
{
	m_pSpriteFramesMap = new map<string, CCSpriteFrame*>();
	return this;
}

CCSpriteFrameCache::~CCSpriteFrameCache(void)
{
	pSharedSpriteFrameCache->release();
	delete m_pSpriteFramesMap;
}

void CCSpriteFrameCache::addSpriteFramesWithDictionary(map<string, void*> *pobDictionary, CCTexture2D *pobTexture)
{
	/*
	Supported Zwoptex Formats:
		enum {
			ZWTCoordinatesListXMLFormat_Legacy = 0
			ZWTCoordinatesListXMLFormat_v1_0,
		};
	*/

	map<string, void*>::iterator metadataIter = pobDictionary->find("metadata");
	map<string, string> *pMetadataMap = NULL;
	if (metadataIter != pobDictionary->end())
	{
		pMetadataMap = static_cast<map<string, string>*>(metadataIter->second);
	}

	map<string, void*>::iterator framesIter = pobDictionary->find("frames");
	map<string ,void*> *pFramesMap = NULL;
	if (framesIter != pobDictionary->end())
	{
		pFramesMap = static_cast<map<string, void*>*>(framesIter->second);
	}
	int format = 0;

	// get the format
	if (pMetadataMap)
	{
		map<string, string>::iterator formatIter = pMetadataMap->find("format");
		if (formatIter != pMetadataMap->end())
		{
			format = atoi(formatIter->second.c_str());
		}
	}

	// check the format
	if (format < 0 || format > 1)
	{
		// format is not supported for CCSpriteFrameCache addSpriteFramesWithDictionary:texture
		assert(0);
		return;
	}

	
	map<string, void*>::iterator frameIter;
	map<string, string> *pFrame;
	string key;
	for (frameIter = pFramesMap->begin(); frameIter != pFramesMap->end(); ++frameIter)
	{
		// skip registered frames
		key = frameIter->first;
		CCSpriteFrame *pOldFrame = m_pSpriteFramesMap->find(key)->second;
		if (pOldFrame)
		{
			continue;
		}

		CCSpriteFrame *pSpriteFrame;
		pFrame = static_cast<map<string, string>*>(frameIter->second);
		if (format == 0)
		{
			/*
			float x = (float)atof(pFrameDict->objectForKey("x").c_str());
			float y = (float)atof(pFrameDict->objectForKey("y").c_str());
			float w = (float)atof(pFrameDict->objectForKey("width").c_str());
			float h = (float)atof(pFrameDict->objectForKey("height").c_str());
			float ox = (float)atof(pFrameDict->objectForKey("offsetX").c_str());
			float oy = (float)atof(pFrameDict->objectForKey("offsetY").c_str());
			int ow = (int)atof(pFrameDict->objectForKey("originalWidth").c_str());
			int oh = (int)atof(pFrameDict->objectForKey("originalHeight").c_str());
			*/

			float x = (float)atof(pFrame->find("x")->second.c_str());
			float y = (float)atof(pFrame->find("y")->second.c_str());
			float w = (float)atof(pFrame->find("width")->second.c_str());
			float h = (float)atof(pFrame->find("height")->second.c_str());
			float ox = (float)atof(pFrame->find("offsetX")->second.c_str());
			float oy = (float)atof(pFrame->find("offsetY")->second.c_str());
			int ow = (int)atof(pFrame->find("originalWidth")->second.c_str());
			int oh = (int)atof(pFrame->find("originalHeight")->second.c_str());



			// check ow/oh
			if ((! ow) || (! oh))
			{
				CCLOG("cocos2d: WARNING: originalWidth/Height not found on the CCSpriteFrame. AnchorPoint won't work as expected. Regenrate the .plist");
			}

			// abs ow/oh
			ow = abs(ow);
			oh = abs(oh);

			// create frame
			pSpriteFrame = CCSpriteFrame::frameWithTexture(pobTexture, 
				CGRectMake(x, y, w, h), CGPointMake(ox, oy), CGSizeMake((float)ow, (float)oh));
		} else
		if (format == 1)
		{
			///@todo how to implement??
			/*
			CGRect frame = CGRectFromString([frameDict objectForKey:@"frame"]);
			CGPoint offset = CGPointFromString([frameDict objectForKey:@"offset"]);
			CGSize sourceSize = CGSizeFromString([frameDict objectForKey:@"sourceSize"]);
			
			CGRect sourceColorRect = CGRectFromString([frameDict objectForKey:@"sourceColorRect"]);
			int leftTrim = sourceColorRect.origin.x;
			int topTrim = sourceColorRect.origin.y;
			int rightTrim = sourceColorRect.size.width + leftTrim;
			int bottomTrim = sourceColorRect.size.height + topTrim;
			
			// create frame
			spriteFrame = [CCSpriteFrame frameWithTexture:texture rect:frame offset:offset originalSize:sourceSize];
			*/
		}

		(*m_pSpriteFramesMap)[key] = pSpriteFrame;
	}
}

///@todo implement later
/*
void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture)
{
	char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
	
}
*/

///@todo implement later
void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist)
{
}

void CCSpriteFrameCache::addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName)
{
	(*m_pSpriteFramesMap)[pszFrameName] = pobFrame;
}

void CCSpriteFrameCache::removeSpriteFrames(void)
{
	m_pSpriteFramesMap->clear();
}

void CCSpriteFrameCache::removeUnusedSpriteFrames(void)
{
	map<string, CCSpriteFrame*>::iterator iter;
	for (iter = m_pSpriteFramesMap->begin(); iter != m_pSpriteFramesMap->end();)
	{
		CCSpriteFrame *pFrame = iter->second;
		if (pFrame->retainCount() == 1)
		{
			CCLOG("cocos2d: CCSpriteFrameCache: removing unused frame %s", *iter);
			m_pSpriteFramesMap->erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


void CCSpriteFrameCache::removeSpriteFrameByName(const char *pszName)
{
	map<string, CCSpriteFrame*>::iterator iter = m_pSpriteFramesMap->find(pszName);
	m_pSpriteFramesMap->erase(iter);
}

CCSpriteFrame* CCSpriteFrameCache::spriteFrameByName(const char *pszName)
{
	CCSpriteFrame *pFrame = NULL;
	map<string, CCSpriteFrame*>::iterator iter = m_pSpriteFramesMap->find(pszName);

	if (iter != m_pSpriteFramesMap->end())
	{
		pFrame = iter->second;
	}

	if (! pFrame)
	{
		CCLOG("cocos2d: CCSpriteFrameCache: Frame %s, not found", pszName);
	}

	return pFrame;
}
