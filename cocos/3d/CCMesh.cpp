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

#include "CCMesh.h"

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "base/ccMacros.h"
#include "renderer/ccGLStateCache.h"
#include "CCObjLoader.h"
#include "CCSprite3DDataCache.h"

using namespace std;

NS_CC_BEGIN

bool RenderMeshData::hasVertexAttrib(int attrib)
{
    for (auto itr = _vertexAttribs.begin(); itr != _vertexAttribs.end(); itr++)
    {
        if ((*itr).vertexAttrib == attrib)
            return true; //already has
    }
    return false;
}

bool RenderMeshData::initFrom(const std::vector<float>& positions,
                              const std::vector<float>& normals,
                              const std::vector<float>& texs,
                              const std::vector<unsigned short>& indices)
{
    CC_ASSERT(positions.size()<65536 * 3 && "index may out of bound");
    
    _vertexAttribs.clear();
    _vertexsizeBytes = 0;
    
    _vertexNum = positions.size() / 3; //number of vertex
    if (_vertexNum == 0)
        return false;
    
    if ((normals.size() != 0 && _vertexNum * 3 != normals.size()) || (texs.size() != 0 && _vertexNum * 2 != texs.size()))
        return false;
    
    _vertexsizeBytes += 3;
    MeshVertexAttrib meshvertexattrib;
    meshvertexattrib.size = 3;
    meshvertexattrib.type = GL_FLOAT;
    meshvertexattrib.attribSizeBytes = meshvertexattrib.size * sizeof(float);
    meshvertexattrib.vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
    _vertexAttribs.push_back(meshvertexattrib);
    
    //normal
    if (normals.size())
    {
        //add normal flag
        _vertexsizeBytes += 3;
        meshvertexattrib.vertexAttrib = GLProgram::VERTEX_ATTRIB_NORMAL;
        _vertexAttribs.push_back(meshvertexattrib);
    }
    //
    if (texs.size())
    {
        _vertexsizeBytes += 2;
        meshvertexattrib.size = 2;
        meshvertexattrib.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
        meshvertexattrib.attribSizeBytes = meshvertexattrib.size * sizeof(float);
        _vertexAttribs.push_back(meshvertexattrib);
    }
    
    _vertexs.clear();
    _vertexs.reserve(_vertexNum * _vertexsizeBytes);
    _vertexsizeBytes *= sizeof(float);
    
    bool hasNormal = hasVertexAttrib(GLProgram::VERTEX_ATTRIB_NORMAL);
    bool hasTexCoord = hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    //position, normal, texCoordinate into _vertexs
    for(int i = 0; i < _vertexNum; i++)
    {
        _vertexs.push_back(positions[i * 3]);
        _vertexs.push_back(positions[i * 3 + 1]);
        _vertexs.push_back(positions[i * 3 + 2]);
        
        if (hasNormal)
        {
            _vertexs.push_back(normals[i * 3]);
            _vertexs.push_back(normals[i * 3 + 1]);
            _vertexs.push_back(normals[i * 3 + 2]);
        }
        
        if (hasTexCoord)
        {
            _vertexs.push_back(texs[i * 2]);
            _vertexs.push_back(texs[i * 2 + 1]);
        }
    }
    _indices = indices;
    
    return true;
}

Mesh::Mesh()
:_vertexBuffer(0)
, _indexBuffer(0)
, _primitiveType(PrimitiveType::TRIANGLES)
, _indexFormat(IndexFormat::INDEX16)
, _indexCount(0)
{
}

Mesh::~Mesh()
{
    cleanAndFreeBuffers();
}

Mesh* Mesh::create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices)
{
    auto mesh = new Mesh();
    if(mesh && mesh->init(positions, normals, texs, indices))
    {
        mesh->autorelease();
        return mesh;
    }
    CC_SAFE_DELETE(mesh);
    return nullptr;
}

bool Mesh::init(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const std::vector<unsigned short>& indices)
{
    bool bRet = _renderdata.initFrom(positions, normals, texs, indices);
    if (!bRet)
        return false;
    
    restore();
    return true;
}

void Mesh::cleanAndFreeBuffers()
{
    if(glIsBuffer(_vertexBuffer))
    {
        glDeleteBuffers(1, &_vertexBuffer);
        _vertexBuffer = 0;
    }
    
    if(glIsBuffer(_indexBuffer))
    {
        glDeleteBuffers(1, &_indexBuffer);
        _indexBuffer = 0;
    }
    _primitiveType = PrimitiveType::TRIANGLES;
    _indexFormat = IndexFormat::INDEX16;
    _indexCount = 0;
}

void Mesh::buildBuffer()
{
    cleanAndFreeBuffers();

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    
    glBufferData(GL_ARRAY_BUFFER,
                 _renderdata._vertexs.size() * sizeof(_renderdata._vertexs[0]),
                 &_renderdata._vertexs[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &_indexBuffer);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    unsigned int indexSize = 2;
    IndexFormat indexformat = IndexFormat::INDEX16;
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * _renderdata._indices.size(), &_renderdata._indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    _primitiveType = PrimitiveType::TRIANGLES;
    _indexFormat = indexformat;
    _indexCount = _renderdata._indices.size();
}

void Mesh::restore()
{
    cleanAndFreeBuffers();
    buildBuffer();
}

NS_CC_END
