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
#include "3d/CCSubMesh.h"
#include "3d/CCAttachNode.h"
#include "3d/CCSubMeshState.h"
#include "3d/CCSkeleton3D.h"

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

std::string s_attributeNames[] = {GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::ATTRIBUTE_NAME_BLEND_INDEX};

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

bool Sprite3D::loadFromCache(const std::string& path)
{
    //FIX ME, TODO
    
    return false;
}

//.mtl file should at the same directory with the same name if exist
bool Sprite3D::loadFromObj(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::string key = fullPath + "#";
    
    MeshDatas meshdatas;
    MaterialDatas materialdatas;
    NodeDatas   nodeDatas;
    bool ret = Bundle3D::loadObj(meshdatas, materialdatas, nodeDatas, fullPath);
    if (ret)
    {
        return initFrom(nodeDatas, meshdatas, materialdatas);
    }
//    //add mesh to cache
//    MeshCache::getInstance()->addMesh(key, _mesh);

    return false;
}
bool Sprite3D::loadFromC3x(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::string key = fullPath + "#";

    //load from .c3b or .c3t
    auto bundle = Bundle3D::getInstance();
    if (!bundle->load(fullPath))
        return false;
    
    MeshDatas meshdatas;
    MaterialDatas materialdatas;
    NodeDatas   nodeDatas;
    if (bundle->loadMeshDatas(meshdatas)
        && bundle->loadMaterials(materialdatas)
        && bundle->loadNodes(nodeDatas))
    {
        return initFrom(nodeDatas, meshdatas, materialdatas);
    }
    
    return false;
}

Sprite3D::Sprite3D()
: _skeleton(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _aabbDirty(true)
{
}

Sprite3D::~Sprite3D()
{
    _subMeshStates.clear();
    _meshes.clear();
    CC_SAFE_RELEASE_NULL(_skeleton);
    removeAllAttachNode();
}

bool Sprite3D::initWithFile(const std::string &path)
{
    _subMeshStates.clear();
    _meshes.clear();
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
            Mesh* mesh = Mesh::create(*it);
            _meshes.pushBack(mesh);
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
    
    genGLProgramState();
    
    return true;
}

void Sprite3D::genGLProgramState()
{
    if (_meshes.size() == 0)
        return;
    
    //all the mesh should have the same attributes, FIX ME
    auto mesh = _meshes.at(0);
    
    auto programstate = GLProgramState::getOrCreateWithGLProgram(getDefaultGLProgram(mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD)));
    long offset = 0;
    auto attributeCount = mesh->getMeshVertexAttribCount();
    for (auto k = 0; k < attributeCount; k++) {
        auto meshattribute = mesh->getMeshVertexAttribute(k);
        programstate->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
                                             meshattribute.size,
                                             meshattribute.type,
                                             GL_FALSE,
                                             mesh->getVertexSizeInBytes(),
                                             (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }
    
    setGLProgramState(programstate);
    auto count = _subMeshStates.size();
    _meshCommands.resize(count);
    for (int i = 0; i < count; i++) {
        auto tex = _subMeshStates.at(i)->getTexture();
        GLuint texID = tex ? tex->getName() : 0;
        _meshCommands[i].genMaterialID(texID, programstate, _subMeshStates.at(i)->getSubMesh()->getMesh(), _blend);
    }
}

GLProgram* Sprite3D::getDefaultGLProgram(bool textured)
{
    if (_meshes.size() == 0)
        return nullptr;
    
    //all the mesh should have the same attributes, FIX ME
    auto mesh = _meshes.at(0);
    
    bool hasSkin = mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_INDEX)
    && mesh->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
    
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
void Sprite3D::createNode(NodeData* nodedata, Node* root, const MaterialDatas& matrialdatas, bool singleSprite)
{
    Node* node=nullptr;
    ModelNodeData*   modelNodeData=nodedata->asModelNodeData();
    if(modelNodeData)
    {
        if(modelNodeData->bones.size() > 0 || singleSprite)
        {
            auto subMeshState = SubMeshState::create(modelNodeData->id);
            if(subMeshState)
            {
                _subMeshStates.pushBack(subMeshState);
                subMeshState->setSubMesh(getSubMesh(modelNodeData->subMeshId));
                if (_skeleton && modelNodeData->bones.size())
                {
                    auto skin = MeshSkin::create(_skeleton, modelNodeData->bones, modelNodeData->invBindPose);
                    subMeshState->setSkin(skin);
                }
                subMeshState->_visibleChanged = std::bind(&Sprite3D::onAABBDirty, this);

                if (modelNodeData->matrialId == "" && matrialdatas.materials.size())
                {
                    const NTextureData* textureData = matrialdatas.materials[0].getTextureData(NTextureData::Usage::Diffuse);
                    subMeshState->setTexture(textureData->filename);
                }
                else
                {
                    const NMaterialData*  materialData=matrialdatas.getMaterialData(modelNodeData->matrialId);
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
                                subMeshState->setTexture(tex);
                            }

                        }
                    }
                }
            }
        }
        else
        {
            auto sprite = new Sprite3D();
            if (sprite)
            {
                auto subMeshState = SubMeshState::create(modelNodeData->id);
                subMeshState->setSubMesh(getSubMesh(modelNodeData->subMeshId));
                if (modelNodeData->matrialId == "" && matrialdatas.materials.size())
                {
                    const NTextureData* textureData = matrialdatas.materials[0].getTextureData(NTextureData::Usage::Diffuse);
                    subMeshState->setTexture(textureData->filename);
                }
                else
                {
                    const NMaterialData*  materialData=matrialdatas.getMaterialData(modelNodeData->matrialId);
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
                                subMeshState->setTexture(tex);
                            }

                        }
                    }
                }
                sprite->setAdditionalTransform(&nodedata->transform);
                sprite->addSubMeshState(subMeshState);
                sprite->autorelease();
                sprite->genGLProgramState();
                if(root)
                {
                    root->addChild(sprite);
                } 
            }
            node=sprite;
        }
    }
    else
    {
        node= Node::create();
        if(node)
        {
            node->setAdditionalTransform(&nodedata->transform);
            if(root)
            {
                root->addChild(node);
            } 
        }
    }
    for(int i = 0; i < nodedata->children.size(); i++ )
    {
        NodeData* childData = nodedata->children[i];
        if(childData)
        {
            createNode(childData,node, matrialdatas, singleSprite);
        }
    }
}

SubMesh* Sprite3D::getSubMesh(const std::string& subMeshId) const
{
    for (auto it : _meshes) {
        auto subMesh = it->getSubMeshById(subMeshId);
        if (subMesh)
            return subMesh;
    }
    return nullptr;
}

void  Sprite3D::addSubMeshState(SubMeshState* subMeshState)
{
    _meshes.pushBack(subMeshState->getSubMesh()->getMesh());
    _subMeshStates.pushBack(subMeshState);
}

void Sprite3D::setTexture(const std::string& texFile)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
    setTexture(tex);
}

void Sprite3D::setTexture(Texture2D* texture)
{
    _subMeshStates.at(0)->setTexture(texture);
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

void Sprite3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_skeleton)
        _skeleton->updateBoneMatrix();
    
    GLProgramState* programstate = getGLProgramState();
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    int i = 0;
    for (auto& submeshstate : _subMeshStates) {
        if (!submeshstate->isVisible())
            continue;
        
        auto& meshCommand = _meshCommands[i++];
        
        GLuint textureID = submeshstate->getTexture() ? submeshstate->getTexture()->getName() : 0;
        auto submesh = submeshstate->getSubMesh();
        meshCommand.init(_globalZOrder, textureID, programstate, _blend, submesh->getMesh()->getVertexBuffer(), submesh->getIndexBuffer(), (GLenum)submesh->getPrimitiveType(), (GLenum)submesh->getIndexFormat(), submesh->getIndexCount(), transform);
        
        meshCommand.setCullFaceEnabled(true);
        meshCommand.setDepthTestEnabled(true);
        auto skin = submeshstate->getSkin();
        if (skin)
        {
            meshCommand.setMatrixPaletteSize((int)skin->getMatrixPaletteSize());
            meshCommand.setMatrixPalette(skin->getMatrixPalette());
        }
        //support tint and fade
        meshCommand.setDisplayColor(Vec4(color.r, color.g, color.b, color.a));
        renderer->addCommand(&meshCommand);
    }
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
        for (const auto& it : _subMeshStates) {
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
    for (auto& it : _meshCommands) {
        it.setCullFace(cullFace);
    }
}

void Sprite3D::setCullFaceEnabled(bool enable)
{
    for (auto& it : _meshCommands) {
        it.setCullFaceEnabled(enable);
    }
}

SubMeshState* Sprite3D::getSubMeshState(int index) const
{
    CCASSERT(index < _subMeshStates.size(), "invald index");
    return _subMeshStates.at(index);
}

/**get SubMeshState by Name */
SubMeshState* Sprite3D::getSubMeshStateByName(const std::string& name) const
{
    for (const auto& it : _subMeshStates) {
        if (it->getName() == name)
            return it;
    }
    return nullptr;
}

MeshSkin* Sprite3D::getSkin() const
{
    for (const auto& it : _subMeshStates) {
        if (it->getSkin())
            return it->getSkin();
    }
    return nullptr;
}

NS_CC_END
