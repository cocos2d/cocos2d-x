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
#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "CCData.h"
#include "CCDirector.h"
#include "platform/platform.h"
#include "CCFileUtils.h"
#include "CCImage.h"
#include "support/ccUtils.h"

namespace   cocos2d {

class CCAsyncObject : CCObject
{
public:
	fpAsyncCallback m_pfnCallback;
	CCObject* m_pTarget;
	std::string *  m_pData;
public:
	CCAsyncObject();
	~CCAsyncObject()
	{
		CCLOGINFO("cocos2d: deallocing CCAsyncObject.");
		CC_SAFE_DELETE(m_pTarget);
		CC_SAFE_DELETE(m_pData);
	}
};

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
	m_pDictLock = new CCLock();
	m_pContextLock = new CCLock();
}

CCTextureCache::~CCTextureCache()
{
	CCLOGINFO("cocos2d: deallocing CCTextureCache.");

	CC_SAFE_RELEASE(m_pTextures);
	CC_SAFE_DELETE(m_pDictLock);
	CC_SAFE_DELETE(m_pContextLock);
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


// TextureCache - Add Images
/* @todo EAGLContext
void CCTextureCache::addImageWithAsyncObject(CCAsyncObject* async)
{
	
	CCAutoreleasePool *autoreleasepool = [[CCAutoreleasePool alloc] init];

	// textures will be created on the main OpenGL context
	// it seems that in SDK 2.2.x there can't be 2 threads creating textures at the same time
	// the lock is used for this purpose: issue #472
	[contextLock lock];
	if( auxEAGLcontext == nil ) {
		auxEAGLcontext = [[EAGLContext alloc]
initWithAPI:kEAGLRenderingAPIOpenGLES1
sharegroup:[[[[CCDirector sharedDirector] openGLView] context] sharegroup]];

		if( ! auxEAGLcontext )
			CCLOG(@"cocos2d: TextureCache: Could not create EAGL context");
	}

	if( [EAGLContext setCurrentContext:auxEAGLcontext] ) {

		// load / create the texture
		CCTexture2D *tex = [self addImage:async.data];

		// The callback will be executed on the main thread
		[async.target performSelectorOnMainThread:async.selector withObject:tex waitUntilDone:NO];

		[EAGLContext setCurrentContext:nil];
	} else {
		CCLOG(@"cocos2d: TetureCache: EAGLContext error");
	}
	[contextLock unlock];

	[autoreleasepool release];
}*/

/* @todo selector, NSThread
void CCTextureCache::addImageAsync(const char* filename, CCObject *target, fpAsyncCallback func)
{
	CCAssert(filename != NULL , "TextureCache: fileimage MUST not be nill");

	// optimization

	CCTexture2D * tex;
 
 	if ( (tex = m_pTextures->objectForKey(filename)) )

 	{

 		target->

 	}

 	
 	if( (tex=[textures objectForKey: filename] ) ) {
 		[target performSelector:selector withObject:tex];
 		return;
 	}
 
 	// schedule the load
 
 	CCAsyncObject *asyncObject = [[CCAsyncObject alloc] init];
 	asyncObject.selector = selector;
 	asyncObject.target = target;
 	asyncObject.data = filename;
 
 	[NSThread detachNewThreadSelector:@selector(addImageWithAsyncObject:) toTarget:self withObject:asyncObject];
 	[asyncObject release];
}*/

CCTexture2D * CCTextureCache::addImage(const char * path)
{
	CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");

	CCTexture2D * texture = NULL;
	// Split up directory and filename
	// MUTEX:
	// Needed since addImageAsync calls this method from a different thread
	
	m_pDictLock->lock();

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
	m_pDictLock->unlock();
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
		m_pTextures->setObject(tex, key);
		tex->autorelease();
	}
	else
	{
		CCLOG("cocos2d: Couldn't add PVRImage:%s in CCTextureCache",key.c_str());
	}

	return tex;
}

/* @todo CGImageRef
-(CCTexture2D*) addCGImage: (CGImageRef) imageref forKey: (string & )key
{
	CCAssert(imageref != nil, @"TextureCache: image MUST not be nill");

	CCTexture2D * tex = nil;

	// If key is nil, then create a new texture each time
	if( key && (tex=[textures objectForKey: key] ) ) {
		return tex;
	}

	// prevents overloading the autorelease pool
	UIImage *image = [[UIImage alloc] initWithCGImage:imageref];
	tex = [[CCTexture2D alloc] initWithImage: image];
	[image release];

	if(tex && key)
		[textures setObject: tex forKey:key];
	else
		CCLOG(@"cocos2d: Couldn't add CGImage in CCTextureCache");

	return [tex autorelease];
}*/
CCTexture2D* CCTextureCache::addUIImage(CCImage *image, const char *key)
{
	CCAssert(image != NULL && key != NULL, "TextureCache: image MUST not be nill");

	CCTexture2D * texture = NULL;
	std::string forKey = key;

	m_pDictLock->lock();

	do 
	{
		// If key is nil, then create a new texture each time
		if((texture = m_pTextures->objectForKey(forKey)))
		{
			break;
		}

		// prevents overloading the autorelease pool
		texture = new CCTexture2D();
		texture->initWithImage(image);

		if(texture)
		{
			m_pTextures->setObject(texture, forKey);
			texture->autorelease();
		}
		else
		{
			CCLOG("cocos2d: Couldn't add UIImage in CCTextureCache");
		}

	} while (0);
	
	m_pDictLock->unlock();

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
}

void VolatileTexture::addDataTexture(CCTexture2D *tt, void* data, CCTexture2DPixelFormat pixelFormat, CCSize contentSize)
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

void VolatileTexture::addStringTexture(CCTexture2D *tt, const char* text, CCSize dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
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
				CCFileData data(vt->m_strFileName.c_str(), "rb");
				unsigned long nSize  = data.getSize();
				unsigned char* pBuffer = data.getBuffer();

				if (image.initWithImageData((void*)pBuffer, nSize, vt->m_FmtImage))
				{
					vt->texture->initWithImage(&image);
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

