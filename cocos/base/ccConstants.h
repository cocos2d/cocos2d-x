/****************************************************************************
 Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.
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

#pragma once

#include "base/ccMacros.h"

NS_CC_BEGIN

namespace GLBlendConst {
    const int ZERO                    = 0;        //GL_ZERO;
    const int ONE                     = 1;        //GL_ONE;
    const int SRC_COLOR               = 0x0300;   //GL_SRC_COLOR;
    const int ONE_MINUS_SRC_COLOR     = 0x0301;   //GL_ONE_MINUS_SRC_COLOR;
    const int DST_COLOR               = 0x0306;   //GL_DST_COLOR;
    const int ONE_MINUS_DST_COLOR     = 0x0307;   //GL_ONE_MINUS_DST_COLOR;
    const int SRC_ALPHA               = 0x0302;   //GL_SRC_ALPHA;
    const int ONE_MINUS_SRC_ALPHA     = 0x0303;   //GL_ONE_MINUS_SRC_ALPHA;
    const int DST_ALPHA               = 0x0304;   //GL_DST_ALPHA;
    const int ONE_MINUS_DST_ALPHA     = 0x0305;   //GL_ONE_MINUS_DST_ALPHA;
    const int CONSTANT_ALPHA          = 0x8003;   //GL_CONSTANT_ALPHA;
    const int ONE_MINUS_CONSTANT_ALPHA = 0x8004;  //GL_ONE_MINUS_CONSTANT_ALPHA;
    const int SRC_ALPHA_SATURATE      = 0x0308;   //GL_SRC_ALPHA_SATURATE;
    const int BLEND_COLOR             = 0x8005;   //GL_BLEND_COLOR
}


NS_CC_END