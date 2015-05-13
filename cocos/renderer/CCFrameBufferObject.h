/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __CC_FRAME_BUFFER_H__
#define __CC_FRAME_BUFFER_H__

#include "base/CCRef.h"
#include "platform/CCGL.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

class FrameBufferObject : public Texture2D
{
public:
    static FrameBufferObject* create(uint8_t fid, unsigned int width, unsigned int height);
    
    bool init(uint8_t fid, unsigned int width, unsigned int height);
public:
    GLuint getFBO() const { return _fbo; }
    GLuint getFID() const { return _fid; }
    
CC_CONSTRUCTOR_ACCESS:
    FrameBufferObject();
    virtual ~FrameBufferObject();
private:
    //openGL content for FrameBuffer
    GLuint _fbo;
    GLuint _depthBuffer;
    //
    uint8_t _fid;
public:
    static void initDefaultFBO();
    static void applyDefaultFBO();
private:
    static GLuint _defaultFBO;
    static GLuint _defaultRenderBuffer;
};

NS_CC_END

#endif /* defined(__CC_FRAME_BUFFER_H__) */
