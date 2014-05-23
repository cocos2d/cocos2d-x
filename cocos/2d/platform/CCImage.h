/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CC_IMAGE_H__
#define __CC_IMAGE_H__

#include "base/CCRef.h"
#include "2d/CCTexture2D.h"

//  透明像素复合（premultiply alpha）。如果我们在Texture2D中使用其他的像素格式（如：RGB888, RGB5A1），效果就会出错
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
 @brief 用来辨别mipmap起始位置和长度的结构体
 */
typedef struct _MipmapInfo
{
    unsigned char* address;
    int len;
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

    /** 支持的图片格式 */
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
        UNKOWN
    };

    /**
    @brief 从指定的路径加载图片
    @param path   文件的绝对路径
    @return 如果正确加载则返回true
    */
    bool initWithImageFile(const std::string& path);

    /**
    @brief 从流缓冲区加载图片
    @param data  存放图片数据的流缓冲区
    @param dataLen 数据的字节数
    @return true if loaded correctly.如果正确加载则返回true
    * @js NA
    * @lua NA
    */
    bool initWithImageData(const unsigned char * data, ssize_t dataLen);

    // @warning kFmtRawData只支持RGBA8888
    bool initWithRawData(const unsigned char * data, ssize_t dataLen, int width, int height, int bitsPerComponent, bool preMulti = false);

    // get函数
    inline unsigned char *   getData()               { return _data; }
    inline ssize_t           getDataLen()            { return _dataLen; }
    inline Format            getFileType()           {return _fileType; }
    inline Texture2D::PixelFormat getRenderFormat()  { return _renderFormat; }
    inline int               getWidth()              { return _width; }
    inline int               getHeight()             { return _height; }
    inline bool              isPremultipliedAlpha()  { return _preMulti;   }
    inline int               getNumberOfMipmaps()    { return _numberOfMipmaps; }
    inline MipmapInfo*       getMipmaps()            { return _mipmaps; }
    inline bool              hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }

    int                      getBitPerPixel();
    bool                     hasAlpha();
    bool                     isCompressed();


    /**
     @brief    以指定的格式把图片数据保存到指定的文件中
     @param    filePath        包括文件后缀的绝对路径
     @param    isToRGB        图片是否以RGB格式保存
     */
    bool saveToFile(const std::string &filename, bool isToRGB = true);

protected:
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
    
protected:
    /**
     @brief 决定mipmap允许的最大数量
     这个和使用define是一样的，只不过它遵守命名空间的规则
     */
    static const int MIPMAP_MAX = 16;
    unsigned char *_data;
    ssize_t _dataLen;
    int _width;
    int _height;
    Format _fileType;
    Texture2D::PixelFormat _renderFormat;
    bool _preMulti;
    MipmapInfo _mipmaps[MIPMAP_MAX];   // 存放mipmap的数组
    int _numberOfMipmaps;
    // 如果我们无法检测图片是否是自左乘的，将返回false
    bool _hasPremultipliedAlpha;
    std::string _filePath;


protected:
    // 不可复制
    Image(const Image&    rImg);
    Image & operator=(const Image&);
    
    /*
     @brief 它和使用initWithImageFile的结果是一样的，只不过线程相对安全。它在源文件TextureCache.cpp中被 loadImage()调用
     @param fullpath  文件的完整路径
     @param imageType 图片类型，当前只支持两个类型
     @return  如果正确加载则返回true
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

#endif    // __CC_IMAGE_H__
