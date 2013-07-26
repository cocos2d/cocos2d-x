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
#include "support/ccUtils.h"
#include "CCScheduler.h"
#include "cocoa/CCString.h"


#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include "platform/emscripten/CCTextureCacheEmscripten.h"
#endif // EMSCRIPTEN

using namespace std;

NS_CC_BEGIN

// implementation TextureCache

TextureCache* TextureCache::_sharedTextureCache = nullptr;

TextureCache * TextureCache::getInstance()
{
    if (!_sharedTextureCache)
    {
#ifdef EMSCRIPTEN
        _sharedTextureCache = new TextureCacheEmscripten();
#else
        _sharedTextureCache = new TextureCache();
#endif // EMSCRIPTEN
    }
    return _sharedTextureCache;
}

TextureCache::TextureCache()
: _loadingThread(nullptr)
, _asyncStructQueue(nullptr)
, _imageInfoQueue(nullptr)
, _needQuit(false)
, _asyncRefCount(0)
, _textures(new Dictionary())
{
    CCASSERT(_sharedTextureCache == nullptr, "Attempted to allocate a second instance of a singleton.");
}

TextureCache::~TextureCache()
{
    CCLOGINFO("cocos2d: deallocing TextureCache: %p", this);

    CC_SAFE_RELEASE(_textures);

    CC_SAFE_DELETE(_loadingThread);
    _sharedTextureCache = nullptr;
}

void TextureCache::destroyInstance()
{
    // notify sub thread to quick
    _sharedTextureCache->_needQuit = true;
    _sharedTextureCache->_sleepCondition.notify_one();
    if (_sharedTextureCache->_loadingThread) _sharedTextureCache->_loadingThread->join();

    CC_SAFE_RELEASE_NULL(_sharedTextureCache);
}

const char* TextureCache::description() const
{
    return String::createWithFormat("<TextureCache | Number of textures = %u>", _textures->count())->getCString();
}

Dictionary* TextureCache::snapshotTextures()
{ 
    Dictionary* pRet = new Dictionary();
    DictElement* pElement = NULL;
    CCDICT_FOREACH(_textures, pElement)
    {
        pRet->setObject(pElement->getObject(), pElement->getStrKey());
    }
    pRet->autorelease();
    return pRet;
}

void TextureCache::addImageAsync(const char *path, Object *target, SEL_CallFuncO selector)
{
    CCASSERT(path != NULL, "TextureCache: fileimage MUST not be NULL");    

    Texture2D *texture = NULL;

    // optimization

    std::string pathKey = path;

    pathKey = FileUtils::getInstance()->fullPathForFilename(pathKey.c_str());
    texture = static_cast<Texture2D*>(_textures->objectForKey(pathKey.c_str()));

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
    if (_asyncStructQueue == NULL)
    {             
        _asyncStructQueue = new queue<AsyncStruct*>();
        _imageInfoQueue = new queue<ImageInfo*>();        

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
    AsyncStruct *pAsyncStruct = nullptr;

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
            pAsyncStruct = pQueue->front();
            pQueue->pop();
            _asyncStructQueueMutex.unlock();
        }        

        const char *filename = pAsyncStruct->filename.c_str();

        // compute image type
        Image::Format imageType = computeImageFormatType(pAsyncStruct->filename);
        if (imageType == Image::Format::UNKOWN)
        {
            CCLOG("unsupported format %s",filename);
            delete pAsyncStruct;
            
            continue;
        }
        
        // generate image            
        Image *pImage = new Image();
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
        _imageInfoMutex.lock();
        _imageInfoQueue->push(pImageInfo);
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

Image::Format TextureCache::computeImageFormatType(string& filename)
{
    Image::Format ret = Image::Format::UNKOWN;

    if ((std::string::npos != filename.find(".jpg")) || (std::string::npos != filename.find(".jpeg")))
    {
        ret = Image::Format::JPG;
    }
    else if ((std::string::npos != filename.find(".png")) || (std::string::npos != filename.find(".PNG")))
    {
        ret = Image::Format::PNG;
    }
    else if ((std::string::npos != filename.find(".tiff")) || (std::string::npos != filename.find(".TIFF")))
    {
        ret = Image::Format::TIFF;
    }
    else if ((std::string::npos != filename.find(".webp")) || (std::string::npos != filename.find(".WEBP")))
    {
        ret = Image::Format::WEBP;
    }
   
    return ret;
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
        ImageInfo *pImageInfo = imagesQueue->front();
        imagesQueue->pop();
        _imageInfoMutex.unlock();

        AsyncStruct *pAsyncStruct = pImageInfo->asyncStruct;
        Image *pImage = pImageInfo->image;

        Object *target = pAsyncStruct->target;
        SEL_CallFuncO selector = pAsyncStruct->selector;
        const char* filename = pAsyncStruct->filename.c_str();

        // generate texture in render thread
        Texture2D *texture = new Texture2D();

        texture->initWithImage(pImage);

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

        --_asyncRefCount;
        if (0 == _asyncRefCount)
        {
            Director::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(TextureCache::addImageAsyncCallBack), this);
        }
    }
}

Texture2D * TextureCache::addImage(const char * path)
{
    CCASSERT(path != NULL, "TextureCache: fileimage MUST not be NULL");

    Texture2D * texture = NULL;
    Image* pImage = NULL;
    // Split up directory and filename
    // MUTEX:
    // Needed since addImageAsync calls this method from a different thread

    std::string pathKey = path;

    pathKey = FileUtils::getInstance()->fullPathForFilename(pathKey.c_str());
    if (pathKey.size() == 0)
    {
        return NULL;
    }
    texture = static_cast<Texture2D*>(_textures->objectForKey(pathKey.c_str()));

    std::string fullpath = pathKey;
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
                Image::Format eImageFormat = Image::Format::UNKOWN;
                if (std::string::npos != lowerCase.find(".png"))
                {
                    eImageFormat = Image::Format::PNG;
                }
                else if (std::string::npos != lowerCase.find(".jpg") || std::string::npos != lowerCase.find(".jpeg"))
                {
                    eImageFormat = Image::Format::JPG;
                }
                else if (std::string::npos != lowerCase.find(".tif") || std::string::npos != lowerCase.find(".tiff"))
                {
                    eImageFormat = Image::Format::TIFF;
                }
                else if (std::string::npos != lowerCase.find(".webp"))
                {
                    eImageFormat = Image::Format::WEBP;
                }
                
                pImage = new Image();
                CC_BREAK_IF(NULL == pImage);

                bool bRet = pImage->initWithImageFile(fullpath.c_str(), eImageFormat);
                CC_BREAK_IF(!bRet);

                texture = new Texture2D();
                
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
                    CCLOG("cocos2d: Couldn't create texture for file:%s in TextureCache", path);
                }
            }
        } while (0);
    }

    CC_SAFE_RELEASE(pImage);

    return texture;
}

Texture2D * TextureCache::addPVRImage(const char* path)
{
    CCASSERT(path != NULL, "TextureCache: fileimage MUST not be nil");

    Texture2D* texture = NULL;
    std::string key(path);
    
    if( (texture = (Texture2D*)_textures->objectForKey(key.c_str())) ) 
    {
        return texture;
    }

    // Split up directory and filename
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(key.c_str());
    texture = new Texture2D();
    if(texture != NULL && texture->initWithPVRFile(fullpath.c_str()) )
    {
#if CC_ENABLE_CACHE_TEXTURE_DATA
        // cache the texture file name
        VolatileTexture::addImageTexture(texture, fullpath.c_str(), Image::Format::RAW_DATA);
#endif
        _textures->setObject(texture, key.c_str());
        texture->autorelease();
    }
    else
    {
        CCLOG("cocos2d: Couldn't add PVRImage:%s in TextureCache",key.c_str());
        CC_SAFE_DELETE(texture);
    }

    return texture;
}

Texture2D* TextureCache::addETCImage(const char* path)
{
    CCASSERT(path != NULL, "TextureCache: fileimage MUST not be nil");
    
    Texture2D* texture = NULL;
    std::string key(path);
    
    if( (texture = (Texture2D*)_textures->objectForKey(key.c_str())) )
    {
        return texture;
    }
    
    // Split up directory and filename
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename(key.c_str());
    texture = new Texture2D();
    if(texture != NULL && texture->initWithETCFile(fullpath.c_str()))
    {
        _textures->setObject(texture, key.c_str());
        texture->autorelease();
    }
    else
    {
        CCLOG("cocos2d: Couldn't add ETCImage:%s in TextureCache",key.c_str());
        CC_SAFE_DELETE(texture);
    }
    
    return texture;
}

Texture2D* TextureCache::addUIImage(Image *image, const char *key)
{
    CCASSERT(image != NULL, "TextureCache: image MUST not be nil");

    Texture2D * texture = NULL;
    // textureForKey() use full path,so the key should be full path
    std::string forKey;
    if (key)
    {
        forKey = FileUtils::getInstance()->fullPathForFilename(key);
    }

    // Don't have to lock here, because addImageAsync() will not 
    // invoke opengl function in loading thread.

    do 
    {
        // If key is nil, then create a new texture each time
        if(key && (texture = (Texture2D *)_textures->objectForKey(forKey.c_str())))
        {
            break;
        }

        // prevents overloading the autorelease pool
        texture = new Texture2D();
        texture->initWithImage(image);

        if(key && texture)
        {
            _textures->setObject(texture, forKey.c_str());
            texture->autorelease();
        }
        else
        {
            CCLOG("cocos2d: Couldn't add UIImage in TextureCache");
        }

    } while (0);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTexture::addImage(texture, image);
#endif
    
    return texture;
}

// TextureCache - Remove

void TextureCache::removeAllTextures()
{
    _textures->removeAllObjects();
}

void TextureCache::removeUnusedTextures()
{
    /*
    DictElement* pElement = NULL;
    CCDICT_FOREACH(_textures, pElement)
    {
        CCLOG("cocos2d: TextureCache: texture: %s", pElement->getStrKey());
        Texture2D *value = static_cast<Texture2D*>(pElement->getObject());
        if (value->retainCount() == 1)
        {
            CCLOG("cocos2d: TextureCache: removing unused texture: %s", pElement->getStrKey());
            _textures->removeObjectForElememt(pElement);
        }
    }
     */
    
    /** Inter engineer zhuoshi sun finds that this way will get better performance
     */    
    if (_textures->count())
    {   
        // find elements to be removed
        DictElement* pElement = NULL;
        list<DictElement*> elementToRemove;
        CCDICT_FOREACH(_textures, pElement)
        {
            CCLOG("cocos2d: TextureCache: texture: %s", pElement->getStrKey());
            Texture2D *value = static_cast<Texture2D*>(pElement->getObject());
            if (value->retainCount() == 1)
            {
                elementToRemove.push_back(pElement);
            }
        }
        
        // remove elements
        for (auto iter = elementToRemove.begin(); iter != elementToRemove.end(); ++iter)
        {
            CCLOG("cocos2d: TextureCache: removing unused texture: %s", (*iter)->getStrKey());
            _textures->removeObjectForElememt(*iter);
        }
    }
}

void TextureCache::removeTexture(Texture2D* texture)
{
    if( ! texture )
    {
        return;
    }

    Array* keys = _textures->allKeysForObject(texture);
    _textures->removeObjectsForKeys(keys);
}

void TextureCache::removeTextureForKey(const char *textureKeyName)
{
    if (textureKeyName == NULL)
    {
        return;
    }

    string fullPath = FileUtils::getInstance()->fullPathForFilename(textureKeyName);
    _textures->removeObjectForKey(fullPath);
}

Texture2D* TextureCache::textureForKey(const char* key)
{
    return static_cast<Texture2D*>(_textures->objectForKey(FileUtils::getInstance()->fullPathForFilename(key)));
}

void TextureCache::reloadAllTextures()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    VolatileTexture::reloadAllTextures();
#endif
}

void TextureCache::dumpCachedTextureInfo()
{
    unsigned int count = 0;
    unsigned int totalBytes = 0;

    DictElement* pElement = NULL;
    CCDICT_FOREACH(_textures, pElement)
    {
        Texture2D* tex = static_cast<Texture2D*>(pElement->getObject());
        unsigned int bpp = tex->getBitsPerPixelForFormat();
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

    CCLOG("cocos2d: TextureCache dumpDebugInfo: %ld textures, for %lu KB (%.2f MB)", (long)count, (long)totalBytes / 1024, totalBytes / (1024.0f*1024.0f));
}

#if CC_ENABLE_CACHE_TEXTURE_DATA

std::list<VolatileTexture*> VolatileTexture::_textures;
bool VolatileTexture::_isReloading = false;

VolatileTexture::VolatileTexture(Texture2D *t)
: _texture(t)
, _cashedImageType(kInvalid)
, _textureData(NULL)
, _pixelFormat(Texture2D::PixelFormat::RGBA8888)
, _fileName("")
, _fmtImage(Image::Format::PNG)
, _text("")
, _uiImage(NULL)
{
    _texParams.minFilter = GL_LINEAR;
    _texParams.magFilter = GL_LINEAR;
    _texParams.wrapS = GL_CLAMP_TO_EDGE;
    _texParams.wrapT = GL_CLAMP_TO_EDGE;
    _textures.push_back(this);
}

VolatileTexture::~VolatileTexture()
{
    _textures.remove(this);
    CC_SAFE_RELEASE(_uiImage);
}

void VolatileTexture::addImageTexture(Texture2D *tt, const char* imageFileName, Image::Format format)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = kImageFile;
    vt->_fileName = imageFileName;
    vt->_fmtImage    = format;
    vt->_pixelFormat = tt->getPixelFormat();
}

void VolatileTexture::addImage(Texture2D *tt, Image *image)
{
    VolatileTexture *vt = findVolotileTexture(tt);
    image->retain();
    vt->_uiImage = image;
    vt->_cashedImageType = kImage;
}

VolatileTexture* VolatileTexture::findVolotileTexture(Texture2D *tt)
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
    }
    
    return vt;
}

void VolatileTexture::addDataTexture(Texture2D *tt, void* data, Texture2D::PixelFormat pixelFormat, const Size& contentSize)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = kImageData;
    vt->_textureData = data;
    vt->_pixelFormat = pixelFormat;
    vt->_textureSize = contentSize;
}

void VolatileTexture::addStringTexture(Texture2D *tt, const char* text, const FontDefinition& fontDefinition)
{
    if (_isReloading)
    {
        return;
    }

    VolatileTexture *vt = findVolotileTexture(tt);

    vt->_cashedImageType = kString;
    vt->_text     = text;
    vt->_fontDefinition = fontDefinition;
}

void VolatileTexture::setTexParameters(Texture2D *t, const ccTexParams &texParams)
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

void VolatileTexture::removeTexture(Texture2D *t) 
{
    auto i = _textures.begin();
    while (i != _textures.end())
    {
        VolatileTexture *vt = *i++;
        if (vt->_texture == t) 
        {
            delete vt;
            break;
        }
    }
}

void VolatileTexture::reloadAllTextures()
{
    _isReloading = true;

    CCLOG("reload all texture");
    auto iter = _textures.begin();

    while (iter != _textures.end())
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
                    Texture2D::PixelFormat oldPixelFormat = Texture2D::getDefaultAlphaPixelFormat();
                    Texture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);

                    vt->_texture->initWithPVRFile(vt->_fileName.c_str());
                    Texture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                } 
                else 
                {
                    Image* pImage = new Image();
                    unsigned long nSize = 0;
                    unsigned char* pBuffer = FileUtils::getInstance()->getFileData(vt->_fileName.c_str(), "rb", &nSize);

                    if (pImage && pImage->initWithImageData((void*)pBuffer, nSize, vt->_fmtImage))
                    {
                        Texture2D::PixelFormat oldPixelFormat = Texture2D::getDefaultAlphaPixelFormat();
                        Texture2D::setDefaultAlphaPixelFormat(vt->_pixelFormat);
                        vt->_texture->initWithImage(pImage);
                        Texture2D::setDefaultAlphaPixelFormat(oldPixelFormat);
                    }

                    CC_SAFE_DELETE_ARRAY(pBuffer);
                    CC_SAFE_RELEASE(pImage);
                }
            }
            break;
        case kImageData:
            {
                vt->_texture->initWithData(vt->_textureData, 
                                          vt->_pixelFormat, 
                                          vt->_textureSize.width, 
                                          vt->_textureSize.height, 
                                          vt->_textureSize);
            }
            break;
        case kString:
            {
                vt->_texture->initWithString(vt->_text.c_str(), vt->_fontDefinition);
            }
            break;
        case kImage:
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

