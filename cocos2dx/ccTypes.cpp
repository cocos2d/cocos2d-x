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

const Color3B Color3B::WHITE(255,255,255);
const Color3B Color3B::YELLOW(255,255,0);
const Color3B Color3B::GREEN(0,255,0);
const Color3B Color3B::BLUE(0,0,255);
const Color3B Color3B::RED(255,0,0);
const Color3B Color3B::MAGENTA(255,0,255);
const Color3B Color3B::BLACK(0,0,0);
const Color3B Color3B::ORANGE(255,127,0);
const Color3B Color3B::GRAY(166,166,166);

Color4B::Color4B(const Color4F &color4F)
: r((GLubyte)(color4F.r * 255.0f)),
  g((GLubyte)(color4F.g * 255.0f)),
  b((GLubyte)(color4F.b * 255.0f)),
  a((GLubyte)(color4F.a * 255.0f))
{}

const BlendFunc BlendFunc::DISABLE = {GL_ONE, GL_ZERO};
const BlendFunc BlendFunc::ALPHA_PREMULTIPLIED = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
const BlendFunc BlendFunc::ALPHA_NON_PREMULTIPLIED = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
const BlendFunc BlendFunc::ADDITIVE = {GL_SRC_ALPHA, GL_ONE};

NS_CC_END
