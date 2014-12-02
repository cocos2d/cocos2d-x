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

#include "CCParticleSystem3D.h"
#include "CCParticle3DEmitter.h"
#include "CCParticle3DAffector.h"
#include "CCParticle3DRender.h"

NS_CC_BEGIN

ParticleSystem3D::ParticleSystem3D()
: _emitter(nullptr)
, _render(nullptr)
, _aliveParticlesCnt(0)
, _state(State::RUNNING)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
{
    
}
ParticleSystem3D::~ParticleSystem3D()
{
    stop();
    removeAllAffector();
    CC_SAFE_RELEASE(_emitter);
    CC_SAFE_RETAIN(_render);
}

void ParticleSystem3D::start()
{
    if (_state != State::RUNNING)
    {
		_particles.clear();
        
		if (_render)
			_render->notifyStart();
        
        scheduleUpdate();
        _state = State::RUNNING;
    }
}

void ParticleSystem3D::stop()
{
    if (_state != State::STOP)
    {
		if (_render)
			_render->notifyStop();
        
        unscheduleUpdate();
        _state = State::STOP;
    }
}

void ParticleSystem3D::pause()
{
    if (_state == State::RUNNING)
    {
        _state = State::PAUSE;
    }
}

void ParticleSystem3D::resume()
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
        CC_SAFE_RETAIN(_render);
    }
}

void ParticleSystem3D::addAddAffector(Particle3DAffector* affector)
{
    if (std::find(_affectors.begin(), _affectors.end(), affector) != _affectors.end()){
        affector->_particleSystem = this;
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
    CCASSERT(index < _affectors.size(), "wrong index");
    return _affectors[index];
}

void ParticleSystem3D::update(float delta)
{
    if (_state != State::RUNNING)
        return;
    
    if (_emitter)
    {
        for (auto& particle : _particles) {
            _emitter->updateEmitter(particle, delta);
        }
    }
    
    for (auto& it : _affectors) {
        it->updateAffector(delta);
    }
        
}

void ParticleSystem3D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (_state != State::STOP && _render)
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

NS_CC_END
