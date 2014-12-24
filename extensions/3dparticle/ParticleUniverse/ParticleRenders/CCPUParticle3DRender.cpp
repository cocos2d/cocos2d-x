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

#include "3dparticle/CCParticleSystem3D.h"
#include "3dparticle/ParticleUniverse/ParticleRenders/CCPUParticle3DRender.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"
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

static bool compareParticle3D(PUParticle3D* left, PUParticle3D* right)
{
    return left->depthInView > right->depthInView;
}

PUParticle3DQuadRender* PUParticle3DQuadRender::create(const std::string& texFile)
{
    auto ret = new PUParticle3DQuadRender();
    ret->autorelease();
    ret->initQuadRender(texFile);
    return ret;
}

void PUParticle3DQuadRender::render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    //batch and generate draw
    const ParticlePool &particlePool = particleSystem->getParticlePool();
    if (!_isVisible || particlePool.empty())
        return;
    
    if (_vertexBuffer == nullptr){
        GLsizei stride = sizeof(Particle3DQuadRender::posuvcolor);
        _vertexBuffer = VertexBuffer::create(stride, 4 * particleSystem->getParticleQuota());
        _vertexBuffer->retain();
    }

    if (_indexBuffer == nullptr){
        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * particleSystem->getParticleQuota());
        _indexBuffer->retain();
    }
    ParticlePool::PoolList activeParticleList = particlePool.getActiveParticleList();
    if (_posuvcolors.size() < activeParticleList.size() * 4)
    {
        _posuvcolors.resize(activeParticleList.size() * 4);
        _indexData.resize(activeParticleList.size() * 6);
    }

    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();
    const Mat4 &viewMat = cameraMat.getInversed();
    

    //for (auto iter : activeParticleList){
    //    iter->depthInView = -(viewMat.m[2] * iter->positionInWorld.x + viewMat.m[6] * iter->positionInWorld.y + viewMat.m[10] * iter->positionInWorld.z + viewMat.m[14]);
    //}

    //std::sort(activeParticleList.begin(), activeParticleList.end(), compareParticle3D);
    Mat4 pRotMat;
    Vec3 right(cameraMat.m[0], cameraMat.m[1], cameraMat.m[2]);
    Vec3 up(cameraMat.m[4], cameraMat.m[5], cameraMat.m[6]);
    Vec3 backward(cameraMat.m[8], cameraMat.m[9], cameraMat.m[10]);
    
    Vec3 position; //particle position
    int vertexindex = 0;
    int index = 0;
    int offsetX,offsetY;
    getOriginOffset(offsetX, offsetY);

    if (_type == PERPENDICULAR_COMMON){
        up = _commonUp;
        up.normalize();
        Vec3::cross(up, _commonDir, &right);
        right.normalize();
    }

    for (auto iter : activeParticleList)
    {
        auto particle = static_cast<PUParticle3D *>(iter);
        determineUVCoords(particle);
        if (_type == ORIENTED_SELF){
            Vec3 direction;
            transform.transformVector(particle->direction, &direction);
            up = direction;
            up.normalize();
            Vec3::cross(direction, backward, &right);
            right.normalize();
        }
        Vec3 halfwidth = particle->widthInWorld * 0.5f * right;
        Vec3 halfheight = particle->heightInWorld * 0.5f * up;
        //transform.transformPoint(particle->position, &position);
        position = particle->positionInWorld;
        Mat4::createRotation(backward, particle->zRotation, &pRotMat);
        _posuvcolors[vertexindex].position = (position + pRotMat * (- halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY));
        _posuvcolors[vertexindex].color = particle->color;
        _posuvcolors[vertexindex].uv = Vec2(particle->lb_uv);

        _posuvcolors[vertexindex + 1].position = (position + pRotMat * (halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY));
        _posuvcolors[vertexindex + 1].color = particle->color;
        _posuvcolors[vertexindex + 1].uv = Vec2(particle->rt_uv.x, particle->lb_uv.y);
        
        _posuvcolors[vertexindex + 2].position = (position + pRotMat * (- halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY));
        _posuvcolors[vertexindex + 2].color = particle->color;
        _posuvcolors[vertexindex + 2].uv = Vec2(particle->lb_uv.x, particle->rt_uv.y);
        
        _posuvcolors[vertexindex + 3].position = (position + pRotMat * (halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY));
        _posuvcolors[vertexindex + 3].color = particle->color;
        _posuvcolors[vertexindex + 3].uv = Vec2(particle->rt_uv);
        
        
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
    _meshCommand->init(depthZ, texId, _glProgramState, particleSystem->getBlendFunc(), _vertexBuffer->getVBO(), _indexBuffer->getVBO(), GL_TRIANGLES, GL_UNSIGNED_SHORT, index, transform);
    renderer->addCommand(_meshCommand);
}

PUParticle3DQuadRender::PUParticle3DQuadRender()
    : _type(POINT)
    , _origin(CENTER)
    , _commonDir(Vec3(0.0f, 0.0f, 1.0f))
    , _commonUp(Vec3(0.0f, 1.0f, 0.0f))
    , _textureCoordsRows(1)
    , _textureCoordsColumns(1)
    , _textureCoordsRowStep(1.0f)
    , _textureCoordsColStep(1.0f)
{

}

PUParticle3DQuadRender::~PUParticle3DQuadRender()
{

}

void PUParticle3DQuadRender::getOriginOffset( int &offsetX, int &offsetY )
{
    switch (_origin)
    {
    case TOP_LEFT:
        {
            offsetX = 1;
            offsetY = -1;
        }
        break;

    case TOP_CENTER:
        {
            offsetX = 0;
            offsetY = -1;
        }
        break;

    case TOP_RIGHT:
        {
            offsetX = -1;
            offsetY = -1;
        }
        break;

    case CENTER_LEFT:
        {
            offsetX = 1;
            offsetY = 0;
        }
        break;

    case CENTER:
        {
            offsetX = 0;
            offsetY = 0;
        }
        break;

    case CENTER_RIGHT:
        {
            offsetX = -1;
            offsetY = 0;
        }
        break;

    case BOTTOM_LEFT:
        {
            offsetX = 1;
            offsetY = 1;
        }
        break;

    case BOTTOM_CENTER:
        {
            offsetX = 0;
            offsetY = 1;
        }
        break;

    case BOTTOM_RIGHT:
        {
            offsetX = -1;
            offsetY = 1;
        }
        break;
    }
}

unsigned short PUParticle3DQuadRender::getTextureCoordsRows() const
{
    return _textureCoordsRows;
}

void PUParticle3DQuadRender::setTextureCoordsRows( unsigned short textureCoordsRows )
{
    _textureCoordsRows = textureCoordsRows;
    _textureCoordsRowStep = 1.0f / (float)_textureCoordsRows;
}

unsigned short PUParticle3DQuadRender::getTextureCoordsColumns() const
{
    return _textureCoordsColumns;
}

void PUParticle3DQuadRender::setTextureCoordsColumns( unsigned short textureCoordsColumns )
{
    _textureCoordsColumns = textureCoordsColumns;
    _textureCoordsColStep = 1.0f / (float)_textureCoordsColumns;
}

unsigned int PUParticle3DQuadRender::getNumTextureCoords()
{
    return _textureCoordsColumns * _textureCoordsRows;
}

void PUParticle3DQuadRender::determineUVCoords( PUParticle3D *particle )
{
    if (_textureCoordsColumns == 1 && _textureCoordsRows == 1) return;

    unsigned short currentRow = particle->textureCoordsCurrent / _textureCoordsColumns;
    unsigned short currentCol = particle->textureCoordsCurrent - _textureCoordsColumns * currentRow;
    currentRow = _textureCoordsRows - currentRow - 1;

    particle->lb_uv = Vec2(_textureCoordsColStep * currentCol, _textureCoordsRowStep * currentRow);
    particle->rt_uv = particle->lb_uv + Vec2(_textureCoordsColStep, _textureCoordsRowStep);
}


PUParticle3DModelRender* PUParticle3DModelRender::create( const std::string& modelFile, const std::string &texFile /*= ""*/ )
{
    auto ret = new PUParticle3DModelRender();
    ret->_modelFile = modelFile;
    ret->_texFile = texFile;
    return ret;
}

void PUParticle3DModelRender::render( Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem )
{
    if (!_isVisible)
        return;

    if (_spriteList.empty()){
        for (unsigned int i = 0; i < particleSystem->getParticleQuota(); ++i){
            Sprite3D *sprite = Sprite3D::create(_modelFile);
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
    ParticlePool::PoolList activeParticleList = particlePool.getActiveParticleList();
    Mat4 mat;
    Mat4 rotMat;
    Mat4 sclMat;
    Quaternion q;
    transform.decompose(nullptr, &q, nullptr);
    for (unsigned int i = 0; i < activeParticleList.size(); ++i)
    {
        auto particle = static_cast<PUParticle3D *>(activeParticleList[i]);
        q *= particle->orientation;
        Mat4::createRotation(q, &rotMat);
        sclMat.m[0] = particle->widthInWorld / _spriteSize.x;
        sclMat.m[5]  = particle->heightInWorld / _spriteSize.y; 
        sclMat.m[10] = particle->depthInWorld / _spriteSize.z;
        mat = rotMat * sclMat;
        mat.m[12] = particle->positionInWorld.x;
        mat.m[13] = particle->positionInWorld.y;
        mat.m[14] = particle->positionInWorld.z;
        _spriteList[i]->draw(renderer, mat, 0);
    }
}

PUParticle3DModelRender::PUParticle3DModelRender()
{

}

PUParticle3DModelRender::~PUParticle3DModelRender()
{

}

NS_CC_END
