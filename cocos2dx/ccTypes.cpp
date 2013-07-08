/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "include/ccTypes.h"

NS_CC_BEGIN

const Color3B Color3B::white(255,255,255);
const Color3B Color3B::yellow(255,255,0);
const Color3B Color3B::green(0,255,0);
const Color3B Color3B::blue(0,0,255);
const Color3B Color3B::red(255,0,0);
const Color3B Color3B::magenta(255,0,255);
const Color3B Color3B::black(0,0,0);
const Color3B Color3B::orange(255,127,0);
const Color3B Color3B::gray(166,166,166);

Color4B::Color4B(const Color4F &color4F)
:r((GLubyte)color4F.r * 255),
g((GLubyte)color4F.g * 255),
b((GLubyte)color4F.b * 255),
a((GLubyte)color4F.a * 255)
{}

const BlendFunc BlendFunc::blendFuncDisable = {GL_ONE, GL_ZERO};

NS_CC_END
