/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2015 Chukong Technologies Inc.

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

#ifndef __CC_IMAGE_H__
#define __CC_IMAGE_H__
/// @cond DO_NOT_SHOW

#include "base/CCRef.h"
#include "renderer/CCTexture2D.h"

#if defined(CC_USE_WIC)
#include "WICImageLoader-winrt.h"
#endif

/** @~english premultiply alpha, or the effect will wrong when want to use other pixel format in Texture2D,
// such as RGB888, RGB5A1
    @~chinese 透明像素复合 如果我们在Texture2D中使用其他的像素格式（如：RGB888, RGB5A1），效果就会出错
*/
#define CC_RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/**
 @brief @~english Structure which can tell where mipmap begins and how long is it
 * @~chinese 用来辨别mipmap起始位置和长度的结构体
 */
typedef struct _MipmapInfo
{
    unsigned char* address;
    int len;
    _MipmapInfo():address(NULL),len(0){}
}MipmapInfo;

class CC_DLL Image : public Ref
{
public:
    friend class TextureCache;
    /**
     * @js ctor
     */
    Image();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Image();

    /** @~english Supported formats for Image  @~chinese 支持的图片格式*/
    enum class Format
    {
        //! JPEG
        JPG,
        //! PNG
        PNG,
        //! TIFF
        TIFF,
        //! WebP
        WEBP,
        //! PVR
        PVR,
        //! ETC
        ETC,
        //! S3TC
        S3TC,
        //! ATITC
        ATITC,
        //! TGA
        TGA,
        //! 原始数据
        RAW_DATA,
        //! 未知格式
        UNKNOWN
    };

    /**
    @brief @~english Load the image from the specified path.
     * @~chinese 从指定的路径加载图片
    @param path   @~english the absolute file path.
     * @~chinese 文件的绝对路径
    @return @~english true if loaded correctly.
     * @~chinese 如果正确加载则返回true
    */
    bool initWithImageFile(const std::string& path);

    /**
    @brief @~english Load image from stream buffer.
     * @~chinese 从流缓冲区加载图片
    @param data  @~english stream buffer which holds the image data.
     * @~chinese 存放图片数据的流缓冲区
    @param dataLen  @~english data length expressed in (number of) bytes.
     * @~chinese 数据的字节数
    @return @~english true if loaded correctly.
     * @~chinese 如果正确加载则返回true
    * @js NA
    * @lua NA
    */
    bool initWithImageData(const unsigned char * data, ssize_t dataLen);

    /** @~english Load image from raw data @~chinese 从原始数据中加载图片
    // @warning kFmtRawData @~english only support RGBA8888 @~english 只支持RGBA8888
    */
    bool initWithRawData(const unsigned char * data, ssize_t dataLen, int width, int height, int bitsPerComponent, bool preMulti = false);

    // Getters
    inline unsigned char *   getData()               { return _data; }
    inline ssize_t           getDataLen()            { return _dataLen; }
    inline Format            getFileType()           {return _fileType; }
    inline Texture2D::PixelFormat getRenderFormat()  { return _renderFormat; }
    inline int               getWidth()              { return _width; }
    inline int               getHeight()             { return _height; }
    inline int               getNumberOfMipmaps()    { return _numberOfMipmaps; }
    inline MipmapInfo*       getMipmaps()            { return _mipmaps; }
    inline bool              hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }
    CC_DEPRECATED_ATTRIBUTE inline bool isPremultipliedAlpha()  { return _hasPremultipliedAlpha;   }

    int                      getBitPerPixel();
    bool                     hasAlpha();
    bool                     isCompressed();


    /**
     @brief    @~english Save Image data to the specified file, with specified format.
     * @~chinese 以指定的格式把图片数据保存到指定的文件中
     @param    filePath        @~english the file's absolute path, including file suffix.
     * @~chinese 包括文件后缀的绝对路径
     @param    isToRGB        @~english whether the image is saved as RGB format.
     * @~chinese 图片是否以RGB格式保存。
     */
    bool saveToFile(const std::string &filename, bool isToRGB = true);
    
    
    /** @~english treats (or not) PVR files as if they have alpha premultiplied.
     Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is
     possible load them as if they have (or not) the alpha channel premultiplied.
     
     By default it is disabled.
     * @~chinese 设置PVR文件是否进行透明像素混合。
     * 因为不可能知道在运行时PVR图像是否已有alpha通道的混合,
     * 可能加载它们时有(或没有)透明通道混合。
     * 
     * 在默认情况下是禁用的。
     */
    static void setPVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);

protected:
#if defined(CC_USE_WIC)
	bool encodeWithWIC(const std::string& filePath, bool isToRGB, GUID containerFormat);
	bool decodeWithWIC(const unsigned char *data, ssize_t dataLen);
#endif
    bool initWithJpgData(const unsigned char *  data, ssize_t dataLen);
    bool initWithPngData(const unsigned char * data, ssize_t dataLen);
    bool initWithTiffData(const unsigned char * data, ssize_t dataLen);
    bool initWithWebpData(const unsigned char * data, ssize_t dataLen);
    bool initWithPVRData(const unsigned char * data, ssize_t dataLen);
    bool initWithPVRv2Data(const unsigned char * data, ssize_t dataLen);
    bool initWithPVRv3Data(const unsigned char * data, ssize_t dataLen);
    bool initWithETCData(const unsigned char * data, ssize_t dataLen);
    bool initWithS3TCData(const unsigned char * data, ssize_t dataLen);
    bool initWithATITCData(const unsigned char *data, ssize_t dataLen);
    typedef struct sImageTGA tImageTGA;
    bool initWithTGAData(tImageTGA* tgaData);

    bool saveImageToPNG(const std::string& filePath, bool isToRGB = true);
    bool saveImageToJPG(const std::string& filePath);
    
    void premultipliedAlpha();
    
protected:
    /**
     @brief @~english Determine how many mipmaps can we have.
     Its same as define but it respects namespaces
     * @~chinese 决定mipmap允许的最大数量
     * 这个和使用define是一样的，只不过它遵守命名空间的规则
     */
    static const int MIPMAP_MAX = 16;
    unsigned char *_data;
    ssize_t _dataLen;
    int _width;
    int _height;
    bool _unpack;
    Format _fileType;
    Texture2D::PixelFormat _renderFormat;
    MipmapInfo _mipmaps[MIPMAP_MAX];   // pointer to mipmap images
    int _numberOfMipmaps;
    // false if we cann't auto detect the image is premultiplied or not.
    bool _hasPremultipliedAlpha;
    std::string _filePath;


protected:
    // noncopyable
    Image(const Image&    rImg);
    Image & operator=(const Image&);
    
    /*
     @brief @~english The same result as with initWithImageFile, but thread safe. It is caused by
     loadImage() in TextureCache.cpp.
     * @~chinese 它和使用initWithImageFile的结果是一样的，只不过线程相对安全。它在源文件TextureCache.cpp中被 loadImage()调用
     @param fullpath  @~english full path of the file.
     * @~chinese 文件的完整路径。
     @param imageType @~english the type of image, currently only supporting two types.
     * @~chinese 图片类型，当前只支持两个类型
     @return  @~english true if loaded correctly.
     * @~chinese 如果正确加载则返回true
     */
    bool initWithImageFileThreadSafe(const std::string& fullpath);
    
    Format detectFormat(const unsigned char * data, ssize_t dataLen);
    bool isPng(const unsigned char * data, ssize_t dataLen);
    bool isJpg(const unsigned char * data, ssize_t dataLen);
    bool isTiff(const unsigned char * data, ssize_t dataLen);
    bool isWebp(const unsigned char * data, ssize_t dataLen);
    bool isPvr(const unsigned char * data, ssize_t dataLen);
    bool isEtc(const unsigned char * data, ssize_t dataLen);
    bool isS3TC(const unsigned char * data,ssize_t dataLen);
    bool isATITC(const unsigned char *data, ssize_t dataLen);
};

// end of platform group
/// @}

NS_CC_END

/// @endcond
#endif    // __CC_IMAGE_H__
