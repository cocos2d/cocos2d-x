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

#include "3d/CCSprite3D.h"
#include "3d/CCMesh.h"
#include "3d/CCObjLoader.h"
#include "3d/CCMeshSkin.h"
#include "3d/CCBundle3D.h"
#include "3d/CCSprite3DMaterial.h"

#include "base/CCDirector.h"
#include "base/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"

#include "deprecated/CCString.h" // For StringUtils::format

NS_CC_BEGIN

std::string s_attributeNames[] = {GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::ATTRIBUTE_NAME_BLEND_INDEX};

Sprite3D* Sprite3D::create(const std::string &modelPath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new Sprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite3D* Sprite3D::create(const std::string &modelPath, const std::string &texturePath)
{
    auto sprite = create(modelPath);
    if (sprite)
    {
        sprite->setTexture(texturePath);
    }
    
    return sprite;
}

// Sprite3D* Sprite3D::create(Mesh* mesh, const std::string& texturePath)
// {
//     CCASSERT(nullptr != mesh, "Could not create a Sprite3D from a null Mesh");
//     auto sprite = new Sprite3D();
//     if(sprite)
//     {
//         sprite->_mesh = mesh;
//         sprite->_mesh->retain();
//         sprite->setTexture(texturePath);
//         sprite->autorelease();
//         return sprite;
//     }
//     CC_SAFE_DELETE(sprite);
//     return nullptr;
// }

//.mtl file should at the same directory with the same name if exist
bool Sprite3D::loadFromObj(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    //find from the cache
    std::string key = fullPath + "#";
    auto mesh = MeshCache::getInstance()->getMesh(key);
    if (mesh)
    {
        _mesh = mesh;
        _mesh->retain();
        
        auto tex = Sprite3DMaterialCache::getInstance()->getSprite3DMaterial(key);
        setTexture(tex);
        
        genGLProgramState();
        
        return true;
    }
    
    //.mtl file directory
    std::string dir = "";
    auto last = fullPath.rfind("/");
    if (last != -1)
        dir = fullPath.substr(0, last + 1);
    
    ObjLoader::shapes_t shapes;
    std::string errstr = ObjLoader::LoadObj(shapes, fullPath.c_str(), dir.c_str());
    if (!errstr.empty())
        return false;
    
    //convert to mesh and material
    std::vector<unsigned short> indices;
    std::vector<std::string> matnames;
    std::string texname;
    for (auto it = shapes.shapes.begin(); it != shapes.shapes.end(); it++)
    {
        indices.insert(indices.end(), (*it).mesh.indices.begin(),(*it).mesh.indices.end());
        //indices.push_back((*it).mesh.indices);
        if (texname.empty())
            texname = (*it).material.diffuse_texname;
        else if (texname != (*it).material.diffuse_texname)
        {
            CCLOGWARN("cocos2d:WARNING: more than one texture in %s", path.c_str());
        }
            
        matnames.push_back(dir + (*it).material.diffuse_texname);
    }
    _mesh = Mesh::create(shapes.positions, shapes.normals, shapes.texcoords, indices);
    
    _mesh->retain();
    if (_mesh == nullptr)
        return false;
    
    if (matnames.size())
    {
        setTexture(matnames[0]);
    }
    genGLProgramState();
    
    //add to cache
    
    if (_texture)
    {
        Sprite3DMaterialCache::getInstance()->addSprite3DMaterial(key, _texture);
    }
    
    MeshCache::getInstance()->addMesh(key, _mesh);

    return true;
}

bool Sprite3D::loadFromC3x(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    //find from the cache
    std::string key = fullPath + "#";
    auto mesh = MeshCache::getInstance()->getMesh(key);
    if (mesh)
    {
        _mesh = mesh;
        _mesh->retain();
        
        auto tex = Sprite3DMaterialCache::getInstance()->getSprite3DMaterial(key);
        setTexture(tex);
        
        _skin = MeshSkin::create(fullPath, "");
        CC_SAFE_RETAIN(_skin);
        
        genGLProgramState();
        
        return true;
    }
    
    //load from .c3b or .c3t
    auto bundle = Bundle3D::getInstance();
    if (!bundle->load(fullPath))
        return false;
    
    MeshData meshdata;
    bool ret = bundle->loadMeshData("", &meshdata);
    if (!ret)
    {
        return false;
    }
    
    _mesh = Mesh::create(meshdata.vertex, meshdata.vertexSizeInFloat, meshdata.indices, meshdata.attribs);
    CC_SAFE_RETAIN(_mesh);
    
    _skin = MeshSkin::create(fullPath, "");
    CC_SAFE_RETAIN(_skin);
    
    MaterialData materialdata;
    ret = bundle->loadMaterialData("", &materialdata);
    if (ret)
    {
        setTexture(materialdata.texturePath);
    }
    
    genGLProgramState();
    
    //add to cache
    auto cache = Director::getInstance()->getTextureCache();
    auto tex = cache->addImage(materialdata.texturePath);
    if (tex)
        Sprite3DMaterialCache::getInstance()->addSprite3DMaterial(key, tex);
    
    MeshCache::getInstance()->addMesh(key, _mesh);
    
    return true;
}

Sprite3D::Sprite3D()
: _mesh(nullptr)
, _skin(nullptr)
, _texture(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
{
}

Sprite3D::~Sprite3D()
{
    CC_SAFE_RELEASE_NULL(_texture);
    CC_SAFE_RELEASE_NULL(_mesh);
    CC_SAFE_RELEASE_NULL(_skin);
}

bool Sprite3D::initWithFile(const std::string &path)
{
    CC_SAFE_RELEASE_NULL(_mesh);
    CC_SAFE_RELEASE_NULL(_skin);
    CC_SAFE_RELEASE_NULL(_texture);
    
    //load from file
    std::string ext = path.substr(path.length() - 4, 4);
    std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
    
    if (ext == ".obj")
    {
        return loadFromObj(path);
    }
    else if (ext == ".c3b" || ext == ".c3t")
    {
        return loadFromC3x(path);
    }
    
    return false;
}

void Sprite3D::genGLProgramState()
{
    auto programstate = GLProgramState::getOrCreateWithGLProgram(getDefaultGLProgram(_mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD)));
    long offset = 0;
    auto attributeCount = _mesh->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = _mesh->getMeshVertexAttribute(k);
        programstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                             meshattribute.size,
                                             meshattribute.type,
                                             GL_FALSE,
                                             _mesh->getVertexSizeInBytes(),
                                             (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }
    
    setGLProgramState(programstate);
    GLuint texID = _texture ? _texture->getName() : 0;
    _meshCommand.genMaterialID(texID, programstate, _mesh, _blend);
}

GLProgram* Sprite3D::getDefaultGLProgram(bool textured)
{
    bool hasSkin = _skin && _mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_INDEX)
    && _mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
    
    if(textured)
    {
        if (hasSkin)
            return GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_SKINPOSITION_TEXTURE);
        
        return GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
    }
    else
    {
        return GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION);
    }
}

void Sprite3D::setTexture(const std::string& texFile)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
//    if( tex && _texture != tex ) {
//        CC_SAFE_RETAIN(tex);
//        CC_SAFE_RELEASE_NULL(_texture);
//        _texture = tex;
//    }
    setTexture(tex);
}

void Sprite3D::setTexture(Texture2D* texture)
{
    if(_texture != texture) {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE_NULL(_texture);
        _texture = texture;
        if (getGLProgramState() && _mesh)
        {
            GLuint texID = _texture ? _texture->getName() : 0;
            _meshCommand.genMaterialID(texID, getGLProgramState(), _mesh, _blend);
        }
    }
}

void Sprite3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    GLProgramState* programstate = getGLProgramState();
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    GLuint textureID = _texture ? _texture->getName() : 0;
    _meshCommand.init(_globalZOrder,
                      textureID,
                      programstate,
                      _blend,
                      _mesh->getVertexBuffer(),
                      _mesh->getIndexBuffer(),
                      (GLenum)_mesh->getPrimitiveType(),
                      (GLenum)_mesh->getIndexFormat(),
                      _mesh->getIndexCount(),
                      transform);
    
    _meshCommand.setCullFaceEnabled(true);
    _meshCommand.setDepthTestEnabled(true);
    if (_skin)
    {
        _meshCommand.setMatrixPaletteSize((int)_skin->getMatrixPaletteSize());
        _meshCommand.setMatrixPalette(_skin->getMatrixPalette());
    }
    //support tint and fade
    _meshCommand.setDisplayColor(Vec4(color.r, color.g, color.b, color.a));
    Director::getInstance()->getRenderer()->addCommand(&_meshCommand);
}

void Sprite3D::setBlendFunc(const BlendFunc &blendFunc)
{
    if(_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
    {
        _blend = blendFunc;
    }
}

const BlendFunc& Sprite3D::getBlendFunc() const
{
    return _blend;
}

NS_CC_END
