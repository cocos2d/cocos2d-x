/****************************************************************************
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

#ifndef _CC_MESHCOMMAND_H_
#define _CC_MESHCOMMAND_H_

#include <unordered_map>
#include "renderer/CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCRenderState.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class GLProgramState;
class EventListenerCustom;
class EventCustom;
class Material;

//it is a common mesh
class CC_DLL MeshCommand : public RenderCommand
{
public:

    MeshCommand();
    virtual ~MeshCommand();

    void init(float globalZOrder, Material* material, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, ssize_t indexCount, const Mat4 &mv, uint32_t flags);

    void init(float globalZOrder, GLuint textureID, GLProgramState* glProgramState, RenderState::StateBlock* stateBlock, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, ssize_t indexCount, const Mat4 &mv, uint32_t flags);

    void setDisplayColor(const Vec4& color);
    void setMatrixPalette(const Vec4* matrixPalette);
    void setMatrixPaletteSize(int size);
    void setLightMask(unsigned int lightmask);

    void execute();
    
    //used for batch
    void preBatchDraw();
    void batchDraw();
    void postBatchDraw();
    
    void genMaterialID(GLuint texID, void* glProgramState, GLuint vertexBuffer, GLuint indexBuffer, BlendFunc blend);
    
    uint32_t getMaterialID() const;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    void listenRendererRecreated(EventCustom* event);
#endif

protected:
    //build & release vao
    void buildVAO();
    void releaseVAO();
    
    // apply renderstate, not used when using material
    void applyRenderState();


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


    // ModelView transform
    Mat4 _mv;

    // Mode A: Material
    // weak ref
    Material* _material;

    // Mode B: StateBlock
    // weak ref
    GLProgramState* _glProgramState;
    RenderState::StateBlock* _stateBlock;
    GLuint _textureID;


#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _rendererRecreatedListener;
#endif
};

NS_CC_END

#endif //_CC_MESHCOMMAND_H_
