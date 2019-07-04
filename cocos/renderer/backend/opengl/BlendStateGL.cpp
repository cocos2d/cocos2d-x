/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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
 
#include "BlendStateGL.h"
#include "renderer/backend/opengl/UtilsGL.h"
CC_BACKEND_BEGIN

void BlendStateGL::reset()
{
    glDisable(GL_BLEND);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

BlendStateGL::BlendStateGL(const BlendDescriptor& descriptor)
: _blendEnabled(descriptor.blendEnabled)
, _rgbBlendOperation(UtilsGL::toGLBlendOperation(descriptor.rgbBlendOperation))
, _alphaBlendOperation(UtilsGL::toGLBlendOperation(descriptor.alphaBlendOperation))
, _sourceRGBBlendFactor(UtilsGL::toGLBlendFactor(descriptor.sourceRGBBlendFactor))
, _destinationRGBBlendFactor(UtilsGL::toGLBlendFactor(descriptor.destinationRGBBlendFactor))
, _sourceAlphaBlendFactor(UtilsGL::toGLBlendFactor(descriptor.sourceAlphaBlendFactor))
, _destinationAlphaBlendFactor(UtilsGL::toGLBlendFactor(descriptor.destinationAlphaBlendFactor))
, _writeMaskRed((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::RED)
, _writeMaskGreen((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::GREEN)
, _writeMaskBlue((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::BLUE)
, _writeMaskAlpha((uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::ALPHA)
{
}

void BlendStateGL::apply() const
{
    if (_blendEnabled)
    {
        glEnable(GL_BLEND);
        glBlendEquationSeparate(_rgbBlendOperation, _alphaBlendOperation);
        glBlendFuncSeparate(_sourceRGBBlendFactor,
                            _destinationRGBBlendFactor,
                            _sourceAlphaBlendFactor,
                            _destinationAlphaBlendFactor);
    }
    else
        glDisable(GL_BLEND);
    
    glColorMask(_writeMaskRed, _writeMaskGreen, _writeMaskBlue, _writeMaskAlpha);
}

CC_BACKEND_END
