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
#include "renderer/CCMeshCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCCallbackCommand.h"

NS_CC_BEGIN

class Technique;
class Node;
class VertexAttribBinding;
class MeshIndexData;
class RenderState;

namespace backend
{
    class ProgramState;
    class Buffer;
}

class CC_DLL Pass : public Ref
{
    friend class Material;
    friend class Technique;
    friend class RenderState;
    friend class VertexAttribBinding;
public:
    /** Creates a Pass with a GLProgramState.
     */
    static Pass* createWithProgramState(Technique* parent, backend::ProgramState* programState);

    static Pass* create(Technique* parent);

    /** Returns the ProgramState */
    backend::ProgramState* getProgramState() const;

    void draw(MeshCommand *meshCommand, float globalZOrder, backend::Buffer* vertexBuffer, backend::Buffer* indexBuffer,
              MeshCommand::PrimitiveType primitive, MeshCommand::IndexFormat indexFormat,
              unsigned int indexCount, const Mat4& modelView);

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

    void setName(const std::string &name) { _name = name; }
    const std::string &getName() const { return _name; }

    inline RenderState::StateBlock &getStateBlock() { return _renderState._state; }

    /**
     * Returns a clone (deep-copy) of this instance */
    Pass* clone() const;

    void setTechnique(Technique *technique);

    void updateMVPUniform(const Mat4& modelView);
    
    void setUniformTexture(uint32_t slot, backend::TextureBackend *);      //u_texture
    void setUniformNormTexture(uint32_t slot, backend::TextureBackend *);  //u_texture

    void setUniformColor(const void *, size_t);                 //ucolor
    void setUniformMatrixPalette(const void *, size_t);         //u_matrixPalette

    void setUniformDirLightColor(const void *, size_t);
    void setUniformDirLightDir(const void *, size_t);

    void setUniformPointLightColor(const void *, size_t);
    void setUniformPointLightPosition(const void *, size_t);
    void setUniformPointLightRangeInverse(const void *, size_t);

    void setUniformSpotLightColor(const void *, size_t);
    void setUniformSpotLightPosition(const void *, size_t);
    void setUniformSpotLightDir(const void *, size_t);
    void setUniformSpotLightInnerAngleCos(const void *, size_t);
    void setUniformSpotLightOuterAngleCos(const void *, size_t);
    void setUniformSpotLightRangeInverse(const void *, size_t);

    void setUniformAmbientLigthColor(const void *, size_t);

protected:
    Pass();
    ~Pass();
    bool init(Technique* parent);
    bool initWithProgramState(Technique* parent, backend::ProgramState *glProgramState);

    void setProgramState(backend::ProgramState* programState);
    Node* getTarget() const;

    VertexAttribBinding*        _vertexAttribBinding    = nullptr;
    backend::ProgramState *     _programState           = nullptr;
    Technique *                 _technique              = nullptr;
    bool                        _hashDirty              = true;
    RenderState                 _renderState;
    std::string                 _name;

private:
    
    void initUniformLocations();
    void onBeforeVisitCmd(MeshCommand *);
    void onAfterVisitCmd(MeshCommand *);

    backend::UniformLocation _locMVPMatrix;
    backend::UniformLocation _locMVMatrix;
    backend::UniformLocation _locPMatrix;
    backend::UniformLocation _locNormalMatrix;

    backend::UniformLocation _locTexture;               //u_texture
    backend::UniformLocation _locNormalTexture;         //u_normalTex

    backend::UniformLocation _locColor;                 //ucolor
    backend::UniformLocation _locMatrixPalette;         //u_matrixPalette

    backend::UniformLocation _locDirLightColor;
    backend::UniformLocation _locDirLightDir;

    backend::UniformLocation _locPointLightColor;
    backend::UniformLocation _locPointLightPosition;
    backend::UniformLocation _locPointLightRangeInverse;

    backend::UniformLocation _locSpotLightColor;
    backend::UniformLocation _locSpotLightPosition;
    backend::UniformLocation _locSpotLightDir;
    backend::UniformLocation _locSpotLightInnerAngleCos;
    backend::UniformLocation _locSpotLightOuterAngleCos;
    backend::UniformLocation _locSpotLightRangeInverse;

    backend::UniformLocation _locAmbientLigthColor;

    //renderer state cache variables
    bool                        _rendererDepthTestEnabled   = true;
    backend::CompareFunction    _rendererDepthCmpFunc       = backend::CompareFunction::LESS;
    backend::CullMode           _rendererCullMode           = backend::CullMode::BACK;
    backend::Winding            _rendererWinding            = backend::Winding::COUNTER_CLOCK_WISE;
    bool                        _rendererDepthWrite         = false;
};

NS_CC_END
