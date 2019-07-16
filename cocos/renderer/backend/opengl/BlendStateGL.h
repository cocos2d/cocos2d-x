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
 
#pragma once

#include "../BlendState.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN
/**
 * @addtogroup _opengl
 * @{
 */

/**
 * Set blend state to pipeline 
 */
class BlendStateGL : public BlendState
{
public:
    /// Reset to default state.
    static void reset();
    
    /**
     * @descriptor Specifies the blend descriptor.
     */
    BlendStateGL(const BlendDescriptor& descriptor);
    
    /// Set blend status to pipeline.
    void apply() const;
    
private:
    GLboolean _writeMaskRed = GL_TRUE;
    GLboolean _writeMaskGreen = GL_TRUE;
    GLboolean _writeMaskBlue = GL_TRUE;
    GLboolean _writeMaskAlpha = GL_TRUE;
    
    bool _blendEnabled = false;
    
    GLenum _rgbBlendOperation = GL_FUNC_ADD;
    GLenum _alphaBlendOperation = GL_FUNC_ADD;
    
    GLenum _sourceRGBBlendFactor = GL_ONE;
    GLenum _destinationRGBBlendFactor = GL_ZERO;
    GLenum _sourceAlphaBlendFactor = GL_ONE;
    GLenum _destinationAlphaBlendFactor = GL_ZERO;
};
//end of _opengl group
/// @}
CC_BACKEND_END
