/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.
 
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

#ifndef COCOS2DX_PLATFORM_THIRDPARTY_ATITC_
#define COCOS2DX_PLATFORM_THIRDPARTY_ATITC_
/// @cond DO_NOT_SHOW

#include "platform/CCStdC.h"

enum class ATITCDecodeFlag
{
    ATC_RGB = 1,
    ATC_EXPLICIT_ALPHA = 3,
    ATC_INTERPOLATED_ALPHA = 5,
};

//Decode ATITC encode data to RGB32
void atitc_decode(uint8_t *encode_data,
                  uint8_t *decode_data,
                  const int pixelsWidth,
                  const int pixelsHeight,
                  ATITCDecodeFlag decodeFlag
                  );

/// @endcond
#endif /* defined(COCOS2DX_PLATFORM_THIRDPARTY_ATITC_) */
