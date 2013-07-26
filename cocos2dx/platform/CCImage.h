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

class CC_DLL Image : public Object
{
public:
    friend class TextureCache;
    
    Image();
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
    @brief  Load the image from the specified path. 
    @param strPath   the absolute file path.
    @param imageType the type of image, currently only supporting two types.
    @return  true if loaded correctly.
    */
    bool initWithImageFile(const char * strPath, Format imageType = Format::PNG);

    /**
    @brief  Load image from stream buffer.

    @warning kFmtRawData only supports RGBA8888.
    @param pBuffer  stream buffer which holds the image data.
    @param nLength  data length expressed in (number of) bytes.
    @param nWidth, nHeight, nBitsPerComponent are used for kFmtRawData.
    @return true if loaded correctly.
    */
    bool initWithImageData(void * pData, 
                           int nDataLen, 
                           Format eFmt = Format::UNKOWN,
                           int nWidth = 0,
                           int nHeight = 0,
                           int nBitsPerComponent = 8);

    // @warning kFmtRawData only support RGBA8888
    bool initWithRawData(void *pData, int nDatalen, int nWidth, int nHeight, int nBitsPerComponent, bool bPreMulti);

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
        TextAlign       eAlignMask = TextAlign::CENTER,
        const char *    pFontName = 0,
        int             nSize = 0);
    
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
    

    /**
     @brief    Save Image data to the specified file, with specified format.
     @param    pszFilePath        the file's absolute path, including file suffix.
     @param    bIsToRGB        whether the image is saved as RGB format.
     */
    bool saveToFile(const char *pszFilePath, bool bIsToRGB = true);
    
    // Getters
    inline unsigned char *   getData()               { return _data; }
    inline int               getDataLen()            { return _width * _height; }

    inline bool hasAlpha()                     { return _hasAlpha;   }
    inline bool isPremultipliedAlpha()         { return _preMulti;   }

    inline unsigned short getWidth() { return _width; };
    inline unsigned short getHeight() { return _height; };
    inline int getBitsPerComponent() { return _bitsPerComponent; };
    //
    
protected:
    bool initWithJpgData(void *pData, int nDatalen);
    bool initWithPngData(void *pData, int nDatalen);
    bool initWithTiffData(void *pData, int nDataLen);
    bool initWithWebpData(void *pData, int nDataLen);

    bool saveImageToPNG(const char *pszFilePath, bool bIsToRGB = true);
    bool saveImageToJPG(const char *pszFilePath);

    unsigned short   _width;
    unsigned short   _height;
    int     _bitsPerComponent;
    
    unsigned char *_data;
    bool _hasAlpha;
    bool _preMulti;


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
    bool initWithImageFileThreadSafe(const char *fullpath, Format imageType = Format::PNG);
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_IMAGE_H__
