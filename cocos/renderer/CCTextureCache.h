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
 * @addtogroup _2d
 * @{
 */
/*@~english
* From version 3.0, TextureCache will never to treated as a singleton, it will be owned by director.
* All call by TextureCache::getInstance() should be replaced by Director::getInstance()->getTextureCache().
 * @~chinese 
 * 从3.0版本开始，TextureCache 将不再作为一个单例，将由 `Director` 来管理。
 * TextureCache::getInstance() 的调用都应该由 Director::getInstance()->getTextureCache() 来代替。
*/

/** @brief @~english Singleton that handles the loading of textures.
* Once the texture is loaded, the next time it will return.
* A reference of the previously loaded texture reducing GPU & CPU memory.
 * @~chinese 用于处理纹理加载的单例类。
 * 一旦一个纹理被加载，下次使用时将直接返回该纹理。
 * 引用之前加载的纹理可以减少 GPU 与 CPU 的内存消耗。
*/
class CC_DLL TextureCache : public Ref
{
public:
    /** @~english Returns the shared instance of the cache.  @~chinese 返回 TextureCache 的实例。*/
    CC_DEPRECATED_ATTRIBUTE static TextureCache * getInstance();

    /** @deprecated Use getInstance() instead. */
    CC_DEPRECATED_ATTRIBUTE static TextureCache * sharedTextureCache();

    /** @~english Purges the cache. It releases the retained instance.
     * @~chinese 清理缓存。将释放所有 retain 的实例。
     @since v0.99.0
     */
    CC_DEPRECATED_ATTRIBUTE static void destroyInstance();

    /** @deprecated Use destroyInstance() instead. */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedTextureCache();

    /** @~english Reload all textures.
     * Should not call it, called by frame work.
     * Now the function do nothing, use VolatileTextureMgr::reloadAllTextures.
     * @~chinese 重新加载所有的纹理。
     * 不要调用此接口，这个接口是提供给引擎框架调用的。
     * 现在此接口什么也没有做，目前使用 VolatileTextureMgr:reloadAllTextures。
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

    /** @~english Returns a Texture2D object with given an filename.
     * If the filename was not previously loaded, it will create a new Texture2D
     * Object and it will return it. It will use the filename as a key to cache the Texture2D object.
     * Otherwise it will return a reference of a previously loaded image.
     * Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr.
     * @~chinese 加载指定的纹理文件，并返回一个 Texture2D 实例。
     * 如果文件之前未加载，将创建一个新的 Texture2D 实例，并返回这个实例。使用文件名做为 key 将纹理缓存。
     * 否则，将返回一个之前加载的纹理实例。
     * 支持的文件扩展名：.png，.bmp，.tiff，.jpeg，.pvr。
     * @param filepath @~english The path of the image file.
     * @~chinese 图片文件的路径。
     */
    Texture2D* addImage(const std::string &filepath);

    /** @~english Returns a Texture2D object with given a file image by asynchronous.
     * If the file image was not previously loaded, it will create a new Texture2D object.
     * Otherwise it will load a texture in a new thread, and when the image is loaded, the callback will be called with the Texture2D as a parameter.
     * The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
     * Supported image extensions: .png, .jpg
     * @~chinese 异步加载指定的纹理文件。
     * 如果文件图像先前没有被加载,它将创建一个新的 Texture2D 对象。
     * 否则它将会在一个新线程加载纹理，加载完成时，Texture2D 对象会作为参数调用 callback 回调函数。
     * 回调函数将从主线程调用，所以在回调函数中可以创建任何 cocos2d 对象。
     * 支持图像扩展：.png，.jpg
     * @param filepath @~english The path of the image file.
     * @~chinese 图片文件的路径。
     * @param callback @~english A callback function would be invoked after the image is loaded.
     * @~chinese 图像加载完成后被调用的回调函数。
     * @since v0.8
     */
    virtual void addImageAsync(const std::string &filepath, const std::function<void(Texture2D*)>& callback);
    
    /** @~english Unbind a specified bound image asynchronous callback.
     * In the case an object who was bound to an image asynchronous callback was destroyed before the callback is invoked,
     * the object always need to unbind this callback manually.
     * @~chinese 解除异步加载纹理文件时绑定的回调函数。
     * 如果异步加载回调函数所在对象，在回调函数被调用之前被析构了，需要调用此方法手动解除回调函数的绑定。
     * @param filename @~english It's the related/absolute path of the file image.
     * @~chinese 异步加载的纹理文件的绝对路径或相对路径。
     * @since v3.1
     */
    virtual void unbindImageAsync(const std::string &filename);
    
    /** @~english Unbind all bound image asynchronous load callbacks.
     * @~chinese 解除所有异步加载纹理文件时绑定的回调函数。
     * @since v3.1
     */
    virtual void unbindAllImageAsync();

    /** @~english Returns a Texture2D object given an Image.
     * If the image was not previously loaded, it will create a new Texture2D object and it will return it.
     * Otherwise it will return a reference of a previously loaded image.
     * @~chinese 返回一个使用指定的 `Image` 对象创建的 `Texture2D` 对象。
     * 如果之前没有加载该 `Image` 对象的纹理，会创建一个新的 `Texture2D` 对象，并返回该对象。
     * 否则，返回一个之前加载过的纹理对象的引用。
     * @param image @~english The image to be added. @~chinese 要添加的Image对象
     * @param key @~english The "key" parameter will be used as the "key" for the cache.
     * If "key" is nil, then a new texture will be created each time.
     * @~chinese key 参数将作为缓存中的关键字以便之后进行查找。
     * 如果 key 值为 nullptr，那么直接创建一个新的 `Texture2D` 对象。
     * @return @~english A texture object using specified `Image`.
     * @~chinese 使用指定 `Image` 对象的纹理对象。
     */
    Texture2D* addImage(Image *image, const std::string &key);
    CC_DEPRECATED_ATTRIBUTE Texture2D* addUIImage(Image *image, const std::string& key) { return addImage(image,key); }

    /** @~english Returns an already created texture. Returns nil if the texture doesn't exist.
     * @~chinese 获取一个已创建的纹理。如果纹理不存在返回空指针。
     * @param key @~english It's the related/absolute path of the file image.
     * @~chinese 图片文件的绝对路径或相对路径。
     * @return @~english A texture object found by the key.
     * @~chinese 使用指定的 key 查找到的纹理对象。
     * @since v0.99.5
     */
    Texture2D* getTextureForKey(const std::string& key) const;
    CC_DEPRECATED_ATTRIBUTE Texture2D* textureForKey(const std::string& key) const { return getTextureForKey(key); }

    /** @~english Reload texture from the image file.
     * If the file image hasn't loaded before, load it.
     * Otherwise the texture will be reloaded from the file image.
     * @~chinese 重新加载指定的图片文件。
     * 如果文件图片之前没有加载，那么加载该图片文件。
     * 否则将重新加载该图片文件。
     * @param fileName @~english It's the related/absolute path of the file image.
     * @~chinese 图片文件的绝对路径或相对路径。
     * @return @~english True if the reloading is succeed, otherwise return false.
     * @~chinese 如果重新重新加载成功返回 true；否则返回 false。
     */
    bool reloadTexture(const std::string& fileName);

    /** @~english Purges the dictionary of loaded textures.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     * @~chinese 清理所有缓存的纹理对象。
     * 当收到内存警告时，可以调用这个方法如回收内存。
     * 在短期内：释放部分内存资源以防止程序被终止。
     * 在中期：会分配更多的资源。
     * 从长远来看：没有什么区别。
     */
    void removeAllTextures();

    /** @~english Removes unused textures.
     * Textures that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     * @~chinese 删除未使用的纹理。
     * 引用计数为 1 的纹理对象将被删除。
     * 在进入新的场景时，可以调用此方法方便的删除未使用的纹理。
     * @since v0.8
     */
    void removeUnusedTextures();

    /** @~english Deletes a texture from the cache given a texture.
     * @~chinese 从缓存中删除指定的纹理对象。
     * @param texture @~english The texture object will be removed.
     * @~chinese 需要删除的纹理对象。
     */
    void removeTexture(Texture2D* texture);

    /** @~english Deletes a texture from the cache given a its key name.
     * @~chinese 使用指定的 key 在缓存中查找并删除纹理。
     * @param key @~english It's the related/absolute path of the file image.
     * @~chinese 图片文件的绝对路径或相对路径。
     * @since v0.99.4
     */
    void removeTextureForKey(const std::string &key);

    /** @~english Output to CCLOG the current contents of this TextureCache.
     * This will attempt to calculate the size of each texture, and the total texture memory in use.
     *
     * @~chinese 使用 CCLOG 输出 TextureCache 的当前信息。
     * 这将尝试计算每个纹理的大小和总的纹理内存使用。
     * 
     * @since v1.0
     */
    std::string getCachedTextureInfo() const;

    /**@~english Wait for texture cache to quit befor destroy instance.
     * Called by director, please do not called outside.
     * @~chinese 在销毁对象之前等待缓存退出。
     * 被 Director 调用的方法，请不要在引擎外调用。
     */
    void waitForQuit();

    /**@~english
     * Get the file path of the texture
     *
     * @~chinese 
     * 获取纹理对象对应的文件路径。
     * 
     * @param texture @~english A Texture2D object pointer.
     *
     * @~chinese `Texture2D` 对象指针。
     * 
     * @return @~english The full path of the file.
     * @~chinese 对应文件的完整路径。
     */
    const std::string getTextureFilePath(Texture2D* texture)const;

private:
    void addImageAsyncCallBack(float dt);
    void loadImage();
    void parseNinePatchImage(Image* image, Texture2D* texture, const std::string& path);
public:
protected:
    struct AsyncStruct;
    
    std::thread* _loadingThread;

    std::deque<AsyncStruct*> _asyncStructQueue;
    std::deque<AsyncStruct*> _requestQueue;
    std::deque<AsyncStruct*> _responseQueue;

    std::mutex _requestMutex;
    std::mutex _responseMutex;
    
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

