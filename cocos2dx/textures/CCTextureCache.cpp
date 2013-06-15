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

#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "platform/platform.h"
#include "platform/CCFileUtils.h"
#include "platform/CCThread.h"
#include "platform/CCImage.h"
#include "support/ccUtils.h"
#include "CCScheduler.h"
#include "cocoa/CCString.h"
#include <errno.h>
#include <stack>
#include <string>
#include <cctype>
#include <queue>
#include <list>
#include <pthread.h>

using namespace std;

NS_CC_BEGIN

typedef struct _AsyncStruct
{
    std::string            filename;
    CCObject    *target;
    SEL_CallFuncO        selector;
} AsyncStruct;

typedef struct _ImageInfo
{
    AsyncStruct *asyncStruct;
    CCImage        *image;
    CCImage::EImageFormat imageType;
} ImageInfo;

static pthread_t s_loadingThread;

static pthread_mutex_t		s_SleepMutex;
static pthread_cond_t		s_SleepCondition;

static pthread_mutex_t      s_asyncStructQueueMutex;
static pthread_mutex_t      s_ImageInfoMutex;

#ifdef EMSCRIPTEN
// Hack to get ASM.JS validation (no undefined symbols allowed).
#define pthread_cond_signal(_)
#endif // EMSCRIPTEN

static unsigned long s_nAsyncRefCount = 0;

static bool need_quit = false;

static std::queue<AsyncStruct*>* s_pAsyncStructQueue = NULL;
static std::queue<ImageInfo*>*   s_pImageQueue = NULL;

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
    else if ((std::string::npos != filename.find(".tiff")) || (std::string::npos != filename.find(".TIFF")))
    {
        ret = CCImage::kFmtTiff;
    }
    else if ((std::string::npos != filename.find(".webp")) || (std::string::npos != filename.find(".WEBP")))
    {
        ret = CCImage::kFmtWebp;
    }
   
    return ret;
}

static void* loadImage(void* data)
{
    AsyncStruct *pAsyncStruct = NULL;

    while (true)
    {
        // create autorelease pool for iOS
        CCThread thread;
        thread.createAutoreleasePool();

        std::queue<AsyncStruct*> *pQueue = s_pAsyncStructQueue;
        pthread_mutex_lock(&s_asyncStructQueueMutex);// get async struct from queue
        if (pQueue->empty())
        {
            pthread_mutex_unlock(&s_asyncStructQueueMutex);
            if (need_quit) {
                break;
            }
            else {
            	pthread_cond_wait(&s_SleepCondition, &s_SleepMutex);
                continue;
            }
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
            CCLOG("unsupported format %s",filename);
            delete pAsyncStruct;
            
            continue;
        }
        
        // generate image            
        CCImage *pImage = new CCImage();
        if (pImage && !pImage->initWithImageFileThreadSafe(filename, imageType))
        {
            CC_SAFE_RELEASE(pImage);
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
    
    if( s_pAsyncStructQueue != NULL )
    {
        delete s_pAsyncStructQueue;
        s_pAsyncStructQueue = NULL;
        delete s_pImageQueue;
        s_pImageQueue = NULL;

        pthread_mutex_destroy(&s_asyncStructQueueMutex);
        pthread_mutex_destroy(&s_ImageInfoMutex);
        pthread_mutex_destroy(&s_SleepMutex);
        pthread_cond_destroy(&s_SleepCondition);
    }
    
    return 0;
}

// implementation CCTextureCache

// TextureCache - Alloc, Init & Dealloc
static CCTextureCache *g_sharedTextureCache = NULL;

CCTextureCache * CCTextureCache::sharedTextureCache()
{
    if (!g_sharedTextureCache)
    {
        g_sharedTextureCache = new CCTextureCache();
    }
    return g_sharedTextureCache;
}

CCTextureCache::CCTextureCache()
{
    CCAssert(g_sharedTextureCache == NULL, "Attempted to allocate a second instance of a singleton.");
    
    _textures = new CCDictionary();
}

CCTextureCache::~CCTextureCache()
{
    CCLOGINFO("cocos2d: deallocing CCTextureCache: %p", this);
    need_quit = true;

    pthread_cond_signal(&s_SleepCondition);
    CC_SAFE_RELEASE(_textures);
}

void CCTextureCache::purgeSharedTextureCache()
{
    CC_SAFE_RELEASE_NULL(g_sharedTextureCache);
}

const char* CCTextureCache::description()
{
    return CCString::createWithFormat("<CCTextureCache | Number of textures = %u>", _textures->count())->getCString();
}

CCDictionary* CCTextureCache::snapshotTextures()
{ 
    CCDictionary* pRet = new CCDictionary();
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(_textures, pElement)
    {
        pRet->setObject(pElement->getObject(), pElement->getStrKey());
    }
    pRet->autorelease();
    return pRet;
}

void CCTextureCache::addImageAsync(const char *path, CCObject *target, SEL_CallFuncO selector)
{
#ifdef EMSCRIPTEN
    CCLOGWARN("Cannot load image %s asynchronously in Emscripten builds.", path);
    return;
#endif // EMSCRIPTEN

    CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");    

    CCTexture2D *texture = NULL;

    // optimization

    std::string pathKey = path;

    pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(pathKey.c_str());
    texture = (CCTexture2D*)_textures->objectForKey(pathKey.c_str());

    std::string fullpath = pathKey;
    if (texture != NULL)
    {
        if (target && selector)
        {
            (target->*selector)(texture);
        }
        
        return;
    }

    // lazy init
    if (s_pAsyncStructQueue == NULL)
    {             
        s_pAsyncStructQueue = new queue<AsyncStruct*>();
        s_pImageQueue = new queue<ImageInfo*>();        
        
        pthread_mutex_init(&s_asyncStructQueueMutex, NULL);
        pthread_mutex_init(&s_ImageInfoMutex, NULL);
        pthread_mutex_init(&s_SleepMutex, NULL);
        pthread_cond_init(&s_SleepCondition, NULL);
        pthread_create(&s_loadingThread, NULL, loadImage, NULL);

        need_quit = false;
    }

    if (0 == s_nAsyncRefCount)
    {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCTextureCache::addImageAsyncCallBack), this, 0, false);
    }

    ++s_nAsyncRefCount;

    if (target)
    {
        target->retain();
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

    pthread_cond_signal(&s_SleepCondition);
}

void CCTextureCache::addImageAsyncCallBack(float dt)
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
#if 0 //TODO: (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        texture->initWithImage(pImage, kCCResolutioniPhone);
#else
        texture->initWithImage(pImage);
#endif

#if CC_ENABLE_CACHE_TEXTURE_DATA
       // cache the texture file name
       VolatileTexture::addImageTexture(texture, filename, pImageInfo->imageType);
#endif

        // cache the texture
        _textures->setObject(texture, filename);
        texture->autorelease();

        if (target && selector)
        {
            (target->*selector)(texture);
            target->release();
        }        

        pImage->release();
        delete pAsyncStruct;
        delete pImageInfo;

        --s_nAsyncRefCount;
        if (0 == s_nAsyncRefCount)
        {
            CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCTextureCache::addImageAsyncCallBack), this);
        }
    }
}

CCTexture2D * CCTextureCache::addImage(const char * path)
{
    CCAssert(path != NULL, "TextureCache: fileimage MUST not be NULL");

    CCTexture2D * texture = NULL;
    CCImage* pImage = NULL;
    // Split up directory and filename
    // MUTEX:
    // Needed since addImageAsync calls this method from a different thread
    
    //pthread_mutex_lock(_dictLock);

    std::string pathKey = path;

    pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(pathKey.c_str());
    if (pathKey.size() == 0)
    {
        return NULL;
    }
    texture = (CCTexture2D*)_textures->objectForKey(pathKey.c_str());

    std::string fullpath = pathKey; // (CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path));
    if (! texture) 
    {
        std::string lowerCase(pathKey);
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
            else if (std::string::npos != lowerCase.find(".pkm"))
            {
                // ETC1 file format, only supportted on Android
                texture = this->addETCImage(fullpath.c_str());
            }
            else
            {
                CCImage::EImageFormat eImageFormat = CCImage::kFmtUnKnown;
                if (std::string::npos != lowerCase.find(".png"))
                {
                    eImageFormat = CCImage::kFmtPng;
                }
                else if (std::string::npos != lowerCase.find(".jpg") || std::string::npos != lowerCase.find(".jpeg"))
                {
                    eImageFormat = CCImage::kFmtJpg;
                }
                else if (std::string::npos != lowerCase.find(".tif") || std::string::npos != lowerCase.find(".tiff"))
                {
                    eImageFormat = CCImage::kFmtTiff;
                }
                else if (std::string::npos != lowerCase.find(".webp"))
                {
                    eImageFormat = CCImage::kFmtWebp;
                }
                
                pImage = new CCImage();
                CC_BREAK_IF(NULL == pImage);

                bool bRet = pImage->initWithImageFile(fullpath.c_str(), eImageFormat);
                CC_BREAK_IF(!bRet);

                texture = new CCTexture2D();
                
                if( texture &&
                    texture->initWithImage(pImage) )
                {
#if CC_ENABLE_CACHE_TEXTURE_DATA
                    // cache the texture file name
                    VolatileTexture::addImageTexture(texture, fullpath.c_str(), eImageFormat);
#endif
                    _textures->setObject(texture, pathKey.c_str());
                    texture->release();
                }
                else
                {
                    CCLOG("cocos2d: Couldn't create texture for file:%s in CCTextureCache", path);
                }
            }
        } while (0);
    }

    CC_SAFE_RELEASE(pImage);

    //pthread_mutex_unlock(_dictLock);
    return texture;
}

CCTexture2D * CCTextureCache::addPVRImage(const char* path)
{
    CCAssert(path != NULL, "TextureCache: fileimage MUST not be nil");

    CCTexture2D* texture = NULL;
    std::string key(path);
    
    if( (texture = (CCTexture2D*)_textures->objectForKey(key.c_str())) ) 
    {
        return texture;
    }

    // Split up directory and filename
    std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(key.c_str());
    texture = new CCTexture2D();
    if(texture != NULL && texture->initWithPVRFile(fullpath.c_str()) )
    {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        // cache the texture file name
        VolatileTexture::addImageTexture(texture, fullpath.c_str(), CCImage::kFmtRawData);
#endif
        _textures->setObject(texture, key.c_str());
        texture->autorelease();
    }
    else
    {
        CCLOG("cocos2d: Couldn't add PVRImage:%s in CCTextureCache",key.c_str());
        CC_SAFE_DELETE(texture);
    }

    return texture;
}

CCTexture2D* CCTextureCache::addETCImage(const char* path)
{
    CCAssert(path != NULL, "TextureCache: fileimage MUST not be nil");
    
    CCTexture2D* texture = NULL;
    std::string key(path);
    
    if( (texture = (CCTexture2D*)_textures->objectForKey(key.c_str())) )
    {
        return texture;
    }
    
    // Split up directory and filename
    std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(key.c_str());
    texture = new CCTexture2D();
    if(texture != NULL && texture->initWithETCFile(fullpath.c_str()))
    {
        _textures->setObject(texture, key.c_str());
        texture->autorelease();
    }
    else
    {
        CCLOG("cocos2d: Couldn't add ETCImage:%s in CCTextureCache",key.c_str());
        CC_SAFE_DELETE(texture);
    }
    
    return texture;
}

CCTexture2D* CCTextureCache::addUIImage(CCImage *image, const char *key)
{
    CCAssert(image != NULL, "TextureCache: image MUST not be nil");

    CCTexture2D * texture = NULL;
    // textureForKey() use full path,so the key should be full path
    std::string forKey;
    if (key)
    {
        forKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(key);
    }

    // Don't have to lock here, because addImageAsync() will not 
    // invoke opengl function in loading thread.

    do 
    {
        // If key is nil, then create a new texture each time
        if(key && (texture = (CCTexture2D *)_textures->objectForKey(forKey.c_str())))
        {
            break;
        }

        // prevents overloading the autorelease pool
        texture = new CCTexture2D();
        texture->initWithImage(image);

        if(key && texture)
        {
            _textures->setObject(texture, forKey.c_str());
            texture->autorelease();
        }
        else
        {
            CCLOG("cocos2d: Couldn't add UIImage in CCTextureCache");
        }

    } while (0);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTexture::addCCImage(texture, image);
#endif
    
    return texture;
}

// TextureCache - Remove

void CCTextureCache::removeAllTextures()
{
    _textures->removeAllObjects();
}

void CCTextureCache::removeUnusedTextures()
{
    /*
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(_textures, pElement)
    {
        CCLOG("cocos2d: CCTextureCache: texture: %s", pElement->getStrKey());
        CCTexture2D *value = (CCTexture2D*)pElement->getObject();
        if (value->retainCount() == 1)
        {
            CCLOG("cocos2d: CCTextureCache: removing unused texture: %s", pElement->getStrKey());
            _textures->removeObjectForElememt(pElement);
        }
    }
     */
    
    /** Inter engineer zhuoshi sun finds that this way will get better performance
     */    
    if (_textures->count())
    {   
        // find elements to be removed
        CCDictElement* pElement = NULL;
        list<CCDictElement*> elementToRemove;
        CCDICT_FOREACH(_textures, pElement)
        {
            CCLOG("cocos2d: CCTextureCache: texture: %s", pElement->getStrKey());
            CCTexture2D *value = (CCTexture2D*)pElement->getObject();
            if (value->retainCount() == 1)
            {
                elementToRemove.push_back(pElement);
            }
        }
        
        // remove elements
        for (list<CCDictElement*>::iterator iter = elementToRemove.begin(); iter != elementToRemove.end(); ++iter)
        {
            CCLOG("cocos2d: CCTextureCache: removing unused texture: %s", (*iter)->getStrKey());
            _textures->removeObjectForElememt(*iter);
        }
    }
}

void CCTextureCache::removeTexture(CCTexture2D* texture)
{
    if( ! texture )
    {
        return;
    }

    CCArray* keys = _textures->allKeysForObject(texture);
    _textures->removeObjectsForKeys(keys);
}

void CCTextureCache::removeTextureForKey(const char *textureKeyName)
{
    if (textureKeyName == NULL)
    {
        return;
    }

    string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(textureKeyName);
    _textures->removeObjectForKey(fullPath);
}

CCTexture2D* CCTextureCache::textureForKey(const char* key)
{
    return (CCTexture2D*)_textures->objectForKey(CCFileUtils::sharedFileUtils()->fullPathForFilename(key));
}

void CCTextureCache::reloadAllTextures()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTexture::reloadAllTextures();
#endif
}

void CCTextureCache::dumpCachedTextureInfo()
{
    unsigned int count = 0;
    unsigned int totalBytes = 0;

    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(_textures, pElement)
    {
        CCTexture2D* tex = (CCTexture2D*)pElement->getObject();
        unsigned int bpp = tex->bitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        unsigned int bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        CCLOG("cocos2d: \"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB",
               pElement->getStrKey(),
               (long)tex->retainCount(),
               (long)tex->getName(),
               (long)tex->getPixelsWide(),
               (long)tex->getPixelsHigh(),
               (long)bpp,
               (long)bytes / 1024);
    }

    CCLOG("cocos2d: CCTextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
}

#if CC_ENABLE_CACHE_TEXTURE_DATA

std::list<VolatileTexture*> VolatileTexture::textures;
bool VolatileTexture::isReloading = false;

VolatileTexture::VolatileTexture(CCTexture2D *t)
: texture(t)
, _cashedImageType(kInvalid)
, _textureData(NULL)
, _pixelFormat(kTexture2DPixelFormat_RGBA8888)
, _fileName("")
, _fmtImage(CCImage::kFmtPng)
, _alignment(kCCTextAlignmentCenter)
, _vAlignment(kCCVerticalTextAlignmentCenter)
, _fontName("")
, _text("")
, uiImage(NULL)
, _fontSize(0.0f)
{
    _size = CCSizeMake(0, 0);
    _texParams.minFilter = GL_LINEAR;
    _texParams.magFilter = GL_LINEAR;
    _texParams.wrapS = GL_CLAMP_TO_EDGE;
    _texParams.wrapT = GL_CLAMP_TO_EDGE;
    textures.push_back(this);
}

VolatileTexture::~VolatileTexture()
{
    textures.remove(this);
    CC_SAFE_RELEASE(uiImage);
}

void VolatileTexture::addImageTexture(CCTexture2D *tt, const char* imageFileName, CCImage::EImageFormat format)
{
    if (isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = kImageFile;
    vt->_fileName = imageFileName;
    vt->_fmtImage    = format;
    vt->_pixelFormat = tt->getPixelFormat();
}

void VolatileTexture::addCCImage(CCTexture2D *tt, CCImage *image)
{
    VolatileTexture *vt = findVolotileTexture(tt);
    image->retain();
    vt->uiImage = image;
    vt->_cashedImageType = kImage;
}

VolatileTexture* VolatileTexture::findVolotileTexture(CCTexture2D *tt)
{
    VolatileTexture *vt = 0;
    std::list<VolatileTexture *>::iterator i = textures.begin();
    while (i != textures.end())
    {
        VolatileTexture *v = *i++;
        if (v->texture == tt) 
        {
            vt = v;
            break;
        }
    }
    
    if (! vt)
    {
        vt = new VolatileTexture(tt);
    }
    
    return vt;
}

void VolatileTexture::addDataTexture(CCTexture2D *tt, void* data, CCTexture2DPixelFormat pixelFormat, const CCSize& contentSize)
{
    if (isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = kImageData;
    vt->_textureData = data;
    vt->_pixelFormat = pixelFormat;
    vt->_textureSize = contentSize;
}

void VolatileTexture::addStringTexture(CCTexture2D *tt, const char* text, const CCSize& dimensions, CCTextAlignment alignment, 
                                       CCVerticalTextAlignment vAlignment, const char *fontName, float fontSize)
{
    if (isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = kString;
    vt->_size        = dimensions;
    vt->_fontName = fontName;
    vt->_alignment   = alignment;
    vt->_vAlignment  = vAlignment;
    vt->_fontSize   = fontSize;
    vt->_text     = text;
}

void VolatileTexture::setTexParameters(CCTexture2D *t, ccTexParams *texParams) 
{
    VolatileTexture *vt = findVolotileTexture(t);

    if (texParams->minFilter != GL_NONE)
        vt->_texParams.minFilter = texParams->minFilter;
    if (texParams->magFilter != GL_NONE)
        vt->_texParams.magFilter = texParams->magFilter;
    if (texParams->wrapS != GL_NONE)
        vt->_texParams.wrapS = texParams->wrapS;
    if (texParams->wrapT != GL_NONE)
        vt->_texParams.wrapT = texParams->wrapT;
}

void VolatileTexture::removeTexture(CCTexture2D *t) 
{

    std::list<VolatileTexture *>::iterator i = textures.begin();
    while (i != textures.end())
    {
        VolatileTexture *vt = *i++;
        if (vt->texture == t) 
        {
            delete vt;
            break;
        }
    }
}

void VolatileTexture::reloadAllTextures()
{
    isReloading = true;

    CCLOG("reload all texture");
    std::list<VolatileTexture *>::iterator iter = textures.begin();

    while (iter != textures.end())
    {
        VolatileTexture *vt = *iter++;

        switch (vt->_cashedImageType)
        {
        case kImageFile:
            {
                std::string lowerCase(vt->_fileName.c_str());
                for (unsigned int i = 0; i < lowerCase.length(); ++i)
                {
                    lowerCase[i] = tolower(lowerCase[i]);
                }

                if (std::string::npos != lowerCase.find(".pvr")) 
                {
                    CCTexture2DPixelFormat oldPixelFormat = CCTexture2D::defaultAlphaPixelFormat();
                    CCTexture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);

                    vt->texture->initWithPVRFile(vt->_fileName.c_str());
                    CCTexture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                } 
                else 
                {
                    CCImage* pImage = new CCImage();
                    unsigned long nSize = 0;
                    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(vt->_fileName.c_str(), "rb", &nSize);

                    if (pImage && pImage->initWithImageData((void*)pBuffer, nSize, vt->_fmtImage))
                    {
                        CCTexture2DPixelFormat oldPixelFormat = CCTexture2D::defaultAlphaPixelFormat();
                        CCTexture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);
                        vt->texture->initWithImage(pImage);
                        CCTexture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                    }

                    CC_SAFE_DELETE_ARRAY(pBuffer);
                    CC_SAFE_RELEASE(pImage);
                }
            }
            break;
        case kImageData:
            {
                vt->texture->initWithData(vt->_textureData, 
                                          vt->_pixelFormat, 
                                          vt->_textureSize.width, 
                                          vt->_textureSize.height, 
                                          vt->_textureSize);
            }
            break;
        case kString:
            {
                vt->texture->initWithString(vt->_text.c_str(),
                                            vt->_fontName.c_str(),
                                            vt->_fontSize,
                                            vt->_size,
                                            vt->_alignment,
                                            vt->_vAlignment
                                            );
            }
            break;
        case kImage:
            {
                vt->texture->initWithImage(vt->uiImage);
            }
            break;
        default:
            break;
        }
        vt->texture->setTexParameters(&vt->_texParams);
    }

    isReloading = false;
}

#endif // CC_ENABLE_CACHE_TEXTURE_DATA

NS_CC_END

