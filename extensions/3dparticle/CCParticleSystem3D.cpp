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

float Particle3D::DEFAULT_TTL = 10.0f;
float Particle3D::DEFAULT_MASS = 1.0f;

void Particle3D::setOwnDimensions( float newWidth, float newHeight, float newDepth )
{
    ownDimensions = true;
    if (newWidth)
        width = newWidth;
    if (newHeight)
        height = newHeight;
    if (newDepth)
        depth = newDepth;
    calculateBoundingSphereRadius();
    //parentEmitter->getParentTechnique()->_notifyParticleResized();
}

void Particle3D::calculateBoundingSphereRadius()
{
    //radius = 0.5 * Math::Sqrt(width*width + height*height + depth*depth);
    radius = 0.5f * std::max(depth, std::max(width, height)); // approximation
}

void Particle3D::initForEmission()
{
        eventFlags = 0;
        timeFraction = 0.0f;
        /*	Note, that this flag must only be set as soon as the particle is emitted. As soon as the particle has
            been moved once, the flag must be removed again.
        */
        addEventFlags(Particle3D::PEF_EMITTED);

        // Reset freeze flag
        freezed = false;
}

Particle3D::Particle3D(): 
    position(Vec3::ZERO),
    direction(Vec3::ZERO),
    timeToLive(DEFAULT_TTL),
    totalTimeToLive(DEFAULT_TTL),
    timeFraction(0.0f),
    mass(DEFAULT_MASS),
    eventFlags(0),
    freezed(false),
    originalPosition(Vec3::ZERO),
    latestPosition(Vec3::ZERO),
    originalDirection(Vec3::ZERO),
    originalDirectionLength(0.0f),
    originalScaledDirectionLength(0.0f),
    originalVelocity(0.0f),
    parentEmitter(nullptr),
    color(Vec4::ONE),
    originalColor(Vec4::ONE),
    zRotation(0.0f),
    zRotationSpeed(0.0f),
    rotationSpeed(0.0f),
    rotationAxis(Vec3::UNIT_Z),
    ownDimensions(false),
    width(1.0f),
    height(1.0f),
    depth(1.0f),
    radius(0.87f),
    textureAnimationTimeStep(0.1f),
    textureAnimationTimeStepCount(0.0f),
    textureCoordsCurrent(0),
    textureAnimationDirectionUp(true),
    alive(true)
{

}

//-----------------------------------------------------------------------

const float ParticleSystem3D::DEFAULT_WIDTH = 50;
const float ParticleSystem3D::DEFAULT_HEIGHT = 50;
const float ParticleSystem3D::DEFAULT_DEPTH = 50;

ParticleSystem3D::ParticleSystem3D()
: _emitter(nullptr)
, _render(nullptr)
, _prepared(false)
, _aliveParticlesCnt(0)
, _state(State::STOP)
, _particleSystemScaleVelocity(1.0f)
, _defaultWidth(DEFAULT_WIDTH)
, _defaultHeight(DEFAULT_HEIGHT)
, _defaultDepth(DEFAULT_DEPTH)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
{
    
}
ParticleSystem3D::~ParticleSystem3D()
{
    stopSystem();
    unPrepared();

    CC_SAFE_RELEASE(_emitter);
    CC_SAFE_RETAIN(_render);

    for (auto iter : _particles){
        CC_SAFE_DELETE(iter);
    }
    _particles.clear();
}

void ParticleSystem3D::startSystem()
{
    if (_state != State::RUNNING)
    {
        if (_emitter)
            _emitter->notifyStart();

        for (auto& it : _affectors) {
            it->notifyStart();
        }

        if (_render)
            _render->notifyStart();

        scheduleUpdate();
        _state = State::RUNNING;
        _timeElapsedSinceStart = 0.0f;
    }
}

void ParticleSystem3D::stopSystem()
{
    if (_state != State::STOP)
    {
        if (_emitter)
            _emitter->notifyStop();

        for (auto& it : _affectors) {
            it->notifyStop();
        }

        if (_render)
            _render->notifyStop();

        unscheduleUpdate();
        _state = State::STOP;
    }
}

void ParticleSystem3D::pauseSystem()
{
    if (_state == State::RUNNING)
    {
        if (_emitter)
            _emitter->notifyPause();

        for (auto& it : _affectors) {
            it->notifyPause();
        }
        _state = State::PAUSE;
    }
}

void ParticleSystem3D::resumeSystem()
{
    if (_state == State::PAUSE)
    {
        if (_emitter)
            _emitter->notifyResume();

        for (auto& it : _affectors) {
            it->notifyResume();
        }

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
        CC_SAFE_RETAIN(_render);
    }
}

void ParticleSystem3D::addAffector(Particle3DAffector* affector)
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
    _affectors.clear();
}

Particle3DAffector* ParticleSystem3D::getAffector(int index)
{
    CCASSERT((unsigned int)index < _affectors.size(), "wrong index");
    return _affectors[index];
}

void ParticleSystem3D::update(float delta)
{
    if (_state != State::RUNNING)
        return;

    prepared();
    emitParticles(delta);
    preUpdator(delta);
    updator(delta);
    postUpdator(delta);

    _timeElapsedSinceStart += delta;
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

const std::vector<Particle3D*>& ParticleSystem3D::getParticles()
{
    return _particles;
}

float ParticleSystem3D::getParticleSystemScaleVelocity() const
{
    return _particleSystemScaleVelocity;
}

void ParticleSystem3D::rotationOffset( Vec3& pos )
{
    Mat4 rotMat;
    Mat4::createRotation(_rotationOffset, &rotMat);
    pos = _rotationCentre + rotMat * (pos - _rotationCentre);
}

void ParticleSystem3D::prepared()
{
    if (!_prepared){
        if (_emitter && _emitter->isEnabled())
            _emitter->prepare();

        for (auto& it : _affectors) {
            if (it->isEnabled())
                it->prepare();
        }
        _prepared = true;
    }
}

void ParticleSystem3D::unPrepared()
{
    if (_emitter && _emitter->isEnabled())
        _emitter->unPrepare();

    for (auto& it : _affectors) {
        if (it->isEnabled())
            it->unPrepare();
    }
}

void ParticleSystem3D::preUpdator( float elapsedTime )
{
    if (_emitter && _emitter->isEnabled())
        _emitter->preUpdateEmitter(elapsedTime);

    for (auto& it : _affectors) {
        if (it->isEnabled())
            it->preUpdateAffector(elapsedTime);
    }
}

void ParticleSystem3D::updator( float elapsedTime )
{
    bool firstActiveParticle = true; // The first non-expired particle
    for (auto iter = _particles.begin(); iter != _particles.end();){
        Particle3D *particle = *iter;

        if (particle->alive){
            if (!isExpired(particle, elapsedTime)){
                particle->timeFraction = (particle->totalTimeToLive - particle->timeToLive) / particle->totalTimeToLive;

                if (_emitter && _emitter->isEnabled())
                    _emitter->updateEmitter(particle, elapsedTime);

                for (auto& it : _affectors) {
                    if (it->isEnabled()){
                        if (firstActiveParticle)
                            it->firstParticleUpdate(particle, elapsedTime);
                        it->updateAffector(particle, elapsedTime);
                    }
                }

                //need update render?

                //processMotion(Particle* particle, Real timeElapsed, bool firstParticle)

                // Update the position with the direction.
                particle->position += (particle->direction * _particleSystemScaleVelocity * elapsedTime);

                firstActiveParticle = false;
            }
            else{
                particle->alive = false;
            }

            if (particle->hasEventFlags(Particle3D::PEF_EXPIRED))
            {
                particle->setEventFlags(0);
                particle->addEventFlags(Particle3D::PEF_EXPIRED);
            }
            else
            {
                particle->setEventFlags(0);
            }

            particle->timeToLive -= elapsedTime;

            ++iter;
        }
        else{
            CC_SAFE_DELETE(particle);
            iter = _particles.erase(iter);
        }
    }
}

void ParticleSystem3D::postUpdator( float elapsedTime )
{
    if (_emitter && _emitter->isEnabled())
        _emitter->postUpdateEmitter(elapsedTime);

    for (auto& it : _affectors) {
        if (it->isEnabled())
            it->postUpdateAffector(elapsedTime);
    }
}

void ParticleSystem3D::emitParticles( float elapsedTime )
{
    if (!_emitter || !_emitter->isEnabled()) return;

    unsigned short requested = _emitter->calculateRequestedParticles(elapsedTime);
    float timePoint = 0.0f;
    float timeInc = elapsedTime / requested;

    for (unsigned short i = 0; i < requested; ++i)
    {
        Particle3D *particle = new Particle3D;
        _particles.push_back(particle);
        particle->initForEmission();
        _emitter->initParticleForEmission(particle);

        particle->direction = (/*getDerivedOrientation() * */particle->direction);
        particle->originalDirection = (/*getDerivedOrientation() * */particle->originalDirection);

        for (auto& it : _affectors) {
            if (it->isEnabled())
                it->initParticleForEmission(particle);
        }

        particle->position += (particle->direction * _particleSystemScaleVelocity * timePoint);
        // Increment time fragment
        timePoint += timeInc;
    }
}

const float ParticleSystem3D::getDefaultWidth( void ) const
{
    return _defaultWidth;
}

void ParticleSystem3D::setDefaultWidth( const float width )
{
    _defaultWidth = width;
}

const float ParticleSystem3D::getDefaultHeight( void ) const
{
    return _defaultHeight;
}

void ParticleSystem3D::setDefaultHeight( const float height )
{
    _defaultHeight = height;
}

const float ParticleSystem3D::getDefaultDepth( void ) const
{
    return _defaultDepth;
}

void ParticleSystem3D::setDefaultDepth( const float depth )
{
    _defaultDepth = depth;
}

bool ParticleSystem3D::isExpired( Particle3D* particle, float timeElapsed )
{
    bool expired = particle->timeToLive < timeElapsed;
    if (expired)
    {
        // Set the flag to indicate that the particle has been expired
        particle->addEventFlags(Particle3D::PEF_EXPIRED);
    }

    return expired;
}

NS_CC_END
