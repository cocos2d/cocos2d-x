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
typedef struct _MipmapInfo {
    unsigned char* address;
    int len;
}MipmapInfo;

class CC_DLL Image : public Object
{
public:
    friend class TextureCache;
    
    Image();
    ~Image();
    
    /**
     @brief Determine how many mipmaps can we have. 
     Its same as define but it respects namespaces
    */
    enum {
        CC_MIPMAP_MAX = 16,
    };

    typedef enum
    {
        kFmtJpg = 0,
        kFmtPng,
        kFmtTiff,
        kFmtWebp,
        kFmtPvr,
        kFmtEtc,
        kFmtRawData,
        kFmtUnKnown
    }FileType;

    typedef enum
    {
        kAlignCenter        = 0x33, ///< Horizontal center and vertical center.
        kAlignTop           = 0x13, ///< Horizontal center and vertical top.
        kAlignTopRight      = 0x12, ///< Horizontal right and vertical top.
        kAlignRight         = 0x32, ///< Horizontal right and vertical center.
        kAlignBottomRight   = 0x22, ///< Horizontal right and vertical bottom.
        kAlignBottom        = 0x23, ///< Horizontal center and vertical bottom.
        kAlignBottomLeft    = 0x21, ///< Horizontal left and vertical bottom.
        kAlignLeft          = 0x31, ///< Horizontal left and vertical center.
        kAlignTopLeft       = 0x11, ///< Horizontal left and vertical top.
    }TextAlign;

    /**
    @brief  Load the image from the specified path. 
    @param strPath   the absolute file path.
    @param imageType the type of image, currently only supporting two types.
    @return  true if loaded correctly.
    */
    bool initWithImageFile(const char * strPath);

    /**
    @brief  Load image from stream buffer.
    @param data  stream buffer which holds the image data.
    @param dataLen  data length expressed in (number of) bytes.
    @return true if loaded correctly.
    */
    bool initWithImageData(void * data, int dataLen);

    // @warning kFmtRawData only support RGBA8888
    bool initWithRawData(void *data, int dataLen, int nWidth, int nHeight, int nBitsPerComponent = 8, bool bPreMulti = false);

    /**
    @brief    Create image with specified string.
    @param  pText       the text the image will show (cannot be nil).
    @param  nWidth      the image width, if 0, the width will match the text's width.
    @param  nHeight     the image height, if 0, the height will match the text's height.
    @param  eAlignMask  the test Alignment
    @param  pFontName   the name of the font used to draw the text. If nil, use the default system font.
    @param  nSize       the font size, if 0, use the system default size.
    */
    bool initWithString(
        const char *    pText, 
        int             nWidth = 0, 
        int             nHeight = 0,
        TextAlign      eAlignMask = kAlignCenter,
        const char *    pFontName = 0,
        int             nSize = 0);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
        bool initWithStringShadowStroke(
                                            const char *    pText,
                                            int             nWidth      = 0,
                                            int             nHeight     = 0,
                                            TextAlign      eAlignMask  = kAlignCenter,
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
    
        
    unsigned char *   getData()               { return _data; }
    int               getDataLen()            { return _dataLen; }
    FileType          getFileType()           {return _fileType; }
    Texture2DPixelFormat getRenderFormat()    { return _renderFormat; }
    int               getWidth()              { return _width; }
    int               getHeight()             { return _height; }
    bool              isPremultipliedAlpha()  { return _preMulti;   }
    int               getNumberOfMipmaps()    { return _numberOfMipmaps; }
    MipmapInfo*           getMipmaps()        { return _mipmaps; }

    int               getBitPerPixel();
    bool              hasAlpha();
    bool              isCompressed();


    /**
    @brief    Save Image data to the specified file, with specified format.
    @param    pszFilePath        the file's absolute path, including file suffix.
    @param    bIsToRGB        whether the image is saved as RGB format.
    */
    bool saveToFile(const char *pszFilePath, bool bIsToRGB = true);

protected:
    bool _initWithJpgData(void *data, int dataLen);
    bool _initWithPngData(void *data, int dataLen);
    bool _initWithTiffData(void *data, int dataLen);
    bool _initWithWebpData(void *data, int dataLen);
    bool _initWithPVRData(void *data, int dataLen);
    bool _initWithPVRv2Data(void *data, int dataLen);
    bool _initWithPVRv3Data(void *data, int dataLen);
    bool _initWithETCData(void *data, int dataLen);

    bool _saveImageToPNG(const char *pszFilePath, bool bIsToRGB = true);
    bool _saveImageToJPG(const char *pszFilePath);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool _iosSaveToFile(const char *pszFilePath, bool bIsToRGB = true);
#endif

    unsigned char *_data;
    int _dataLen;
    int _width;
    int _height;
    FileType       _fileType;
    Texture2DPixelFormat _renderFormat;
    bool _hasAlpha;
    bool _preMulti;
    bool _compressed;
    MipmapInfo _mipmaps[CC_MIPMAP_MAX];   // pointer to mipmap images
    int _numberOfMipmaps;


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

    FileType detectFormat(void* data, int dataLen);
    bool isPng(void *data, int dataLen);
    bool isJpg(void *data, int dataLen);
    bool isTiff(void *data, int dataLen);
    bool isWebp(void *data, int dataLen);
    bool isPvr(void *data, int dataLen);
    bool isEtc(void *data, int dataLen);

    bool _testFormatForPvrTCSupport(int format);
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_IMAGE_H__
