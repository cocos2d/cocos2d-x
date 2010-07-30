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

#include <stack>
#include <string>
#include <cctype>
#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "cocoa/NSData.h"
#include "platform/platform.h"
#include "CCDirector.h"

/// @todo EAGLContext static EAGLContext *auxEAGLcontext = NULL;

class CCAsyncObject : NSObject
{
public:
	fpAsyncCallback m_pfnCallback;
	NSObject* m_pTarget;
	std::string *  m_pData;
public:
	CCAsyncObject();
	~CCAsyncObject()
	{
		CCLOGINFO("cocos2d: deallocing CCAsyncObject.");
		CCX_SAFE_DELETE(m_pTarget);
		CCX_SAFE_DELETE(m_pData);
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
	NSAssert(sharedTextureCache == NULL, "Attempted to allocate a second instance of a singleton.");
	
	m_pTextures = new NSMutableDictionary<std::string, CCTexture2D*>();
	m_pTextures->retain();
	m_pDictLock = new NSLock();
	m_pContextLock = new NSLock();
}

CCTextureCache::~CCTextureCache()
{
	CCLOG("cocos2d: deallocing CCTextureCache.");
/// @todo release
// 	[textures release];
// 	[dictLock release];
// 	[contextLock release];
// 	[auxEAGLcontext release];
// 	auxEAGLcontext = nil;
// 	sharedTextureCache = nil;
// 	[super dealloc];
}

void CCTextureCache::purgeSharedTextureCache()
{
	CCX_SAFE_RELEASE(g_sharedTextureCache);
}


std::string CCTextureCache::description()
{
	char des[100];
	sprintf_s(des, 100, "<CCTextureCache | Number of textures = %u>", m_pTextures->count());
	std::string ret(des);

	return ret;
}


// TextureCache - Add Images
void CCTextureCache::addImageWithAsyncObject(CCAsyncObject* async)
{
	/** @todo EAGLContext
	NSAutoreleasePool *autoreleasepool = [[NSAutoreleasePool alloc] init];

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

	[autoreleasepool release];*/
}

/** @todo selector, NSThread*/
void CCTextureCache::addImageAsync(const char* filename, NSObject *target, fpAsyncCallback func)
{
	NSAssert(filename != NULL , "TextureCache: fileimage MUST not be nill");

	// optimization

	CCTexture2D * tex;
// 
// 	if ( (tex = m_pTextures->objectForKey(filename)) )
// 	{
// 		target->
// 	}
// 	
// 	if( (tex=[textures objectForKey: filename] ) ) {
// 		[target performSelector:selector withObject:tex];
// 		return;
// 	}
// 
// 	// schedule the load
// 
// 	CCAsyncObject *asyncObject = [[CCAsyncObject alloc] init];
// 	asyncObject.selector = selector;
// 	asyncObject.target = target;
// 	asyncObject.data = filename;
// 
// 	[NSThread detachNewThreadSelector:@selector(addImageWithAsyncObject:) toTarget:self withObject:asyncObject];
// 	[asyncObject release];
}

CCTexture2D * CCTextureCache::addImage(const char * path)
{
	NSAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");

	CCTexture2D * tex = NULL;
	std::string temp(path);

	// MUTEX:
	// Needed since addImageAsync calls this method from a different thread
	
	m_pDictLock->lock();

	tex = m_pTextures->objectForKey(temp);

	if( ! tex ) {

		// Split up directory and filename
		std::string fullpath(CCFileUtils::fullPathFromRelativePath(path));

		// all images are handled by UIImage except PVR extension that is handled by our own handler
		// if ( [[path lowercaseString] hasSuffix:@".pvr"] )
		for (UINT32 i = 0; i < temp.length(); ++i)
			temp[i] = tolower(temp[i]);
		if (temp.find(".pvr"))
		{
			tex = this->addPVRTCImage(fullpath.c_str());
		}
		else
		{
			// prevents overloading the autorelease pool
			UIImage * image = new UIImage();

			NSAssert(image->initWithContentsOfFile(fullpath), "")
			tex = new CCTexture2D();
			tex->initWithImage(image);
			CCX_SAFE_DELETE(image);// image->release();

			if( tex )
				m_pTextures->setObject(tex, path);
			else
				CCLOG("cocos2d: Couldn't add image:%s in CCTextureCache", path);

			tex->release();
		}
	}

	m_pDictLock->uplock();

	return tex;
}

CCTexture2D* CCTextureCache::addPVRTCImage(const char* path, int bpp, bool hasAlpha, int width)
{
	
	NSAssert(path != NULL, "TextureCache: fileimage MUST not be nill");
	NSAssert( bpp==2 || bpp==4, "TextureCache: bpp must be either 2 or 4");

	CCTexture2D * tex;
	std::string temp(path);
	if ( (tex = m_pTextures->objectForKey(temp)) )
	{
		return tex;
	}
	
	// Split up directory and filename
	std::string fullpath( CCFileUtils::fullPathFromRelativePath(path) );

	NSData * data = NSData::dataWithContentsOfFile(fullpath);
	tex = new CCTexture2D();
	tex->initWithPVRTCData(data->bytes(), 0, bpp, hasAlpha, width);
	if( tex )
		m_pTextures->setObject(tex, temp);
	else
		CCLOG("cocos2d: Couldn't add PVRTCImage:%s in CCTextureCache",path);

	CCX_SAFE_DELETE(data);

	tex->autorelease();
	return tex;
}

CCTexture2D * CCTextureCache::addPVRTCImage(const char* fileimage)
{
	NSAssert(fileimage != NULL, "TextureCache: fileimage MUST not be nill");

	CCTexture2D * tex;
	std::string key(fileimage);
	if( (tex = m_pTextures->objectForKey(key)) ) 
	{
		return tex;
	}

	tex = new CCTexture2D();
	tex = tex->initWithPVRTCFile(fileimage);
	if( tex )
		m_pTextures-> setObject( tex, key);
	else
		CCLOG("cocos2d: Couldn't add PVRTCImage:%s in CCTextureCache",fileimage);	

	tex->autorelease();
	return tex;
}

/** @todo UIImage
-(CCTexture2D*) addCGImage: (CGImageRef) imageref forKey: (string & )key
{
	NSAssert(imageref != nil, @"TextureCache: image MUST not be nill");

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

// TextureCache - Remove

void CCTextureCache::removeAllTextures()
{
	m_pTextures->removeAllObjects();
}

void CCTextureCache::removeUnusedTextures()
{
	std::vector<std::string> keys = m_pTextures->allKeys();
	std::vector<std::string>::iterator it;
	for (it = keys.begin(); it <= keys.end(); it++)
	{
		CCTexture2D *value = m_pTextures->objectForKey(*it);
		if (value->retainCount() == 1)
		{
			CCLOG("cocos2d: CCTextureCache: removing unused texture: %s", (*it).c_str());
			m_pTextures->removeObjectForKey(*it);
		}
	}
}

void CCTextureCache::removeTexture(CCTexture2D* tex)
{
	if( ! tex )
		return;

	std::vector<std::string> keys = m_pTextures->allKeysForObject(tex);

	for (UINT32 i = 0; i < keys.size(); i++)
	{
		m_pTextures->removeObjectForKey(keys[i]);
	}
}

void CCTextureCache::removeTextureForKey(const std::string & textureKeyName)
{
	if( textureKeyName.empty() )
		return;

	m_pTextures->removeObjectForKey(textureKeyName);
}


