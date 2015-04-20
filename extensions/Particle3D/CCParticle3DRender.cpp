/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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
#include "extensions/Particle3D/CCParticle3DRender.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCDirector.h"
#include "3d/CCSprite3D.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

Particle3DQuadRender::Particle3DQuadRender()
: _meshCommand(nullptr)
, _texture(nullptr)
, _glProgramState(nullptr)
, _indexBuffer(nullptr)
, _vertexBuffer(nullptr)
{
    
}
Particle3DQuadRender::~Particle3DQuadRender()
{
    CC_SAFE_DELETE(_meshCommand);
    //CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_glProgramState);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

Particle3DQuadRender* Particle3DQuadRender::create(const std::string& texFile)
{
    auto ret = new (std::nothrow)Particle3DQuadRender();
    if (ret && ret->initQuadRender(texFile))
    {
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
        GLsizei stride = sizeof(Particle3DQuadRender::posuvcolor);
        _vertexBuffer = VertexBuffer::create(stride, 4 * particleSystem->getParticleQuota());
        if (_vertexBuffer == nullptr)
        {
            CCLOG("Particle3DQuadRender::render create vertex buffer failed");
            return;
        }
        _vertexBuffer->retain();
    }

    if (_indexBuffer == nullptr){
        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * particleSystem->getParticleQuota());
        if (_indexBuffer == nullptr)
        {
            CCLOG("Particle3DQuadRender::render create index buffer failed");
            return;
        }
        _indexBuffer->retain();
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
    
    _vertexBuffer->updateVertices(&_posuvcolors[0], vertexindex/* * sizeof(_posuvcolors[0])*/, 0);
    _indexBuffer->updateIndices(&_indexData[0], index/* * sizeof(unsigned short)*/, 0);
    
    GLuint texId = (_texture ? _texture->getName() : 0);
    float depthZ = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);
    _meshCommand->init(depthZ, texId, _glProgramState, particleSystem->getBlendFunc(), _vertexBuffer->getVBO(), _indexBuffer->getVBO(), GL_TRIANGLES, GL_UNSIGNED_SHORT, index, transform, 0);
    renderer->addCommand(_meshCommand);
}

bool Particle3DQuadRender::initQuadRender( const std::string& texFile )
{
    GLProgram* glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_PARTICLE_COLOR);
    if (!texFile.empty())
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
        if (tex)
        {
            _texture = tex;
            glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_PARTICLE_TEXTURE);
        }
    }
    auto glProgramState = GLProgramState::create(glProgram);
    glProgramState->retain();

    GLsizei stride = sizeof(Particle3DQuadRender::posuvcolor);

    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_POSITION], 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(posuvcolor, position));
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_TEX_COORD], 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(posuvcolor, uv));
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_COLOR], 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(posuvcolor, color));

    _glProgramState = glProgramState;
    //ret->_vertexBuffer = VertexBuffer::create(stride, 4 * 10000);
    //ret->_vertexBuffer->retain();
    //ret->_indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * 10000);
    //ret->_indexBuffer->retain();

    _meshCommand = new (std::nothrow) MeshCommand();
    _meshCommand->setTransparent(true);
    _meshCommand->setDepthTestEnabled(_depthTest);
    _meshCommand->setDepthWriteEnabled(_depthWrite);
    _meshCommand->setCullFace(GL_BACK);
    _meshCommand->setCullFaceEnabled(true);
    return true;
}

void Particle3DQuadRender::setDepthTest( bool isDepthTest )
{
    Particle3DRender::setDepthTest(isDepthTest);
    _meshCommand->setDepthTestEnabled(_depthTest);
}

void Particle3DQuadRender::setDepthWrite( bool isDepthWrite )
{
    Particle3DRender::setDepthWrite(isDepthWrite);
    _meshCommand->setDepthWriteEnabled(_depthWrite);
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

NS_CC_END
