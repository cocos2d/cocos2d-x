
#include "CCMesh.h"

#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "base/ccMacros.h"
#include "renderer/ccGLStateCache.h"
#include "CCMeshPart.h"
#include "CCObjLoader.h"
#include "CCSprite3DDataCache.h"

using namespace std;

NS_CC_BEGIN

std::vector<float>& RenderMeshData::generateNormals(std::vector<float>& posions, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices)
{
    static std::vector<float> _normalVertexLists;
    
    _normalVertexLists.clear();
    
    if (partindices.size() == 0)
        return _normalVertexLists;
    
    
    //generate normal using positions
    int numVertex = posions.size() / 3;
    
    std::vector<Vector3> normals;
    normals.reserve(numVertex);
    
    Vector3 v1, v2, v3, fn;
    
    std::vector<std::vector<Vector3>> faceVertexNormalList;
    faceVertexNormalList.resize(numVertex);
    
    for (const auto& partIndex : partindices)
    {
        int triangles = partIndex.size() / 3;
        for (int i = 0; i < triangles; i++)
        {
            int triangleIdx = i * 3;
            v1.set(posions[partIndex[triangleIdx] ], posions[partIndex[triangleIdx]+1 ], posions[partIndex[triangleIdx] + 2 ]);
            v2.set(posions[partIndex[triangleIdx + 1] ], posions[partIndex[triangleIdx + 1] + 1 ], posions[partIndex[triangleIdx + 1] + 2 ]);
            v3.set(posions[partIndex[triangleIdx + 2] ], posions[partIndex[triangleIdx + 2] + 1 ], posions[partIndex[triangleIdx + 2] + 2 ]);
            
            Vector3::cross(v2 - v1, v3 - v2, &fn);
            fn.normalize();
            faceVertexNormalList[partIndex[triangleIdx] ].push_back(fn);
            faceVertexNormalList[partIndex[triangleIdx + 1] ].push_back(fn);
            faceVertexNormalList[partIndex[triangleIdx + 2] ].push_back(fn);
        }
    }
    
    
    _normalVertexLists.resize(faceVertexNormalList.size() * 3);
    for (int index = 0; index < faceVertexNormalList.size(); ++index)
    {
        int idx = 3 * index;
        _normalVertexLists[idx] = 0;
        _normalVertexLists[idx + 1] = 0;
        _normalVertexLists[idx + 2] = 0;
        
        for (const auto& facenormal : faceVertexNormalList[index])
        {
            _normalVertexLists[idx] += facenormal.x;
            _normalVertexLists[idx + 1] += facenormal.y;
            _normalVertexLists[idx + 2] += facenormal.z;
        }
        
        float len = _normalVertexLists[idx] * _normalVertexLists[idx] + _normalVertexLists[idx + 1] * _normalVertexLists[idx + 1] + _normalVertexLists[idx + 2] * _normalVertexLists[idx + 2];
        len = sqrtf(len) * faceVertexNormalList[index].size();
        
        _normalVertexLists[idx] /= len;
        _normalVertexLists[idx + 1] /= len;
        _normalVertexLists[idx + 2] /= len;
    }
    return _normalVertexLists;
}

bool RenderMeshData::hasVertexAttrib(int attrib)
{
    for (auto itr = _vertexAttribs.begin(); itr != _vertexAttribs.end(); itr++) {
        if ((*itr).vertexAttrib == GLProgram::VERTEX_ATTRIB_NORMAL)
            return true; //already has normal
    }
    return false;
}

bool RenderMeshData::generateNormals()
{
    if (_partindices.size() == 0)
        return false;
    
    if (hasVertexAttrib(GLProgram::VERTEX_ATTRIB_NORMAL))
        return true;

    //generate normal using positions
    int numVertex = _vertexs.size() / vertexNum;
    
    std::vector<Vector3> normals;
    normals.reserve(numVertex);
    
    Vector3 v1, v2, v3, fn;
    
    std::vector<std::vector<Vector3>> faceVertexNormalList;
    faceVertexNormalList.resize(numVertex);
    
    for (const auto& partIndex : _partindices)
    {
        int triangles = partIndex.size() / 3;
        for (int i = 0; i < triangles; i++)
        {
            int triangleIdx = i * 3;
            v1.set(_vertexs[partIndex[triangleIdx] ], _vertexs[partIndex[triangleIdx]+1 ], _vertexs[partIndex[triangleIdx] + 2 ]);
            v2.set(_vertexs[partIndex[triangleIdx + 1] ], _vertexs[partIndex[triangleIdx + 1] + 1 ], _vertexs[partIndex[triangleIdx + 1] + 2 ]);
            v3.set(_vertexs[partIndex[triangleIdx + 2] ], _vertexs[partIndex[triangleIdx + 2] + 1 ], _vertexs[partIndex[triangleIdx + 2] + 2 ]);
            
            Vector3::cross(v2 - v1, v3 - v2, &fn);
            fn.normalize();
            faceVertexNormalList[partIndex[triangleIdx] ].push_back(fn);
            faceVertexNormalList[partIndex[triangleIdx + 1] ].push_back(fn);
            faceVertexNormalList[partIndex[triangleIdx + 2] ].push_back(fn);
        }
    }
    
    std::vector<Vector3> _normalVertexLists;
    _normalVertexLists.resize(faceVertexNormalList.size());
    for (int index = 0; index < _normalVertexLists.size(); ++index)
    {
        _normalVertexLists[index] = Vector3(0,0,0);
        for (const auto& facenormal : faceVertexNormalList[index])
        {
            _normalVertexLists[index] += facenormal;
        }
        
        _normalVertexLists[index] *= 1.0f / faceVertexNormalList[index].size();
        _normalVertexLists[index].normalize();
    }
    
    //insert normals to _vertexs
    int vertexsize = vertexsizeBytes / sizeof(float);
    std::vector<float> vertexs((vertexsize + 3) * numVertex);
    
    for (int i = 0; i < numVertex; i++)
    {
        int idx = i * vertexsize;
        vertexs.push_back(_vertexs[idx]);
        vertexs.push_back(_vertexs[idx + 1]);
        vertexs.push_back(_vertexs[idx + 2]);
        idx = i * 3;
        vertexs.push_back(_normalVertexLists[idx].x);
        vertexs.push_back(_normalVertexLists[idx].y);
        vertexs.push_back(_normalVertexLists[idx].z);
        if (hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD))
        {
            idx = i * vertexsize;
            vertexs.push_back(_vertexs[idx + 3]);
            vertexs.push_back(_vertexs[idx + 4]);
        }
        
    }
    _vertexs = vertexs;
    
    return true;
}

bool RenderMeshData::initFrom(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices)
{
    CC_ASSERT(posions.size()<65536 * 3 && "index may out of bound");
    
    _vertexAttribs.clear();
    vertexsizeBytes = 0;
    
    vertexNum = posions.size() / 3; //number of vertex
    if (vertexNum == 0)
        return false;
    
    
    if ((normals.size() != 0 && vertexNum * 3 != normals.size()) || (texs.size() != 0 && vertexNum * 2 != texs.size()))
        return false;
    
    if (normals.size() == 0)
        normals = generateNormals(posions, texs, partindices);
    
    vertexsizeBytes += 3;
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
        vertexsizeBytes += 3;
        meshvertexattrib.vertexAttrib = GLProgram::VERTEX_ATTRIB_NORMAL;
        _vertexAttribs.push_back(meshvertexattrib);
    }
    //
    if (texs.size())
    {
        vertexsizeBytes += 2;
        meshvertexattrib.size = 2;
        meshvertexattrib.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
        meshvertexattrib.attribSizeBytes = meshvertexattrib.size * sizeof(float);
        _vertexAttribs.push_back(meshvertexattrib);
    }
    
    _vertexs.clear();
    _vertexs.reserve(vertexNum * vertexsizeBytes);
    vertexsizeBytes *= sizeof(float);
    
    //position, normal, texCoordinate into _vertexs
    for(int i = 0; i < vertexNum; i++)
    {
        _vertexs.push_back(posions[i * 3]);
        _vertexs.push_back(posions[i * 3 + 1]);
        _vertexs.push_back(posions[i * 3 + 2]);
        
        if (hasVertexAttrib(GLProgram::VERTEX_ATTRIB_NORMAL))
        {
            _vertexs.push_back(normals[i * 3]);
            _vertexs.push_back(normals[i * 3 + 1]);
            _vertexs.push_back(normals[i * 3 + 2]);
        }
        
        if (hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD))
        {
            _vertexs.push_back(texs[i * 2]);
            _vertexs.push_back(texs[i * 2 + 1]);
        }
    }
    _partindices = partindices;
    
    return true;
}


Mesh::Mesh()
:_vertexBuffer(0)
, _parts(nullptr)
, _partCount(0)
{
    

}

Mesh::~Mesh()
{
    releaseMeshPart();
    
    freeBuffers();
}

void Mesh::releaseMeshPart()
{
    for (unsigned int i = 0; i < _partCount; ++i)
    {
        delete _parts[i];
    }
    delete _parts;
}

Mesh* Mesh::create(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices)
{
    auto mesh = new Mesh();
    if(mesh && mesh->init(posions, normals, texs, partindices))
    {
        mesh->autorelease();
        return mesh;
    }
    CC_SAFE_DELETE(mesh);
    return nullptr;
}

bool Mesh::init(std::vector<float>& posions, std::vector<float>& normals, std::vector<float>& texs, const std::vector<std::vector<unsigned short> >& partindices)
{
    
    bool bRet = _renderdata.initFrom(posions, normals, texs, partindices);
    if (!bRet)
        return false;
    
    restore();
    
    return true;
}

void Mesh::freeBuffers()
{
    if(glIsBuffer(_vertexBuffer))
    {
        glDeleteBuffers(1, &_vertexBuffer);
        _vertexBuffer = 0;
    }
}

void Mesh::buildBuffer()
{
    freeBuffers();

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    
    glBufferData(GL_ARRAY_BUFFER,
                 _renderdata._vertexs.size() * sizeof(_renderdata._vertexs[0]),
                 &_renderdata._vertexs[0],
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::addMeshPart(PrimitiveType primitiveType, IndexFormat indexformat,  void* indexData, unsigned int indexCount)
{
    MeshPart* part = MeshPart::create(this, _partCount, primitiveType, indexformat, indexData, indexCount);
    if (part)
    {
        // Increase size of part array and copy old subets into it.
        MeshPart** oldParts = _parts;
        _parts = new MeshPart*[_partCount + 1];
        for (unsigned int i = 0; i < _partCount; ++i)
        {
            _parts[i] = oldParts[i];
        }
        
        // Add new part to array.
        _parts[_partCount++] = part;
        
        // Delete old part array.
        delete[] (oldParts);
    }
}

void Mesh::restore()
{
    releaseMeshPart();
    
    buildBuffer();
    
    for (auto i = 0; i < _renderdata._partindices.size(); i++) {
        auto& idxs = _renderdata._partindices[i];
        addMeshPart(PrimitiveType_TRIANGLES, IndexFormat_INDEX16, (void*)&idxs[0], idxs.size());
    }
}

NS_CC_END
