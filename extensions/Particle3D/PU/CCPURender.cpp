/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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
#include "extensions/Particle3D/PU/CCPURender.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUUtil.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCVertexAttribBinding.h"
#include "base/CCDirector.h"
#include "3d/CCSprite3D.h"
#include "3d/CCMesh.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

void PURender::copyAttributesTo( PURender *render )
{
    Particle3DRender::copyAttributesTo(render);

    render->_renderType = _renderType;
}

//static bool compareParticle3D(PUParticle3D* left, PUParticle3D* right)
//{
//    return left->depthInView > right->depthInView;
//}

PUParticle3DQuadRender* PUParticle3DQuadRender::create(const std::string& texFile)
{
    auto ret = new (std::nothrow) PUParticle3DQuadRender();
    if (ret && ret->initRender(texFile))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void PUParticle3DQuadRender::render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem)
{
    //batch and generate draw
    const ParticlePool &particlePool = particleSystem->getParticlePool();
    if (!_isVisible || particlePool.empty())
        return;
    
    if (_vertexBuffer == nullptr){
        GLsizei stride = sizeof(VertexInfo);
        _vertexBuffer = VertexBuffer::create(stride, 4 * particleSystem->getParticleQuota());
        if (_vertexBuffer == nullptr)
        {
            CCLOG("PUParticle3DQuadRender::render create vertex buffer failed");
            return;
        }
        _vertexBuffer->retain();
    }

    if (_indexBuffer == nullptr){
        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * particleSystem->getParticleQuota());
        if (_indexBuffer == nullptr)
        {
            CCLOG("PUParticle3DQuadRender::render create index buffer failed");
            return;
        }
        _indexBuffer->retain();
    }
    const ParticlePool::PoolList &activeParticleList = particlePool.getActiveDataList();
    if (_vertices.size() < activeParticleList.size() * 4)
    {
        _vertices.resize(activeParticleList.size() * 4);
        _indices.resize(activeParticleList.size() * 6);
    }

    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();
    

    //for (auto iter : activeParticleList){
    //    iter->depthInView = -(viewMat.m[2] * iter->positionInWorld.x + viewMat.m[6] * iter->positionInWorld.y + viewMat.m[10] * iter->positionInWorld.z + viewMat.m[14]);
    //}

    //std::sort(activeParticleList.begin(), activeParticleList.end(), compareParticle3D);
    Vec3 right(cameraMat.m[0], cameraMat.m[1], cameraMat.m[2]);
    Vec3 up(cameraMat.m[4], cameraMat.m[5], cameraMat.m[6]);
    Vec3 backward(cameraMat.m[8], cameraMat.m[9], cameraMat.m[10]);
    
    Mat4 pRotMat;
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
        backward = _commonDir;
    }else if (_type == ORIENTED_COMMON){
        up = _commonDir;
        up.normalize();
        Vec3::cross(up, backward, &right);
        right.normalize();
    }

    for (auto iter : activeParticleList)
    {
        auto particle = static_cast<PUParticle3D *>(iter);
        determineUVCoords(particle);
        if (_type == ORIENTED_SELF){
            Vec3 direction = particle->direction;
            //transform.transformVector(particle->direction, &direction);
            up = direction;
            up.normalize();
            Vec3::cross(direction, backward, &right);
            right.normalize();
        }else if (_type == PERPENDICULAR_SELF){
            Vec3 direction = particle->direction;
            //transform.transformVector(particle->direction, &direction);
            direction.normalize();
            //up = PUUtil::perpendicular(direction);
            //up.normalize();
            Vec3::cross(_commonUp, direction, &right);
            right.normalize();
            Vec3::cross(direction, right, &up);
            up.normalize();
            backward = direction;
        }else if (_type == ORIENTED_SHAPE){
            up.set(particle->orientation.x, particle->orientation.y, particle->orientation.z);
            up.normalize();
            Vec3::cross(up, backward, &right);
            right.normalize();
        }
        Vec3 halfwidth = particle->width * 0.5f * right;
        Vec3 halfheight = particle->height * 0.5f * up;
        //transform.transformPoint(particle->position, &position);
        position = particle->position;

        if (_rotateType == TEXTURE_COORDS){
            float costheta = cosf(-particle->zRotation);
            float sintheta = sinf(-particle->zRotation);
            Vec2 texOffset = particle->lb_uv + 0.5f * (particle->rt_uv - particle->lb_uv);
            Vec2 val;
            val.set((particle->lb_uv.x - texOffset.x), (particle->lb_uv.y - texOffset.y));
            val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
            fillVertex(vertexindex, (position + (- halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, Vec2(val.x + texOffset.x, val.y + texOffset.y));

            val.set(particle->rt_uv.x - texOffset.x, particle->lb_uv.y - texOffset.y);
            val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
            fillVertex(vertexindex + 1, (position + (halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, Vec2(val.x + texOffset.x, val.y + texOffset.y));

            val.set(particle->lb_uv.x - texOffset.x, particle->rt_uv.y - texOffset.y);
            val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
            fillVertex(vertexindex + 2, (position + (- halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, Vec2(val.x + texOffset.x, val.y + texOffset.y));

            val.set(particle->rt_uv.x - texOffset.x, particle->rt_uv.y - texOffset.y);
            val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
            fillVertex(vertexindex + 3, (position + (halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, Vec2(val.x + texOffset.x, val.y + texOffset.y));
        }else{
            Mat4::createRotation(backward, -particle->zRotation, &pRotMat);
            fillVertex(vertexindex    , (position + pRotMat * (- halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, particle->lb_uv);
            fillVertex(vertexindex + 1, (position + pRotMat * (halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, Vec2(particle->rt_uv.x, particle->lb_uv.y));
            fillVertex(vertexindex + 2, (position + pRotMat * (- halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, Vec2(particle->lb_uv.x, particle->rt_uv.y));
            fillVertex(vertexindex + 3, (position + pRotMat * (halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY)), particle->color, particle->rt_uv);
        }

        fillTriangle(index, vertexindex, vertexindex + 1, vertexindex + 3);
        fillTriangle(index + 3, vertexindex, vertexindex + 3, vertexindex + 2);

        //_posuvcolors[vertexindex].position = (position + (- halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY));
        //_posuvcolors[vertexindex].color = particle->color;
        //_posuvcolors[vertexindex].uv.set(val.x + texOffset.x, val.y + texOffset.y);

        //val.set(particle->rt_uv.x - texOffset.x, particle->lb_uv.y - texOffset.y);
        //val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
        //_posuvcolors[vertexindex + 1].position = (position + (halfwidth - halfheight + halfwidth * offsetX + halfheight * offsetY));
        //_posuvcolors[vertexindex + 1].color = particle->color;
        //_posuvcolors[vertexindex + 1].uv.set(val.x + texOffset.x, val.y + texOffset.y);
        //
        //val.set(particle->lb_uv.x - texOffset.x, particle->rt_uv.y - texOffset.y);
        //val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
        //_posuvcolors[vertexindex + 2].position = (position + (- halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY));
        //_posuvcolors[vertexindex + 2].color = particle->color;
        //_posuvcolors[vertexindex + 2].uv.set(val.x + texOffset.x, val.y + texOffset.y);
        //
        //val.set(particle->rt_uv.x - texOffset.x, particle->rt_uv.y - texOffset.y);
        //val.set(val.x * costheta - val.y * sintheta, val.x * sintheta + val.y * costheta);
        //_posuvcolors[vertexindex + 3].position = (position + (halfwidth + halfheight + halfwidth * offsetX + halfheight * offsetY));
        //_posuvcolors[vertexindex + 3].color = particle->color;
        //_posuvcolors[vertexindex + 3].uv.set(val.x + texOffset.x, val.y + texOffset.y);
        //
        //
        //_indexData[index] = vertexindex;
        //_indexData[index + 1] = vertexindex + 1;
        //_indexData[index + 2] = vertexindex + 3;
        //_indexData[index + 3] = vertexindex;
        //_indexData[index + 4] = vertexindex + 3;
        //_indexData[index + 5] = vertexindex + 2;
        
        index += 6;
        vertexindex += 4;

    }
    
    _vertices.erase(_vertices.begin() + vertexindex, _vertices.end());
    _indices.erase(_indices.begin() + index, _indices.end());
    
    if (!_vertices.empty() && !_indices.empty()){
        _vertexBuffer->updateVertices(&_vertices[0], vertexindex/* * sizeof(_posuvcolors[0])*/, 0);
        _indexBuffer->updateIndices(&_indices[0], index/* * sizeof(unsigned short)*/, 0);

        _stateBlock->setBlendFunc(particleSystem->getBlendFunc());
        
        GLuint texId = (_texture ? _texture->getName() : 0);
        _meshCommand->init(0,
                           texId,
                           _glProgramState,
                           _stateBlock,
                           _vertexBuffer->getVBO(),
                           _indexBuffer->getVBO(),
                           GL_TRIANGLES,
                           GL_UNSIGNED_SHORT,
                           index,
                           transform,
                           Node::FLAGS_RENDER_AS_3D);
        _meshCommand->setSkipBatching(true);
        _meshCommand->setTransparent(true);
        _glProgramState->setUniformVec4("u_color", Vec4(1,1,1,1));
        renderer->addCommand(_meshCommand);
    }
}

PUParticle3DQuadRender::PUParticle3DQuadRender()
    : _type(POINT)
    , _origin(CENTER)
    , _rotateType(TEXTURE_COORDS)
    , _commonDir(Vec3(0.0f, 0.0f, 1.0f))
    , _commonUp(Vec3(0.0f, 1.0f, 0.0f))
    , _textureCoordsRows(1)
    , _textureCoordsColumns(1)
    , _textureCoordsRowStep(1.0f)
    , _textureCoordsColStep(1.0f)
{
    autoRotate = false;
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

    particle->lb_uv.set(_textureCoordsColStep * currentCol, _textureCoordsRowStep * currentRow);
    particle->rt_uv = particle->lb_uv + Vec2(_textureCoordsColStep, _textureCoordsRowStep);
}

void PUParticle3DQuadRender::fillVertex( unsigned short index, const Vec3 &pos, const Vec4 &color, const Vec2 &uv )
{
    _vertices[index].position = pos;
    _vertices[index].color = color;
    _vertices[index].uv = uv;
}

void PUParticle3DQuadRender::fillTriangle( unsigned short index, unsigned short v0, unsigned short v1, unsigned short v2 )
{
    _indices[index] = v0;
    _indices[index + 1] = v1;
    _indices[index + 2] = v2;
}

void PUParticle3DQuadRender::setType( Type type )
{
    _type = type;
    if (_type == PERPENDICULAR_COMMON || _type == PERPENDICULAR_SELF){
        _stateBlock->setCullFace(false);
    }else{
        _stateBlock->setCullFace(true);
    }
}

void PUParticle3DQuadRender::copyAttributesTo(PUParticle3DQuadRender *quadRender)
{
    PURender::copyAttributesTo(quadRender);
    quadRender->_type = _type;
    quadRender->_origin = _origin;
    quadRender->_rotateType = _rotateType;
    quadRender->_commonDir = _commonDir;
    quadRender->_commonUp = _commonUp;
    quadRender->_textureCoordsRows = _textureCoordsRows;
    quadRender->_textureCoordsColumns = _textureCoordsColumns;
    quadRender->_textureCoordsRowStep = _textureCoordsRowStep;
    quadRender->_textureCoordsColStep = _textureCoordsColStep;
}

PUParticle3DQuadRender* PUParticle3DQuadRender::clone()
{
    auto render = PUParticle3DQuadRender::create(_texFile);
    copyAttributesTo(render);
    return render;
}

PUParticle3DModelRender* PUParticle3DModelRender::create( const std::string& modelFile, const std::string &texFile /*= ""*/ )
{
    auto ret = new (std::nothrow) PUParticle3DModelRender();
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
        }else{
            _isVisible = false;
            return;
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
        auto particle = static_cast<PUParticle3D *>(iter);
        Mat4::createRotation(q * particle->orientation, &rotMat);
        sclMat.m[0] = particle->width / _spriteSize.x;
        sclMat.m[5]  = particle->height / _spriteSize.y; 
        sclMat.m[10] = particle->depth / _spriteSize.z;
        mat = rotMat * sclMat;
        mat.m[12] = particle->position.x;
        mat.m[13] = particle->position.y;
        mat.m[14] = particle->position.z;
        _spriteList[index]->setColor(Color3B(particle->color.x * 255, particle->color.y * 255, particle->color.z * 255));
        _spriteList[index]->setOpacity(particle->color.w * 255);
        _spriteList[index]->draw(renderer, mat, 0);
        ++index;
    }
}

PUParticle3DModelRender::PUParticle3DModelRender()
{
    autoRotate = true;
}

PUParticle3DModelRender::~PUParticle3DModelRender()
{
    for (auto iter : _spriteList){
        iter->release();
    }
}

void PUParticle3DModelRender::copyAttributesTo(PUParticle3DModelRender *render)
{
    PURender::copyAttributesTo(render);
}

PUParticle3DModelRender* PUParticle3DModelRender::clone()
{
    auto mr = PUParticle3DModelRender::create(_modelFile, _texFile);
    copyAttributesTo(mr);
    return mr;
}


PUParticle3DEntityRender::PUParticle3DEntityRender()
    : _meshCommand(nullptr)
    , _texture(nullptr)
    , _glProgramState(nullptr)
    , _indexBuffer(nullptr)
    , _vertexBuffer(nullptr)
{
    _stateBlock = RenderState::StateBlock::create();
    CC_SAFE_RETAIN(_stateBlock);

    _stateBlock->setCullFace(false);
    _stateBlock->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
    _stateBlock->setDepthTest(false);
    _stateBlock->setDepthWrite(false);
    _stateBlock->setBlend(true);
}

PUParticle3DEntityRender::~PUParticle3DEntityRender()
{
    CC_SAFE_DELETE(_meshCommand);
    CC_SAFE_RELEASE(_stateBlock);
    //CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_glProgramState);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
}

bool PUParticle3DEntityRender::initRender( const std::string &texFile )
{
    GLProgram* glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_PARTICLE_COLOR);
    if (!texFile.empty())
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage(texFile);
        if (tex)
        {
            _texture = tex;
            _texFile = texFile;
            glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_PARTICLE_TEXTURE);
        }
    }
    auto glProgramState = GLProgramState::create(glProgram);
    glProgramState->retain();

    GLsizei stride = sizeof(VertexInfo);

    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_POSITION], 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(VertexInfo, position));
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_TEX_COORD], 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(VertexInfo, uv));
    glProgramState->setVertexAttribPointer(s_attributeNames[GLProgram::VERTEX_ATTRIB_COLOR], 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offsetof(VertexInfo, color));

    _glProgramState = glProgramState;

    _meshCommand = new (std::nothrow) MeshCommand();
    _meshCommand->setSkipBatching(true);
    _meshCommand->setTransparent(true);

    _stateBlock->setDepthTest(_depthTest);
    _stateBlock->setDepthWrite(_depthWrite);
    _stateBlock->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
    _stateBlock->setCullFace(true);
    return true;
}

void PUParticle3DEntityRender::copyAttributesTo(PUParticle3DEntityRender *render)
{
    PURender::copyAttributesTo(render);
}

PUParticle3DBoxRender::PUParticle3DBoxRender()
{
    autoRotate = false;
}

PUParticle3DBoxRender::~PUParticle3DBoxRender()
{
}

PUParticle3DBoxRender* PUParticle3DBoxRender::create( const std::string &texFile )
{
    auto ret = new (std::nothrow) PUParticle3DBoxRender();
    if (ret && ret->initRender(texFile))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void PUParticle3DBoxRender::render( Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem )
{
    //batch and generate draw
    const ParticlePool &particlePool = particleSystem->getParticlePool();
    if (!_isVisible || particlePool.empty())
        return;

    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();
    Vec3 backward(cameraMat.m[8], cameraMat.m[9], cameraMat.m[10]);

    if (_vertexBuffer == nullptr && _indexBuffer == nullptr){
        GLsizei stride = sizeof(VertexInfo);
        _vertexBuffer = VertexBuffer::create(stride, 8 * particleSystem->getParticleQuota());
        if (_vertexBuffer == nullptr)
        {
            CCLOG("PUParticle3DBoxRender::render create vertex buffer failed");
            return;
        }
        _vertexBuffer->retain();
        _vertices.resize(8 * particleSystem->getParticleQuota());

        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 36 * particleSystem->getParticleQuota());
        if (_indexBuffer == nullptr)
        {
            CCLOG("PUParticle3DBoxRender::render create index buffer failed");
            return;
        }
        _indexBuffer->retain();
        _indices.resize(36 * particleSystem->getParticleQuota());
        reBuildIndices(particleSystem->getParticleQuota());
    }

    unsigned int vertexindex = 0;
    unsigned int index = 0;
    Mat4 texRot;
    Vec3 val;
    for (auto iter : particlePool.getActiveDataList())
    {
        auto particle = static_cast<PUParticle3D *>(iter);
        float halfHeight = particle->height * 0.5f;
        float halfWidth = particle->width * 0.5f;
        float halfDepth = particle->depth * 0.5f;
        Mat4::createRotation(backward, particle->zRotation, &texRot);
        val = texRot * Vec3(0.0f, 0.75f, 0.0);
        _vertices[vertexindex + 0].position = particle->position + Vec3(-halfWidth, -halfHeight, halfDepth);
        _vertices[vertexindex + 0].color = particle->color;
        _vertices[vertexindex + 0].uv.x = val.x; _vertices[vertexindex + 0].uv.y = val.y; 
        val = texRot * Vec3(0.0f, 0.25f, 0.0);
        _vertices[vertexindex + 1].position = particle->position + Vec3(halfWidth, -halfHeight, halfDepth);
        _vertices[vertexindex + 1].color = particle->color;
        _vertices[vertexindex + 1].uv.x = val.x; _vertices[vertexindex + 1].uv.y = val.y;
        val = texRot * Vec3(0.5f, 0.25f, 0.0);
        _vertices[vertexindex + 2].position = particle->position + Vec3(halfWidth, halfHeight, halfDepth);
        _vertices[vertexindex + 2].color = particle->color;
        _vertices[vertexindex + 2].uv.x = val.x; _vertices[vertexindex + 2].uv.y = val.y;
        val = texRot * Vec3(0.5f, 0.75f, 0.0);
        _vertices[vertexindex + 3].position = particle->position + Vec3(-halfWidth, halfHeight, halfDepth);
        _vertices[vertexindex + 3].color = particle->color;
        _vertices[vertexindex + 3].uv.x = val.x; _vertices[vertexindex + 3].uv.y = val.y;

        val = texRot * Vec3(0.0f, 0.0f, 0.0);
        _vertices[vertexindex + 4].position = particle->position + Vec3(halfWidth, -halfHeight, -halfDepth);
        _vertices[vertexindex + 4].color = particle->color;
        _vertices[vertexindex + 4].uv.x = val.x; _vertices[vertexindex + 4].uv.y = val.y;
        val = texRot * Vec3(0.0f, 1.0f, 0.0);
        _vertices[vertexindex + 5].position = particle->position + Vec3(-halfWidth, -halfHeight, -halfDepth);
        _vertices[vertexindex + 5].color = particle->color;
        _vertices[vertexindex + 5].uv.x = val.x; _vertices[vertexindex + 5].uv.y = val.y;
        val = texRot * Vec3(0.5f, 1.0f, 0.0);
        _vertices[vertexindex + 6].position = particle->position + Vec3(-halfWidth, halfHeight, -halfDepth);
        _vertices[vertexindex + 6].color = particle->color;
        _vertices[vertexindex + 6].uv.x = val.x; _vertices[vertexindex + 6].uv.y = val.y;
        val = texRot * Vec3(0.5f, 0.0f, 0.0);
        _vertices[vertexindex + 7].position = particle->position + Vec3(halfWidth, halfHeight, -halfDepth);
        _vertices[vertexindex + 7].color = particle->color;
        _vertices[vertexindex + 7].uv.x = val.x; _vertices[vertexindex + 7].uv.y = val.y;

        vertexindex += 8;
        index += 36;
    }

    if (!_vertices.empty() && !_indices.empty()){
        _vertexBuffer->updateVertices(&_vertices[0], vertexindex/* * sizeof(_posuvcolors[0])*/, 0);
        _indexBuffer->updateIndices(&_indices[0], index/* * sizeof(unsigned short)*/, 0);

        GLuint texId = (_texture ? _texture->getName() : 0);
        _stateBlock->setBlendFunc(_particleSystem->getBlendFunc());
        _meshCommand->init(0,
                           texId,
                           _glProgramState,
                           _stateBlock,
                           _vertexBuffer->getVBO(),
                           _indexBuffer->getVBO(),
                           GL_TRIANGLES,
                           GL_UNSIGNED_SHORT,
                           index,
                           transform,
                           Node::FLAGS_RENDER_AS_3D);
        _meshCommand->setSkipBatching(true);
        _meshCommand->setTransparent(true);

        _glProgramState->setUniformVec4("u_color", Vec4(1,1,1,1));
        renderer->addCommand(_meshCommand);
    }
}

void PUParticle3DBoxRender::reBuildIndices(unsigned short count)
{
    unsigned short vertexIndex = 0;
    for (unsigned short i = 0; i < 36 * count;){
        //front
        _indices[i++] = vertexIndex + 0;
        _indices[i++] = vertexIndex + 2;
        _indices[i++] = vertexIndex + 3;
        _indices[i++] = vertexIndex + 0;
        _indices[i++] = vertexIndex + 1;
        _indices[i++] = vertexIndex + 2;
        //right
        _indices[i++] = vertexIndex + 1;
        _indices[i++] = vertexIndex + 7;
        _indices[i++] = vertexIndex + 2;
        _indices[i++] = vertexIndex + 1;
        _indices[i++] = vertexIndex + 4;
        _indices[i++] = vertexIndex + 7;
        //back
        _indices[i++] = vertexIndex + 4;
        _indices[i++] = vertexIndex + 6;
        _indices[i++] = vertexIndex + 7;
        _indices[i++] = vertexIndex + 4;
        _indices[i++] = vertexIndex + 5;
        _indices[i++] = vertexIndex + 6;
        //left
        _indices[i++] = vertexIndex + 5;
        _indices[i++] = vertexIndex + 3;
        _indices[i++] = vertexIndex + 6;
        _indices[i++] = vertexIndex + 5;
        _indices[i++] = vertexIndex + 0;
        _indices[i++] = vertexIndex + 3;
        //top
        _indices[i++] = vertexIndex + 3;
        _indices[i++] = vertexIndex + 7;
        _indices[i++] = vertexIndex + 6;
        _indices[i++] = vertexIndex + 3;
        _indices[i++] = vertexIndex + 2;
        _indices[i++] = vertexIndex + 7;
        //bottom
        _indices[i++] = vertexIndex + 5;
        _indices[i++] = vertexIndex + 1;
        _indices[i++] = vertexIndex + 0;
        _indices[i++] = vertexIndex + 5;
        _indices[i++] = vertexIndex + 4;
        _indices[i++] = vertexIndex + 1;

        vertexIndex += 8;
    }
}

PUParticle3DBoxRender* PUParticle3DBoxRender::clone()
{
    auto render = PUParticle3DBoxRender::create(_texFile);
    copyAttributesTo(render);
    return render;
}


PUSphereRender* PUSphereRender::create( const std::string &texFile)
{
    auto ret = new (std::nothrow) PUSphereRender();
    if (ret && ret->initRender(texFile))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void PUSphereRender::render( Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem )
{
    //batch and generate draw
    const ParticlePool &particlePool = particleSystem->getParticlePool();
    if (!_isVisible || particlePool.empty())
        return;

    auto camera = Camera::getVisitingCamera();
    auto cameraMat = camera->getNodeToWorldTransform();
    Vec3 backward(cameraMat.m[8], cameraMat.m[9], cameraMat.m[10]);

    unsigned int vertexCount = (_numberOfRings + 1) * (_numberOfSegments + 1);
    unsigned int indexCount = 6 * _numberOfRings * (_numberOfSegments + 1);
    if (_vertexBuffer == nullptr && _indexBuffer == nullptr){
        GLsizei stride = sizeof(VertexInfo);
        _vertexBuffer = VertexBuffer::create(stride, vertexCount * particleSystem->getParticleQuota());
        if (_vertexBuffer == nullptr)
        {
            CCLOG("PUSphereRender::render create vertex buffer failed");
            return;
        }
        _vertexBuffer->retain();
        _vertices.resize(vertexCount * particleSystem->getParticleQuota());

        _indexBuffer = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, indexCount * particleSystem->getParticleQuota());
        if (_indexBuffer == nullptr)
        {
            CCLOG("PUSphereRender::render create index buffer failed");
            return;
        }
        _indexBuffer->retain();
        _indices.resize(indexCount * particleSystem->getParticleQuota());

        buildBuffers(particleSystem->getParticleQuota());
    }

    unsigned int vertexindex = 0;
    unsigned int index = 0;

    Mat4 mat;
    Mat4 rotMat;
    Mat4 sclMat;
    Mat4 texRot;
    Vec3 val;
    for (auto iter : particlePool.getActiveDataList())
    {
        auto particle = static_cast<PUParticle3D *>(iter);
        float radius = particle->width * 0.5f;
        Mat4::createRotation(particle->orientation, &rotMat);
        Mat4::createScale(radius, radius, radius, &sclMat);
        Mat4::createRotation(backward, particle->zRotation, &texRot);
        mat = rotMat * sclMat;
        mat.m[12] = particle->position.x;
        mat.m[13] = particle->position.y;
        mat.m[14] = particle->position.z;

        for (unsigned int i = 0; i < vertexCount; ++i){
            val = texRot * Vec3(_vertexTemplate[vertexindex + i].uv.x, _vertexTemplate[vertexindex + i].uv.y, 0.0f);
            mat.transformPoint(_vertexTemplate[vertexindex + i].position, &_vertices[vertexindex + i].position);
            _vertices[vertexindex + i].color = particle->color;
            _vertices[vertexindex + i].uv.x = val.x; _vertices[vertexindex + i].uv.y = val.y;
        }
        vertexindex += vertexCount;
        index += indexCount;
    }

    if (!_vertices.empty() && !_indices.empty()){
        _vertexBuffer->updateVertices(&_vertices[0], vertexindex/* * sizeof(_posuvcolors[0])*/, 0);
        _indexBuffer->updateIndices(&_indices[0], index/* * sizeof(unsigned short)*/, 0);

        GLuint texId = (_texture ? _texture->getName() : 0);

        _stateBlock->setBlendFunc(particleSystem->getBlendFunc());
        _meshCommand->init(
                           0,
                           texId,
                           _glProgramState,
                           _stateBlock,
                           _vertexBuffer->getVBO(),
                           _indexBuffer->getVBO(),
                           GL_TRIANGLES,
                           GL_UNSIGNED_SHORT,
                           index,
                           transform,
                           Node::FLAGS_RENDER_AS_3D);
        _meshCommand->setSkipBatching(true);
        _meshCommand->setTransparent(true);

        _glProgramState->setUniformVec4("u_color", Vec4(1,1,1,1));
        renderer->addCommand(_meshCommand);
    }
}

void PUSphereRender::buildBuffers( unsigned short count )
{
    float stepRingAngle = (M_PI / _numberOfRings);
    float stepSegmentAngle = (2.0 * M_PI / _numberOfSegments);

    unsigned short vertexIndex = 0;
    unsigned short index = 0;

    for (unsigned short i = 0; i < count; ++i){
        for(unsigned int ring = 0; ring <= _numberOfRings; ring++)
        {
            float r0 = sinf (ring * stepRingAngle);
            float y0 = cosf (ring * stepRingAngle);

            for(unsigned int segment = 0; segment <= _numberOfSegments; segment++)
            {
                VertexInfo vi;
                float x0 = r0 * sinf(segment * stepSegmentAngle);
                float z0 = r0 * cosf(segment * stepSegmentAngle);

                // Vertex
                vi.position.set(x0, y0, z0);

                // Colour
                vi.color = Vec4::ONE;

                // Texture Coordinates
                vi.uv.x = (float) segment / (float) _numberOfSegments;
                vi.uv.y = 1.0f - (float) ring / (float) _numberOfRings;

                if (ring != _numberOfRings)
                {
                    // each vertex (except the last) has six indices pointing to it
                    _indices[index++] = vertexIndex + _numberOfSegments + 1;
                    _indices[index++] = vertexIndex;
                    _indices[index++] = vertexIndex + _numberOfSegments;
                    _indices[index++] = vertexIndex + _numberOfSegments + 1;
                    _indices[index++] = vertexIndex + 1;
                    _indices[index++] = vertexIndex;
                }
                ++vertexIndex;
                _vertexTemplate.push_back(vi);
            }
        }
    }
}

PUSphereRender::PUSphereRender()
    : _numberOfRings(16)
    , _numberOfSegments(16)
{
    autoRotate = false;
}

PUSphereRender::~PUSphereRender()
{

}

void PUSphereRender::copyAttributesTo(PUSphereRender *sphereRender)
{
    PURender::copyAttributesTo(sphereRender);
    sphereRender->_numberOfRings = _numberOfRings;
    sphereRender->_numberOfSegments = _numberOfSegments;
}

PUSphereRender* PUSphereRender::clone()
{
    auto render = PUSphereRender::create(_texFile);
    copyAttributesTo(render);
    return render;
}

NS_CC_END
