/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
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


#include "2d/CCParticleSystemQuad.h"

#include <algorithm>

#include "2d/CCSpriteFrame.h"
#include "2d/CCParticleBatchNode.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

ParticleSystemQuad::ParticleSystemQuad()
:_quads(nullptr)
,_indices(nullptr)
,_VAOname(0)
{
    memset(_buffersVBO, 0, sizeof(_buffersVBO));
}

ParticleSystemQuad::~ParticleSystemQuad()
{
    if (nullptr == _batchNode)
    {
        CC_SAFE_FREE(_quads);
        CC_SAFE_FREE(_indices);
        glDeleteBuffers(2, &_buffersVBO[0]);
        if (Configuration::getInstance()->supportsShareableVAO())
        {
            glDeleteVertexArrays(1, &_VAOname);
            GL::bindVAO(0);
        }
    }
}

// implementation ParticleSystemQuad

ParticleSystemQuad * ParticleSystemQuad::create(const std::string& filename)
{
    ParticleSystemQuad *ret = new (std::nothrow) ParticleSystemQuad();
    if (ret && ret->initWithFile(filename))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

ParticleSystemQuad * ParticleSystemQuad::createWithTotalParticles(int numberOfParticles) {
    ParticleSystemQuad *ret = new (std::nothrow) ParticleSystemQuad();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

ParticleSystemQuad * ParticleSystemQuad::create(ValueMap &dictionary)
{
    ParticleSystemQuad *ret = new (std::nothrow) ParticleSystemQuad();
    if (ret && ret->initWithDictionary(dictionary))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

//implementation ParticleSystemQuad
// overriding the init method
bool ParticleSystemQuad::initWithTotalParticles(int numberOfParticles)
{
    // base initialization
    if( ParticleSystem::initWithTotalParticles(numberOfParticles) )
    {
        // allocating data space
        if( ! this->allocMemory() ) {
            this->release();
            return false;
        }

        initIndices();
        if (Configuration::getInstance()->supportsShareableVAO())
        {
            setupVBOandVAO();
        }
        else
        {
            setupVBO();
        }

        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));

#if CC_ENABLE_CACHE_TEXTURE_DATA
        // Need to listen the event only when not use batchnode, because it will use VBO
        auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(ParticleSystemQuad::listenRendererRecreated, this));
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

        return true;
    }
    return false;
}

// pointRect should be in Texture coordinates, not pixel coordinates
void ParticleSystemQuad::initTexCoordsWithRect(const Rect& pointRect)
{
    // convert to Tex coords

    Rect rect = Rect(
        pointRect.origin.x * CC_CONTENT_SCALE_FACTOR(),
        pointRect.origin.y * CC_CONTENT_SCALE_FACTOR(),
        pointRect.size.width * CC_CONTENT_SCALE_FACTOR(),
        pointRect.size.height * CC_CONTENT_SCALE_FACTOR());

    GLfloat wide = (GLfloat) pointRect.size.width;
    GLfloat high = (GLfloat) pointRect.size.height;

    if (_texture)
    {
        wide = (GLfloat)_texture->getPixelsWide();
        high = (GLfloat)_texture->getPixelsHigh();
    }

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    GLfloat left = (rect.origin.x*2+1) / (wide*2);
    GLfloat bottom = (rect.origin.y*2+1) / (high*2);
    GLfloat right = left + (rect.size.width*2-2) / (wide*2);
    GLfloat top = bottom + (rect.size.height*2-2) / (high*2);
#else
    GLfloat left = rect.origin.x / wide;
    GLfloat bottom = rect.origin.y / high;
    GLfloat right = left + rect.size.width / wide;
    GLfloat top = bottom + rect.size.height / high;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

    // Important. Texture in cocos2d are inverted, so the Y component should be inverted
    std::swap(top, bottom);

    V3F_C4B_T2F_Quad *quads = nullptr;
    unsigned int start = 0, end = 0;
    if (_batchNode)
    {
        quads = _batchNode->getTextureAtlas()->getQuads();
        start = _atlasIndex;
        end = _atlasIndex + _totalParticles;
    }
    else
    {
        quads = _quads;
        start = 0;
        end = _totalParticles;
    }

    for(unsigned int i=start; i<end; i++) 
    {
        // bottom-left vertex:
        quads[i].bl.texCoords.u = left;
        quads[i].bl.texCoords.v = bottom;
        // bottom-right vertex:
        quads[i].br.texCoords.u = right;
        quads[i].br.texCoords.v = bottom;
        // top-left vertex:
        quads[i].tl.texCoords.u = left;
        quads[i].tl.texCoords.v = top;
        // top-right vertex:
        quads[i].tr.texCoords.u = right;
        quads[i].tr.texCoords.v = top;
    }
}

void ParticleSystemQuad::updateTexCoords()
{
    if (_texture)
    {
        const Size& s = _texture->getContentSize();
        initTexCoordsWithRect(Rect(0, 0, s.width, s.height));
    }
}

void ParticleSystemQuad::setTextureWithRect(Texture2D *texture, const Rect& rect)
{
    // Only update the texture if is different from the current one
    if( !_texture || texture->getName() != _texture->getName() )
    {
        ParticleSystem::setTexture(texture);
    }

    this->initTexCoordsWithRect(rect);
}

void ParticleSystemQuad::setTexture(Texture2D* texture)
{
    const Size& s = texture->getContentSize();
    this->setTextureWithRect(texture, Rect(0, 0, s.width, s.height));
}

void ParticleSystemQuad::setDisplayFrame(SpriteFrame *spriteFrame)
{
    CCASSERT(spriteFrame->getOffsetInPixels().isZero(), 
             "QuadParticle only supports SpriteFrames with no offsets");

    this->setTextureWithRect(spriteFrame->getTexture(), spriteFrame->getRect());
}

void ParticleSystemQuad::initIndices()
{
    for(int i = 0; i < _totalParticles; ++i)
    {
        const unsigned int i6 = i*6;
        const unsigned int i4 = i*4;
        _indices[i6+0] = (GLushort) i4+0;
        _indices[i6+1] = (GLushort) i4+1;
        _indices[i6+2] = (GLushort) i4+2;

        _indices[i6+5] = (GLushort) i4+1;
        _indices[i6+4] = (GLushort) i4+2;
        _indices[i6+3] = (GLushort) i4+3;
    }
}

inline void updatePosWithParticle(V3F_C4B_T2F_Quad *quad, const Vec2& newPosition,float size,float rotation)
{
    // vertices
    GLfloat size_2 = size/2;
    GLfloat x1 = -size_2;
    GLfloat y1 = -size_2;
    
    GLfloat x2 = size_2;
    GLfloat y2 = size_2;
    GLfloat x = newPosition.x;
    GLfloat y = newPosition.y;
    
    GLfloat r = (GLfloat)-CC_DEGREES_TO_RADIANS(rotation);
    GLfloat cr = cosf(r);
    GLfloat sr = sinf(r);
    GLfloat ax = x1 * cr - y1 * sr + x;
    GLfloat ay = x1 * sr + y1 * cr + y;
    GLfloat bx = x2 * cr - y1 * sr + x;
    GLfloat by = x2 * sr + y1 * cr + y;
    GLfloat cx = x2 * cr - y2 * sr + x;
    GLfloat cy = x2 * sr + y2 * cr + y;
    GLfloat dx = x1 * cr - y2 * sr + x;
    GLfloat dy = x1 * sr + y2 * cr + y;
    
    // bottom-left
    quad->bl.vertices.x = ax;
    quad->bl.vertices.y = ay;
    
    // bottom-right vertex:
    quad->br.vertices.x = bx;
    quad->br.vertices.y = by;
    
    // top-left vertex:
    quad->tl.vertices.x = dx;
    quad->tl.vertices.y = dy;
    
    // top-right vertex:
    quad->tr.vertices.x = cx;
    quad->tr.vertices.y = cy;
}

void ParticleSystemQuad::updateParticleQuads()
{
    if (_particleCount <= 0) {
        return;
    }
 
    Vec2 currentPosition;
    if (_positionType == PositionType::FREE)
    {
        currentPosition = this->convertToWorldSpace(Vec2::ZERO);
    }
    else if (_positionType == PositionType::RELATIVE)
    {
        currentPosition = _position;
    }
    
    V3F_C4B_T2F_Quad *startQuad;
    Vec2 pos = Vec2::ZERO;
    if (_batchNode)
    {
        V3F_C4B_T2F_Quad *batchQuads = _batchNode->getTextureAtlas()->getQuads();
        startQuad = &(batchQuads[_atlasIndex]);
        pos = _position;
    }
    else
    {
        startQuad = &(_quads[0]);
    }
    
    if( _positionType == PositionType::FREE )
    {
        Vec3 p1(currentPosition.x, currentPosition.y, 0);
        Mat4 worldToNodeTM = getWorldToNodeTransform();
        worldToNodeTM.transformPoint(&p1);
        Vec3 p2;
        Vec2 newPos;
        float* startX = _particleData.startPosX;
        float* startY = _particleData.startPosY;
        float* x = _particleData.posx;
        float* y = _particleData.posy;
        float* s = _particleData.size;
        float* r = _particleData.rotation;
        V3F_C4B_T2F_Quad* quadStart = startQuad;
        for (int i = 0 ; i < _particleCount; ++i, ++startX, ++startY, ++x, ++y, ++quadStart, ++s, ++r)
        {
            p2.set(*startX, *startY, 0);
            worldToNodeTM.transformPoint(&p2);
            newPos.set(*x,*y);
            p2 = p1 - p2;
            newPos.x -= p2.x - pos.x;
            newPos.y -= p2.y - pos.y;
            updatePosWithParticle(quadStart, newPos, *s, *r);
        }
    }
    else if( _positionType == PositionType::RELATIVE )
    {
        Vec2 newPos;
        float* startX = _particleData.startPosX;
        float* startY = _particleData.startPosY;
        float* x = _particleData.posx;
        float* y = _particleData.posy;
        float* s = _particleData.size;
        float* r = _particleData.rotation;
        V3F_C4B_T2F_Quad* quadStart = startQuad;
        for (int i = 0 ; i < _particleCount; ++i, ++startX, ++startY, ++x, ++y, ++quadStart, ++s, ++r)
        {
            newPos.set(*x, *y);
            newPos.x = *x - (currentPosition.x - *startX);
            newPos.y = *y - (currentPosition.y - *startY);
            newPos += pos;
            updatePosWithParticle(quadStart, newPos, *s, *r);
        }
    }
    else
    {
        Vec2 newPos;
        float* startX = _particleData.startPosX;
        float* startY = _particleData.startPosY;
        float* x = _particleData.posx;
        float* y = _particleData.posy;
        float* s = _particleData.size;
        float* r = _particleData.rotation;
        V3F_C4B_T2F_Quad* quadStart = startQuad;
        for (int i = 0 ; i < _particleCount; ++i, ++startX, ++startY, ++x, ++y, ++quadStart, ++s, ++r)
        {
            newPos.set(*x + pos.x, *y + pos.y);
            updatePosWithParticle(quadStart, newPos, *s, *r);
        }
    }
    
    //set color
    if(_opacityModifyRGB)
    {
        V3F_C4B_T2F_Quad* quad = startQuad;
        float* r = _particleData.colorR;
        float* g = _particleData.colorG;
        float* b = _particleData.colorB;
        float* a = _particleData.colorA;
        
        for (int i = 0; i < _particleCount; ++i,++quad,++r,++g,++b,++a)
        {
            GLubyte colorR = *r * *a * 255;
            GLubyte colorG = *g * *a * 255;
            GLubyte colorB = *b * *a * 255;
            GLubyte colorA = *a * 255;
            quad->bl.colors.set(colorR, colorG, colorB, colorA);
            quad->br.colors.set(colorR, colorG, colorB, colorA);
            quad->tl.colors.set(colorR, colorG, colorB, colorA);
            quad->tr.colors.set(colorR, colorG, colorB, colorA);
        }
    }
    else
    {
        V3F_C4B_T2F_Quad* quad = startQuad;
        float* r = _particleData.colorR;
        float* g = _particleData.colorG;
        float* b = _particleData.colorB;
        float* a = _particleData.colorA;
        
        for (int i = 0; i < _particleCount; ++i,++quad,++r,++g,++b,++a)
        {
            GLubyte colorR = *r * 255;
            GLubyte colorG = *g * 255;
            GLubyte colorB = *b * 255;
            GLubyte colorA = *a * 255;
            quad->bl.colors.set(colorR, colorG, colorB, colorA);
            quad->br.colors.set(colorR, colorG, colorB, colorA);
            quad->tl.colors.set(colorR, colorG, colorB, colorA);
            quad->tr.colors.set(colorR, colorG, colorB, colorA);
        }
    }
}

void ParticleSystemQuad::postStep()
{
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    
    // Option 1: Sub Data
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_quads[0])*_totalParticles, _quads);
    
    // Option 2: Data
    //  glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * particleCount, quads_, GL_DYNAMIC_DRAW);
    
    // Option 3: Orphaning + glMapBuffer
    // glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0])*_totalParticles, nullptr, GL_STREAM_DRAW);
    // void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    // memcpy(buf, _quads, sizeof(_quads[0])*_totalParticles);
    // glUnmapBuffer(GL_ARRAY_BUFFER);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CHECK_GL_ERROR_DEBUG();
}

// overriding draw method
void ParticleSystemQuad::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    //quad command
    if(_particleCount > 0)
    {
        _quadCommand.init(_globalZOrder, _texture, getGLProgramState(), _blendFunc, _quads, _particleCount, transform, flags);
        renderer->addCommand(&_quadCommand);
    }
}

void ParticleSystemQuad::setTotalParticles(int tp)
{
    // If we are setting the total number of particles to a number higher
    // than what is allocated, we need to allocate new arrays
    if( tp > _allocatedParticles )
    {
        // Allocate new memory
        size_t quadsSize = sizeof(_quads[0]) * tp * 1;
        size_t indicesSize = sizeof(_indices[0]) * tp * 6 * 1;

        _particleData.release();
        if (!_particleData.init(tp))
        {
            CCLOG("Particle system: not enough memory");
            return;
        }
        V3F_C4B_T2F_Quad* quadsNew = (V3F_C4B_T2F_Quad*)realloc(_quads, quadsSize);
        GLushort* indicesNew = (GLushort*)realloc(_indices, indicesSize);

        if (quadsNew && indicesNew)
        {
            // Assign pointers
            _quads = quadsNew;
            _indices = indicesNew;

            // Clear the memory
            memset(_quads, 0, quadsSize);
            memset(_indices, 0, indicesSize);
            
            _allocatedParticles = tp;
        }
        else
        {
            // Out of memory, failed to resize some array
            if (quadsNew) _quads = quadsNew;
            if (indicesNew) _indices = indicesNew;

            CCLOG("Particle system: out of memory");
            return;
        }

        _totalParticles = tp;

        // Init particles
        if (_batchNode)
        {
            for (int i = 0; i < _totalParticles; i++)
            {
                _particleData.atlasIndex[i] = i;
            }
        }

        initIndices();
        if (Configuration::getInstance()->supportsShareableVAO())
        {
            setupVBOandVAO();
        }
        else
        {
            setupVBO();
        }
        
        // fixed http://www.cocos2d-x.org/issues/3990
        // Updates texture coords.
        updateTexCoords();
    }
    else
    {
        _totalParticles = tp;
    }
    
    // fixed issue #5762
    // reset the emission rate
    setEmissionRate(_totalParticles / _life);
    
    resetSystem();
}

void ParticleSystemQuad::setupVBOandVAO()
{
    glDeleteBuffers(2, &_buffersVBO[0]);

    // clean VAO
    if (_VAOname)
    {
        glDeleteVertexArrays(1, &_VAOname);
        GL::bindVAO(0);
        _VAOname = 0;
    }
    
    glGenVertexArrays(1, &_VAOname);
    GL::bindVAO(_VAOname);

#define kQuadSize sizeof(_quads[0].bl)

    glGenBuffers(2, &_buffersVBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _totalParticles, _quads, GL_DYNAMIC_DRAW);

    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, vertices));

    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, colors));

    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _totalParticles * 6, _indices, GL_STATIC_DRAW);

    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

void ParticleSystemQuad::setupVBO()
{
    glDeleteBuffers(2, &_buffersVBO[0]);
    
    glGenBuffers(2, &_buffersVBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _totalParticles, _quads, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _totalParticles * 6, _indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

void ParticleSystemQuad::listenRendererRecreated(EventCustom* /*event*/)
{
    //when comes to foreground in android, _buffersVBO and _VAOname is a wild handle
    //before recreating, we need to reset them to 0
    memset(_buffersVBO, 0, sizeof(_buffersVBO));
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        _VAOname = 0;
        setupVBOandVAO();
    }
    else
    {
        setupVBO();
    }
}

bool ParticleSystemQuad::allocMemory()
{
    CCASSERT( !_batchNode, "Memory should not be alloced when not using batchNode");

    CC_SAFE_FREE(_quads);
    CC_SAFE_FREE(_indices);

    _quads = (V3F_C4B_T2F_Quad*)malloc(_totalParticles * sizeof(V3F_C4B_T2F_Quad));
    _indices = (GLushort*)malloc(_totalParticles * 6 * sizeof(GLushort));
    
    if( !_quads || !_indices) 
    {
        CCLOG("cocos2d: Particle system: not enough memory");
        CC_SAFE_FREE(_quads);
        CC_SAFE_FREE(_indices);

        return false;
    }

    memset(_quads, 0, _totalParticles * sizeof(V3F_C4B_T2F_Quad));
    memset(_indices, 0, _totalParticles * 6 * sizeof(GLushort));

    return true;
}

void ParticleSystemQuad::setBatchNode(ParticleBatchNode * batchNode)
{
    if( _batchNode != batchNode ) 
    {
        ParticleBatchNode* oldBatch = _batchNode;

        ParticleSystem::setBatchNode(batchNode);

        // NEW: is self render ?
        if( ! batchNode ) 
        {
            allocMemory();
            initIndices();
            setTexture(oldBatch->getTexture());
            if (Configuration::getInstance()->supportsShareableVAO())
            {
                setupVBOandVAO();
            }
            else
            {
                setupVBO();
            }
        }
        // OLD: was it self render ? cleanup
        else if( !oldBatch )
        {
            // copy current state to batch
            V3F_C4B_T2F_Quad *batchQuads = _batchNode->getTextureAtlas()->getQuads();
            V3F_C4B_T2F_Quad *quad = &(batchQuads[_atlasIndex] );
            memcpy( quad, _quads, _totalParticles * sizeof(_quads[0]) );

            CC_SAFE_FREE(_quads);
            CC_SAFE_FREE(_indices);

            glDeleteBuffers(2, &_buffersVBO[0]);
            memset(_buffersVBO, 0, sizeof(_buffersVBO));
            if (Configuration::getInstance()->supportsShareableVAO())
            {
                glDeleteVertexArrays(1, &_VAOname);
                GL::bindVAO(0);
                _VAOname = 0;
            }
        }
    }
}

ParticleSystemQuad * ParticleSystemQuad::create() {
    ParticleSystemQuad *particleSystemQuad = new (std::nothrow) ParticleSystemQuad();
    if (particleSystemQuad && particleSystemQuad->init())
    {
        particleSystemQuad->autorelease();
        return particleSystemQuad;
    }
    CC_SAFE_DELETE(particleSystemQuad);
    return nullptr;
}

std::string ParticleSystemQuad::getDescription() const
{
    return StringUtils::format("<ParticleSystemQuad | Tag = %d, Total Particles = %d>", _tag, _totalParticles);
}
NS_CC_END
