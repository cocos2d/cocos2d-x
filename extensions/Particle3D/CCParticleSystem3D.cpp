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

#include "CCParticleSystem3D.h"
#include "CCParticle3DEmitter.h"
#include "CCParticle3DAffector.h"
#include "CCParticle3DRender.h"

NS_CC_BEGIN

Particle3D::Particle3D()
: color(Vec4::ONE)
, rt_uv(Vec2::ONE)
, width(1.0f)
, height(1.0f)
, depth(1.0f)
{

}

Particle3D::~Particle3D()
{

}

ParticleSystem3D::ParticleSystem3D()
: _state(State::STOP)
, _emitter(nullptr)
, _render(nullptr)
, _aliveParticlesCnt(0)
, _particleQuota(0)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _keepLocal(false)
, _isEnabled(true)
{
    
}
ParticleSystem3D::~ParticleSystem3D()
{
    //stopParticle();
    removeAllAffector();
    CC_SAFE_RELEASE(_emitter);
    CC_SAFE_RELEASE(_render);
}

void ParticleSystem3D::startParticleSystem()
{
    if (_state != State::RUNNING)
    {
        if (_render)
            _render->notifyStart();
        
        scheduleUpdate();
        _state = State::RUNNING;
    }
}

void ParticleSystem3D::stopParticleSystem()
{
    if (_state != State::STOP)
    {
        if (_render)
            _render->notifyStop();
        
        unscheduleUpdate();
        _state = State::STOP;
    }
}

void ParticleSystem3D::pauseParticleSystem()
{
    if (_state == State::RUNNING)
    {
        _state = State::PAUSE;
    }
}

void ParticleSystem3D::resumeParticleSystem()
{
    if (_state == State::PAUSE)
    {
        _state = State::RUNNING;
    }
}

void ParticleSystem3D::setEmitter(Particle3DEmitter* emitter)
{
    if (_emitter != emitter)
    {
        CC_SAFE_RELEASE(_emitter);
        emitter->_particleSystem = this;
        _emitter = emitter;
        CC_SAFE_RETAIN(_emitter);
    }
}

void ParticleSystem3D::setRender(Particle3DRender* render)
{
    if (_render != render)
    {
        CC_SAFE_RELEASE(_render);
        _render = render;
        _render->_particleSystem = this;
        CC_SAFE_RETAIN(_render);
    }
}

void ParticleSystem3D::addAffector(Particle3DAffector* affector)
{
    if (affector && std::find(_affectors.begin(), _affectors.end(), affector) == _affectors.end()){
        affector->_particleSystem = this;
        affector->retain();
        _affectors.push_back(affector);
    }
}

void ParticleSystem3D::removeAffector(int index)
{
    CCASSERT((unsigned int)index < _affectors.size(), "wrong index");
    _affectors.erase(_affectors.begin() + index);
}

void ParticleSystem3D::removeAllAffector()
{
    //release all affectors
    for (auto it : _affectors) {
        it->release();
    }
    _affectors.clear();
}

Particle3DAffector* ParticleSystem3D::getAffector(int index)
{
    CCASSERT(index < (int)_affectors.size(), "wrong index");
    return _affectors[index];
}

void ParticleSystem3D::update(float delta)
{
    if (_state != State::RUNNING)
        return;
    
    Particle3D *particle = _particlePool.getFirst();
    while (particle)
    {
        if (_emitter)
        {
            _emitter->updateEmitter(particle, delta);
        }

        for (auto& it : _affectors) {
            it->updateAffector(particle, delta);
        }

        particle = _particlePool.getNext();
    }
}

void ParticleSystem3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t /*flags*/)
{
    if (getAliveParticleCount() && _render)
    {
        _render->render(renderer, transform, this);
    }
}

void ParticleSystem3D::setBlendFunc(const BlendFunc &blendFunc)
{
    _blend = blendFunc;
}

const BlendFunc &ParticleSystem3D::getBlendFunc() const
{
    return _blend;
}

void ParticleSystem3D::setParticleQuota( unsigned int quota )
{
    _particleQuota = quota;
}

unsigned int ParticleSystem3D::getParticleQuota() const
{
    return _particleQuota;
}

void ParticleSystem3D::setKeepLocal( bool keepLocal )
{
    _keepLocal = keepLocal;
}

void ParticleSystem3D::setEnabled( bool enabled )
{
    _isEnabled = enabled;
}

NS_CC_END
