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

#include "CCRenderCommand.h"
#include "renderer/CCGLProgram.h"
#include "math/CCMath.h"
#include "CCRenderCommandPool.h"

NS_CC_BEGIN

class GLProgramState;
class GLProgram;
class Uniform;

//it is a common mesh
class MeshCommand : public RenderCommand
{
public:

    MeshCommand();
    ~MeshCommand();

    void init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexType, ssize_t indexCount, const Mat4 &mv);
    
    void setCullFaceEnabled(bool enable);
    
    void setCullFace(GLenum cullFace);
    
    void setDepthTestEnabled(bool enable);
    
    void setDepthWriteEnabled(bool enable);
    
    void setDisplayColor(const Vec4& color);
    
    void setMatrixPalette(const Vec4* matrixPalette) { _matrixPalette = matrixPalette; }
    
    void setMatrixPaletteSize(int size) { _matrixPaletteSize = size; }

    void execute();

protected:
    // apply renderstate
    void applyRenderState();
    
    //restore to all false
    void restoreRenderState();
    
    void MatrixPalleteCallBack( GLProgram* glProgram, Uniform* uniform);

    GLuint _textureID;
    GLProgramState* _glProgramState;
    BlendFunc _blendType;

    GLuint _textrueID;
    
    Vec4 _displayColor; // in order to support tint and fade in fade out
    
    // used for skin
    const Vec4* _matrixPalette;
    int   _matrixPaletteSize;
    
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

    // ModelView transform
    Mat4 _mv;
};
NS_CC_END

#endif //_CC_MESHCOMMAND_H_
