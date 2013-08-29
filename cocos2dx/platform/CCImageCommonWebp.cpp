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

#include "platform/CCImage.h"
#include "textures/CCTexture2D.h"
#if defined(__native_client__) || defined(EMSCRIPTEN)
// TODO(sbc): I'm pretty sure all platforms should be including
// webph headers in this way.
#include "webp/decode.h"
#else
#include "decode.h"
#endif
#include "ccMacros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

NS_CC_BEGIN

bool CCImage::_initWithWebpData(void *pData, int nDataLen)
{
	bool bRet = false;
	do
	{
        WebPDecoderConfig config;
        if (WebPInitDecoderConfig(&config) == 0) break;
        if (WebPGetFeatures((uint8_t*)pData, nDataLen, &config.input) != VP8_STATUS_OK) break;
        if (config.input.width == 0 || config.input.height == 0) break;
        
        config.output.colorspace = MODE_RGBA;
        m_nBitsPerComponent = 8;
        m_nWidth    = config.input.width;
        m_nHeight   = config.input.height;
        m_bHasAlpha = true;
        
        int bufferSize = m_nWidth * m_nHeight * 4;
        m_pData = new unsigned char[bufferSize];
        
        config.output.u.RGBA.rgba = (uint8_t*)m_pData;
        config.output.u.RGBA.stride = m_nWidth * 4;
        config.output.u.RGBA.size = bufferSize;
        config.output.is_external_memory = 1;

        if (WebPDecode((uint8_t*)pData, nDataLen, &config) != VP8_STATUS_OK)
        {
            delete []m_pData;
            m_pData = NULL;
            break;
        }
               
        bRet = true;
	} while (0);
	return bRet;
}

NS_CC_END
