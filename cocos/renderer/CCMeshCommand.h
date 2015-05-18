/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef _CC_MESHCOMMAND_H_
#define _CC_MESHCOMMAND_H_

#include <unordered_map>
#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class GLProgramState;
class GLProgram;
struct Uniform;
class EventListenerCustom;
class EventCustom;
class Material;

//it is a common mesh
class CC_DLL MeshCommand : public RenderCommand
{
public:

    MeshCommand();
    ~MeshCommand();

    void init(float globalZOrder, Material* material, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, ssize_t indexCount, const Mat4 &mv, uint32_t flags);

    void init(float globalZOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, ssize_t indexCount, const Mat4 &mv, uint32_t flags);
    
    CC_DEPRECATED_ATTRIBUTE void init(float globalZOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexType, ssize_t indexCount, const Mat4 &mv);
    
    void setCullFaceEnabled(bool enable);
    
    void setCullFace(GLenum cullFace);
    
    void setDepthTestEnabled(bool enable);
    
    void setDepthWriteEnabled(bool enable);
    
    void setDisplayColor(const Vec4& color);
    
    void setMatrixPalette(const Vec4* matrixPalette);
    
    void setMatrixPaletteSize(int size);

    void setLightMask(unsigned int lightmask);
    
    void setTransparent(bool value);
    
    void execute();
    
    //used for batch
    void preBatchDraw();
    void batchDraw();
    void postBatchDraw();
    
    void genMaterialID(GLuint texID, void* glProgramState, GLuint vertexBuffer, GLuint indexBuffer, BlendFunc blend);
    
    uint32_t getMaterialID() const;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    void listenRendererRecreated(EventCustom* event);
#endif

protected:
    //build & release vao
    void buildVAO();
    void releaseVAO();
    
    // apply renderstate, not used when using material
    void applyRenderState();
    void restoreRenderState();

    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;
    
    Vec4 _displayColor; // in order to support tint and fade in fade out
    
    // used for skin
    const Vec4* _matrixPalette;
    int   _matrixPaletteSize;
    
    uint32_t _materialID; //material ID
    
    GLuint   _vao; //use vao if possible
    
    GLuint _vertexBuffer;
    GLuint _indexBuffer;
    GLenum _primitive;
    GLenum _indexFormat;
    ssize_t _indexCount;
    
    // States, default value all false
    bool _cullFaceEnabled;
    GLenum _cullFace;
    bool _depthTestEnabled;
    bool _depthWriteEnabled;
    bool _forceDepthWrite;
    
    bool _renderStateCullFaceEnabled;
    bool _renderStateDepthTest;
    GLboolean _renderStateDepthWrite;
    GLenum    _renderStateCullFace;

    // ModelView transform
    Mat4 _mv;

    // weak ref
    Material* _material;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

NS_CC_END

#endif //_CC_MESHCOMMAND_H_
