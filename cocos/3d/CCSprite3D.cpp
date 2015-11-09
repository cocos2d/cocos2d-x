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
#include "3d/CCSprite3DMaterial.h"

#include "base/CCDirector.h"
#include "base/CCAsyncTaskPool.h"
#include "2d/CCLight.h"
#include "2d/CCCamera.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"

#include "deprecated/CCString.h" // For StringUtils::format

NS_CC_BEGIN

static Sprite3DMaterial* getSprite3DMaterialForAttribs(MeshVertexData* meshVertexData, bool usesLight);

Sprite3D* Sprite3D::create()
{
    //
    auto sprite = new (std::nothrow) Sprite3D();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Sprite3D* Sprite3D::create(const std::string& modelPath)
{
    CCASSERT(modelPath.length() >= 4, "invalid filename for Sprite3D");
    
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
Sprite3D* Sprite3D::create(const std::string& modelPath, const std::string& texturePath)
{
    auto sprite = create(modelPath);
    if (sprite)
    {
        sprite->setTexture(texturePath);
    }
    
    return sprite;
}

void Sprite3D::createAsync(const std::string& modelPath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam)
{
    createAsync(modelPath, "", callback, callbackparam);
}

void Sprite3D::createAsync(const std::string& modelPath, const std::string& texturePath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam)
{
    Sprite3D *sprite = new (std::nothrow) Sprite3D();
    if (sprite->loadFromCache(modelPath))
    {
        sprite->autorelease();
        if (!texturePath.empty())
            sprite->setTexture(texturePath);
        callback(sprite, callbackparam);
        return;
    }
    
    sprite->_asyncLoadParam.afterLoadCallback = callback;
    sprite->_asyncLoadParam.texPath = texturePath;
    sprite->_asyncLoadParam.modlePath = modelPath;
    sprite->_asyncLoadParam.callbackParam = callbackparam;
    sprite->_asyncLoadParam.materialdatas = new (std::nothrow) MaterialDatas();
    sprite->_asyncLoadParam.meshdatas = new (std::nothrow) MeshDatas();
    sprite->_asyncLoadParam.nodeDatas = new (std::nothrow) NodeDatas();
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, CC_CALLBACK_1(Sprite3D::afterAsyncLoad, sprite), (void*)(&sprite->_asyncLoadParam), [sprite]()
    {
        sprite->_asyncLoadParam.result = sprite->loadFromFile(sprite->_asyncLoadParam.modlePath, sprite->_asyncLoadParam.nodeDatas, sprite->_asyncLoadParam.meshdatas, sprite->_asyncLoadParam.materialdatas);
    });
    
}

void Sprite3D::afterAsyncLoad(void* param)
{
    Sprite3D::AsyncLoadParam* asyncParam = (Sprite3D::AsyncLoadParam*)param;
    autorelease();
    if (asyncParam)
    {
        if (asyncParam->result)
        {
            _meshes.clear();
            _meshVertexDatas.clear();
            CC_SAFE_RELEASE_NULL(_skeleton);
            removeAllAttachNode();
            
            //create in the main thread
            auto& meshdatas = asyncParam->meshdatas;
            auto& materialdatas = asyncParam->materialdatas;
            auto&   nodeDatas = asyncParam->nodeDatas;
            if (initFrom(*nodeDatas, *meshdatas, *materialdatas))
            {
                auto spritedata = Sprite3DCache::getInstance()->getSpriteData(asyncParam->modlePath);
                if (spritedata == nullptr)
                {
                    //add to cache
                    auto data = new (std::nothrow) Sprite3DCache::Sprite3DData();
                    data->materialdatas = materialdatas;
                    data->nodedatas = nodeDatas;
                    data->meshVertexDatas = _meshVertexDatas;
                    for (const auto mesh : _meshes) {
                        data->glProgramStates.pushBack(mesh->getGLProgramState());
                    }
                    
                    Sprite3DCache::getInstance()->addSprite3DData(asyncParam->modlePath, data);
                    
                    CC_SAFE_DELETE(meshdatas);
                    materialdatas = nullptr;
                    nodeDatas = nullptr;
                }
            }
            CC_SAFE_DELETE(meshdatas);
            CC_SAFE_DELETE(materialdatas);
            CC_SAFE_DELETE(nodeDatas);
            
            if (asyncParam->texPath != "")
            {
                setTexture(asyncParam->texPath);
            }
        }
        else
        {
            CCLOG("file load failed: %s ", asyncParam->modlePath.c_str());
        }
        asyncParam->afterLoadCallback(this, asyncParam->callbackParam);
    }
}

AABB Sprite3D::getAABBRecursivelyImp(Node *node)
{
    AABB aabb;
    for (auto iter : node->getChildren()){
        aabb.merge(getAABBRecursivelyImp(iter));
    }
    
    Sprite3D *sprite3d = dynamic_cast<Sprite3D*>(node);
    if (sprite3d)
        aabb.merge(sprite3d->getAABB());

    return aabb;
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
            // cloning is needed in order to have one state per sprite
            auto glstate = spritedata->glProgramStates.at(i);
            _meshes.at(i)->setGLProgramState(glstate->clone());
        }
        return true;
    }
    
    return false;
}

bool Sprite3D::loadFromFile(const std::string& path, NodeDatas* nodedatas, MeshDatas* meshdatas,  MaterialDatas* materialdatas)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    std::string ext = FileUtils::getInstance()->getFileExtension(path);
    if (ext == ".obj")
    {
        return Bundle3D::loadObj(*meshdatas, *materialdatas, *nodedatas, fullPath);
    }
    else if (ext == ".c3b" || ext == ".c3t")
    {
        //load from .c3b or .c3t
        auto bundle = Bundle3D::createBundle();
        if (!bundle->load(fullPath))
        {
            Bundle3D::destroyBundle(bundle);
            return false;
        }
        
        auto ret = bundle->loadMeshDatas(*meshdatas)
            && bundle->loadMaterials(*materialdatas) && bundle->loadNodes(*nodedatas);
        Bundle3D::destroyBundle(bundle);
        
        return ret;
    }
    return false;
}

Sprite3D::Sprite3D()
: _skeleton(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _aabbDirty(true)
, _lightMask(-1)
, _shaderUsingLight(false)
, _forceDepthWrite(false)
, _usingAutogeneratedGLProgram(true)
{
}

Sprite3D::~Sprite3D()
{
    _meshes.clear();
    _meshVertexDatas.clear();
    CC_SAFE_RELEASE_NULL(_skeleton);
    removeAllAttachNode();
}

bool Sprite3D::init()
{
    if(Node::init())
    {
        return true;
    }
    return false;
}

bool Sprite3D::initWithFile(const std::string& path)
{
    _meshes.clear();
    _meshVertexDatas.clear();
    CC_SAFE_RELEASE_NULL(_skeleton);
    removeAllAttachNode();
    
    if (loadFromCache(path))
        return true;
    
    MeshDatas* meshdatas = new (std::nothrow) MeshDatas();
    MaterialDatas* materialdatas = new (std::nothrow) MaterialDatas();
    NodeDatas* nodeDatas = new (std::nothrow) NodeDatas();
    if (loadFromFile(path, nodeDatas, meshdatas, materialdatas))
    {
        if (initFrom(*nodeDatas, *meshdatas, *materialdatas))
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
            CC_SAFE_DELETE(meshdatas);
            _contentSize = getBoundingBox().size;
            return true;
        }
    }
    CC_SAFE_DELETE(meshdatas);
    CC_SAFE_DELETE(materialdatas);
    CC_SAFE_DELETE(nodeDatas);
    
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
    genMaterial();
    
    return true;
}
Sprite3D* Sprite3D::createSprite3DNode(NodeData* nodedata,ModelData* modeldata,const MaterialDatas& materialdatas)
{
    auto sprite = new (std::nothrow) Sprite3D();
    if (sprite)
    {
        sprite->setName(nodedata->id);
        auto mesh = Mesh::create(nodedata->id, getMeshIndexData(modeldata->subMeshId));
        if (modeldata->matrialId == "" && materialdatas.materials.size())
        {
            const NTextureData* textureData = materialdatas.materials[0].getTextureData(NTextureData::Usage::Diffuse);
            mesh->setTexture(textureData->filename);
        }
        else
        {
            const NMaterialData*  materialData=materialdatas.getMaterialData(modeldata->matrialId);
            if(materialData)
            {
                const NTextureData* textureData = materialData->getTextureData(NTextureData::Usage::Diffuse);
                if(textureData)
                {
                    mesh->setTexture(textureData->filename);
                    auto tex = mesh->getTexture();
                    if(tex)
                    {
                        Texture2D::TexParams texParams;
                        texParams.minFilter = GL_LINEAR;
                        texParams.magFilter = GL_LINEAR;
                        texParams.wrapS = textureData->wrapS;
                        texParams.wrapT = textureData->wrapT;
                        tex->setTexParameters(texParams);
                        mesh->_isTransparent = (materialData->getTextureData(NTextureData::Usage::Transparency) != nullptr);
                    }
                }
            }
        }

        // set locale transform
        Vec3 pos;
        Quaternion qua;
        Vec3 scale;
        nodedata->transform.decompose(&scale, &qua, &pos);
        sprite->setPosition3D(pos);
        sprite->setRotationQuat(qua);
        sprite->setScaleX(scale.x);
        sprite->setScaleY(scale.y);
        sprite->setScaleZ(scale.z);
        
        sprite->addMesh(mesh);
        sprite->autorelease();
        sprite->genMaterial();
    }
    return   sprite;
}
void Sprite3D::createAttachSprite3DNode(NodeData* nodedata, const MaterialDatas& materialdatas)
{
    for(const auto& it : nodedata->modelNodeDatas)
    {
        if(it && getAttachNode(nodedata->id))
        {
            auto sprite = createSprite3DNode(nodedata,it,materialdatas);
            if (sprite)
            {
                getAttachNode(nodedata->id)->addChild(sprite);
            } 
        }
    }
    for(const auto& it : nodedata->children)
    {
        createAttachSprite3DNode(it,materialdatas);
    }
}

void Sprite3D::setMaterial(Material *material)
{
    setMaterial(material, -1); 
}

void Sprite3D::setMaterial(Material *material, int meshIndex)
{
    CCASSERT(material, "Invalid Material");
    CCASSERT(meshIndex == -1 || (meshIndex >=0 && meshIndex < _meshes.size()), "Invalid meshIndex");


    if (meshIndex == -1)
    {
        for (auto mesh: _meshes)
        {
            mesh->setMaterial(material);
        }
    }
    else
    {
        auto mesh = _meshes.at(meshIndex);
        mesh->setMaterial(material);
    }

    _usingAutogeneratedGLProgram = false;
}

Material* Sprite3D::getMaterial(int meshIndex) const
{
    CCASSERT(meshIndex >=0 && meshIndex < _meshes.size(), "Invalid meshIndex");
    return _meshes.at(meshIndex)->getMaterial();
}


void Sprite3D::genMaterial(bool useLight)
{
    _shaderUsingLight = useLight;

    std::unordered_map<const MeshVertexData*, Sprite3DMaterial*> materials;
    for(auto meshVertexData : _meshVertexDatas)
    {
        auto material = getSprite3DMaterialForAttribs(meshVertexData, useLight);
        materials[meshVertexData] = material;
    }
    
    for (auto& mesh: _meshes)
    {
        auto material = materials[mesh->getMeshIndexData()->getMeshVertexData()];
        
        //keep original state block if exist
        auto oldmaterial = mesh->getMaterial();
        if (oldmaterial)
        {
            material->setStateBlock(oldmaterial->getStateBlock());
        }

        if (material->getReferenceCount() == 1)
            mesh->setMaterial(material);
        else
            mesh->setMaterial(material->clone());
    }
}

void Sprite3D::createNode(NodeData* nodedata, Node* root, const MaterialDatas& materialdatas, bool singleSprite)
{
    Node* node=nullptr;
    for(const auto& it : nodedata->modelNodeDatas)
    {
        if(it)
        {
            if(it->bones.size() > 0 || singleSprite)
            {
                if(singleSprite && root!=nullptr)
                    root->setName(nodedata->id);
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

                    if (it->matrialId == "" && materialdatas.materials.size())
                    {
                        const NTextureData* textureData = materialdatas.materials[0].getTextureData(NTextureData::Usage::Diffuse);
                        mesh->setTexture(textureData->filename);
                    }
                    else
                    {
                        const NMaterialData*  materialData=materialdatas.getMaterialData(it->matrialId);
                        if(materialData)
                        {
                            const NTextureData* textureData = materialData->getTextureData(NTextureData::Usage::Diffuse);
                            if(textureData)
                            {
                                mesh->setTexture(textureData->filename);
                                auto tex = mesh->getTexture();
                                if(tex)
                                {
                                    Texture2D::TexParams texParams;
                                    texParams.minFilter = GL_LINEAR;
                                    texParams.magFilter = GL_LINEAR;
                                    texParams.wrapS = textureData->wrapS;
                                    texParams.wrapT = textureData->wrapT;
                                    tex->setTexParameters(texParams);
                                    mesh->_isTransparent = (materialData->getTextureData(NTextureData::Usage::Transparency) != nullptr);
                                }
                            }
                        }
                    }
                    
                    Vec3 pos;
                    Quaternion qua;
                    Vec3 scale;
                    nodedata->transform.decompose(&scale, &qua, &pos);
                    setPosition3D(pos);
                    setRotationQuat(qua);
                    setScaleX(scale.x);
                    setScaleY(scale.y);
                    setScaleZ(scale.z);
                    
                }
            }
            else
            {
                auto sprite = createSprite3DNode(nodedata,it,materialdatas);
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
            
            // set locale transform
            Vec3 pos;
            Quaternion qua;
            Vec3 scale;
            nodedata->transform.decompose(&scale, &qua, &pos);
            node->setPosition3D(pos);
            node->setRotationQuat(qua);
            node->setScaleX(scale.x);
            node->setScaleY(scale.y);
            node->setScaleZ(scale.z);
            
            if(root)
            {
                root->addChild(node);
            } 
        }
    }
    for(const auto& it : nodedata->children)
    {
        createNode(it,node, materialdatas, nodedata->children.size() == 1);
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
    for (auto mesh: _meshes) {
        mesh->setTexture(texture);
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
        if (bone)
        {
            auto attachNode = AttachNode::create(bone);
            addChild(attachNode);
            _attachments[boneName] = attachNode;
            return attachNode;
        }
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

void Sprite3D::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    flags |= FLAGS_RENDER_AS_3D;
    
    //
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    bool visibleByCamera = isVisitableByVisitingCamera();
    
    int i = 0;
    
    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);
            
            if (node && node->getLocalZOrder() < 0)
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }
        // self draw
        if (visibleByCamera)
            this->draw(renderer, _modelViewTransform, flags);
        
        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Sprite3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
#if CC_USE_CULLING
    // camera clipping
    if(Camera::getVisitingCamera() && !Camera::getVisitingCamera()->isVisibleInFrustum(&this->getAABB()))
        return;
#endif
    
    if (_skeleton)
        _skeleton->updateBoneMatrix();
    
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    //check light and determine the shader used
    const auto& scene = Director::getInstance()->getRunningScene();

    // Don't override GLProgramState if using manually set Material
    if (_usingAutogeneratedGLProgram && scene)
    {
        const auto lights = scene->getLights();
        bool usingLight = false;
        for (const auto light : lights) {
            usingLight = (light->isEnabled() && (unsigned int)light->getLightFlag() & _lightMask) > 0;
            if (usingLight)
                break;
        }
        if (usingLight != _shaderUsingLight)
        {
            genMaterial(usingLight);
        }
    }
    
    for (auto mesh: _meshes)
    {
        mesh->draw(renderer,
                   _globalZOrder,
                   transform,
                   flags,
                   _lightMask,
                   Vec4(color.r, color.g, color.b, color.a),
                   _forceDepthWrite);

    }
}

void Sprite3D::setGLProgramState(GLProgramState* glProgramState)
{
    Node::setGLProgramState(glProgramState);
    for (auto state : _meshes) {
        state->setGLProgramState(glProgramState);
    }
}
void Sprite3D::setGLProgram(GLProgram* glprogram)
{
    auto glProgramState = GLProgramState::create(glprogram);
    setGLProgramState(glProgramState);
}

void Sprite3D::setBlendFunc(const BlendFunc& blendFunc)
{
    if(_blend.src != blendFunc.src || _blend.dst != blendFunc.dst)
    {
        _blend = blendFunc;
        for(auto mesh: _meshes)
        {
            mesh->setBlendFunc(blendFunc);
        }
    }
}

const BlendFunc& Sprite3D::getBlendFunc() const
{
    return _blend;
}

AABB Sprite3D::getAABBRecursively()
{
    return getAABBRecursivelyImp(this);
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
        if (_meshes.size())
        {
            Mat4 transform(nodeToWorldTransform);
            for (const auto& it : _meshes) {
                if (it->isVisible())
                    _aabb.merge(it->getAABB());
            }
            
            _aabb.transform(transform);
            _nodeToWorldTransform = nodeToWorldTransform;
            _aabbDirty = false;
        }
    }
    
    return _aabb;
}

Action* Sprite3D::runAction(Action *action)
{
    setForceDepthWrite(true);
    return Node::runAction(action);
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
        it->getMaterial()->getStateBlock()->setCullFaceSide((RenderState::CullFaceSide)cullFace);
//        it->getMeshCommand().setCullFace(cullFace);
    }
}

void Sprite3D::setCullFaceEnabled(bool enable)
{
    for (auto& it : _meshes) {
        it->getMaterial()->getStateBlock()->setCullFace(enable);
//        it->getMeshCommand().setCullFaceEnabled(enable);
    }
}

Mesh* Sprite3D::getMeshByIndex(int index) const
{
    CCASSERT(index < _meshes.size(), "invalid index");
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

void Sprite3D::setForce2DQueue(bool force2D)
{
    for (const auto &mesh : _meshes) {
        mesh->setForce2DQueue(force2D);
    }
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

//
// MARK: Helpers
//
static Sprite3DMaterial* getSprite3DMaterialForAttribs(MeshVertexData* meshVertexData, bool usesLight)
{
    bool textured = meshVertexData->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    bool hasSkin = meshVertexData->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_INDEX)
    && meshVertexData->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
    bool hasNormal = meshVertexData->hasVertexAttrib(GLProgram::VERTEX_ATTRIB_NORMAL);
    Sprite3DMaterial::MaterialType type;
    if(textured)
    {
        type = hasNormal && usesLight ? Sprite3DMaterial::MaterialType::DIFFUSE : Sprite3DMaterial::MaterialType::UNLIT;
    }
    else
    {
        type = hasNormal && usesLight ? Sprite3DMaterial::MaterialType::DIFFUSE_NOTEX : Sprite3DMaterial::MaterialType::UNLIT_NOTEX;
    }
    
    return Sprite3DMaterial::createBuiltInMaterial(type, hasSkin);
}

NS_CC_END
