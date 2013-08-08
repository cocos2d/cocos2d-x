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


#ifndef COCOS2DX_PLATFORM_THIRDPARTY_S3TC_
#define COCOS2DX_PLATFORM_THIRDPARTY_S3TC_

#include "CCStdC.h"

enum class S3TCDecodeFlag
{
    dxt1 = 1,
    dxt3 = 3,
    dxt5 = 5,
};

//Decode S3TC encode block to 4x4 RGB32 pixels
extern void s3tc_decode_block(uint8_t **block_data,
                       uint32_t *decode_block_data,
                       unsigned int stride,
                       bool oneBitAlphaFlag,
                       uint64_t alpha,
                       S3TCDecodeFlag decodeFlag);

//Decode S3TC encode data to RGB32
 void s3tc_decode(uint8_t *encode_data,
                 uint8_t *decode_data,
                 const unsigned int pixelsWidth,
                 const unsigned int pixelsHeight,
                 S3TCDecodeFlag decodeFlag
                 );


#endif /* defined(COCOS2DX_PLATFORM_THIRDPARTY_S3TC_) */

