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

#include "deprecated/CCString.h" // For StringUtils::format

NS_CC_BEGIN

std::string s_attributeNames[] = {GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::ATTRIBUTE_NAME_TEX_COORD2,GLProgram::ATTRIBUTE_NAME_TEX_COORD3,GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::ATTRIBUTE_NAME_BLEND_INDEX};

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

Sprite3D* Sprite3D::create(const std::string &modelPath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "invalid filename for Sprite3D");
    
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

void Sprite3D::createAsync(const std::string &modelPath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam)
{
    createAsync(modelPath, "", callback, callbackparam);
}

void Sprite3D::createAsync(const std::string &modelPath, const std::string &texturePath, const std::function<void(Sprite3D*, void*)>& callback, void* callbackparam)
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

bool Sprite3D::loadFromFile(const std::string& path, NodeDatas* nodedatas, MeshDatas* meshdatas,  MaterialDatas* materialdatas)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    std::string ext = path.substr(path.length() - 4, 4);
    std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
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

bool Sprite3D::initWithFile(const std::string &path)
{
    _meshes.clear();
    _meshVertexDatas.clear();
    CC_SAFE_RELEASE_NULL(_skeleton);
    removeAllAttachNode();
    
    if (loadFromCache(path))
        return true;
    
    MeshDatas* meshdatas = new (std::nothrow) MeshDatas();
    MaterialDatas* materialdatas = new (std::nothrow) MaterialDatas();
    NodeDatas*   nodeDatas = new (std::nothrow) NodeDatas();
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
            if (!textureData->filename.empty())
                mesh->setTexture(textureData->filename);
        }
        else
        {
            const NMaterialData*  materialData=matrialdatas.getMaterialData(modeldata->matrialId);
            if(materialData)
            {
                const NTextureData* textureData = materialData->getTextureData(NTextureData::Usage::Diffuse);
                if(textureData && !textureData->filename.empty())
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
                if(singleSprite)
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
                            if(textureData && !textureData->filename.empty())
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
        createNode(it,node, matrialdatas, nodedata->children.size() == 1);
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
    if(!Camera::getVisitingCamera()->isVisibleInFrustum(&this->getAABB()))
        return;
#endif
    
    if (_skeleton)
        _skeleton->updateBoneMatrix();
    
    Color4F color(getDisplayedColor());
    color.a = getDisplayedOpacity() / 255.0f;
    
    //check light and determine the shader used
    const auto& scene = Director::getInstance()->getRunningScene();
    if (scene)
    {
        const auto& lights = scene->getLights();
        bool usingLight = false;
        for (const auto light : lights) {
            usingLight = ((unsigned int)light->getLightFlag() & _lightMask) > 0;
            if (usingLight)
                break;
        }
        if (usingLight != _shaderUsingLight)
            genGLProgramState(usingLight);
    }
    
    int i = 0;
    for (auto& mesh : _meshes) {
        if (!mesh->isVisible())
        {
            i++;
            continue;
        }
        auto programstate = mesh->getGLProgramState();
        auto& meshCommand = mesh->getMeshCommand();

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

        bool isTransparent = (mesh->_isTransparent || color.a < 1.f);
        float globalZ = isTransparent ? 0 : _globalZOrder;
        if (isTransparent)
            flags |= Node::FLAGS_RENDER_AS_3D;

        meshCommand.init(globalZ, textureID, programstate, _blend, mesh->getVertexBuffer(), mesh->getIndexBuffer(), mesh->getPrimitiveType(), mesh->getIndexFormat(), mesh->getIndexCount(), transform, flags);
        
        meshCommand.setLightMask(_lightMask);

        auto skin = mesh->getSkin();
        if (skin)
        {
            meshCommand.setMatrixPaletteSize((int)skin->getMatrixPaletteSize());
            meshCommand.setMatrixPalette(skin->getMatrixPalette());
        }
        //support tint and fade
        meshCommand.setDisplayColor(Vec4(color.r, color.g, color.b, color.a));
        if (_forceDepthWrite)
        {
            meshCommand.setDepthWriteEnabled(true);
        }
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

AABB Sprite3D::getAABBRecursively()
{
    AABB aabb;
    const Vector<Node*>& children = getChildren();
    for (const auto& iter : children)
    {
        Sprite3D* child = dynamic_cast<Sprite3D*>(iter);
        if(child)
        {
            aabb.merge(child->getAABBRecursively());
        }
    }
    aabb.merge(getAABB());
    return aabb;
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
