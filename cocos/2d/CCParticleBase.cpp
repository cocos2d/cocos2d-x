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

NS_CC_BEGIN

// Particle implementation
Particle::Particle()
: positionZ(0.0f)
, rotationX(0.0f)
, rotationY(0.0f)
, frame(0.0f)
, alpha(0.0f)
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

void ParticleEmitter::setParticleParent(Node* parent)
{
    _particleParent = parent;
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

void ParticleEmitter::update(float delta)
{
    updateParticles(delta);
    spawnParticles(delta, _need);
    updateEffectors(delta);
}

void ParticleEmitter::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    if (_renderer != nullptr)
    {
        _renderer->draw(this, renderer, transform, flags);
    }
}

// ParticleRenderer implementation
ParticleTextureAtlasRenderer::ParticleTextureAtlasRenderer()
: _quads(nullptr)
, _atlas(nullptr)
{
}

ParticleTextureAtlasRenderer::~ParticleTextureAtlasRenderer()
{
    
}

NS_CC_END