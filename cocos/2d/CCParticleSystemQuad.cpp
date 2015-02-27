/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include "2d/CCSpriteFrame.h"
#include "2d/CCParticleBatchNode.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#include "base/ccUTF8.h"

NS_CC_BEGIN

ParticleSystemQuad::ParticleSystemQuad()
    : _vdParticles(nullptr)
    , _vbParticles(nullptr)
    , _ibParticles(nullptr)
{}

ParticleSystemQuad::~ParticleSystemQuad()
{
    CC_SAFE_RELEASE(_vdParticles);
    CC_SAFE_RELEASE(_vbParticles);
    CC_SAFE_RELEASE(_ibParticles);
}

std::string ParticleSystemQuad::getDescription() const
{
    return StringUtils::format("<ParticleSystemQuad | Tag = %d, Total Particles = %d>", _tag, _totalParticles);
}

// implementation ParticleSystemQuad

ParticleSystemQuad* ParticleSystemQuad::create()
{
    ParticleSystemQuad* particleSystemQuad = new (std::nothrow) ParticleSystemQuad();
    if (particleSystemQuad && particleSystemQuad->init())
    {
        particleSystemQuad->autorelease();
        return particleSystemQuad;
    }
    CC_SAFE_DELETE(particleSystemQuad);
    return nullptr;
}

ParticleSystemQuad* ParticleSystemQuad::create(const std::string& filename)
{
    ParticleSystemQuad* ret = new (std::nothrow) ParticleSystemQuad();
    if (ret && ret->initWithFile(filename))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

ParticleSystemQuad* ParticleSystemQuad::createWithTotalParticles(int numberOfParticles) {
    ParticleSystemQuad* ret = new (std::nothrow) ParticleSystemQuad();
    if (ret && ret->initWithTotalParticles(numberOfParticles))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

ParticleSystemQuad* ParticleSystemQuad::create(ValueMap &dictionary)
{
    ParticleSystemQuad* ret = new (std::nothrow) ParticleSystemQuad();
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
    if (!ParticleSystem::initWithTotalParticles(numberOfParticles))
        return false;
    
    setupVertices(numberOfParticles);
    setupIndices(numberOfParticles);

    if (_batchNode)
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    else
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return true;
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

    float wide = pointRect.size.width;
    float high = pointRect.size.height;

    if (_texture)
    {
        wide = _texture->getPixelsWide();
        high = _texture->getPixelsHigh();
    }

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
    float left = (rect.origin.x*2+1) / (wide*2);
    float bottom = (rect.origin.y*2+1) / (high*2);
    float right = left + (rect.size.width*2-2) / (wide*2);
    float top = bottom + (rect.size.height*2-2) / (high*2);
#else
    float left = rect.origin.x / wide;
    float bottom = rect.origin.y / high;
    float right = left + rect.size.width / wide;
    float top = bottom + rect.size.height / high;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

    // Important. Texture in cocos2d are inverted, so the Y component should be inverted
    std::swap(top, bottom);

    V3F_C4B_T2F_Quad* quads = nullptr;
    unsigned int start = 0, end = 0;
    if (_batchNode)
    {
        quads = _batchNode->getTextureAtlas()->getQuads();
        start = _atlasIndex;
        end = _atlasIndex + _totalParticles;
    }
    else
    {
        quads = _vbParticles->getElementsOfType<V3F_C4B_T2F_Quad>();
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

void ParticleSystemQuad::setTextureWithRect(Texture2D* texture, const Rect& rect)
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

void ParticleSystemQuad::setDisplayFrame(SpriteFrame* spriteFrame)
{
    CCASSERT(spriteFrame->getOffsetInPixels().equals(Vec2::ZERO), 
             "QuadParticle only supports SpriteFrames with no offsets");

    // update texture before updating texture rect
    if ( !_texture || spriteFrame->getTexture()->getName() != _texture->getName())
    {
        this->setTexture(spriteFrame->getTexture());
    }
}

// count and begin are both quad indices
void ParticleSystemQuad::setupIndices(size_t count, size_t begin)
{
    if (0 == count)
        return;
    
    auto indices = 6 * begin + _ibParticles->getElementsOfType<uint16_t>();
    auto end = begin + count;
    
    // count is in quads, begin is in indices, so quads * 6
    for (auto i = begin; i < end; ++i)
    {
        *indices++ = i*4+0;
        *indices++ = i*4+1;
        *indices++ = i*4+2;
        *indices++ = i*4+3;
        *indices++ = i*4+2;
        *indices++ = i*4+1;
    }
    
    _ibParticles->setDirty(true);
}

void ParticleSystemQuad::setupVertices(size_t count)
{
    // If you remove this node from a batch it
    // will attempt to re-setup vertex buffers.
    CC_SAFE_RELEASE_NULL(_vdParticles);
    CC_SAFE_RELEASE_NULL(_vbParticles);
    CC_SAFE_RELEASE_NULL(_ibParticles);

    _vdParticles = VertexData::create(VertexData::Primitive::Triangles);
    _vbParticles = VertexBuffer::create(sizeof(V3F_C4B_T2F), 4 * count, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic, true);
    _ibParticles = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, 6 * count, IndexBuffer::ArrayType::All, VertexBuffer::ArrayMode::LongLived, true);
    _vdParticles->setIndexBuffer(_ibParticles);
    
    _vdParticles->addStream(_vbParticles, VertexAttribute(offsetof(V3F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 3));
    _vdParticles->addStream(_vbParticles, VertexAttribute(offsetof(V3F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
    _vdParticles->addStream(_vbParticles, VertexAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2));
    
    CC_SAFE_RETAIN(_vdParticles);
    CC_SAFE_RETAIN(_vbParticles);
    CC_SAFE_RETAIN(_ibParticles);
}

void ParticleSystemQuad::updateQuadWithParticle(tParticle* particle, const Vec2& newPosition)
{
    V3F_C4B_T2F_Quad* quad;

    if (_batchNode)
    {
        V3F_C4B_T2F_Quad* batchQuads = _batchNode->getTextureAtlas()->getQuads();
        quad = &(batchQuads[_atlasIndex+particle->atlasIndex]);
    }
    else
    {
        auto quads = _vbParticles->getElementsOfType<V3F_C4B_T2F_Quad>();
        quad = &(quads[_particleIdx]);
    }
    Color4B color = (_opacityModifyRGB)
        ? Color4B( particle->color.r*particle->color.a*255, particle->color.g*particle->color.a*255, particle->color.b*particle->color.a*255, particle->color.a*255)
        : Color4B( particle->color.r*255, particle->color.g*255, particle->color.b*255, particle->color.a*255);

    quad->bl.colors = color;
    quad->br.colors = color;
    quad->tl.colors = color;
    quad->tr.colors = color;

    // vertices
    float size_2 = particle->size/2;
    if (particle->rotation) 
    {
        float x1 = -size_2;
        float y1 = -size_2;

        float x2 = size_2;
        float y2 = size_2;
        float x = newPosition.x;
        float y = newPosition.y;

        float r = (float)-CC_DEGREES_TO_RADIANS(particle->rotation);
        float cr = cosf(r);
        float sr = sinf(r);
        float ax = x1 * cr - y1 * sr + x;
        float ay = x1 * sr + y1 * cr + y;
        float bx = x2 * cr - y1 * sr + x;
        float by = x2 * sr + y1 * cr + y;
        float cx = x2 * cr - y2 * sr + x;
        float cy = x2 * sr + y2 * cr + y;
        float dx = x1 * cr - y2 * sr + x;
        float dy = x1 * sr + y2 * cr + y;

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
    else 
    {
        // bottom-left vertex:
        quad->bl.vertices.x = newPosition.x - size_2;
        quad->bl.vertices.y = newPosition.y - size_2;

        // bottom-right vertex:
        quad->br.vertices.x = newPosition.x + size_2;
        quad->br.vertices.y = newPosition.y - size_2;

        // top-left vertex:
        quad->tl.vertices.x = newPosition.x - size_2;
        quad->tl.vertices.y = newPosition.y + size_2;

        // top-right vertex:
        quad->tr.vertices.x = newPosition.x + size_2;
        quad->tr.vertices.y = newPosition.y + size_2;                
    }
}

void ParticleSystemQuad::postStep()
{
    _vbParticles->setDirty(true);
}

// overriding draw method
void ParticleSystemQuad::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    CCASSERT( _particleIdx == 0 || _particleIdx == _particleCount, "Abnormal error in particle quad");
    if(_particleIdx > 0)
    {
        _vbParticles->setElementCount(4 * _particleIdx);
        _ibParticles->setElementCount(6 * _particleIdx);

        _batchCommand.init(_globalZOrder, getGLProgram(), _blendFunc, _texture, _vdParticles, transform, flags);
        renderer->addCommand(&_batchCommand);
    }
}

void ParticleSystemQuad::setTotalParticles(int tp)
{
    // If we are setting the total number of particles to a number higher
    // than what is allocated, we need to expand the vertex buffer
    if (tp > _allocatedParticles)
    {
        auto amount = tp - _allocatedParticles;
        if (amount > 0)
        {
            auto begin = _ibParticles->getCapacity() / 6;     // determine first quad to update
            _ibParticles->addCapacityOfType<uint16_t>(6 * amount, true); // add capacity 6 indices per quad
            setupIndices(amount, begin);                  // update new indices for quads
            _vbParticles->addCapacityOfType<V3F_C4B_T2F_Quad>(amount, true);
        }
    
        _particles = (tParticle*)realloc(_particles, tp * sizeof(tParticle));
        _allocatedParticles = tp;
        _totalParticles = tp;

        // Init particles
        if (_batchNode)
        {
            auto p = _particles;
            for (int i = 0; i < _totalParticles; ++i, ++p)
                p->atlasIndex = i;
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

void ParticleSystemQuad::setBatchNode(ParticleBatchNode* batchNode)
{
    if( _batchNode != batchNode ) 
    {
        ParticleBatchNode* oldBatch = _batchNode;

        ParticleSystem::setBatchNode(batchNode);

        // NEW: is self render ?
        if (!batchNode)
        {
            setupVertices(_totalParticles);
            setupIndices(_totalParticles);
            setTexture(oldBatch->getTexture());
        }
        // OLD: was it self render ? cleanup
        else if (!oldBatch)
        {
            // copy current state to batch
            V3F_C4B_T2F_Quad* batchQuads = _batchNode->getTextureAtlas()->getQuads();
            V3F_C4B_T2F_Quad* dest = &(batchQuads[_atlasIndex]);
            auto source = _vbParticles->getElementsOfType<V3F_C4B_T2F_Quad>();
            memcpy(dest, source, _totalParticles * sizeof(V3F_C4B_T2F_Quad));

            CC_SAFE_RELEASE_NULL(_ibParticles);
            CC_SAFE_RELEASE_NULL(_vbParticles);
            CC_SAFE_RELEASE_NULL(_vdParticles);
        }
    }
    
    if (_batchNode)
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    else
        setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
}

NS_CC_END
