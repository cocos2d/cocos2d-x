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
#include "3d/CCObjLoader.h"
#include "3d/CCMeshSkin.h"
#include "3d/CCBundle3D.h"
#include "3d/CCSprite3DMaterial.h"
#include "3d/CCAttachNode.h"
#include "3d/CCMesh.h"

#include "base/CCDirector.h"
#include "2d/CCLight.h"
#include "2d/CCCamera.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"

#include "deprecated/CCString.h" // For StringUtils::format

NS_CC_BEGIN

std::string s_attributeNames[] = {GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::ATTRIBUTE_NAME_TEX_COORD2,GLProgram::ATTRIBUTE_NAME_TEX_COORD3,GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::ATTRIBUTE_NAME_BLEND_INDEX};

Sprite3D* Sprite3D::create(const std::string &modelPath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new (std::nothrow) Sprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->_contentSize = sprite->getBoundingBox().size;
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

bool Sprite3D::loadFromCache(const std::string& path)
{
    auto spritedata = Sprite3DCache::getInstance()->getSpriteData(path);
    if (spritedata)
    {
        for (auto it : spritedata->meshVertexDatas) {
            _meshVertexDatas.pushBack(it);
        }
        _skeleton = Skeleton3D::create(spritedata->nodedatas->skeleton);
        CC_SAFE_RETAIN(_skeleton);
        
        for(const auto& it : spritedata->nodedatas->nodes)
        {
            if(it)
            {
                createNode(it, this, *(spritedata->materialdatas), spritedata->nodedatas->nodes.size() == 1);
            }
        }
        
        for(const auto& it : spritedata->nodedatas->skeleton)
        {
            if(it)
            {
                createAttachSprite3DNode(it,*(spritedata->materialdatas));
            }
        }
        
        for (ssize_t i = 0; i < _meshes.size(); i++) {
            _meshes.at(i)->setGLProgramState(spritedata->glProgramStates.at(i));
        }
        return true;
    }
    
    return false;
}

//.mtl file should at the same directory with the same name if exist
bool Sprite3D::loadFromObj(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    MeshDatas meshdatas;
    MaterialDatas* materialdatas = new (std::nothrow) MaterialDatas();
    NodeDatas*   nodeDatas = new (std::nothrow) NodeDatas();
    bool ret = Bundle3D::loadObj(meshdatas, *materialdatas, *nodeDatas, fullPath);
    if (ret && initFrom(*nodeDatas, meshdatas, *materialdatas))
    {
        //add to cache
        auto data = new (std::nothrow) Sprite3DCache::Sprite3DData();
        data->materialdatas = materialdatas;
        data->nodedatas = nodeDatas;
        data->meshVertexDatas = _meshVertexDatas;
        for (const auto mesh : _meshes) {
            data->glProgramStates.pushBack(mesh->getGLProgramState());
        }
        
        Sprite3DCache::getInstance()->addSprite3DData(path, data);
        return true;
    }
    delete materialdatas;
    delete nodeDatas;

    return false;
}
bool Sprite3D::loadFromC3x(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);

    //load from .c3b or .c3t
    auto bundle = Bundle3D::getInstance();
    if (!bundle->load(fullPath))
        return false;
    
    MeshDatas meshdatas;
    MaterialDatas* materialdatas = new (std::nothrow) MaterialDatas();
    NodeDatas*   nodeDatas = new (std::nothrow) NodeDatas();
    if (bundle->loadMeshDatas(meshdatas)
        && bundle->loadMaterials(*materialdatas)
        && bundle->loadNodes(*nodeDatas)
        && initFrom(*nodeDatas, meshdatas, *materialdatas))
    {
        //add to cache
        auto data = new (std::nothrow) Sprite3DCache::Sprite3DData();
        data->materialdatas = materialdatas;
        data->nodedatas = nodeDatas;
        data->meshVertexDatas = _meshVertexDatas;
        for (const auto mesh : _meshes) {
            data->glProgramStates.pushBack(mesh->getGLProgramState());
        }
        Sprite3DCache::getInstance()->addSprite3DData(path, data);
        return true;
    }
    
    delete materialdatas;
    delete nodeDatas;
    
    return false;
}

Sprite3D::Sprite3D()
: _skeleton(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _aabbDirty(true)
, _lightMask(-1)
, _shaderUsingLight(false)
{
}

Sprite3D::~Sprite3D()
{
    _meshes.clear();
    _meshVertexDatas.clear();
    CC_SAFE_RELEASE_NULL(_skeleton);
    removeAllAttachNode();
}

bool Sprite3D::initWithFile(const std::string &path)
{
    _meshes.clear();
    _meshVertexDatas.clear();
    CC_SAFE_RELEASE_NULL(_skeleton);
    removeAllAttachNode();
    
    if (loadFromCache(path))
        return true;
    
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

bool Sprite3D::initFrom(const NodeDatas& nodeDatas, const MeshDatas& meshdatas, const MaterialDatas& materialdatas)
{
    for(const auto& it : meshdatas.meshDatas)
    {
        if(it)
        {
//            Mesh* mesh = Mesh::create(*it);
//            _meshes.pushBack(mesh);
            auto meshvertex = MeshVertexData::create(*it);
            _meshVertexDatas.pushBack(meshvertex);
        }
    }
    _skeleton = Skeleton3D::create(nodeDatas.skeleton);
    CC_SAFE_RETAIN(_skeleton);
    
    for(const auto& it : nodeDatas.nodes)
    {
        if(it)
        {
            createNode(it, this, materialdatas, nodeDatas.nodes.size() == 1);
        }
    }
    for(const auto& it : nodeDatas.skeleton)
    {
        if(it)
        {
             createAttachSprite3DNode(it,materialdatas);
        }
    }
    genGLProgramState();
    
    return true;
}
Sprite3D* Sprite3D::createSprite3DNode(NodeData* nodedata,ModelData* modeldata,const MaterialDatas& matrialdatas)
{
    auto sprite = new (std::nothrow) Sprite3D();
    if (sprite)
    {
        sprite->setName(nodedata->id);
        auto mesh = Mesh::create(nodedata->id, getMeshIndexData(modeldata->subMeshId));
        if (modeldata->matrialId == "" && matrialdatas.materials.size())
        {
            const NTextureData* textureData = matrialdatas.materials[0].getTextureData(NTextureData::Usage::Diffuse);
            mesh->setTexture(textureData->filename);
        }
        else
        {
            const NMaterialData*  materialData=matrialdatas.getMaterialData(modeldata->matrialId);
            if(materialData)
            {
                const NTextureData* textureData = materialData->getTextureData(NTextureData::Usage::Diffuse);
                if(textureData)
                {
                    auto tex = Director::getInstance()->getTextureCache()->addImage(textureData->filename);
                    if(tex)
                    {
                        Texture2D::TexParams    texParams;
                        texParams.minFilter = GL_LINEAR;
                        texParams.magFilter = GL_LINEAR;
                        texParams.wrapS = textureData->wrapS;
                        texParams.wrapT = textureData->wrapT;
                        tex->setTexParameters(texParams);
                        mesh->setTexture(tex);
                        mesh->_isTransparent = (materialData->getTextureData(NTextureData::Usage::Transparency) != nullptr);
                    }

                }
            }
        }
        sprite->setAdditionalTransform(&nodedata->transform);
        sprite->addMesh(mesh);
        sprite->autorelease();
        sprite->genGLProgramState(); 
    }
    return   sprite;
}
void Sprite3D::createAttachSprite3DNode(NodeData* nodedata,const MaterialDatas& matrialdatas)
{
    for(const auto& it : nodedata->modelNodeDatas)
    {
        if(it && getAttachNode(nodedata->id))
        {
            auto sprite = createSprite3DNode(nodedata,it,matrialdatas);
            if (sprite)
            {
                getAttachNode(nodedata->id)->addChild(sprite);
            } 
        }
    }
    for(const auto& it : nodedata->children)
    {
        createAttachSprite3DNode(it,matrialdatas);
    }
}
void Sprite3D::genGLProgramState(bool useLight)
{
    _shaderUsingLight = useLight;
    
    std::unordered_map<const MeshVertexData*, GLProgramState*> glProgramestates;
    for(auto& mesh : _meshVertexDatas)
    {
        bool textured = mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD);
        bool hasSkin = mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_INDEX)
        && mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
        bool hasNormal = mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_NORMAL);
        
        GLProgram* glProgram = nullptr;
        const char* shader = nullptr;
        if(textured)
        {
            if (hasSkin)
            {
                if (hasNormal && _shaderUsingLight)
                    shader = GLProgram::SHADER_3D_SKINPOSITION_NORMAL_TEXTURE;
                else
                    shader = GLProgram::SHADER_3D_SKINPOSITION_TEXTURE;
            }
            else
            {
                if (hasNormal && _shaderUsingLight)
                    shader = GLProgram::SHADER_3D_POSITION_NORMAL_TEXTURE;
                else
                    shader = GLProgram::SHADER_3D_POSITION_TEXTURE;
            }
        }
        else
        {
            shader = GLProgram::SHADER_3D_POSITION;
        }
        if (shader)
            glProgram = GLProgramCache::getInstance()->getGLProgram(shader);
        
        auto programstate = GLProgramState::create(glProgram);
        long offset = 0;
        auto attributeCount = mesh->getMeshVertexAttribCount();
        for (auto k = 0; k < attributeCount; k++) {
            auto meshattribute = mesh->getMeshVertexAttrib(k);
            programstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                                 meshattribute.size,
                                                 meshattribute.type,
                                                 GL_FALSE,
                                                 mesh->getVertexBuffer()->getSizePerVertex(),
                                                 (GLvoid*)offset);
            offset += meshattribute.attribSizeBytes;
        }
        
        glProgramestates[mesh] = programstate;
    }
    
    for (auto& it : _meshes) {
        auto glProgramState = glProgramestates[it->getMeshIndexData()->getMeshVertexData()];
        it->setGLProgramState(glProgramState);
    }
}

void Sprite3D::createNode(NodeData* nodedata, Node* root, const MaterialDatas& matrialdatas, bool singleSprite)
{
    Node* node=nullptr;
    for(const auto& it : nodedata->modelNodeDatas)
    {
        if(it)
        {
            if(it->bones.size() > 0 || singleSprite)
            {
                auto mesh = Mesh::create(nodedata->id, getMeshIndexData(it->subMeshId));
                if(mesh)
                {
                    _meshes.pushBack(mesh);
                    if (_skeleton && it->bones.size())
                    {
                        auto skin = MeshSkin::create(_skeleton, it->bones, it->invBindPose);
                        mesh->setSkin(skin);
                    }
                    mesh->_visibleChanged = std::bind(&Sprite3D::onAABBDirty, this);

                    if (it->matrialId == "" && matrialdatas.materials.size())
                    {
                        const NTextureData* textureData = matrialdatas.materials[0].getTextureData(NTextureData::Usage::Diffuse);
                        mesh->setTexture(textureData->filename);
                    }
                    else
                    {
                        const NMaterialData*  materialData=matrialdatas.getMaterialData(it->matrialId);
                        if(materialData)
                        {
                            const NTextureData* textureData = materialData->getTextureData(NTextureData::Usage::Diffuse);
                            if(textureData)
                            {
                                auto tex = Director::getInstance()->getTextureCache()->addImage(textureData->filename);
                                if(tex)
                                {
                                    Texture2D::TexParams    texParams;
                                    texParams.minFilter = GL_LINEAR;
                                    texParams.magFilter = GL_LINEAR;
                                    texParams.wrapS = textureData->wrapS;
                                    texParams.wrapT = textureData->wrapT;
                                    tex->setTexParameters(texParams);
                                    mesh->setTexture(tex);
                                    mesh->_isTransparent = (materialData->getTextureData(NTextureData::Usage::Transparency) != nullptr);
                                }

                            }
                        }
                    }
                }
            }
            else
            {
                auto sprite = createSprite3DNode(nodedata,it,matrialdatas);
                if (sprite)
                {
                    if(root)
                    {
                        root->addChild(sprite);
                    } 
                }
                node=sprite;
            } 
        }
    }
    if(nodedata->modelNodeDatas.size() ==0 )
    {
        node= Node::create();
        if(node)
        {
            node->setName(nodedata->id);
            node->setAdditionalTransform(&nodedata->transform);
            if(root)
            {
                root->addChild(node);
            } 
        }
    }
    for(const auto& it : nodedata->children)
    {
        createNode(it,node, matrialdatas, singleSprite);
    }
}

MeshIndexData* Sprite3D::getMeshIndexData(const std::string& indexId) const
{
    for (auto it : _meshVertexDatas) {
        auto index = it->getMeshIndexDataById(indexId);
        if (index)
            return index;
    }
    return nullptr;
}

void  Sprite3D::addMesh(Mesh* mesh)
{
    auto meshVertex = mesh->getMeshIndexData()->_vertexData;
    _meshVertexDatas.pushBack(meshVertex);
    _meshes.pushBack(mesh);
}

void Sprite3D::setTexture(const std::string& texFile)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
    setTexture(tex);
}

void Sprite3D::setTexture(Texture2D* texture)
{
    for (auto& state : _meshes) {
        state->setTexture(texture);
    }
}
AttachNode* Sprite3D::getAttachNode(const std::string& boneName)
{
    auto it = _attachments.find(boneName);
    if (it != _attachments.end())
        return it->second;
    
    if (_skeleton)
    {
        auto bone = _skeleton->getBoneByName(boneName);
        auto attachNode = AttachNode::create(bone);
        addChild(attachNode);
        _attachments[boneName] = attachNode;
        return attachNode;
    }
    
    return nullptr;
}

void Sprite3D::removeAttachNode(const std::string& boneName)
{
    auto it = _attachments.find(boneName);
    if (it != _attachments.end())
    {
        removeChild(it->second);
        _attachments.erase(it);
    }
}

void Sprite3D::removeAllAttachNode()
{
    for (auto& it : _attachments) {
        removeChild(it.second);
    }
    _attachments.clear();
}

#ifndef NDEBUG
//Generate a dummy texture when the texture file is missing
static Texture2D * getDummyTexture()
{
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("/dummyTexture");
    if(!texture)
    {
        unsigned char data[] ={255,0,0,255};//1*1 pure red picture
        Image * image =new (std::nothrow) Image();
        image->initWithRawData(data,sizeof(data),1,1,sizeof(unsigned char));
        texture=Director::getInstance()->getTextureCache()->addImage(image,"/dummyTexture");
        image->release();
    }
    return texture;
}
#endif

void Sprite3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_skeleton)
        _skeleton->updateBoneMatrix();
    
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    //check light and determine the shader used
    const auto& lights = Director::getInstance()->getRunningScene()->getLights();
    bool usingLight = false;
    for (const auto light : lights) {
        usingLight = ((unsigned int)light->getLightFlag() & _lightMask) > 0;
        if (usingLight)
            break;
    }
    if (usingLight != _shaderUsingLight)
        genGLProgramState(usingLight);
    
    int i = 0;
    for (auto& mesh : _meshes) {
        if (!mesh->isVisible())
        {
            i++;
            continue;
        }
        auto programstate = mesh->getGLProgramState();
        auto& meshCommand = mesh->getMeshCommand();
#ifdef NDEBUG
        GLuint textureID = mesh->getTexture() ? mesh->getTexture()->getName() : 0;
#else
        GLuint textureID = 0;
        if(mesh->getTexture())
        {
            textureID = mesh->getTexture()->getName();
        }else
        { //let the mesh use a dummy texture instead of the missing or crashing texture file
            auto texture = getDummyTexture();
            mesh->setTexture(texture);
            textureID = texture->getName();
        }
#endif
        float globalZ = _globalZOrder;
        bool isTransparent = (mesh->_isTransparent || color.a < 1.f);
        if (isTransparent && Camera::getVisitingCamera())
        {   // use the view matrix for Applying to recalculating transparent mesh's Z-Order
            const auto& viewMat = Camera::getVisitingCamera()->getViewMatrix();
            globalZ = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);//fetch the Z from the result matrix
        }
        meshCommand.init(globalZ, textureID, programstate, _blend, mesh->getVertexBuffer(), mesh->getIndexBuffer(), mesh->getPrimitiveType(), mesh->getIndexFormat(), mesh->getIndexCount(), transform);
        
        meshCommand.setLightMask(_lightMask);

        auto skin = mesh->getSkin();
        if (skin)
        {
            meshCommand.setMatrixPaletteSize((int)skin->getMatrixPaletteSize());
            meshCommand.setMatrixPalette(skin->getMatrixPalette());
        }
        //support tint and fade
        meshCommand.setDisplayColor(Vec4(color.r, color.g, color.b, color.a));
        meshCommand.setTransparent(isTransparent);
        renderer->addCommand(&meshCommand);
    }
}

void Sprite3D::setGLProgramState(GLProgramState *glProgramState)
{
    Node::setGLProgramState(glProgramState);
    for (auto& state : _meshes) {
        state->setGLProgramState(glProgramState);
    }
}
void Sprite3D::setGLProgram(GLProgram *glprogram)
{
    Node::setGLProgram(glprogram);
    setGLProgramState(getGLProgramState());
}

void Sprite3D::setBlendFunc(const BlendFunc &blendFunc)
{
    if(_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
    {
        _blend = blendFunc;
        for(auto& state : _meshes)
        {
            state->setBlendFunc(blendFunc);
        }
    }
}

const BlendFunc& Sprite3D::getBlendFunc() const
{
    return _blend;
}

const AABB& Sprite3D::getAABB() const
{
    Mat4 nodeToWorldTransform(getNodeToWorldTransform());
    
    // If nodeToWorldTransform matrix isn't changed, we don't need to transform aabb.
    if (memcmp(_nodeToWorldTransform.m, nodeToWorldTransform.m, sizeof(Mat4)) == 0 && !_aabbDirty)
    {
        return _aabb;
    }
    else
    {
        _aabb.reset();
        Mat4 transform(nodeToWorldTransform);
        for (const auto& it : _meshes) {
            if (it->isVisible())
                _aabb.merge(it->getAABB());
        }
        
        _aabb.transform(transform);
        _nodeToWorldTransform = nodeToWorldTransform;
    }
    
    return _aabb;
}

Rect Sprite3D::getBoundingBox() const
{
    AABB aabb = getAABB();
    Rect ret(aabb._min.x, aabb._min.y, (aabb._max.x - aabb._min.x), (aabb._max.y - aabb._min.y));
    return ret;
}

void Sprite3D::setCullFace(GLenum cullFace)
{
    for (auto& it : _meshes) {
        it->getMeshCommand().setCullFace(cullFace);
    }
}

void Sprite3D::setCullFaceEnabled(bool enable)
{
    for (auto& it : _meshes) {
        it->getMeshCommand().setCullFaceEnabled(enable);
    }
}

Mesh* Sprite3D::getMeshByIndex(int index) const
{
    CCASSERT(index < _meshes.size(), "invald index");
    return _meshes.at(index);
}

/**get Mesh by Name */
Mesh* Sprite3D::getMeshByName(const std::string& name) const
{
    for (const auto& it : _meshes) {
        if (it->getName() == name)
            return it;
    }
    return nullptr;
}

std::vector<Mesh*> Sprite3D::getMeshArrayByName(const std::string& name) const
{
    std::vector<Mesh*> meshes;
    for (const auto& it : _meshes) {
        if (it->getName() == name)
            meshes.push_back(it);
    }
    return meshes;
}

MeshSkin* Sprite3D::getSkin() const
{
    for (const auto& it : _meshes) {
        if (it->getSkin())
            return it->getSkin();
    }
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////
Sprite3DCache* Sprite3DCache::_cacheInstance = nullptr;
Sprite3DCache* Sprite3DCache::getInstance()
{
    if (_cacheInstance == nullptr)
        _cacheInstance = new (std::nothrow) Sprite3DCache();
    return _cacheInstance;
}
void Sprite3DCache::destroyInstance()
{
    if (_cacheInstance)
    {
        delete _cacheInstance;
        _cacheInstance = nullptr;
    }
}

Sprite3DCache::Sprite3DData* Sprite3DCache::getSpriteData(const std::string& key) const
{
    auto it = _spriteDatas.find(key);
    if (it != _spriteDatas.end())
        return it->second;
    return nullptr;
}

bool Sprite3DCache::addSprite3DData(const std::string& key, Sprite3DCache::Sprite3DData* spritedata)
{
    auto it = _spriteDatas.find(key);
    if (it == _spriteDatas.end())
    {
        _spriteDatas[key] = spritedata;
        return true;
    }
    return false;
}

void Sprite3DCache::removeSprite3DData(const std::string& key)
{
    auto it = _spriteDatas.find(key);
    if (it != _spriteDatas.end())
    {
        delete it->second;
    }
    _spriteDatas.erase(it);
}

void Sprite3DCache::removeAllSprite3DData()
{
    for (auto& it : _spriteDatas) {
        delete it.second;
    }
    _spriteDatas.clear();
}

Sprite3DCache::Sprite3DCache()
{
    
}
Sprite3DCache::~Sprite3DCache()
{
    removeAllSprite3DData();
}

NS_CC_END
