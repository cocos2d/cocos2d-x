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

#include "ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"
#include "3dparticle/CCParticle3DRender.h"
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
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_glProgramState);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

Particle3DQuadRender* Particle3DQuadRender::create(const std::string& texFile)
{
    auto ret = new Particle3DQuadRender();
    ret->autorelease();
    
    GLProgram* glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION);
    if (!texFile.empty())
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
        if (tex)
        {
            ret->_texture = tex;
            glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_POSITION_TEXTURE);
        }
    }
    auto glProgramState = GLProgramState::create(glProgram);
    glProgramState->retain();
    
    GLsizei stride = 9 * sizeof(float);
    
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_POSITION], 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_TEX_COORD], 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)3);
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_COLOR], 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)5);
    
    ret->_glProgramState = glProgramState;
    ret->_vertexBuffer = VertexBuffer::create(stride, 4);
    ret->_vertexBuffer->retain();
    ret->_indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6);
    ret->_indexBuffer->retain();
    
    ret->_meshCommand = new MeshCommand();
    ret->_meshCommand->setTransparent(true);
    
    return ret;
}

void Particle3DQuadRender::render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    //batch and generate draw
    const auto& particles = particleSystem->getParticles();
    if (!_isVisible || particles.size() == 0)
        return;
    
    if (_posuvcolors.size() < particles.size() * 4)
    {
        _posuvcolors.resize(particles.size() * 4);
        _indexData.resize(particles.size() * 6);
    }
    
    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();
    Vec3 right(cameraMat.m[0], cameraMat.m[1], cameraMat.m[2]);
    Vec3 up(cameraMat.m[4], cameraMat.m[5], cameraMat.m[6]);
    
    Vec3 position; //particle position
    int vertexindex = 0;
    int index = 0;
    for (ssize_t i = 0; i < particles.size(); i++)
    {
        auto particle = static_cast<PUParticle3D*>(particles[i]);
        Vec3 halfwidth = particle->width * 0.5f * right;
        Vec3 halfheight = particle->height * 0.5f * up;
        transform.transformPoint(particle->position, &position);
        
        _posuvcolors[vertexindex].position = position - halfwidth - halfheight;
        _posuvcolors[vertexindex].color = particle->color;
        //_posuvcolors[i].uv = particle->
        _posuvcolors[vertexindex + 1].position = position + halfwidth - halfheight;
        _posuvcolors[vertexindex + 1].color = particle->color;
        
        _posuvcolors[vertexindex + 2].position = position - halfwidth + halfheight;
        _posuvcolors[vertexindex + 2].color = particle->color;
        
        _posuvcolors[vertexindex + 3].position = position + halfwidth + halfheight;
        _posuvcolors[vertexindex + 3].color = particle->color;
        
        
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
    
    _vertexBuffer->updateVertices(&_posuvcolors[0], vertexindex * sizeof(_posuvcolors[0]), 0);
    _indexBuffer->updateIndices(&_indexData[0], index * sizeof(unsigned short), 0);
    
    GLuint texId = (_texture ? _texture->getName() : 0);
    const Mat4 &viewMat = cameraMat.getInversed();
    float depthZ = -(viewMat.m[2] * transform.m[12] + viewMat.m[6] * transform.m[13] + viewMat.m[10] * transform.m[14] + viewMat.m[14]);
    _meshCommand->init(depthZ, texId, _glProgramState, particleSystem->getBlendFunc(), _vertexBuffer->getVBO(), _indexBuffer->getVBO(), GL_TRIANGLES, GL_UNSIGNED_SHORT, index, transform);
    renderer->addCommand(_meshCommand);
}

//////////////////////////////////////////////////////////////////////////////
Particle3DModelRender::Particle3DModelRender()
: _sprite(nullptr)
{
    
}
Particle3DModelRender::~Particle3DModelRender()
{
    CC_SAFE_RELEASE(_sprite);
}


Particle3DModelRender* Particle3DModelRender::create(Sprite3D* sprite)
{
    auto ret = new Particle3DModelRender();
    ret->_sprite = sprite;
    sprite->retain();
    
    return ret;
}

void Particle3DModelRender::render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    if (!_isVisible || _sprite == nullptr)
        return;
    
    const auto& particles = particleSystem->getParticles();
    Mat4 mat;
    for (auto it : particles)
    {
        auto particle = static_cast<PUParticle3D*>(it);
        Mat4::createRotation(particle->orientation, &mat);
        mat.m[12] = particle->position.x;
        mat.m[13] = particle->position.y;
        mat.m[14] = particle->position.z;
        _sprite->draw(renderer, transform * mat, 0);
    }
}


void Particle3DRender::notifyStart( void )
{
	setVisible(true);
}

void Particle3DRender::notifyStop( void )
{
	setVisible(false);
}

void Particle3DRender::notifyRescaled( const Vec3& scale )
{
	_rendererScale = scale;
}

NS_CC_END
