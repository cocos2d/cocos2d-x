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
#pragma once

#include <stdio.h>

#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCCustomCommand.h"

NS_CC_BEGIN

class Technique;
class Node;
class VertexAttribBinding;
class MeshIndexData;

namespace backend
{
    class ProgramState;
    class Buffer;
}

class CC_DLL Pass : public RenderState
{
    friend class Material;

public:
    /** Creates a Pass with a GLProgramState.
     */
    static Pass* createWithProgramState(Technique* parent, backend::ProgramState* programState);

    static Pass* create(Technique* parent);

    /** Returns the ProgramState */
    backend::ProgramState* getProgramState() const;

    /** Binds the GLProgramState and the RenderState.
     This method must be called before call the actual draw call.
     */
    void bind(const Mat4& modelView);
    void bind(const Mat4& modelView, bool bindAttributes);

    void draw(const Mat4& modelView);

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
//    void setVertexAttribBinding(VertexAttribBinding* binding);

    void setAttributeInfo(MeshIndexData* meshIndexData);

    /**
     * Returns the vertex attribute binding for this pass.
     *
     * @return The vertex attribute binding for this pass.
     */
     //TODO minggo
//    VertexAttribBinding* getVertexAttributeBinding() const;

    uint32_t getHash() const;

    /**
     * Returns a clone (deep-copy) of this instance */
    Pass* clone() const;

protected:
    Pass() = default;
    ~Pass();
    bool init(Technique* parent);
    bool initWithProgramState(Technique* parent, backend::ProgramState *glProgramState);

    void setProgramState(backend::ProgramState* programState);
    Node* getTarget() const;

    backend::ProgramState* _programState = nullptr;
//    VertexAttribBinding* _vertexAttribBinding;
    CustomCommand _customCommand;
};

NS_CC_END
