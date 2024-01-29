/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#ifndef StencilStateManager_hpp
#define StencilStateManager_hpp
#include "base/ccConfig.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCGL.h"

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

class CC_DLL StencilStateManager
{
public:
    StencilStateManager();
    void onBeforeVisit();
    void onAfterDrawStencil();
    void onAfterVisit();
    void setAlphaThreshold(GLfloat alphaThreshold);
    void setInverted(bool inverted);
    bool isInverted()const;
    GLfloat getAlphaThreshold()const;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(StencilStateManager);
    static GLint s_layer;
    /**draw fullscreen quad to clear stencil bits
     */
    void drawFullScreenQuadClearStencil();
    
    
    GLfloat _alphaThreshold;
    bool    _inverted;
    
    GLboolean _currentStencilEnabled;
    GLuint _currentStencilWriteMask;
    GLenum _currentStencilFunc;
    GLint _currentStencilRef;
    GLuint _currentStencilValueMask;
    GLenum _currentStencilFail;
    GLenum _currentStencilPassDepthFail;
    GLenum _currentStencilPassDepthPass;
    GLboolean _currentDepthWriteMask;
    
    GLboolean _currentAlphaTestEnabled;
    GLenum _currentAlphaTestFunc;
    GLclampf _currentAlphaTestRef;
    
    GLint _mask_layer_le;
};

NS_CC_END
// end of base group
/** @} */
#endif /* StencilStateManager_hpp */
