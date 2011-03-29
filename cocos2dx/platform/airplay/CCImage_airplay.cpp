/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 
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

#include "CCImage.h"
#include "CCCommon.h"
#include "CCStdC.h"
#include "CCFileUtils.h"
#include "s3eFile.h"
#include "IwImage.h"
#include "IwUtil.h"

#include <string>
typedef struct 
{
    unsigned char* data;
    int size;
    int offset;
}tImageSource;

NS_CC_BEGIN;


//////////////////////////////////////////////////////////////////////////
// Implement CCImage
//////////////////////////////////////////////////////////////////////////

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_pData(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
{
	
}

CCImage::~CCImage()
{
    CC_SAFE_DELETE_ARRAY(m_pData);
}
bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
	IW_CALLSTACK("UIImage::initWithImageFile");
    CCFileData data(CCFileUtils::fullPathFromRelativePath(strPath), "rb");
    return initWithImageData(data.getBuffer(), data.getSize(), eImgFmt);
}

bool CCImage::initWithImageData(void * pData, int nDataLen, EImageFormat eFmt/* = eSrcFmtPng*/)
{
    bool bRet = false;
    do 
    {
    	CC_BREAK_IF(! pData || nDataLen <= 0);
		
        if (kFmtPng == eFmt)
        {
            bRet = _initWithPngData(pData, nDataLen);
            break;
        }
        else if (kFmtJpg == eFmt)
        {
            bRet = _initWithJpgData(pData, nDataLen);
            break;
        }
    } while (0);
    return bRet;
}

bool CCImage::_initWithJpgData(void * data, int nSize)
{	
    return true;
}

bool CCImage::_initWithPngData(void * pData, int nDatalen)
{
	IW_CALLSTACK("CCImage::_initWithPngData");
	
    bool bRet = false;
	
	s3eFile* pFile = s3eFileOpenFromMemory(pData, nDatalen);
	
	IwAssert(GAME, pFile);
	
	CIwImage    *image		= NULL;
	image = new CIwImage;
	
	image->ReadFile( pFile);
	
    s3eFileClose(pFile);
	
	// init image info
	m_bPreMulti	= true;
	m_bHasAlpha = image->HasAlpha();
	
	unsigned int bytesPerComponent = 3;
	if (m_bHasAlpha)
	{
		bytesPerComponent = 4;
	} 
	m_nHeight = (unsigned int)image->GetHeight();
	m_nWidth = (unsigned int)image->GetWidth();
	m_nBitsPerComponent = (unsigned int)image->GetBitDepth()/bytesPerComponent;
	
	tImageSource imageSource;
	
	imageSource.data    = (unsigned char*)pData;
	imageSource.size    = nDatalen;
	imageSource.offset  = 0;
	
	m_pData = new unsigned char[m_nHeight * m_nWidth * bytesPerComponent];
	
	unsigned int bytesPerRow = m_nWidth * bytesPerComponent;

	if(m_bHasAlpha)
	{
		unsigned char *src = NULL;
		src = (unsigned char *)image->GetTexels();
		
		unsigned char *tmp = (unsigned char *) m_pData;
		
		for(unsigned int i = 0; i < m_nHeight*bytesPerRow; i += bytesPerComponent)
		{
			*(tmp + i + 0)	=  (*(src + i + 0) * *(src + i + 3) + 1) >> 8;
			*(tmp + i + 1)	=  (*(src + i + 1) * *(src + i + 3) + 1) >> 8;					
			*(tmp + i + 2)	=  (*(src + i + 2) * *(src + i + 3) + 1) >> 8;
			*(tmp + i + 3)	=   *(src + i + 3);
		}
		
	}
	else
	{
		for (int j = 0; j < (m_nHeight); ++j)
		{
			memcpy(m_pData + j * bytesPerRow, image->GetTexels()+j * bytesPerRow, bytesPerRow);
			
		}
	}

	delete image;
	bRet = true;
    return bRet;
}
bool CCImage::initWithString(
							 const char *    pText, 
							 int             nWidth/* = 0*/, 
							 int             nHeight/* = 0*/,
							 ETextAlign      eAlignMask/* = kAlignCenter*/,
							 const char *    pFontName/* = nil*/,
							 int             nSize/* = 0*/)
{
	bool bRet = false;
    return bRet;	
}
NS_CC_END;
