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

#ifndef __CCX_IMAGE_H_YANGWS_20110115__
#define __CCX_IMAGE_H_YANGWS_20110115__

#include "ccxCommon.h"

NS_CC_BEGIN;

class CCXImage;

class CCX_DLL_PS CCXImage
{
public:
    CCXImage();

    typedef enum
    {
        eFmtJpg = 0,
        eFmtPng,
    }EImageFormat;

    /** 
    Load the image from the specified path. 
    @param strPath   the absolute file path
    @param imageType the type of image, now only support tow types.
    @return  true if load correctly
    */
    bool initWithImageFile(const char * strPath, EImageFormat imageType = eFmtPng);

    /**
    Load image from stream buffer.

    @warning Only support png data now.
    @param pBuffer  stream buffer that hold the image data
    @param nLength  the length of data(managed in byte)
    @return true if load correctly
    */
    bool initWithImageData(void * pData, int nDataLen, EImageFormat eFmt = eFmtPng);

    ccxByte *   getData()               { return m_pData.get(); }
    int         getDataLen()            { return m_nWidth * m_nHeight; }
    int         getColorSpace()         { return 1; }

    bool hasAlpha()                     { return m_bHasAlpha; }
    bool isPremultipliedAlpha()         { return m_bPreMulti; }

    /**
    @brief	Save the CCXImage data to specified file with specified format.
    */
    bool saveToFile(const char * pszFilePath) { return false; }

    CCX_SYNTHESIZE_READONLY(ccxInt16,   m_nWidth,       Width);
    CCX_SYNTHESIZE_READONLY(ccxInt16,   m_nHeight,      Height);
    CCX_SYNTHESIZE_READONLY(int,        m_nBitsPerComponent,         BitsPerComponent);

protected:
    bool _initWithJpgData(void * pData, int nDatalen);
    bool _initWithJpgFile(const char * strPath);
    bool _initWithPngData(void * pData, int nDatalen);

    CCXScopedPtr<ccxByte> m_pData;
    bool m_bHasAlpha;
    bool m_bPreMulti;

private:
    // noncopyable
    CCXImage(const CCXImage&    rImg);
    CCXImage & operator=(const CCXImage&);
};

NS_CC_END;

#endif	// __CCX_IMAGE_H_YANGWS_20110115__
