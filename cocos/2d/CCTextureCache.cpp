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

#include <errno.h>
#include <stack>
#include <cctype>
#include <list>

#include "CCTextureCache.h"
#include "CCTexture2D.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "platform/CCFileUtils.h"
#include "platform/CCThread.h"
#include "ccUtils.h"
#include "CCScheduler.h"
#include "CCString.h"


#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include "platform/emscripten/CCTextureCacheEmscripten.h"
#endif // EMSCRIPTEN

using namespace std;

NS_CC_BEGIN

// implementation TextureCache

TextureCache * TextureCache::getInstance()
{
    return Director::getInstance()->getTextureCache();
}

TextureCache::TextureCache()
: _loadingThread(nullptr)
, _asyncStructQueue(nullptr)
, _imageInfoQueue(nullptr)
, _needQuit(false)
, _asyncRefCount(0)
{
}

TextureCache::~TextureCache()
{
    CCLOGINFO("deallocing TextureCache: %p", this);

    for( auto it=_textures.begin(); it!=_textures.end(); ++it)
        (it->second)->release();

    CC_SAFE_DELETE(_loadingThread);
}

void TextureCache::destroyInstance()
{
}

TextureCache * TextureCache::sharedTextureCache() 
{
    return Director::getInstance()->getTextureCache();
}

void TextureCache::purgeSharedTextureCache() 
{ 
}

const char* TextureCache::description() const
{
    return String::createWithFormat("<TextureCache | Number of textures = %lu>", _textures.size() )->getCString();
}

//Dictionary* TextureCache::snapshotTextures()
//{ 
//    Dictionary* pRet = new Dictionary();
//    DictElement* pElement = NULL;
//    CCDICT_FOREACH(_textures, pElement)
//    {
//        pRet->setObject(pElement->getObject(), pElement->getStrKey());
//    }
//    pRet->autorelease();
//    return pRet;
//}

void TextureCache::addImageAsync(const std::string &path, Object *target, SEL_CallFuncO selector)
{
    Texture2D *texture = NULL;

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path.c_str());

    auto it = _textures.find(fullpath);
    if( it != _textures.end() )
        texture = it->second;

    if (texture != NULL && target && selector)
    {
        (target->*selector)(texture);
        return;
    }

    // lazy init
    if (_asyncStructQueue == NULL)
    {             
        _asyncStructQueue = new queue<AsyncStruct*>();
        _imageInfoQueue   = new queue<ImageInfo*>();        

        // create a new thread to load images
        _loadingThread = new std::thread(&TextureCache::loadImage, this);

        _needQuit = false;
    }

    if (0 == _asyncRefCount)
    {
        Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(TextureCache::addImageAsyncCallBack), this, 0, false);
    }

    ++_asyncRefCount;

    if (target)
    {
        target->retain();
    }

    // generate async struct
    AsyncStruct *data = new AsyncStruct(fullpath, target, selector);

    // add async struct into queue
    _asyncStructQueueMutex.lock();
    _asyncStructQueue->push(data);
    _asyncStructQueueMutex.unlock();

    _sleepCondition.notify_one();
}

void TextureCache::loadImage()
{
    AsyncStruct *asyncStruct = nullptr;

    while (true)
    {
        // create autorelease pool for iOS
        Thread thread;
        thread.createAutoreleasePool();

        std::queue<AsyncStruct*> *pQueue = _asyncStructQueue;
        _asyncStructQueueMutex.lock();
        if (pQueue->empty())
        {
            _asyncStructQueueMutex.unlock();
            if (_needQuit) {
                break;
            }
            else {
                std::unique_lock<std::mutex> lk(_sleepMutex);
                _sleepCondition.wait(lk);
                continue;
            }
        }
        else
        {
            asyncStruct = pQueue->front();
            pQueue->pop();
            _asyncStructQueueMutex.unlock();
        }        

        const char *filename = asyncStruct->filename.c_str();
        
        // generate image            
        Image *image = new Image();
        if (image && !image->initWithImageFileThreadSafe(filename))
        {
            CC_SAFE_RELEASE(image);
            CCLOG("can not load %s", filename);
            continue;
        }

        // generate image info
        ImageInfo *imageInfo = new ImageInfo();
        imageInfo->asyncStruct = asyncStruct;
        imageInfo->image = image;

        // put the image info into the queue
        _imageInfoMutex.lock();
        _imageInfoQueue->push(imageInfo);
        _imageInfoMutex.unlock();
    }
    
	if(_asyncStructQueue != nullptr)
    {
        delete _asyncStructQueue;
	    _asyncStructQueue = nullptr;
        delete _imageInfoQueue;
	    _imageInfoQueue = nullptr;
    }
}

void TextureCache::addImageAsyncCallBack(float dt)
{
    // the image is generated in loading thread
    std::queue<ImageInfo*> *imagesQueue = _imageInfoQueue;

    _imageInfoMutex.lock();
    if (imagesQueue->empty())
    {
        _imageInfoMutex.unlock();
    }
    else
    {
        ImageInfo *imageInfo = imagesQueue->front();
        imagesQueue->pop();
        _imageInfoMutex.unlock();

        AsyncStruct *asyncStruct = imageInfo->asyncStruct;
        Image *image = imageInfo->image;

        Object *target = asyncStruct->target;
        SEL_CallFuncO selector = asyncStruct->selector;
        const char* filename = asyncStruct->filename.c_str();

        // generate texture in render thread
        Texture2D *texture = new Texture2D();

        texture->initWithImage(image);

#if CC_ENABLE_CACHE_TEXTURE_DATA
       // cache the texture file name
       VolatileTextureMgr::addImageTexture(texture, filename);
#endif
        // cache the texture. retain it, since it is added in the map
        _textures.insert( std::make_pair(filename, texture) );
        texture->retain();

        texture->autorelease();

        if (target && selector)
        {
            (target->*selector)(texture);
            target->release();
        }        

        image->release();
        delete asyncStruct;
        delete imageInfo;

        --_asyncRefCount;
        if (0 == _asyncRefCount)
        {
            Director::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(TextureCache::addImageAsyncCallBack), this);
        }
    }
}

Texture2D * TextureCache::addImage(const std::string &path)
{
    Texture2D * texture = NULL;
    Image* image = NULL;
    // Split up directory and filename
    // MUTEX:
    // Needed since addImageAsync calls this method from a different thread

    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path.c_str());
    if (fullpath.size() == 0)
    {
        return NULL;
    }
    auto it = _textures.find(fullpath);
    if( it != _textures.end() )
        texture = it->second;

    if (! texture)
    {
        // all images are handled by UIImage except PVR extension that is handled by our own handler
        do 
        {
            image = new Image();
            CC_BREAK_IF(NULL == image);

            bool bRet = image->initWithImageFile(fullpath.c_str());
            CC_BREAK_IF(!bRet);

            texture = new Texture2D();

            if( texture && texture->initWithImage(image) )
            {
#if CC_ENABLE_CACHE_TEXTURE_DATA
                // cache the texture file name
                VolatileTextureMgr::addImageTexture(texture, fullpath.c_str());
#endif
                // texture already retained, no need to re-retain it
                _textures.insert( std::make_pair(fullpath, texture) );
            }
            else
            {
                CCLOG("cocos2d: Couldn't create texture for file:%s in TextureCache", path.c_str());
            }
        } while (0);
    }

    CC_SAFE_RELEASE(image);

    return texture;
}

Texture2D* TextureCache::addImage(Image *image, const std::string &key)
{
    CCASSERT(image != NULL, "TextureCache: image MUST not be nil");

    Texture2D * texture = NULL;

    do
    {
        auto it = _textures.find(key);
        if( it != _textures.end() ) {
            texture = it->second;
            break;
        }

        // prevents overloading the autorelease pool
        texture = new Texture2D();
        texture->initWithImage(image);

        if(texture)
        {
            _textures.insert( std::make_pair(key, texture) );
            texture->retain();

            texture->autorelease();
        }
        else
        {
            CCLOG("cocos2d: Couldn't add UIImage in TextureCache");
        }

    } while (0);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTextureMgr::addImage(texture, image);
#endif
    
    return texture;
}

// TextureCache - Remove

void TextureCache::removeAllTextures()
{
    for( auto it=_textures.begin(); it!=_textures.end(); ++it ) {
        (it->second)->release();
    }
    _textures.clear();
}

void TextureCache::removeUnusedTextures()
{
    for( auto it=_textures.cbegin(); it!=_textures.cend(); /* nothing */) {
        Texture2D *tex = it->second;
        if( tex->retainCount() == 1 ) {
            CCLOG("cocos2d: TextureCache: removing unused texture: %s", it->first.c_str());

            tex->release();
            _textures.erase(it++);
        } else {
            ++it;
        }

    }
}

void TextureCache::removeTexture(Texture2D* texture)
{
    if( ! texture )
    {
        return;
    }

    for( auto it=_textures.cbegin(); it!=_textures.cend(); /* nothing */ ) {
        if( it->second == texture ) {
            texture->release();
            _textures.erase(it++);
            break;
        } else
            ++it;
    }
}

void TextureCache::removeTextureForKey(const std::string &textureKeyName)
{
    auto it = _textures.find(textureKeyName);
    if( it != _textures.end() ) {
        (it->second)->release();
        _textures.erase(it);
    }
}

Texture2D* TextureCache::getTextureForKey(const std::string &key) const
{
    auto it = _textures.find(key);
    if( it != _textures.end() )
        return it->second;
    return NULL;
}

void TextureCache::reloadAllTextures()
{
//will do nothing
// #if CC_ENABLE_CACHE_TEXTURE_DATA
//     VolatileTextureMgr::reloadAllTextures();
// #endif
}

void TextureCache::waitForQuit()
{
    // notify sub thread to quick
    _needQuit = true;
    _sleepCondition.notify_one();
    if (_loadingThread) _loadingThread->join();
}

void TextureCache::dumpCachedTextureInfo() const
{
    unsigned int count = 0;
    unsigned int totalBytes = 0;

    for( auto it = _textures.begin(); it != _textures.end(); ++it ) {

        Texture2D* tex = it->second;
        unsigned int bpp = tex->getBitsPerPixelForFormat();
        // Each texture takes up width * height * bytesPerPixel bytes.
        long bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
        totalBytes += bytes;
        count++;
        log("cocos2d: \"%s\" rc=%lu id=%lu %lu x %lu @ %ld bpp => %lu KB",
               it->first.c_str(),
               (long)tex->retainCount(),
               (long)tex->getName(),
               (long)tex->getPixelsWide(),
               (long)tex->getPixelsHigh(),
               (long)bpp,
               (long)bytes / 1024);
    }

    log("cocos2d: TextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
}

#if CC_ENABLE_CACHE_TEXTURE_DATA

std::list<VolatileTexture*> VolatileTextureMgr::_textures;
bool VolatileTextureMgr::_isReloading = false;

VolatileTexture::VolatileTexture(Texture2D *t)
: _texture(t)
, _cashedImageType(kInvalid)
, _textureData(NULL)
, _pixelFormat(Texture2D::PixelFormat::RGBA8888)
, _fileName("")
, _text("")
, _uiImage(NULL)
{
    _texParams.minFilter = GL_LINEAR;
    _texParams.magFilter = GL_LINEAR;
    _texParams.wrapS = GL_CLAMP_TO_EDGE;
    _texParams.wrapT = GL_CLAMP_TO_EDGE;
}

VolatileTexture::~VolatileTexture()
{
    CC_SAFE_RELEASE(_uiImage);
}

void VolatileTextureMgr::addImageTexture(Texture2D *tt, const char* imageFileName)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kImageFile;
    vt->_fileName = imageFileName;
    vt->_pixelFormat = tt->getPixelFormat();
}

void VolatileTextureMgr::addImage(Texture2D *tt, Image *image)
{
    VolatileTexture *vt = findVolotileTexture(tt);
    image->retain();
    vt->_uiImage = image;
    vt->_cashedImageType = VolatileTexture::kImage;
}

VolatileTexture* VolatileTextureMgr::findVolotileTexture(Texture2D *tt)
{
    VolatileTexture *vt = 0;
    auto i = _textures.begin();
    while (i != _textures.end())
    {
        VolatileTexture *v = *i++;
        if (v->_texture == tt)
        {
            vt = v;
            break;
        }
    }
    
    if (! vt)
    {
        vt = new VolatileTexture(tt);
        _textures.push_back(vt);
    }
    
    return vt;
}

void VolatileTextureMgr::addDataTexture(Texture2D *tt, void* data, int dataLen, Texture2D::PixelFormat pixelFormat, const Size& contentSize)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kImageData;
    vt->_textureData = data;
    vt->_dataLen = dataLen;
    vt->_pixelFormat = pixelFormat;
    vt->_textureSize = contentSize;
}

void VolatileTextureMgr::addStringTexture(Texture2D *tt, const char* text, const FontDefinition& fontDefinition)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = VolatileTexture::kString;
    vt->_text     = text;
    vt->_fontDefinition = fontDefinition;
}

void VolatileTextureMgr::setTexParameters(Texture2D *t, const Texture2D::TexParams &texParams)
{
    VolatileTexture *vt = findVolotileTexture(t);

    if (texParams.minFilter != GL_NONE)
        vt->_texParams.minFilter = texParams.minFilter;
    if (texParams.magFilter != GL_NONE)
        vt->_texParams.magFilter = texParams.magFilter;
    if (texParams.wrapS != GL_NONE)
        vt->_texParams.wrapS = texParams.wrapS;
    if (texParams.wrapT != GL_NONE)
        vt->_texParams.wrapT = texParams.wrapT;
}

void VolatileTextureMgr::removeTexture(Texture2D *t) 
{
    auto i = _textures.begin();
    while (i != _textures.end())
    {
        VolatileTexture *vt = *i++;
        if (vt->_texture == t) 
        {
            _textures.remove(vt);
            delete vt;
            break;
        }
    }
}

void VolatileTextureMgr::reloadAllTextures()
{
    _isReloading = true;

    CCLOG("reload all texture");
    auto iter = _textures.begin();

    while (iter != _textures.end())
    {
        VolatileTexture *vt = *iter++;

        switch (vt->_cashedImageType)
        {
        case VolatileTexture::kImageFile:
            {
                Image* image = new Image();
                long size = 0;
                unsigned char* pBuffer = FileUtils::getInstance()->getFileData(vt->_fileName.c_str(), "rb", &size);
                
                if (image && image->initWithImageData(pBuffer, size))
                {
                    Texture2D::PixelFormat oldPixelFormat = Texture2D::getDefaultAlphaPixelFormat();
                    Texture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);
                    vt->_texture->initWithImage(image);
                    Texture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                }
                
                free(pBuffer);
                CC_SAFE_RELEASE(image);
            }
            break;
        case VolatileTexture::kImageData:
            {
                vt->_texture->initWithData(vt->_textureData,
                                           vt->_dataLen,
                                          vt->_pixelFormat, 
                                          vt->_textureSize.width, 
                                          vt->_textureSize.height, 
                                          vt->_textureSize);
            }
            break;
        case VolatileTexture::kString:
            {
                vt->_texture->initWithString(vt->_text.c_str(), vt->_fontDefinition);
            }
            break;
        case VolatileTexture::kImage:
            {
                vt->_texture->initWithImage(vt->_uiImage);
            }
            break;
        default:
            break;
        }
        vt->_texture->setTexParameters(vt->_texParams);
    }

    _isReloading = false;
}

#endif // CC_ENABLE_CACHE_TEXTURE_DATA

NS_CC_END

