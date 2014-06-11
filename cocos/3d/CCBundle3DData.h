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

#ifndef __CC_BUNDLE_3D_DATA_H__
#define __CC_BUNDLE_3D_DATA_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"

#include <vector>
#include <map>

NS_CC_BEGIN

//mesh vertex attribute
struct MeshVertexAttrib
{
    //attribute size
    GLint size;
    //GL_FLOAT
    GLenum type;
    //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX, GLProgram for detail
    int  vertexAttrib;
    //size in bytes
    int attribSizeBytes;
};

struct MeshData
{
    float* vertex;
    int vertexSizeInFloat;
    unsigned short* indices;
    int numIndex;
    MeshVertexAttrib* attribs;
    int attribCount;

public:
    void resetData()
    {
        CC_SAFE_DELETE_ARRAY(vertex);
        CC_SAFE_DELETE_ARRAY(indices);
        CC_SAFE_DELETE_ARRAY(attribs);
        vertexSizeInFloat = 0;
        numIndex = 0;
        attribCount = 0;
    }
    MeshData()
    : vertex(nullptr)
    , vertexSizeInFloat(0)
    , indices(nullptr)
    , numIndex(0)
    , attribs(nullptr)
    , attribCount(0)
    {
    }
    ~MeshData()
    {
        resetData();
    }
};

struct SkinData
{
    Mat4                     bindShape;
    std::vector<std::string> boneNames;
    std::vector<Mat4>        inverseBindPoseMatrices; //bind pose of bone
    
    std::map<int, std::vector<int> > boneChild;//key parent, value child
    int                              rootBoneIndex;
    void resetData()
    {
        bindShape.setIdentity();
        boneNames.clear();
        inverseBindPoseMatrices.clear();
        boneChild.clear();
        rootBoneIndex = -1;
    }
};

struct MaterialData
{
    std::string texturePath;
};

NS_CC_END

#endif //__CC_BUNDLE_3D_DATA_H__
