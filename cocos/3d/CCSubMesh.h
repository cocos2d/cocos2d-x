/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCSUBMESH_H__
#define __CCSUBMESH_H__

#include <string>
#include <vector>

#include "3d/CCBundle3DData.h"

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"
#include "3d/3dExport.h"

NS_CC_BEGIN

/** Defines supported index formats. */
enum class IndexFormat
{
    INDEX8 = GL_UNSIGNED_BYTE,
    INDEX16 = GL_UNSIGNED_SHORT,
};

/** Defines supported primitive types. */
enum class PrimitiveType
{
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    LINES = GL_LINES,
    LINE_STRIP = GL_LINE_STRIP,
    POINTS = GL_POINTS
};

/**
 * SubMesh: Defines the way the mesh's vertices how to be connected together.
 */
class CC_3D_DLL SubMesh : public Ref
{
    friend class Mesh;
public:

    /**create submesh from primitivetype indexformat and indices*/
    static SubMesh* create(PrimitiveType primitivetype, IndexFormat indexformat, const std::vector<unsigned short>& indices);
    
    /** get primitive type*/
    PrimitiveType getPrimitiveType() const { return _primitiveType; }
    /**get index count*/
    ssize_t getIndexCount() const { return _indexCount; }
    /**get index format*/
    IndexFormat getIndexFormat() const { return _indexFormat; }
    /**get index buffer*/
    GLuint getIndexBuffer() const {return _indexBuffer; }


CC_CONSTRUCTOR_ACCESS:
    
    SubMesh();
    virtual ~SubMesh();

    /**build buffer*/
    void buildBuffer(const std::vector<unsigned short>& indices);
    /**free buffer*/
    void cleanAndFreeBuffers();

protected:
    PrimitiveType _primitiveType;
    IndexFormat _indexFormat;

    GLuint _indexBuffer;
    ssize_t _indexCount;
};

NS_CC_END

#endif // __CCMESH_H_
