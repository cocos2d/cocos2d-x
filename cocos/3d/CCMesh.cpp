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

#include "3d/CCMesh.h"
#include "3d/CCMeshSkin.h"
#include "3d/CCSkeleton3D.h"
#include "3d/CCMeshVertexIndexData.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCRenderer.h"
#include "math/Mat4.h"

#define USE_MATERIAL 1

using namespace std;

NS_CC_BEGIN

//Generate a dummy texture when the texture file is missing
static Texture2D * getDummyTexture()
{
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("/dummyTexture");
    if(!texture)
    {
#ifdef NDEBUG
        unsigned char data[] ={0,0,0,0};//1*1 transparent picture
#else
        unsigned char data[] ={255,0,0,255};//1*1 red picture
#endif
        Image * image =new (std::nothrow) Image();
        image->initWithRawData(data,sizeof(data),1,1,sizeof(unsigned char));
        texture=Director::getInstance()->getTextureCache()->addImage(image,"/dummyTexture");
        image->release();
    }
    return texture;
}


Mesh::Mesh()
: _texture(nullptr)
, _skin(nullptr)
, _visible(true)
, _isTransparent(false)
, _meshIndexData(nullptr)
, _material(nullptr)
, _glProgramState(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _visibleChanged(nullptr)
, _blendDirty(false)
{
    
}
Mesh::~Mesh()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_skin);
    CC_SAFE_RELEASE(_meshIndexData);
    CC_SAFE_RELEASE(_material);
    CC_SAFE_RELEASE(_glProgramState);
}

GLuint Mesh::getVertexBuffer() const
{
    return _meshIndexData->getVertexBuffer()->getVBO();
}

bool Mesh::hasVertexAttrib(int attrib) const
{
    return _meshIndexData->getMeshVertexData()->hasVertexAttrib(attrib);
}

ssize_t Mesh::getMeshVertexAttribCount() const
{
    return _meshIndexData->getMeshVertexData()->getMeshVertexAttribCount();
}

const MeshVertexAttrib& Mesh::getMeshVertexAttribute(int idx)
{
    return _meshIndexData->getMeshVertexData()->getMeshVertexAttrib(idx);
}

int Mesh::getVertexSizeInBytes() const
{
    return _meshIndexData->getVertexBuffer()->getSizePerVertex();
}

Mesh* Mesh::create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices)
{
    int perVertexSizeInFloat = 0;
    std::vector<float> vertices;
    std::vector<MeshVertexAttrib> attribs;
    MeshVertexAttrib att;
    att.size = 3;
    att.type = GL_FLOAT;
    att.attribSizeBytes = att.size * sizeof(float);
    
    if (positions.size())
    {
        perVertexSizeInFloat += 3;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
        attribs.push_back(att);
    }
    if (normals.size())
    {
        perVertexSizeInFloat += 3;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_NORMAL;
        attribs.push_back(att);
    }
    if (texs.size())
    {
        perVertexSizeInFloat += 2;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
        att.size = 2;
        att.attribSizeBytes = att.size * sizeof(float);
        attribs.push_back(att);
    }
    
    bool hasNormal = (normals.size() != 0);
    bool hasTexCoord = (texs.size() != 0);
    //position, normal, texCoordinate into _vertexs
    size_t vertexNum = positions.size() / 3;
    for(size_t i = 0; i < vertexNum; i++)
    {
        vertices.push_back(positions[i * 3]);
        vertices.push_back(positions[i * 3 + 1]);
        vertices.push_back(positions[i * 3 + 2]);

        if (hasNormal)
        {
            vertices.push_back(normals[i * 3]);
            vertices.push_back(normals[i * 3 + 1]);
            vertices.push_back(normals[i * 3 + 2]);
        }
    
        if (hasTexCoord)
        {
            vertices.push_back(texs[i * 2]);
            vertices.push_back(texs[i * 2 + 1]);
        }
    }
    return create(vertices, perVertexSizeInFloat, indices, attribs);
}

Mesh* Mesh::create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs)
{
    MeshData meshdata;
    meshdata.attribs = attribs;
    meshdata.vertex = vertices;
    meshdata.subMeshIndices.push_back(indices);
    meshdata.subMeshIds.push_back("");
    auto meshvertexdata = MeshVertexData::create(meshdata);
    auto indexData = meshvertexdata->getMeshIndexDataByIndex(0);
    
    return create("", indexData);
}

Mesh* Mesh::create(const std::string& name, MeshIndexData* indexData, MeshSkin* skin)
{
    auto state = new (std::nothrow) Mesh();
    state->autorelease();
    state->bindMeshCommand();
    state->_name = name;
    state->setMeshIndexData(indexData);
    state->setSkin(skin);
    
    return state;
}

void Mesh::setVisible(bool visible)
{
    if (_visible != visible)
    {
        _visible = visible;
        if (_visibleChanged)
            _visibleChanged();
    }
}

bool Mesh::isVisible() const
{
    return _visible;
}

void Mesh::setTexture(const std::string& texPath)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texPath);
    setTexture(tex);
}

void Mesh::setTexture(Texture2D* tex)
{
#if USE_MATERIAL

    // Texture must be saved for future use
    // it doesn't matter if the material is already set or not
    // This functionality is added for compatibility issues
    if (tex != _texture)
    {
        CC_SAFE_RETAIN(tex);
        CC_SAFE_RELEASE(_texture);
        _texture = tex;
    }

    if (_material) {
        auto technique = _material->_currentTechnique;
        for(auto& pass: technique->_passes)
        {
            pass->setTexture(tex);
        }
    }

    bindMeshCommand();
#else
    if (tex != _texture)
    {
        CC_SAFE_RETAIN(tex);
        CC_SAFE_RELEASE(_texture);
        _texture = tex;
        bindMeshCommand();
    }
#endif
}

Texture2D* Mesh::getTexture() const
{
    return _texture;
}

void Mesh::setMaterial(Material* material)
{
    if (_material != material) {
        CC_SAFE_RELEASE(_material);
        _material = material;
        CC_SAFE_RETAIN(_material);
    }
}

Material* Mesh::getMaterial() const
{
    return _material;
}

void Mesh::draw(Renderer* renderer, float globalZOrder, const Mat4& transform, uint32_t flags, unsigned int lightMask, const Vec4& color, bool forceDepthWrite)
{
    if (! isVisible())
        return;

    bool isTransparent = (_isTransparent || color.w < 1.f);
    float globalZ = isTransparent ? 0 : globalZOrder;
    if (isTransparent)
        flags |= Node::FLAGS_RENDER_AS_3D;


#if USE_MATERIAL
    _meshCommand.init(globalZ,
                      _material,
                      getVertexBuffer(),
                      getIndexBuffer(),
                      getPrimitiveType(),
                      getIndexFormat(),
                      getIndexCount(),
                      transform,
                      flags);


    if (isTransparent && !forceDepthWrite)
        _material->getStateBlock()->setDepthWrite(false);
    else
        _material->getStateBlock()->setDepthWrite(true);

    // set default uniforms for Mesh
    // 'u_color' and others
    auto technique = _material->_currentTechnique;
    for(auto& pass : technique->_passes)
    {
        auto programState = pass->getGLProgramState();
        programState->setUniformVec4("u_color", color);

        if (_skin)
            programState->setUniformVec4v("u_matrixPalette", _skin->getMatrixPalette(), (int)_skin->getMatrixPaletteSize());
    }
#else

    if(!_texture)
    {
        //let the mesh use a dummy texture instead of the missing or crashing texture file
        setTexture(getDummyTexture());
    }
    GLuint textureID = _texture->getName();


    _meshCommand.init(globalZ,
                      textureID,
                      _glProgramState,
                      _blend,
                      getVertexBuffer(),
                      getIndexBuffer(),
                      getPrimitiveType(),
                      getIndexFormat(),
                      getIndexCount(),
                      transform,
                      flags);

    if (forceDepthWrite)
    {
        _meshCommand.setDepthWriteEnabled(true);
    }
    _meshCommand.setTransparent(isTransparent);

    //support tint and fade
    _meshCommand.setDisplayColor(color);

    if (_skin)
    {
        _meshCommand.setMatrixPaletteSize((int)_skin->getMatrixPaletteSize());
        _meshCommand.setMatrixPalette(_skin->getMatrixPalette());
    }

#endif // !MATERIAL

    _meshCommand.setLightMask(lightMask);


    renderer->addCommand(&_meshCommand);
}

void Mesh::setSkin(MeshSkin* skin)
{
    if (_skin != skin)
    {
        CC_SAFE_RETAIN(skin);
        CC_SAFE_RELEASE(_skin);
        _skin = skin;
        calculateAABB();
    }
}

void Mesh::setMeshIndexData(MeshIndexData* subMesh)
{
    if (_meshIndexData != subMesh)
    {
        CC_SAFE_RETAIN(subMesh);
        CC_SAFE_RELEASE(_meshIndexData);
        _meshIndexData = subMesh;
        calculateAABB();
        bindMeshCommand();
    }
}

void Mesh::setGLProgramState(GLProgramState* glProgramState)
{
    // XXX create dummy texture
#if USE_MATERIAL
    auto material = Material::createWithGLStateProgram(glProgramState);
    setMaterial(material);

    // Was the texture set before teh GLProgramState ? Set it
    if (_texture)
        setTexture(_texture);

    if (_blendDirty)
        setBlendFunc(_blend);

    bindMeshCommand();
#else
    if (_glProgramState != glProgramState)
    {
        CC_SAFE_RETAIN(glProgramState);
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = glProgramState;
        bindMeshCommand();
    }
#endif
}

GLProgramState* Mesh::getGLProgramState() const
{
#if USE_MATERIAL
    return _material ? _material->_currentTechnique->_passes.at(0)->getGLProgramState()
                    : nullptr;
#else
    return _glProgramState;
#endif
}

void Mesh::calculateAABB()
{
    if (_meshIndexData)
    {
        _aabb = _meshIndexData->getAABB();
        if (_skin)
        {
            //get skin root
            Bone3D* root = nullptr;
            Mat4 invBindPose;
            if (_skin->_skinBones.size())
            {
                root = _skin->_skinBones.at(0);
                while (root) {
                    auto parent = root->getParentBone();
                    bool parentInSkinBone = false;
                    for (const auto& bone : _skin->_skinBones) {
                        if (bone == parent)
                        {
                            parentInSkinBone = true;
                            break;
                        }
                    }
                    if (!parentInSkinBone)
                        break;
                    root = parent;
                }
            }
            
            if (root)
            {
                _aabb.transform(root->getWorldMat() * _skin->getInvBindPose(root));
            }
        }
    }
}

void Mesh::bindMeshCommand()
{
#if USE_MATERIAL
    if (_material && _meshIndexData)
    {
        auto pass = _material->_currentTechnique->_passes.at(0);
        auto glprogramstate = pass->getGLProgramState();
        auto texture = pass->getTexture();
        auto textureid = texture ? texture->getName() : 0;
        // XXX
//        auto blend = pass->getStateBlock()->getBlendFunc();
        auto blend = BlendFunc::ALPHA_PREMULTIPLIED;

        _meshCommand.genMaterialID(textureid, glprogramstate, _meshIndexData->getVertexBuffer()->getVBO(), _meshIndexData->getIndexBuffer()->getVBO(), blend);
        _material->getStateBlock()->setCullFace(true);
        _material->getStateBlock()->setDepthTest(true);
    }
#else
    if (_glProgramState && _meshIndexData && _texture)
    {
        GLuint texID = _texture ? _texture->getName() : 0;
        _meshCommand.genMaterialID(texID, _glProgramState, _meshIndexData->getVertexBuffer()->getVBO(), _meshIndexData->getIndexBuffer()->getVBO(), _blend);
        _meshCommand.setCullFaceEnabled(true);
        _meshCommand.setDepthTestEnabled(true);
    }
#endif
}

void Mesh::setBlendFunc(const BlendFunc &blendFunc)
{
#if USE_MATERIAL
    // Blend must be saved for future use
    // it doesn't matter if the material is already set or not
    // This functionality is added for compatibility issues
    if(_blend != blendFunc)
    {
        _blendDirty = true;
        _blend = blendFunc;
    }

    if (_material) {
        _material->getStateBlock()->setBlendFunc(blendFunc);
        bindMeshCommand();
    }
#else
    if(_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
    {
        _blend = blendFunc;
        bindMeshCommand();
    }
#endif
}
const BlendFunc& Mesh::getBlendFunc() const
{
#if USE_MATERIAL
// return _material->_currentTechnique->_passes.at(0)->getBlendFunc();
    return _blend;
#else
    return _blend;
#endif
}

GLenum Mesh::getPrimitiveType() const
{
    return _meshIndexData->getPrimitiveType();
}

ssize_t Mesh::getIndexCount() const
{
    return _meshIndexData->getIndexBuffer()->getIndexNumber();
}

GLenum Mesh::getIndexFormat() const
{
    return GL_UNSIGNED_SHORT;
}

GLuint Mesh::getIndexBuffer() const
{
    return _meshIndexData->getIndexBuffer()->getVBO();
}

NS_CC_END
