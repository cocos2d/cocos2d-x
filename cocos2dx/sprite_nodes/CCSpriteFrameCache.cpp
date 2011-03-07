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

#include "platform/CCNS.h"
#include "ccMacros.h"
#include "CCTextureCache.h"
#include "CCSpriteFrameCache.h"
#include "CCSpriteFrame.h"
#include "CCSprite.h"
#include "support/TransformUtils.h"
#include "CCFileUtils.h"
#include "CCString.h"

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
	CC_SAFE_RELEASE_NULL(pSharedSpriteFrameCache);
}

bool CCSpriteFrameCache::init(void)
{
	m_pSpriteFrames= new NSDictionary<std::string, CCSpriteFrame*>();
	m_pSpriteFramesAliases = new NSDictionary<std::string, CCSpriteFrame*>();
	return true;
}

CCSpriteFrameCache::~CCSpriteFrameCache(void)
{
	m_pSpriteFrames->release();
	m_pSpriteFramesAliases->release();
}

void CCSpriteFrameCache::addSpriteFramesWithDictionary(NSDictionary<std::string, CCObject*> *dictionary, CCTexture2D *pobTexture)
{
	/*
	Supported Zwoptex Formats:

	ZWTCoordinatesFormatOptionXMLLegacy = 0, // Flash Version
	ZWTCoordinatesFormatOptionXML1_0 = 1, // Desktop Version 0.0 - 0.4b
	ZWTCoordinatesFormatOptionXML1_1 = 2, // Desktop Version 1.0.0 - 1.0.1
	ZWTCoordinatesFormatOptionXML1_2 = 3, // Desktop Version 1.0.2+
	*/

	NSDictionary<std::string, CCObject*> *metadataDict = (NSDictionary<std::string, CCObject*>*)dictionary->objectForKey(std::string("metadata"));
	NSDictionary<std::string, CCObject*> *framesDict = (NSDictionary<std::string, CCObject*>*)dictionary->objectForKey(std::string("frames"));
	int format = 0;

	// get the format
	if(metadataDict != NULL) 
	{
		format = atoi(valueForKey("format", metadataDict));
	}

	// check the format
	assert(format >=0 && format <= 3);

	framesDict->begin();
	std::string key = "";
	NSDictionary<std::string, CCObject*> *frameDict = NULL;
	while( frameDict = (NSDictionary<std::string, CCObject*>*)framesDict->next(&key) )
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
			spriteFrame = new CCSpriteFrame();
			spriteFrame->initWithTexture(pobTexture, 
				                        CCRectMake(x, y, w, h), 
										false,
                                        CCPointMake(ox, oy),
                                        CCSizeMake((float)ow, (float)oh)
										);
		} 
		else if(format == 1 || format == 2) 
		{
			CCRect frame = CCRectFromString(valueForKey("frame", frameDict));
			bool rotated = false;

			// rotation
			if (format == 2)
			{
				rotated = atoi(valueForKey("rotated", frameDict)) == 0 ? false : true;
			}

			CCPoint offset = CCPointFromString(valueForKey("offset", frameDict));
			CCSize sourceSize = CCSizeFromString(valueForKey("sourceSize", frameDict));

			// create frame
			spriteFrame = new CCSpriteFrame();
			spriteFrame->initWithTexture(pobTexture, 
				frame,
				rotated,
				offset,
				sourceSize
				);
		} else
		if (format == 3)
		{
			/// @todo what's the format look like?
			assert(false);
			return;
			/*
			// get values
			CCSize spriteSize = CCSizeFromString(valueForKey("spriteSize", frameDict));
			CCPoint spriteOffset = CCPointFromString(valueForKey("spriteOffset", frameDict));
			CCSize spriteSourceSize = CCSizeFromString(valueForKey("spriteSourceSize", frameDict));
			CCRect textureRect = CCRectFromString(valueForKey("textureRect", frameDict));
			bool textureRotated = atoi(valueForKey("textureRotated", frameDict)) == 0;

			// get aliases
			NSArray<CCString*> *aliases = NSArray<CCString*>dictionary->objectForKey(std::string("aliases"));

			while( alias = (NSDictionary<std::string, CCObject*>*)aliases->next(&key) )
			{
				std::string value = ((CCString*)alias->objectForKey(key))->m_sString();
				if (m_pSpriteFramesAliases->objectForKey(value))
				{
					CCLOG("cocos2d: WARNING: an alias with name %s already exists", value.c_str());
				}

				m_pSpriteFramesAliases->setObject(frameDict, value);
			}
			*/
		}

		// add sprite frame
		m_pSpriteFrames->setObject(spriteFrame, key);
		spriteFrame->release();
	}
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist, CCTexture2D *pobTexture)
{
	const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
	NSDictionary<std::string, CCObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);

	return addSpriteFramesWithDictionary(dict, pobTexture);
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char* plist, const char* textureFileName)
{
	assert(textureFileName);
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(textureFileName);

	if (texture)
	{
		addSpriteFramesWithFile(plist, texture);
	}
	else
	{
		CCLOG("cocos2d: CCSpriteFrameCache: couldn't load texture file. File not found %s", textureFileName);
	}
}

void CCSpriteFrameCache::addSpriteFramesWithFile(const char *pszPlist)
{
	const char *pszPath = CCFileUtils::fullPathFromRelativePath(pszPlist);
	NSDictionary<std::string, CCObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);
	
	string texturePath("");

	NSDictionary<std::string, CCObject*>* metadataDict = (NSDictionary<std::string, CCObject*>*)dict->objectForKey(string("metadata"));
    if (metadataDict)
	{
		// try to read  texture file name from meta data
		texturePath = string(valueForKey("textureFileName", metadataDict));
	}

	if (! texturePath.empty())
	{
		// build texture path relative to plist file

		// stringByDeletingLastPathComponent
		string textureBase(pszPath);
		int indexOfLastSeperator = textureBase.find_last_of('/');
        if (indexOfLastSeperator == textureBase.length() - 1)
		{
			textureBase.erase(indexOfLastSeperator, 1);
			indexOfLastSeperator = textureBase.find_last_of('/');
		}
		textureBase.erase(indexOfLastSeperator);

		// stringByAppendingPathComponent
        if (! textureBase.empty())
		{
			texturePath = textureBase + "/" + texturePath;
		}
	}
	else
	{
		// build texture path by replacing file extension
        texturePath = pszPath;

		// remove .xxx
		size_t startPos = texturePath.find_last_of("."); 
		texturePath = texturePath.erase(startPos);

		// append .png
		texturePath = texturePath.append(".png");

		CCLOG("cocos2d: CCSpriteFrameCache: Trying to use file %s as texture", texturePath);
	}

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(texturePath.c_str());

	if (pTexture)
	{
        addSpriteFramesWithDictionary(dict, pTexture);
	}
	else
	{
		CCLOG("cocos2d: CCSpriteFrameCache: Couldn't load texture");
	}
}

void CCSpriteFrameCache::addSpriteFrame(CCSpriteFrame *pobFrame, const char *pszFrameName)
{
	m_pSpriteFrames->setObject(pobFrame, std::string(pszFrameName));
}

void CCSpriteFrameCache::removeSpriteFrames(void)
{
	m_pSpriteFrames->removeAllObjects();
	m_pSpriteFramesAliases->removeAllObjects();
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
	// explicit nil handling
	if( ! pszName )
	{
		return;
	}

	// Is this an alias ?
	CCString *key = (CCString*)m_pSpriteFramesAliases->objectForKey(string(pszName));

	if (key)
	{
        m_pSpriteFrames->removeObjectForKey(key->m_sString);
		m_pSpriteFramesAliases->removeObjectForKey(key->m_sString);
	}
	else
	{
        m_pSpriteFrames->removeObjectForKey(std::string(pszName));
	}
}

void CCSpriteFrameCache::removeSpriteFramesFromFile(const char* plist)
{
	const char* path = CCFileUtils::fullPathFromRelativePath(plist);
	NSDictionary<std::string, CCObject*>* dict = CCFileUtils::dictionaryWithContentsOfFile(path);

	removeSpriteFramesFromDictionary((NSDictionary<std::string, CCSpriteFrame*>*)dict);
}

void CCSpriteFrameCache::removeSpriteFramesFromDictionary(NSDictionary<std::string, CCSpriteFrame*> *dictionary)
{
	NSDictionary<std::string, CCObject*>* framesDict = (NSDictionary<std::string, CCObject*>*)dictionary->objectForKey(string("frames"));
	vector<string> keysToRemove;

	framesDict->begin();
	std::string key = "";
	NSDictionary<std::string, CCObject*> *frameDict = NULL;
	while( frameDict = (NSDictionary<std::string, CCObject*>*)framesDict->next(&key) )
	{
		if (m_pSpriteFrames->objectForKey(key))
		{
			keysToRemove.push_back(key);
		}
	}
	framesDict->end();

	vector<string>::iterator iter;
	for (iter = keysToRemove.begin(); iter != keysToRemove.end(); iter++)
	{
		m_pSpriteFrames->removeObjectForKey(*iter);
	}
}

void CCSpriteFrameCache::removeSpriteFramesFromTexture(CCTexture2D* texture)
{
	vector<string> keysToRemove;

	m_pSpriteFrames->begin();
	std::string key = "";
	NSDictionary<std::string, CCObject*> *frameDict = NULL;
	while( frameDict = (NSDictionary<std::string, CCObject*>*)m_pSpriteFrames->next(&key) )
	{
		CCSpriteFrame *frame = m_pSpriteFrames->objectForKey(key);
		if (frame && (frame->getTexture() == texture))
		{
			keysToRemove.push_back(key);
		}
	}
	m_pSpriteFrames->end();

	vector<string>::iterator iter;
	for (iter = keysToRemove.begin(); iter != keysToRemove.end(); iter++)
	{
		m_pSpriteFrames->removeObjectForKey(*iter);
	}
}

CCSpriteFrame* CCSpriteFrameCache::spriteFrameByName(const char *pszName)
{
	CCSpriteFrame *frame = m_pSpriteFrames->objectForKey(std::string(pszName));
	if (! frame)
	{
		// try alias dictionary
		CCString *key = (CCString*)m_pSpriteFramesAliases->objectForKey(string(pszName));  
		if (key)
		{
			frame = m_pSpriteFrames->objectForKey(key->m_sString);
			if (! frame)
			{
				CCLOG("cocos2d: CCSpriteFrameCahce: Frame '%s' not found", pszName);
			}
		}
	}
	return frame;
}

CCSprite* CCSpriteFrameCache::createSpriteWithFrameName(const char *pszName)
{
	CCSpriteFrame *frame = m_pSpriteFrames->objectForKey(std::string(pszName));
	return CCSprite::spriteWithSpriteFrame(frame);
}
const char * CCSpriteFrameCache::valueForKey(const char *key, NSDictionary<std::string, CCObject*> *dict)
{
	if (dict)
	{
		CCString *pString = (CCString*)dict->objectForKey(std::string(key));
		return pString ? pString->m_sString.c_str() : "";
	}
	return "";
}
}//namespace   cocos2d 
