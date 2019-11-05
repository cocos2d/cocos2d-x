/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "extensions/Particle3D/CCParticleSystem3D.h"
#include <stddef.h> // offsetof
#include "base/ccTypes.h"
#include "extensions/Particle3D/CCParticle3DRender.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/Buffer.h"
#include "renderer/backend/Device.h"
#include "renderer/ccShaders.h"
#include "base/CCDirector.h"
#include "3d/CCSprite3D.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

Particle3DQuadRender::Particle3DQuadRender()
: _texture(nullptr)
, _programState(nullptr)
, _indexBuffer(nullptr)
, _vertexBuffer(nullptr)
, _texFile("")
{
}

Particle3DQuadRender::~Particle3DQuadRender()
{
    //CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_programState);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

Particle3DQuadRender* Particle3DQuadRender::create(const std::string& texFile)
{
    auto ret = new (std::nothrow)Particle3DQuadRender();
    if (ret && ret->initQuadRender(texFile))
    {
        ret->_texFile = texFile;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

void Particle3DQuadRender::render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    //batch and generate draw
    const ParticlePool &particlePool = particleSystem->getParticlePool();
    if (!_isVisible || particlePool.empty())
        return;
    
    if (_vertexBuffer == nullptr){
        size_t stride = sizeof(Particle3DQuadRender::posuvcolor);
        _vertexBuffer = backend::Device::getInstance()->newBuffer(stride * 4 * particleSystem->getParticleQuota(), backend::BufferType::VERTEX, backend::BufferUsage::DYNAMIC);
        if (_vertexBuffer == nullptr)
        {
            CCLOG("Particle3DQuadRender::render create vertex buffer failed");
            return;
        }
    }

    if (_indexBuffer == nullptr){
        _indexBuffer = backend::Device::getInstance()->newBuffer(sizeof(uint16_t) * 6 * particleSystem->getParticleQuota(), backend::BufferType::INDEX, backend::BufferUsage::DYNAMIC);
        if (_indexBuffer == nullptr)
        {
            CCLOG("Particle3DQuadRender::render create index buffer failed");
            return;
        }
    }
    ParticlePool::PoolList activeParticleList = particlePool.getActiveDataList();
    if (_posuvcolors.size() < activeParticleList.size() * 4)
    {
        _posuvcolors.resize(activeParticleList.size() * 4);
        _indexData.resize(activeParticleList.size() * 6);
    }

    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();
    const Mat4 &viewMat = cameraMat.getInversed();
    
    Mat4 pRotMat;
    Vec3 right(cameraMat.m[0], cameraMat.m[1], cameraMat.m[2]);
    Vec3 up(cameraMat.m[4], cameraMat.m[5], cameraMat.m[6]);
    Vec3 backward(cameraMat.m[8], cameraMat.m[9], cameraMat.m[10]);
    
    Vec3 position; //particle position
    int vertexindex = 0;
    int index = 0;
    for (auto iter : activeParticleList)
    {
        auto particle = iter;
        Vec3 halfwidth = particle->width * 0.5f * right;
        Vec3 halfheight = particle->height * 0.5f * up;
        //transform.transformPoint(particle->position, &position);
        position = particle->position;
        _posuvcolors[vertexindex].position = (position + (- halfwidth - halfheight));
        _posuvcolors[vertexindex].color = particle->color;
        _posuvcolors[vertexindex].uv.set(particle->lb_uv);

        _posuvcolors[vertexindex + 1].position = (position + (halfwidth - halfheight));
        _posuvcolors[vertexindex + 1].color = particle->color;
        _posuvcolors[vertexindex + 1].uv.set(particle->rt_uv.x, particle->lb_uv.y);
        
        _posuvcolors[vertexindex + 2].position = (position + (- halfwidth + halfheight));
        _posuvcolors[vertexindex + 2].color = particle->color;
        _posuvcolors[vertexindex + 2].uv.set(particle->lb_uv.x, particle->rt_uv.y);
        
        _posuvcolors[vertexindex + 3].position = (position + (halfwidth + halfheight));
        _posuvcolors[vertexindex + 3].color = particle->color;
        _posuvcolors[vertexindex + 3].uv.set(particle->rt_uv);
        
        
        _indexData[index] = vertexindex;
        _indexData[index + 1] = vertexindex + 1;
        _indexData[index + 2] = vertexindex + 3;
        _indexData[index + 3] = vertexindex;
        _indexData[index + 4] = vertexindex + 3;
        _indexData[index + 5] = vertexindex + 2;
        
        index += 6;
        vertexindex += 4;
    }
    
    _posuvcolors.erase(_posuvcolors.begin() + vertexindex, _posuvcolors.end());
    _indexData.erase(_indexData.begin() + index, _indexData.end());
    
    _vertexBuffer->updateData(&_posuvcolors[0], vertexindex * sizeof(_posuvcolors[0]));
    _indexBuffer->updateData(&_indexData[0], index * sizeof(_indexData[0]));
    
    float depthZ = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);

    _beforeCommand.init(depthZ);
    _meshCommand.init(depthZ);
    _afterCommand.init(depthZ);

    _meshCommand.setVertexBuffer(_vertexBuffer);
    _meshCommand.setIndexBuffer(_indexBuffer, MeshCommand::IndexFormat::U_SHORT);

    auto &projectionMatrix = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    _programState->setUniform(_locPMatrix, &projectionMatrix.m, sizeof(projectionMatrix.m));

    if (_texture)
    {
        _programState->setTexture(_locTexture, 0, _texture->getBackendTexture());
    }
    _stateBlock.setBlendFunc(particleSystem->getBlendFunc());
    auto uColor = Vec4(1, 1, 1, 1);
    _programState->setUniform(_locColor, &uColor, sizeof(uColor));


    _meshCommand.setIndexDrawInfo(0, index);
    
    renderer->addCommand(&_beforeCommand);
    renderer->addCommand(&_meshCommand);
    renderer->addCommand(&_afterCommand);
}

bool Particle3DQuadRender::initQuadRender( const std::string& texFile )
{
    CC_SAFE_RELEASE_NULL(_programState);

    if (!texFile.empty())
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
        if (tex)
        {
            _texture = tex;
            auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::PARTICLE_TEXTURE_3D);
            _programState = new backend::ProgramState(program);
        }
    }

    if (!_programState)
    {
        auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::PARTICLE_COLOR_3D);
        _programState = new backend::ProgramState(program);
    }

    auto &pipelineDescriptor = _meshCommand.getPipelineDescriptor();
    pipelineDescriptor.programState = _programState;
    auto layout = _programState->getVertexLayout();
    const auto& attributeInfo = _programState->getProgram()->getActiveAttributes();
    auto iter = attributeInfo.find("a_position");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT3, offsetof(posuvcolor, position), false);
    }
    iter = attributeInfo.find("a_texCoord");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_texCoord", iter->second.location, backend::VertexFormat::FLOAT2, offsetof(posuvcolor, uv), false);
    }
    iter = attributeInfo.find("a_color");
    if(iter != attributeInfo.end())
    {
        layout->setAttribute("a_color", iter->second.location, backend::VertexFormat::FLOAT4, offsetof(posuvcolor, color), false);
    }
    layout->setLayout(sizeof(posuvcolor));

    _locColor = _programState->getUniformLocation("u_color");
    _locPMatrix = _programState->getUniformLocation("u_PMatrix");
    _locTexture = _programState->getUniformLocation("u_texture");

    _meshCommand.setTransparent(true);
    _meshCommand.setSkipBatching(true);

    _stateBlock.setDepthTest(true);
    _stateBlock.setDepthWrite(false);
    _stateBlock.setCullFaceSide(backend::CullMode::BACK);
    _stateBlock.setCullFace(true);

    _beforeCommand.func = CC_CALLBACK_0(Particle3DQuadRender::onBeforeDraw, this);
    _afterCommand.func = CC_CALLBACK_0(Particle3DQuadRender::onAfterDraw, this);
    return true;
}


void Particle3DQuadRender::onBeforeDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    auto &pipelineDescriptor = _meshCommand.getPipelineDescriptor();
    _rendererDepthTestEnabled = renderer->getDepthTest();
    _rendererDepthCmpFunc = renderer->getDepthCompareFunction();
    _rendererCullMode = renderer->getCullMode();
    _rendererDepthWrite = renderer->getDepthWrite();
    _rendererWinding = renderer->getWinding();
    _stateBlock.bind(&pipelineDescriptor);
    renderer->setDepthTest(true);
}

void Particle3DQuadRender::onAfterDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->setDepthTest(_rendererDepthTestEnabled);
    renderer->setDepthCompareFunction(_rendererDepthCmpFunc);
    renderer->setCullMode(_rendererCullMode);
    renderer->setDepthWrite(_rendererDepthWrite);
    renderer->setWinding(_rendererWinding);
}

void Particle3DQuadRender::reset()
{
    this->initQuadRender(_texFile);
}

//////////////////////////////////////////////////////////////////////////////
Particle3DModelRender::Particle3DModelRender()
    : _spriteSize(Vec3::ONE)
{
    
}
Particle3DModelRender::~Particle3DModelRender()
{
    for (auto iter : _spriteList){
        iter->release();
    }
}


Particle3DModelRender* Particle3DModelRender::create(const std::string& modelFile, const std::string &texFile)
{
    auto ret = new (std::nothrow) Particle3DModelRender();
    ret->_modelFile = modelFile;
    ret->_texFile = texFile;
    return ret;
}

void Particle3DModelRender::render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    if (!_isVisible)
        return;
    
    if (_spriteList.empty()){
        for (unsigned int i = 0; i < particleSystem->getParticleQuota(); ++i){
            Sprite3D *sprite = Sprite3D::create(_modelFile);
            if (sprite == nullptr)
            {
                CCLOG("failed to load file %s", _modelFile.c_str());
                continue;
            }
            sprite->setTexture(_texFile);
            sprite->retain();
            _spriteList.push_back(sprite);
        }
        if (!_spriteList.empty()){
            const AABB &aabb = _spriteList[0]->getAABB();
            Vec3 corners[8];
            aabb.getCorners(corners);
            _spriteSize = corners[3] - corners[6];
        }
    }


    const ParticlePool& particlePool = particleSystem->getParticlePool();
    ParticlePool::PoolList activeParticleList = particlePool.getActiveDataList();
    Mat4 mat;
    Mat4 rotMat;
    Mat4 sclMat;
    Quaternion q;
    transform.decompose(nullptr, &q, nullptr);
    unsigned int index = 0;
    for (auto iter : activeParticleList)
    {
        auto particle = iter;
        Mat4::createRotation(q * particle->orientation, &rotMat);
        sclMat.m[0] = particle->width / _spriteSize.x;
        sclMat.m[5]  = particle->height / _spriteSize.y; 
        sclMat.m[10] = particle->depth / _spriteSize.z;
        mat = rotMat * sclMat;
        mat.m[12] = particle->position.x;
        mat.m[13] = particle->position.y;
        mat.m[14] = particle->position.z;
        _spriteList[index++]->draw(renderer, mat, 0);
    }
}

void Particle3DModelRender::reset()
{
    for (auto iter : _spriteList){
        iter->release();
    }
    _spriteList.clear();
}

// MARK: Particle3DRender

Particle3DRender::Particle3DRender()
: _particleSystem(nullptr)
, _isVisible(true)
, _rendererScale(Vec3::ONE)
, _depthTest(true)
, _depthWrite(false)
{
    _stateBlock.setCullFace(false);
    _stateBlock.setCullFaceSide(backend::CullMode::BACK);
    _stateBlock.setDepthTest(false);
    _stateBlock.setDepthWrite(false);
    _stateBlock.setBlend(true);
};

Particle3DRender::~Particle3DRender()
{
}

void Particle3DRender::copyAttributesTo (Particle3DRender *render)
{
    render->_stateBlock = _stateBlock;
    render->_isVisible = _isVisible;
    render->_rendererScale = _rendererScale;
    render->_depthTest = _depthTest;
    render->_depthWrite = _depthWrite;
}

void Particle3DRender::notifyStart()
{
    setVisible(true);
}

void Particle3DRender::notifyStop()
{
    setVisible(false);
}

void Particle3DRender::notifyRescaled( const Vec3& scale )
{
    _rendererScale = scale;
}

void Particle3DRender::setDepthTest( bool isDepthTest )
{
    _depthTest = isDepthTest;
    _stateBlock.setDepthTest(_depthTest);
}

void Particle3DRender::setDepthWrite( bool isDepthWrite )
{
    _depthWrite = isDepthWrite;
    _stateBlock.setDepthWrite(_depthWrite);
}

void Particle3DRender::setBlendFunc(const BlendFunc &blendFunc)
{
    _stateBlock.setBlendFunc(blendFunc);
}

NS_CC_END
