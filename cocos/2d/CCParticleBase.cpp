/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
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

#include "CCParticleBase.h"

#include <algorithm>
#include <stdlib.h>

#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgram.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

// Particle implementation
Particle::Particle()
: positionZ(0.0f)
, rotationX(0.0f)
, rotationY(0.0f)
, frame(0.0f)
, shapeType(ParticleEffector::ShapeType::RECTANGLE)
, contactType(ParticleEffector::ContactType::OUT)
{
}

Particle::~Particle()
{
}

void Particle::setEmitters(const Vector<ParticleEmitter*>& es)
{
    this->emitters.clear();
    for (auto emitter : es)
    {
        this->emitters.pushBack(dynamic_cast<ParticleEmitter*>(emitter->clone()));
    }
}

void Particle::addEmitter(ParticleEmitter* emitter)
{
    CC_ASSERT(emitter != nullptr);
    
    std::size_t i = emitters.size();
    for (; i > 0; ++i )
    {
        if (emitters.at(i - 1)->getZOrder() <= emitter->getZOrder())
        {
            break;
        }
    }
    emitters.insert(i, emitter);
}

// ParticleEffector implementation
ParticleEffector::ParticleEffector()
: _psRotation(0.0f)
{
    memset(&_shape, 0, sizeof(_shape));
}

void ParticleEffector::setShape(Vec2 position, float width, float height)
{
    _shape.shape.rectangle.width = width;
    _shape.shape.rectangle.height = height;
    _shape.type = ShapeType::RECTANGLE;
}

void ParticleEffector::setShape(Vec2 position, float radius)
{
    _shape.shape.circle.radius = radius;
    _shape.type = ShapeType::CIRCLE;
}

void ParticleEffector::update(float delta)
{
    updateContact(delta);
    updateParticles(delta);
}

void ParticleEffector::updateContact(float delta)
{
    // check contaction and push particles to each vector
}

// ParticleEmitter implementation
ParticleEmitter::ParticleEmitter()
: _renderer(nullptr)
, _particleParent(nullptr)
, _psRotation(0.0f)
, _need(0)
{
    memset(&_particleShapeType, 0, sizeof(_particleShapeType));
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::setParticleShape(int frame, ParticleEffector::ShapeType type, bool updateExist/* = false*/)
{
    CCASSERT(frame < PARTICLEFRAME_MAX, "frame out of range, if you want more frame, you need to set PARTICLEFRAME_MAX");
    _particleShapeType[frame] = type;
    
    if (updateExist)
    {
        for (auto particle : _particles)
        {
            if (particle->frame == frame)
            {
                particle->shapeType = type;
            }
        }
    }
}

void ParticleEmitter::addEffector(ParticleEffector* effector)
{
    CC_ASSERT(effector != nullptr);
    
    _effectors.pushBack(effector);
}

void ParticleEmitter::removeEffector(ParticleEffector* effector)
{
    if (effector == nullptr)
    {
        return;
    }
    
    _effectors.eraseObject(effector);
}

void ParticleEmitter::setRenderer(ParticleRendererProtocol* renderer)
{
    CC_SAFE_RELEASE(_renderer);
    _renderer = renderer;
    CC_SAFE_RETAIN(_renderer);
}

void ParticleEmitter::updateEffectors(float delta)
{
    for (auto effector : _effectors)
    {
        effector->update(delta);
    }
}

void ParticleEmitter::updateQuads()
{
    int i = 0;
    for (; i < _emitters.size(); ++i)
    {
        if (_emitters.at(i)->getZOrder() < 0)
        {
            for (auto particle : _particles)
            {
                if (particle->emitters.at(i) != nullptr)
                {
                    particle->emitters.at(i)->updateQuads();
                }
            }
        }
    }
    
    _renderer->updateQuads(this);
    
    for (; i < _emitters.size(); ++i)
    {
        for (auto particle : _particles)
        {
            if (particle->emitters.at(i) != nullptr)
            {
                particle->emitters.at(i)->updateQuads();
            }
        }
    }
}

void ParticleEmitter::update(float delta)
{
    updateParticles(delta);
    spawnParticles(delta, _need);
    updateEffectors(delta);
    updateQuads();
}

void ParticleEmitter::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    if (_renderer != nullptr)
    {
        _renderer->draw(renderer, transform, flags);
    }
}

// ParticleRenderer implementation
ParticleTextureAtlasRenderer::ParticleTextureAtlasRenderer()
: _texture(nullptr)
, _lock(true)
{
}

ParticleTextureAtlasRenderer::~ParticleTextureAtlasRenderer()
{
    for (auto each : _render)
    {
        delete each.second;
    }
    
    _render.clear();
}

ParticleTextureAtlasRenderer* ParticleTextureAtlasRenderer::create(Texture2D* texture)
{
    auto ret = new ParticleTextureAtlasRenderer();
    if (ret != nullptr && ret->init(texture))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ParticleTextureAtlasRenderer::init(Texture2D* texture)
{
    _texture = texture;
    Size size = _texture->getContentSize();
    
    // set frame 0 as whole texture by default
    setTextureRectForFrame(0, Rect(0, 0, size.width, size.height));
    
    return true;
}

void ParticleTextureAtlasRenderer::setTextureRectForFrame(int frame, const cocos2d::Rect &rect)
{
    auto it = _rectForFrame.find(frame);
    if (it != _rectForFrame.end())
    {
        it->second = rect;
    }
    else
    {
        _rectForFrame.insert(std::pair<int, Rect>(frame, rect));
    }
}

Rect ParticleTextureAtlasRenderer::getTextureRectForFrame(int frame)
{
    auto it = _rectForFrame.find(frame);
    if (it == _rectForFrame.end())
    {
        CCLOG("ParticleTextureAtlasRenderer: frame is not found");
        return Rect();
    }
    
    return it->second;
}


void ParticleTextureAtlasRenderer::updateQuads(ParticleEmitter* emitter)
{
    int total = emitter->getTotalParticles();
    int z = emitter->getGlobalZOrder();
    auto it = _render.find(z);
    RenderStruct* render = nullptr;
    
    if (it == _render.end())
    {
        render = new RenderStruct();
        if (render == nullptr)
        {
            CCLOG("ParticleTextureAtlasRenderer: out of memory");
            return;
        }
    }
    else
    {
        render = it->second;
    }
    
    if (render->nextAvalibleQuads + total > render->quads.size())
    {
        render->quads.resize(render->nextAvalibleQuads + total);
        render->indices.resize((render->nextAvalibleQuads + total) * 6);
        
        initIndices(render);
    }
    
    auto particles = emitter->getParticles();
    auto parent = emitter->getParent();
    auto transform = parent->getNodeToWorldTransform();
    auto scaleX = emitter->getScaleX();
    auto scaleY = emitter->getScaleY();
    auto texSize = _texture->getContentSize();
    for (int i = 0; i < total; ++i)
    {
        V2F_C4B_T2F_Quad& quad = render->quads[render->nextAvalibleQuads + i];
        auto particle = particles.at(i);
        
        CC_ASSERT(particle != nullptr);
        
        // ignore z
        Vec3 pos = Vec3(particle->position.x, particle->position.y, 0);
        transform.transformPoint(&pos);
        
        float left, right, top, bottom;
        
        // vertices
        left = (pos.x - particle->anchor.x * particle->size.x) * scaleX;
        right = (pos.x + (1 - particle->anchor.x) * particle->size.x) * scaleX;
        top = (pos.y - particle->anchor.y * particle->size.y) * scaleY;
        bottom = (pos.y + (1 - particle->anchor.y) * particle->size.y) * scaleY;
        
        
        quad.bl.vertices.x = left;
        quad.bl.vertices.y = bottom;
        quad.br.vertices.x = left;
        quad.br.vertices.y = top;
        quad.tl.vertices.x = right;
        quad.tl.vertices.y = bottom;
        quad.tr.vertices.x = right;
        quad.tr.vertices.y = top;
        
        // texcoords
        Rect rect = getTextureRectForFrame(particle->frame);
        left   = (rect.origin.x / texSize.width);
        right  = left + (rect.size.width / texSize.width);
        bottom = (rect.origin.y / texSize.height);
        top    = bottom + (rect.size.height / texSize.height);
        
        quad.bl.texCoords.u = left;
        quad.bl.texCoords.v = bottom;
        quad.br.texCoords.u = right;
        quad.br.texCoords.v = bottom;
        quad.tl.texCoords.u = left;
        quad.tl.texCoords.v = top;
        quad.tr.texCoords.u = right;
        quad.tr.texCoords.v = top;
        
        quad.bl.colors = particle->color;
        quad.br.colors = particle->color;
        quad.tl.colors = particle->color;
        quad.tr.colors = particle->color;
    }
    
    render->nextAvalibleQuads =  render->nextAvalibleQuads + total;
    _lock = false;
}

void ParticleTextureAtlasRenderer::initIndices(RenderStruct* render)
{
    if (render == nullptr)
    {
        return;
    }
    
    for(int i = render->nextAvalibleQuads; i < render->quads.size(); ++i)
    {
        const unsigned int i6 = i*6;
        const unsigned int i4 = i*4;
        render->indices[i6+0] = (GLushort) i4+0;
        render->indices[i6+1] = (GLushort) i4+1;
        render->indices[i6+2] = (GLushort) i4+2;
        
        render->indices[i6+5] = (GLushort) i4+1;
        render->indices[i6+4] = (GLushort) i4+2;
        render->indices[i6+3] = (GLushort) i4+3;
    }
}

void ParticleTextureAtlasRenderer::updateVertexBuffer(RenderStruct* render)
{
    if (render == nullptr)
    {
        return;
    }
    
    GL::bindVAO(0);
    if(!glIsBuffer(render->buffersVBO[0]))
    {
        glGenBuffers(1, &render->buffersVBO[0]);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, render->buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B_T2F_Quad) * render->nextAvalibleQuads, (GLvoid*)&render->quads[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleTextureAtlasRenderer::updateIndexBuffer(RenderStruct* render)
{
    if (render == nullptr)
    {
        return;
    }
    
    if(!glIsBuffer(render->buffersVBO[1]))
    {
        glGenBuffers(1, &render->buffersVBO[1]);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * render->nextAvalibleQuads * 6, &render->indices[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ParticleTextureAtlasRenderer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    if (_lock)
    {
        return;
    }
    
    for (auto each : _render)
    {
        auto render = each.second;
        if (render != nullptr)
        {
            updateVertexBuffer(render);
            updateIndexBuffer(render);
            render->command.init(each.first);
            render->command.func = CC_CALLBACK_0(ParticleTextureAtlasRenderer::onDraw, this, render);
            renderer->addCommand(&render->command);
            render->nextAvalibleQuads = 0;
        }
    }
    
    _lock = true;
}
void ParticleTextureAtlasRenderer::onDraw(RenderStruct* render)
{
    GL::bindTexture2D(_texture->getName());
    
    GL::bindVAO(0);
    glBindBuffer(GL_ARRAY_BUFFER, render->buffersVBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render->buffersVBO[1]);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)0);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, colors));
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*)offsetof(V3F_C4B_T2F, texCoords));
    glDrawElements(GL_TRIANGLES, (GLsizei)render->nextAvalibleQuads * 6, GL_UNSIGNED_INT, (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, render->nextAvalibleQuads * 4);
}

NS_CC_END