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

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL CCImage : public CCObject
{
public:
    CCImage();
    ~CCImage();

    typedef enum
    {
        kFmtJpg = 0,
        kFmtPng,
        kFmtTiff,
        kFmtRawData,
        kFmtUnKnown
    }EImageFormat;

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
    }ETextAlign;

    /** 
    @brief  Load the image from the specified path. 
    @param strPath   the absolute file path
    @param imageType the type of image, now only support tow types.
    @return  true if load correctly
    */
    bool initWithImageFile(const char * strPath, EImageFormat imageType = kFmtPng);

    /*
     @brief The same meaning as initWithImageFile, but it is thread safe. It is casued by
            loadImage() in CCTextureCache.cpp.
     @param fullpath  full path of the file   
     @param imageType the type of image, now only support tow types.
     @return  true if load correctly
     */
    bool initWithImageFileThreadSafe(const char *fullpath, EImageFormat imageType = kFmtPng);

    /**
    @brief  Load image from stream buffer.

    @warning kFmtRawData only support RGBA8888
    @param pBuffer  stream buffer that hold the image data
    @param nLength  the length of data(managed in byte)
    @param nWidth, nHeight, nBitsPerComponent are used for kFmtRawData
    @return true if load correctly
    */
    bool initWithImageData(void * pData, 
                           int nDataLen, 
                           EImageFormat eFmt = kFmtUnKnown,
                           int nWidth = 0,
                           int nHeight = 0,
                           int nBitsPerComponent = 8);

    /**
    @brief    Create image with specified string.
    @param  pText       the text which the image show, nil cause init fail
    @param  nWidth      the image width, if 0, the width match the text's width
    @param  nHeight     the image height, if 0, the height match the text's height
    @param  eAlignMask  the test Alignment
    @param  pFontName   the name of the font which use to draw the text. If nil, use the default system font.
    @param  nSize       the font size, if 0, use the system default size.
    */
    bool initWithString(
        const char *    pText, 
        int             nWidth = 0, 
        int             nHeight = 0,
        ETextAlign      eAlignMask = kAlignCenter,
        const char *    pFontName = 0,
        int             nSize = 0);

    unsigned char *   getData()               { return m_pData; }
    int         getDataLen()            { return m_nWidth * m_nHeight; }

    bool hasAlpha()                     { return m_bHasAlpha; }
    bool isPremultipliedAlpha()         { return m_bPreMulti; }

    /**
    @brief    Save the CCImage data to specified file with specified format.
    @param    pszFilePath        the file's absolute path, including file subfix
    @param    bIsToRGB        if the image is saved as RGB format
    */
    bool saveToFile(const char *pszFilePath, bool bIsToRGB = true);

    CC_SYNTHESIZE_READONLY(unsigned short,   m_nWidth,       Width);
    CC_SYNTHESIZE_READONLY(unsigned short,   m_nHeight,      Height);
    CC_SYNTHESIZE_READONLY(int,     m_nBitsPerComponent,   BitsPerComponent);

protected:
    bool _initWithJpgData(void *pData, int nDatalen);
    bool _initWithPngData(void *pData, int nDatalen);
    bool _initWithTiffData(void* pData, int nDataLen);
    // @warning kFmtRawData only support RGBA8888
    bool _initWithRawData(void *pData, int nDatalen, int nWidth, int nHeight, int nBitsPerComponent);

    bool _saveImageToPNG(const char *pszFilePath, bool bIsToRGB = true);
    bool _saveImageToJPG(const char *pszFilePath);

    unsigned char *m_pData;
    bool m_bHasAlpha;
    bool m_bPreMulti;

private:
    // noncopyable
    CCImage(const CCImage&    rImg);
    CCImage & operator=(const CCImage&);
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_IMAGE_H__
