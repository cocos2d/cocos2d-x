/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

#include <stack>
#include <string>
#include <cctype>
#include <queue>
#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "CCData.h"
#include "CCDirector.h"
#include "platform/platform.h"
#include "CCFileUtils.h"
#include "CCImage.h"
#include "support/ccUtils.h"
#include "CCScheduler.h"
#include "pthread.h"
#include "CCThread.h"
#include "semaphore.h"

namespace   cocos2d {

typedef struct _AsyncStruct
{
	std::string			filename;
	CCObject	*target;
	SEL_CallFuncO		selector;
} AsyncStruct;

typedef struct _ImageInfo
{
	AsyncStruct *asyncStruct;
	CCImage		*image;
	CCImage::EImageFormat imageType;
} ImageInfo;

static pthread_t s_loadingThread;

static pthread_mutex_t		s_asyncStructQueueMutex;
static pthread_mutex_t      s_ImageInfoMutex;

static sem_t s_sem;
static bool need_quit;

static std::queue<AsyncStruct*>		*s_pAsyncStructQueue;
static std::queue<ImageInfo*>		*s_pImageQueue;

static CCImage::EImageFormat computeImageFormatType(string& filename)
{
	CCImage::EImageFormat ret = CCImage::kFmtUnKnown;

	if ((std::string::npos != filename.find(".jpg")) || (std::string::npos != filename.find(".jpeg")))
	{
		ret = CCImage::kFmtJpg;
	}
	else if ((std::string::npos != filename.find(".png")) || (std::string::npos != filename.find(".PNG")))
	{
		ret = CCImage::kFmtPng;
	}

	return ret;
}

static void* loadImage(void* data)
{
	// create autorelease pool for iOS
	CCThread thread;
	thread.createAutoreleasePool();

    AsyncStruct *pAsyncStruct = NULL;

	while (true)
	{
		// wait for rendering thread to ask for loading if s_pAsyncStructQueue is empty
		sem_wait(&s_sem);

		std::queue<AsyncStruct*> *pQueue = s_pAsyncStructQueue;

		pthread_mutex_lock(&s_asyncStructQueueMutex);// get async struct from queue
        if (pQueue->empty())
        {
            pthread_mutex_unlock(&s_asyncStructQueueMutex);
	if (need_quit)
		break;
	else
		continue;
        }
        else
        {
            pAsyncStruct = pQueue->front();
            pQueue->pop();
            pthread_mutex_unlock(&s_asyncStructQueueMutex);
        }		

		const char *filename = pAsyncStruct->filename.c_str();

		// compute image type
		CCImage::EImageFormat imageType = computeImageFormatType(pAsyncStruct->filename);
		if (imageType == CCImage::kFmtUnKnown)
		{
			CCLOG("unsupportted format %s",filename);
			delete pAsyncStruct;
			
			continue;
		}
		
        // generate image			
		CCImage *pImage = new CCImage();
		if (! pImage->initWithImageFileThreadSafe(filename, imageType))
		{
			delete pImage;
			CCLOG("can not load %s", filename);
			continue;
		}

		// generate image info
		ImageInfo *pImageInfo = new ImageInfo();
		pImageInfo->asyncStruct = pAsyncStruct;
		pImageInfo->image = pImage;
		pImageInfo->imageType = imageType;

		// put the image info into the queue
		pthread_mutex_lock(&s_ImageInfoMutex);
		s_pImageQueue->push(pImageInfo);
		pthread_mutex_unlock(&s_ImageInfoMutex);	
	}
	
	return 0;
}

// implementation CCTextureCache

// TextureCache - Alloc, Init & Dealloc
static CCTextureCache *g_sharedTextureCache;

CCTextureCache * CCTextureCache::sharedTextureCache()
{
	if (!g_sharedTextureCache)
		g_sharedTextureCache = new CCTextureCache();

	return g_sharedTextureCache;
}

CCTextureCache::CCTextureCache()
{
	CCAssert(g_sharedTextureCache == NULL, "Attempted to allocate a second instance of a singleton.");
	
	m_pTextures = new CCMutableDictionary<std::string, CCTexture2D*>();
}

CCTextureCache::~CCTextureCache()
{
	CCLOGINFO("cocos2d: deallocing CCTextureCache.");
	need_quit = true;
	sem_post(&s_sem);
	CC_SAFE_RELEASE(m_pTextures);
}

void CCTextureCache::purgeSharedTextureCache()
{
	CC_SAFE_RELEASE_NULL(g_sharedTextureCache);
}


char * CCTextureCache::description()
{
	char *ret = new char[100];
	sprintf(ret, "<CCTextureCache | Number of textures = %u>", m_pTextures->count());
	return ret;
}

void CCTextureCache::addImageAsync(const char *path, CCObject *target, SEL_CallFuncO selector)
{
	CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");	

	CCTexture2D *texture = NULL;

	// optimization

	std::string pathKey = path;
	CCFileUtils::ccRemoveHDSuffixFromFile(pathKey);

	pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
	texture = m_pTextures->objectForKey(pathKey);

	std::string fullpath = pathKey;
	if (texture != NULL)
	{
		if (target && selector)
		{
			(target->*selector)(texture);
		}
		
		return;
	}

	if (target)
	{
		target->retain();
	}

	// lazy init
	static bool firstRun = true;
	if (firstRun)
	{		     
        s_pAsyncStructQueue = new queue<AsyncStruct*>();
	    s_pImageQueue = new queue<ImageInfo*>();		

		pthread_mutex_init(&s_asyncStructQueueMutex, NULL);
		sem_init(&s_sem, 0, 0);
		pthread_mutex_init(&s_ImageInfoMutex, NULL);
		pthread_create(&s_loadingThread, NULL, loadImage, NULL);

		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(CCTextureCache::addImageAsyncCallBack), this, 0, false);
		need_quit = false;
		firstRun = false;
	}

	// generate async struct
	AsyncStruct *data = new AsyncStruct();
	data->filename = fullpath.c_str();
	data->target = target;
	data->selector = selector;

	// add async struct into queue
	pthread_mutex_lock(&s_asyncStructQueueMutex);
	s_pAsyncStructQueue->push(data);
	pthread_mutex_unlock(&s_asyncStructQueueMutex);

	sem_post(&s_sem);
}

void CCTextureCache::addImageAsyncCallBack(ccTime dt)
{
	// the image is generated in loading thread
	std::queue<ImageInfo*> *imagesQueue = s_pImageQueue;

	pthread_mutex_lock(&s_ImageInfoMutex);
	if (imagesQueue->empty())
	{
		pthread_mutex_unlock(&s_ImageInfoMutex);
	}
	else
	{
		ImageInfo *pImageInfo = imagesQueue->front();
		imagesQueue->pop();
		pthread_mutex_unlock(&s_ImageInfoMutex);

		AsyncStruct *pAsyncStruct = pImageInfo->asyncStruct;
		CCImage *pImage = pImageInfo->image;

		CCObject *target = pAsyncStruct->target;
		SEL_CallFuncO selector = pAsyncStruct->selector;
		const char* filename = pAsyncStruct->filename.c_str();

		// generate texture in render thread
		CCTexture2D *texture = new CCTexture2D();
		texture->initWithImage(pImage);

#if CC_ENABLE_CACHE_TEXTTURE_DATA
        // cache the texture file name
		if (pImageInfo->imageType == CCImage::kFmtJpg)
		{
			VolatileTexture::addImageTexture(texture, filename, CCImage::kFmtJpg);
		}
		else
		{
			VolatileTexture::addImageTexture(texture, filename, CCImage::kFmtPng);
		}
#endif

		// cache the texture
		m_pTextures->setObject(texture, filename);
		texture->autorelease();

		if (target && selector)
		{
			(target->*selector)(texture);
			target->release();
		}		

		delete pImage;
		delete pAsyncStruct;
		delete pImageInfo;
	}
}

CCTexture2D * CCTextureCache::addImage(const char * path)
{
	CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");

	CCTexture2D * texture = NULL;
	// Split up directory and filename
	// MUTEX:
	// Needed since addImageAsync calls this method from a different thread
	
	//pthread_mutex_lock(m_pDictLock);

	// remove possible -HD suffix to prevent caching the same image twice (issue #1040)
    std::string pathKey = path;
	CCFileUtils::ccRemoveHDSuffixFromFile(pathKey);

    pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
	texture = m_pTextures->objectForKey(pathKey);

    std::string fullpath = pathKey; // (CCFileUtils::fullPathFromRelativePath(path));
	if( ! texture ) 
	{
		std::string lowerCase(path);
		for (unsigned int i = 0; i < lowerCase.length(); ++i)
		{
			lowerCase[i] = tolower(lowerCase[i]);
		}
		// all images are handled by UIImage except PVR extension that is handled by our own handler
		do 
		{
			if (std::string::npos != lowerCase.find(".pvr"))
			{
				texture = this->addPVRImage(fullpath.c_str());
			}
			// Issue #886: TEMPORARY FIX FOR TRANSPARENT JPEGS IN IOS4
			else if (std::string::npos != lowerCase.find(".jpg") || std::string::npos != lowerCase.find(".jpeg"))
			{
				CCImage image;
                CCFileData data(fullpath.c_str(), "rb");
                unsigned long nSize  = data.getSize();
                unsigned char* pBuffer = data.getBuffer();
                CC_BREAK_IF(! image.initWithImageData((void*)pBuffer, nSize, CCImage::kFmtJpg));

				texture = new CCTexture2D();
				texture->initWithImage(&image);

				if( texture )
				{
#if CC_ENABLE_CACHE_TEXTTURE_DATA
                    // cache the texture file name
                    VolatileTexture::addImageTexture(texture, fullpath.c_str(), CCImage::kFmtJpg);
#endif

					m_pTextures->setObject(texture, pathKey);
					// autorelease prevents possible crash in multithreaded environments
					texture->autorelease();
				}
				else
				{
					CCLOG("cocos2d: Couldn't add image:%s in CCTextureCache", path);
				}
			}
			else
			{
				// prevents overloading the autorelease pool
				CCImage image;
                CCFileData data(fullpath.c_str(), "rb");
                unsigned long nSize  = data.getSize();
                unsigned char* pBuffer = data.getBuffer();
                CC_BREAK_IF(! image.initWithImageData((void*)pBuffer, nSize, CCImage::kFmtPng));

				texture = new CCTexture2D();
				texture->initWithImage(&image);

				if( texture )
				{
#if CC_ENABLE_CACHE_TEXTTURE_DATA
                    // cache the texture file name
                    VolatileTexture::addImageTexture(texture, fullpath.c_str(), CCImage::kFmtPng);
#endif

					m_pTextures->setObject(texture, pathKey);
					// autorelease prevents possible crash in multithreaded environments
					texture->autorelease();
				}
				else
				{
					CCLOG("cocos2d: Couldn't add image:%s in CCTextureCache", path);
				}
			}

		} while (0);
	}

	//pthread_mutex_unlock(m_pDictLock);
	return texture;
}

#ifdef CC_SUPPORT_PVRTC
CCTexture2D* CCTextureCache::addPVRTCImage(const char* path, int bpp, bool hasAlpha, int width)
{
	CCAssert(path != NULL, "TextureCache: fileimage MUST not be nill");
	CCAssert( bpp==2 || bpp==4, "TextureCache: bpp must be either 2 or 4");

	CCTexture2D * texture;

	std::string temp(path);
    CCFileUtils::ccRemoveHDSuffixFromFile(temp);
    
	if ( (texture = m_pTextures->objectForKey(temp)) )
	{
		return texture;
	}
	
	// Split up directory and filename
	std::string fullpath( CCFileUtils::fullPathFromRelativePath(path) );

	CCData * data = CCData::dataWithContentsOfFile(fullpath);
	texture = new CCTexture2D();
	
	if( texture->initWithPVRTCData(data->bytes(), 0, bpp, hasAlpha, width,
                                   (bpp==2 ? kCCTexture2DPixelFormat_PVRTC2 : kCCTexture2DPixelFormat_PVRTC4)))
	{
		m_pTextures->setObject(texture, temp);
		texture->autorelease();
	}
	else
	{
		CCLOG("cocos2d: Couldn't add PVRTCImage:%s in CCTextureCache",path);
	}
	CC_SAFE_DELETE(data);

	return texture;
}
#endif // CC_SUPPORT_PVRTC

CCTexture2D * CCTextureCache::addPVRImage(const char* path)
{
	CCAssert(path != NULL, "TextureCache: fileimage MUST not be nill");

	CCTexture2D * tex;
	std::string key(path);
    // remove possible -HD suffix to prevent caching the same image twice (issue #1040)
    CCFileUtils::ccRemoveHDSuffixFromFile(key);
    
	if( (tex = m_pTextures->objectForKey(key)) ) 
	{
		return tex;
	}

    // Split up directory and filename
    std::string fullpath = CCFileUtils::fullPathFromRelativePath(key.c_str());
	tex = new CCTexture2D();
	if( tex->initWithPVRFile(fullpath.c_str()) )
	{
#if CC_ENABLE_CACHE_TEXTTURE_DATA
        // cache the texture file name
        VolatileTexture::addImageTexture(tex, fullpath.c_str(), CCImage::kFmtRawData);
#endif
		m_pTextures->setObject(tex, key);
		tex->autorelease();
	}
	else
	{
		CCLOG("cocos2d: Couldn't add PVRImage:%s in CCTextureCache",key.c_str());
	}

	return tex;
}

CCTexture2D* CCTextureCache::addUIImage(CCImage *image, const char *key)
{
	CCAssert(image != NULL, "TextureCache: image MUST not be nill");

	CCTexture2D * texture = NULL;
	// textureForKey() use full path,so the key should be full path
	std::string forKey;
	if (key)
	{
		forKey = CCFileUtils::fullPathFromRelativePath(key);
	}

	// Don't have to lock here, because addImageAsync() will not 
	// invoke opengl function in loading thread.

	do 
	{
		// If key is nil, then create a new texture each time
		if(key && (texture = m_pTextures->objectForKey(forKey)))
		{
			break;
		}

		// prevents overloading the autorelease pool
		texture = new CCTexture2D();
		texture->initWithImage(image);

		if(key && texture)
		{
			m_pTextures->setObject(texture, forKey);
			texture->autorelease();
		}
		else
		{
			CCLOG("cocos2d: Couldn't add UIImage in CCTextureCache");
		}

	} while (0);

	return texture;
}

// TextureCache - Remove

void CCTextureCache::removeAllTextures()
{
	m_pTextures->removeAllObjects();
}

void CCTextureCache::removeUnusedTextures()
{
	std::vector<std::string> keys = m_pTextures->allKeys();
	std::vector<std::string>::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
	{
		CCTexture2D *value = m_pTextures->objectForKey(*it);
		if (value->retainCount() == 1)
		{
			CCLOG("cocos2d: CCTextureCache: removing unused texture: %s", (*it).c_str());
			m_pTextures->removeObjectForKey(*it);
		}
	}
}

void CCTextureCache::removeTexture(CCTexture2D* texture)
{
	if( ! texture )
		return;

	std::vector<std::string> keys = m_pTextures->allKeysForObject(texture);

	for (unsigned int i = 0; i < keys.size(); i++)
	{
		m_pTextures->removeObjectForKey(keys[i]);
	}
}

void CCTextureCache::removeTextureForKey(const char *textureKeyName)
{
	if (textureKeyName == NULL)
	{
		return;
	}

    string fullPath = CCFileUtils::fullPathFromRelativePath(textureKeyName);
	m_pTextures->removeObjectForKey(fullPath);
}

CCTexture2D* CCTextureCache::textureForKey(const char* key)
{
    std::string strKey = CCFileUtils::fullPathFromRelativePath(key);
	return m_pTextures->objectForKey(strKey);
}

void CCTextureCache::reloadAllTextures()
{
#if CC_ENABLE_CACHE_TEXTTURE_DATA
    VolatileTexture::reloadAllTextures();
#endif
}

void CCTextureCache::dumpCachedTextureInfo()
{
	unsigned int count = 0;
	unsigned int totalBytes = 0;

	vector<string> keys = m_pTextures->allKeys();
	vector<string>::iterator iter;
	for (iter = keys.begin(); iter != keys.end(); iter++)
	{
		CCTexture2D *tex = m_pTextures->objectForKey(*iter);
		unsigned int bpp = tex->bitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
		unsigned int bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
		totalBytes += bytes;
		count++;
		CCLOG("cocos2d: \"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB",
			   (*iter).c_str(),
			   (long)tex->retainCount(),
			   (long)tex->getName(),
			   (long)tex->getPixelsWide(),
			   (long)tex->getPixelsHigh(),
			   (long)bpp,
			   (long)bytes / 1024);
	}

	CCLOG("cocos2d: CCTextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
}

#if CC_ENABLE_CACHE_TEXTTURE_DATA

std::list<VolatileTexture*> VolatileTexture::textures;
bool VolatileTexture::isReloading = false;

VolatileTexture::VolatileTexture(CCTexture2D *t)
: texture(t)
, m_eCashedImageType(kInvalid)
, m_pTextureData(NULL)
, m_PixelFormat(kTexture2DPixelFormat_RGBA8888)
, m_strFileName("")
, m_FmtImage(CCImage::kFmtPng)
, m_alignment(CCTextAlignmentCenter)
, m_strFontName("")
, m_strText("")
, m_fFontSize(0.0f)
{
    m_size = CCSizeMake(0, 0);
    textures.push_back(this);
}

VolatileTexture::~VolatileTexture()
{
    textures.remove(this);
}

void VolatileTexture::addImageTexture(CCTexture2D *tt, const char* imageFileName, CCImage::EImageFormat format)
{
    if (isReloading)
        return;

    VolatileTexture *vt = 0;
    std::list<VolatileTexture *>::iterator i = textures.begin();
    while( i != textures.end() )
    {
        VolatileTexture *v = *i++;
        if (v->texture == tt) {
            vt = v;
            break;
        }
    }

    if (!vt)
        vt = new VolatileTexture(tt);

    vt->m_eCashedImageType = kImageFile;
    vt->m_strFileName = imageFileName;
    vt->m_FmtImage    = format;
    vt->m_PixelFormat = tt->getPixelFormat();
}

void VolatileTexture::addDataTexture(CCTexture2D *tt, void* data, CCTexture2DPixelFormat pixelFormat, const CCSize& contentSize)
{
	if (isReloading)
		return;

	VolatileTexture *vt = 0;
	std::list<VolatileTexture *>::iterator i = textures.begin();
	while( i != textures.end() )
	{
		VolatileTexture *v = *i++;
		if (v->texture == tt) {
			vt = v;
			break;
		}
	}

	if (!vt)
		vt = new VolatileTexture(tt);

	vt->m_eCashedImageType = kImageData;
	vt->m_pTextureData = data;
	vt->m_PixelFormat = pixelFormat;
	vt->m_TextureSize = contentSize;
}

void VolatileTexture::addStringTexture(CCTexture2D *tt, const char* text, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    if (isReloading)
        return;

    VolatileTexture *vt = 0;
    std::list<VolatileTexture *>::iterator i = textures.begin();
    while( i != textures.end() )
    {
        VolatileTexture *v = *i++;
        if (v->texture == tt) {
            vt = v;
            break;
        }
    }

    if (!vt)
        vt = new VolatileTexture(tt);

    vt->m_eCashedImageType = kString;
    vt->m_size        = dimensions;
    vt->m_strFontName = fontName;
    vt->m_alignment   = alignment;
    vt->m_fFontSize   = fontSize;
    vt->m_strText     = text;
}

void VolatileTexture::removeTexture(CCTexture2D *t) {

    std::list<VolatileTexture *>::iterator i = textures.begin();
    while( i != textures.end() )
    {
        VolatileTexture *vt = *i++;
        if (vt->texture == t) {
            delete vt;
            break;
        }
    }
}

void VolatileTexture::reloadAllTextures()
{
    isReloading = true;

    CCLOG("reload all texture");
    std::list<VolatileTexture *>::iterator i = textures.begin();

    while( i != textures.end() )
    {
        VolatileTexture *vt = *i++;

		switch (vt->m_eCashedImageType)
		{
        case kImageFile:
            {
                CCImage image;
                std::string lowerCase(vt->m_strFileName.c_str());
                for (unsigned int i = 0; i < lowerCase.length(); ++i)
                {
                    lowerCase[i] = tolower(lowerCase[i]);
                }

                if (std::string::npos != lowerCase.find(".pvr")) 
                {
                    CCTexture2DPixelFormat oldPixelFormat = CCTexture2D::defaultAlphaPixelFormat();
                    CCTexture2D::setDefaultAlphaPixelFormat(vt->m_PixelFormat);

                    vt->texture->initWithPVRFile(vt->m_strFileName.c_str());
                    CCTexture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                } 
                else 
                {
                    CCFileData data(vt->m_strFileName.c_str(), "rb");
                    unsigned long nSize  = data.getSize();
                    unsigned char* pBuffer = data.getBuffer();

                    if (image.initWithImageData((void*)pBuffer, nSize, vt->m_FmtImage))
                    {
                        CCTexture2DPixelFormat oldPixelFormat = CCTexture2D::defaultAlphaPixelFormat();
                        CCTexture2D::setDefaultAlphaPixelFormat(vt->m_PixelFormat);
                        vt->texture->initWithImage(&image);
                        CCTexture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                    }
                }
            }
            break;
		case kImageData:
			{
				unsigned int nPOTWide, nPOTHigh;
				nPOTWide = ccNextPOT((int)vt->m_TextureSize.width);
				nPOTHigh = ccNextPOT((int)vt->m_TextureSize.height);
				vt->texture->initWithData(vt->m_pTextureData, vt->m_PixelFormat, nPOTWide, nPOTHigh, vt->m_TextureSize);
			}
			break;
		case kString:
			{
				vt->texture->initWithString(vt->m_strText.c_str(),
					vt->m_size,
					vt->m_alignment,
					vt->m_strFontName.c_str(),
					vt->m_fFontSize);
			}
			break;
		default:
			break;
		}
    }

    isReloading = false;
}

#endif // CC_ENABLE_CACHE_TEXTTURE_DATA

}//namespace   cocos2d 

