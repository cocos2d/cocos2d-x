/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#ifndef __cocos2d_libs__CCPass__
#define __cocos2d_libs__CCPass__

#include <stdio.h>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderState.h"

NS_CC_BEGIN

class GLProgramState;
class Technique;
class Node;
class VertexAttribBinding;

class CC_DLL Pass : public RenderState
{
    friend class Material;

public:
    /** Creates a Pass with a GLProgramState.
     */
    static Pass* createWithGLProgramState(Technique* parent, GLProgramState* programState);

    static Pass* create(Technique* parent);

    /** Returns the GLProgramState */
    GLProgramState* getGLProgramState() const;

    /** Binds the GLProgramState and the RenderState.
     This method must be called before call the actual draw call.
     */
    void bind(const Mat4& modelView);
    void bind(const Mat4& modelView, bool bindAttributes);

    /** Unbinds the Pass.
     This method must be called AFTER calling the actual draw call
     */
    void unbind();

    /**
     * Sets a vertex attribute binding for this pass.
     *
     * When a mesh binding is set, the VertexAttribBinding will be automatically
     * bound when the bind() method is called for the pass.
     *
     * @param binding The VertexAttribBinding to set (or NULL to remove an existing binding).
     */
    void setVertexAttribBinding(VertexAttribBinding* binding);

    /**
     * Returns the vertex attribute binding for this pass.
     *
     * @return The vertex attribute binding for this pass.
     */
    VertexAttribBinding* getVertexAttributeBinding() const;

    uint32_t getHash() const;

    /**
     * Returns a clone (deep-copy) of this instance */
    Pass* clone() const;

protected:
    Pass();
    ~Pass();
    bool init(Technique* parent);
    bool initWithGLProgramState(Technique* parent, GLProgramState *glProgramState);

    void setGLProgramState(GLProgramState* glProgramState);
    Node* getTarget() const;

    GLProgramState* _glProgramState;
    VertexAttribBinding* _vertexAttribBinding;
};

NS_CC_END



#endif /* defined(__cocos2d_libs__CCPass__) */
