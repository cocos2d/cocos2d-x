/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCTEXTURE_CACHE_H__
#define __CCTEXTURE_CACHE_H__

#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <string>
#include <unordered_map>
#include <functional>

#include "base/CCRef.h"
#include "renderer/CCTexture2D.h"
#include "platform/CCImage.h"

#if CC_ENABLE_CACHE_TEXTURE_DATA
    #include "platform/CCImage.h"
    #include <list>
#endif

NS_CC_BEGIN

/**
 * @addtogroup textures
 * @{
 */
/*
* from version 3.0, TextureCache will never to treated as a singleton, it will be owned by director.
* all call by TextureCache::getInstance() should be replaced by Director::getInstance()->getTextureCache()
*/

/** @brief Singleton that handles the loading of textures
* Once the texture is loaded, the next time it will return
* a reference of the previously loaded texture reducing GPU & CPU memory
*/
class CC_DLL TextureCache : public Ref
{
public:
    /** Returns the shared instance of the cache */
    CC_DEPRECATED_ATTRIBUTE static TextureCache * getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static TextureCache * sharedTextureCache();

    /** purges the cache. It releases the retained instance.
     @since v0.99.0
     */
    CC_DEPRECATED_ATTRIBUTE static void destroyInstance();

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedTextureCache();

    /** Reload all textures
    should not call it, called by frame work
    now the function do nothing, use VolatileTextureMgr::reloadAllTextures
     */
    CC_DEPRECATED_ATTRIBUTE static void reloadAllTextures();

public:
    /**
     * @js ctor
     */
    TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TextureCache();
    /**
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

//    Dictionary* snapshotTextures();

    /** Returns a Texture2D object given an filename.
    * If the filename was not previously loaded, it will create a new Texture2D
    *  object and it will return it. It will use the filename as a key.
    * Otherwise it will return a reference of a previously loaded image.
    * Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr
    */
    Texture2D* addImage(const std::string &filepath);

    /* Returns a Texture2D object given a file image
    * If the file image was not previously loaded, it will create a new Texture2D object and it will return it.
    * Otherwise it will load a texture in a new thread, and when the image is loaded, the callback will be called with the Texture2D as a parameter.
    * The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
    * Supported image extensions: .png, .jpg
    * @since v0.8
    */
    virtual void addImageAsync(const std::string &filepath, const std::function<void(Texture2D*)>& callback);
    
    /* Unbind a specified bound image asynchronous callback
     * In the case an object who was bound to an image asynchronous callback was destroyed before the callback is invoked,
     * the object always need to unbind this callback manually.
     * @since v3.1
     */
    virtual void unbindImageAsync(const std::string &filename);
    
    /* Unbind all bound image asynchronous load callbacks
     * @since v3.1
     */
    virtual void unbindAllImageAsync();

    /** Returns a Texture2D object given an Image.
    * If the image was not previously loaded, it will create a new Texture2D object and it will return it.
    * Otherwise it will return a reference of a previously loaded image.
    * The "key" parameter will be used as the "key" for the cache.
    * If "key" is nil, then a new texture will be created each time.
    */
    Texture2D* addImage(Image *image, const std::string &key);
    CC_DEPRECATED_ATTRIBUTE Texture2D* addUIImage(Image *image, const std::string& key) { return addImage(image,key); }

    /** Returns an already created texture. Returns nil if the texture doesn't exist.
    @since v0.99.5
    */
    Texture2D* getTextureForKey(const std::string& key) const;
    CC_DEPRECATED_ATTRIBUTE Texture2D* textureForKey(const std::string& key) const { return getTextureForKey(key); }

    /** Reload texture from the image file
    * If the file image hasn't loaded before, load it.
    * Otherwise the texture will be reloaded from the file image.
    * The "filenName" parameter is the related/absolute path of the file image.
    * Return true if the reloading is succeed, otherwise return false.
    */
    bool reloadTexture(const std::string& fileName);

    /** Purges the dictionary of loaded textures.
    * Call this method if you receive the "Memory Warning"
    * In the short term: it will free some resources preventing your app from being killed
    * In the medium term: it will allocate more resources
    * In the long term: it will be the same
    */
    void removeAllTextures();

    /** Removes unused textures
    * Textures that have a retain count of 1 will be deleted
    * It is convenient to call this method after when starting a new Scene
    * @since v0.8
    */
    void removeUnusedTextures();

    /** Deletes a texture from the cache given a texture
    */
    void removeTexture(Texture2D* texture);

    /** Deletes a texture from the cache given a its key name
    @since v0.99.4
    */
    void removeTextureForKey(const std::string &key);

    /** Output to CCLOG the current contents of this TextureCache
    * This will attempt to calculate the size of each texture, and the total texture memory in use
    *
    * @since v1.0
    */
    std::string getCachedTextureInfo() const;

    //wait for texture cahe to quit befor destroy instance
    //called by director, please do not called outside
    void waitForQuit();

private:
    void addImageAsyncCallBack(float dt);
    void loadImage();

public:
    struct AsyncStruct
    {
    public:
        AsyncStruct(const std::string& fn, std::function<void(Texture2D*)> f) : filename(fn), callback(f) {}

        std::string filename;
        std::function<void(Texture2D*)> callback;
    };

protected:
    typedef struct _ImageInfo
    {
        AsyncStruct *asyncStruct;
        Image        *image;
    } ImageInfo;
    
    std::thread* _loadingThread;

    std::queue<AsyncStruct*>* _asyncStructQueue;
    std::deque<ImageInfo*>* _imageInfoQueue;

    std::mutex _asyncStructQueueMutex;
    std::mutex _imageInfoMutex;

    std::mutex _sleepMutex;
    std::condition_variable _sleepCondition;

    bool _needQuit;

    int _asyncRefCount;

    std::unordered_map<std::string, Texture2D*> _textures;
};

#if CC_ENABLE_CACHE_TEXTURE_DATA

class VolatileTexture
{
    typedef enum {
        kInvalid = 0,
        kImageFile,
        kImageData,
        kString,
        kImage,
    }ccCachedImageType;

private:
    VolatileTexture(Texture2D *t);
    /**
     * @js NA
     * @lua NA
     */
    ~VolatileTexture();

protected:
    friend class  VolatileTextureMgr;
    Texture2D *_texture;
    
    Image *_uiImage;

    ccCachedImageType _cashedImageType;

    void *_textureData;
    int  _dataLen;
    Size _textureSize;
    Texture2D::PixelFormat _pixelFormat;

    std::string _fileName;

    bool                      _hasMipmaps;
    Texture2D::TexParams      _texParams;
    std::string               _text;
    FontDefinition            _fontDefinition;
};

class CC_DLL VolatileTextureMgr
{
public:
    static void addImageTexture(Texture2D *tt, const std::string& imageFileName);
    static void addStringTexture(Texture2D *tt, const char* text, const FontDefinition& fontDefinition);
    static void addDataTexture(Texture2D *tt, void* data, int dataLen, Texture2D::PixelFormat pixelFormat, const Size& contentSize);
    static void addImage(Texture2D *tt, Image *image);

    static void setHasMipmaps(Texture2D *t, bool hasMipmaps);
    static void setTexParameters(Texture2D *t, const Texture2D::TexParams &texParams);
    static void removeTexture(Texture2D *t);
    static void reloadAllTextures();
public:
    static std::list<VolatileTexture*> _textures;
    static bool _isReloading;
private:
    // find VolatileTexture by Texture2D*
    // if not found, create a new one
    static VolatileTexture* findVolotileTexture(Texture2D *tt);
};

#endif

// end of textures group
/// @}

NS_CC_END

#endif //__CCTEXTURE_CACHE_H__

