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

#include "CCImage.h"
#include <stdio.h>
#include <string.h>
#include "platform/third_party/common/webp/webp/decode.h"
#include "platform/third_party/common/webp/webp/mux.h"

NS_CC_BEGIN

bool CCImage::initWithWebpData(void * pData, int nDataLen)
{
	bool bRet = false;
	do
	{
		int width = 0;
		int height = 0;
		//WebPGetInfo((uint8_t*)pData, nDataLen, &width, &height);
		uint8_t* data = WebPDecodeRGBA((uint8_t*)pData, nDataLen, &width, &height);
		if(data) {
			if(0 == width || 0 == height) {
				free(data);
				break;
			}
			m_nBitsPerComponent = 8;
			m_nHeight   = (short)height;
			m_nWidth    = (short)width;
			m_bHasAlpha = true;
			m_pData = (unsigned char*)data;
			bRet = true;
		}
	} while (0);
	return bRet;
}

NS_CC_END
