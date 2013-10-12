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

#ifndef __CC_IMAGE_H__
#define __CC_IMAGE_H__

#include "cocoa/CCObject.h"
#include "textures/CCTexture2D.h"

// premultiply alpha, or the effect will wrong when want to use other pixel format in Texture2D,
// such as RGB888, RGB5A1
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
 @brief Structure which can tell where mipmap begins and how long is it
 */
typedef struct _MipmapInfo
{
    unsigned char* address;
    int len;
}MipmapInfo;

class CC_DLL Image : public Object
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

    /** Supported formats for Image */
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
        //! Raw Data
        RAW_DATA,
        //! Unknown format
        UNKOWN
    };

    enum class TextAlign
    {
        CENTER        = 0x33, ///< Horizontal center and vertical center.
        TOP           = 0x13, ///< Horizontal center and vertical top.
        TOP_RIGHT     = 0x12, ///< Horizontal right and vertical top.
        RIGHT         = 0x32, ///< Horizontal right and vertical center.
        BOTTOM_RIGHT = 0x22, ///< Horizontal right and vertical bottom.
        BOTTOM        = 0x23, ///< Horizontal center and vertical bottom.
        BOTTOM_LEFT  = 0x21, ///< Horizontal left and vertical bottom.
        LEFT          = 0x31, ///< Horizontal left and vertical center.
        TOP_LEFT      = 0x11, ///< Horizontal left and vertical top.
    };
    
    /**
    @brief Load the image from the specified path.
    @param path   the absolute file path.
    @return true if loaded correctly.
    */
    bool initWithImageFile(const char *path);

    /**
    @brief Load image from stream buffer.
    @param data  stream buffer which holds the image data.
    @param dataLen  data length expressed in (number of) bytes.
    @return true if loaded correctly.
    * @js NA
    * @lua NA
    */
    bool initWithImageData(const unsigned char * data, int dataLen);

    // @warning kFmtRawData only support RGBA8888
    bool initWithRawData(const unsigned char * data, int dataLen, int width, int height, int bitsPerComponent, bool preMulti = false);

    /**
    @brief Create image with specified string.
    @param text       the text the image will show (cannot be nil).
    @param width      the image width, if 0, the width will match the text's width.
    @param height     the image height, if 0, the height will match the text's height.
    @param alignMask  the test Alignment
    @param fontName   the name of the font used to draw the text. If nil, use the default system font.
    @param size       the font size, if 0, use the system default size.
    * @js NA
    * @lua NA
    */
    bool initWithString(
        const char *    text,
        int             width = 0,
        int             height = 0,
        TextAlign       alignMask = TextAlign::CENTER,
        const char *    fontName = 0,
        int             size = 0);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool initWithStringShadowStroke(
                                            const char *    pText,
                                            int             nWidth      = 0,
                                            int             nHeight     = 0,
                                            TextAlign       eAlignMask  = TextAlign::CENTER,
                                            const char *    pFontName   = 0,
                                            int             nSize       = 0,
                                            float           textTintR   = 1,
                                            float           textTintG   = 1,
                                            float           textTintB   = 1,
                                            bool shadow                 = false,
                                            float shadowOffsetX         = 0.0,
                                            float shadowOffsetY         = 0.0,
                                            float shadowOpacity         = 0.0,
                                            float shadowBlur            = 0.0,
                                            bool  stroke                =  false,
                                            float strokeR               = 1,
                                            float strokeG               = 1,
                                            float strokeB               = 1,
                                            float strokeSize            = 1
                                        
                                        );
    
    #endif
    
    
    // Getters
    inline unsigned char *   getData()               { return _data; }
    inline int               getDataLen()            { return _dataLen; }
    inline Format            getFileType()           {return _fileType; }
    inline Texture2D::PixelFormat getRenderFormat()    { return _renderFormat; }
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
     @brief    Save Image data to the specified file, with specified format.
     @param    filePath        the file's absolute path, including file suffix.
     @param    isToRGB        whether the image is saved as RGB format.
     */
    bool saveToFile(const char *filePath, bool isToRGB = true);

protected:
    bool initWithJpgData(const unsigned char *  data, int dataLen);
    bool initWithPngData(const unsigned char * data, int dataLen);
    bool initWithTiffData(const unsigned char * data, int dataLen);
    bool initWithWebpData(const unsigned char * data, int dataLen);
    bool initWithPVRData(const unsigned char * data, int dataLen);
    bool initWithPVRv2Data(const unsigned char * data, int dataLen);
    bool initWithPVRv3Data(const unsigned char * data, int dataLen);
    bool initWithETCData(const unsigned char * data, int dataLen);
    bool initWithS3TCData(const unsigned char * data, int dataLen);
    bool initWithATITCData(const unsigned char *data, int dataLen);

    bool saveImageToPNG(const char *filePath, bool isToRGB = true);
    bool saveImageToJPG(const char *filePath);
    
private:
    /**
     @brief Determine how many mipmaps can we have.
     Its same as define but it respects namespaces
     */
    static const int MIPMAP_MAX = 16;
    unsigned char *_data;
    int _dataLen;
    int _width;
    int _height;
    Format _fileType;
    Texture2D::PixelFormat _renderFormat;
    bool _preMulti;
    MipmapInfo _mipmaps[MIPMAP_MAX];   // pointer to mipmap images
    int _numberOfMipmaps;
    // false if we cann't auto detect the image is premultiplied or not.
    bool _hasPremultipliedAlpha;


private:
    // noncopyable
    Image(const Image&    rImg);
    Image & operator=(const Image&);
    
    /*
     @brief The same result as with initWithImageFile, but thread safe. It is caused by
     loadImage() in TextureCache.cpp.
     @param fullpath  full path of the file.
     @param imageType the type of image, currently only supporting two types.
     @return  true if loaded correctly.
     */
    bool initWithImageFileThreadSafe(const char *fullpath);
    
    Format detectFormat(const unsigned char * data, int dataLen);
    bool isPng(const unsigned char * data, int dataLen);
    bool isJpg(const unsigned char * data, int dataLen);
    bool isTiff(const unsigned char * data, int dataLen);
    bool isWebp(const unsigned char * data, int dataLen);
    bool isPvr(const unsigned char * data, int dataLen);
    bool isEtc(const unsigned char * data, int dataLen);
    bool isS3TC(const unsigned char * data,int dataLen);
    bool isATITC(const unsigned char *data, int dataLen);
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_IMAGE_H__
