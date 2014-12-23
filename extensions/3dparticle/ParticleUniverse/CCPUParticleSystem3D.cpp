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

#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "3dparticle/CCParticle3DRender.h"
#include "3dparticle/ParticleUniverse/CCPUParticle3DScriptCompiler.h"
#include "3dparticle/ParticleUniverse/CCPUParticle3DMaterialManager.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

float PUParticle3D::DEFAULT_TTL = 10.0f;
float PUParticle3D::DEFAULT_MASS = 1.0f;

float PUParticle3D::calculateVelocity() const
{
    if (originalScaledDirectionLength != 0)
    {
        return originalVelocity * (direction.length() / originalScaledDirectionLength);
    }
    else
    {
        // Assume originalScaledDirectionLength to be 1.0 (unit vector)
        return originalVelocity * direction.length();
    }
}

void PUParticle3D::setOwnDimensions( float newWidth, float newHeight, float newDepth )
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

void PUParticle3D::calculateBoundingSphereRadius()
{
    //radius = 0.5 * Math::Sqrt(width*width + height*height + depth*depth);
    radius = 0.5f * std::max(depth, std::max(width, height)); // approximation
}

void PUParticle3D::initForEmission()
{
    eventFlags = 0;
    timeFraction = 0.0f;
    /*	Note, that this flag must only be set as soon as the particle is emitted. As soon as the particle has
        been moved once, the flag must be removed again.
    */
    addEventFlags(PUParticle3D::PEF_EMITTED);

    // Reset freeze flag
    freezed = false;
}

PUParticle3D::PUParticle3D():
    //position(Vec3::ZERO),
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
    //color(Vec4::ONE),
    originalColor(Vec4::ONE),
    //zRotation(0.0f),
    zRotationSpeed(0.0f),
    rotationSpeed(0.0f),
    rotationAxis(Vec3::UNIT_Z),
    ownDimensions(false),
    radius(0.87f),
    textureAnimationTimeStep(0.1f),
    textureAnimationTimeStepCount(0.0f),
    textureCoordsCurrent(0),
    textureAnimationDirectionUp(true)
{
}
//-----------------------------------------------------------------------

const float PUParticleSystem3D::DEFAULT_WIDTH = 50;
const float PUParticleSystem3D::DEFAULT_HEIGHT = 50;
const float PUParticleSystem3D::DEFAULT_DEPTH = 50;
const unsigned short PUParticleSystem3D::DEFAULT_PARTICLE_QUOTA = 500;
const float PUParticleSystem3D::DEFAULT_MAX_VELOCITY = 9999.0f;


PUParticleSystem3D::PUParticleSystem3D()
: _prepared(false)
, _particleSystemScaleVelocity(1.0f)
, _defaultWidth(DEFAULT_WIDTH)
, _defaultHeight(DEFAULT_HEIGHT)
, _defaultDepth(DEFAULT_DEPTH)
, _maxVelocity(DEFAULT_MAX_VELOCITY)
, _maxVelocitySet(false)
{
    _particleQuota = DEFAULT_PARTICLE_QUOTA;
}
PUParticleSystem3D::~PUParticleSystem3D()
{
    unPrepared();
}

void PUParticleSystem3D::startParticle()
{
    if (_state != State::RUNNING)
    {
        if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            emitter->notifyStart();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyStart();
        }

        if (_render)
            _render->notifyStart();

        for (auto iter : _children)
        {
            PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
            if (system)
                system->startParticle();
        }

        scheduleUpdate();
        _state = State::RUNNING;
        _timeElapsedSinceStart = 0.0f;
    }
}

void PUParticleSystem3D::stopParticle()
{
    if (_state != State::STOP)
    {
        if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            emitter->notifyStop();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyStop();
        }

        if (_render)
            _render->notifyStop();

        for (auto iter : _children)
        {
            PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
            if (system)
                system->stopParticle();
        }

        unscheduleUpdate();
        _particlePool.lockAllParticles();
        _state = State::STOP;
    }
}

void PUParticleSystem3D::pauseParticle()
{
    if (_state == State::RUNNING)
    {
        if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            emitter->notifyPause();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyPause();
        }

        for (auto iter : _children)
        {
            PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
            if (system)
                system->pauseParticle();
        }

        _state = State::PAUSE;
    }
}

void PUParticleSystem3D::resumeParticle()
{
    if (_state == State::PAUSE)
    {
        if (_emitter)
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            emitter->notifyResume();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyResume();
        }

        for (auto iter : _children)
        {
            PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
            if (system)
                system->resumeParticle();
        }

        _state = State::RUNNING;
    }
}

void PUParticleSystem3D::update(float delta)
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

float PUParticleSystem3D::getParticleSystemScaleVelocity() const
{
    return _particleSystemScaleVelocity;
}

void PUParticleSystem3D::rotationOffset( Vec3& pos )
{
    Mat4 rotMat;
    Mat4::createRotation(_rotationOffset, &rotMat);
    pos = _rotationCentre + rotMat * (pos - _rotationCentre);
}

void PUParticleSystem3D::prepared()
{
    if (!_prepared){
        if (_emitter && _emitter->isEnabled())
        {
            auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            emitter->prepare();
        }

        for (auto it : _affectors) {
            if (it->isEnabled())
                (static_cast<PUParticle3DAffector*>(it))->prepare();
        }
        
        for (unsigned short i = 0; i < _particleQuota; ++i){
            _particlePool.addParticle(new PUParticle3D());
        }
        _prepared = true;
    }
}

void PUParticleSystem3D::unPrepared()
{
    if (_emitter && _emitter->isEnabled())
    {
         auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        emitter->unPrepare();
    }

    for (auto it : _affectors) {
        if (it->isEnabled())
            (static_cast<PUParticle3DAffector*>(it))->unPrepare();
    }

    _particlePool.removeAllParticles(true);
    PUParticle3DMaterialManager::Instance()->clearAllMaterials();
}

void PUParticleSystem3D::preUpdator( float elapsedTime )
{
    if (_emitter && _emitter->isEnabled())
    {
         auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
         emitter->notifyRescaled(getDerivedScale());
        emitter->preUpdateEmitter(elapsedTime);
    }

    for (auto it : _affectors) {
        if (it->isEnabled()){
            (static_cast<PUParticle3DAffector*>(it))->notifyRescaled(getDerivedScale());
            (static_cast<PUParticle3DAffector*>(it))->preUpdateAffector(elapsedTime);
        }
    }
}

void PUParticleSystem3D::updator( float elapsedTime )
{
    bool firstActiveParticle = true; // The first non-expired particle
    PUParticle3D *particle = static_cast<PUParticle3D *>(_particlePool.getFirst());

    while (particle){

        if (!isExpired(particle, elapsedTime)){
            particle->timeFraction = (particle->totalTimeToLive - particle->timeToLive) / particle->totalTimeToLive;

            if (_emitter && _emitter->isEnabled())
                _emitter->updateEmitter(particle, elapsedTime);

            for (auto& it : _affectors) {
                if (it->isEnabled()){
                    if (firstActiveParticle)
                            (static_cast<PUParticle3DAffector*>(it))->firstParticleUpdate(particle, elapsedTime);
                        (static_cast<PUParticle3DAffector*>(it))->updatePUAffector(particle, elapsedTime);
                }
            }

            // Keep latest position
            particle->latestPosition = particle->position;

            if (_maxVelocitySet && particle->calculateVelocity() > _maxVelocity)
            {
                particle->direction *= (_maxVelocity / particle->direction.length());
            }

            // Update the position with the direction.
            particle->position += (particle->direction * _particleSystemScaleVelocity * elapsedTime);
            particle->positionInWorld = particle->position;

            if (_keepLocal){
                getNodeToWorldTransform().transformPoint(particle->positionInWorld, &particle->positionInWorld);
            }
            firstActiveParticle = false;
        }
        else{
            _particlePool.lockLatestParticle();
        }

        if (particle->hasEventFlags(PUParticle3D::PEF_EXPIRED))
        {
            particle->setEventFlags(0);
            particle->addEventFlags(PUParticle3D::PEF_EXPIRED);
        }
        else
        {
            particle->setEventFlags(0);
        }

        particle->timeToLive -= elapsedTime;

        particle = static_cast<PUParticle3D *>(_particlePool.getNext());
    }
}

void PUParticleSystem3D::postUpdator( float elapsedTime )
{
    if (_emitter && _emitter->isEnabled())
    {
        auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        emitter->postUpdateEmitter(elapsedTime);
    }

    for (auto it : _affectors) {
        if (it->isEnabled())
        {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->postUpdateAffector(elapsedTime);
        }
    }
}

void PUParticleSystem3D::emitParticles( float elapsedTime )
{
    if (!_emitter) return;

    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);

    unsigned short requested = emitter->calculateRequestedParticles(elapsedTime);
    float timePoint = 0.0f;
    float timeInc = elapsedTime / requested;

    for (unsigned short i = 0; i < requested; ++i)
    {
        PUParticle3D *particle = static_cast<PUParticle3D *>(_particlePool.createParticle());
        if (particle){
            particle->initForEmission();
            emitter->initParticleForEmission(particle);

            particle->direction = (/*getDerivedOrientation() * */particle->direction);
            particle->originalDirection = (/*getDerivedOrientation() * */particle->originalDirection);

            for (auto& it : _affectors) {
                if (it->isEnabled())
                {
                    (static_cast<PUParticle3DAffector*>(it))->initParticleForEmission(particle);
                }
            }

            particle->position += (particle->direction * _particleSystemScaleVelocity * timePoint);
            // Increment time fragment
            timePoint += timeInc;
        }
    }
}

const float PUParticleSystem3D::getDefaultWidth( void ) const
{
    return _defaultWidth;
}

void PUParticleSystem3D::setDefaultWidth( const float width )
{
    _defaultWidth = width;
}

const float PUParticleSystem3D::getDefaultHeight( void ) const
{
    return _defaultHeight;
}

void PUParticleSystem3D::setDefaultHeight( const float height )
{
    _defaultHeight = height;
}

const float PUParticleSystem3D::getDefaultDepth( void ) const
{
    return _defaultDepth;
}

void PUParticleSystem3D::setDefaultDepth( const float depth )
{
    _defaultDepth = depth;
}

bool PUParticleSystem3D::isExpired( PUParticle3D* particle, float timeElapsed )
{
    bool expired = particle->timeToLive < timeElapsed;
    if (expired)
    {
        // Set the flag to indicate that the particle has been expired
        particle->addEventFlags(PUParticle3D::PEF_EXPIRED);
    }

    return expired;
}

PUParticleSystem3D* PUParticleSystem3D::create()
{
    auto pups = new PUParticleSystem3D();
    pups->autorelease();
    return pups;
}

PUParticleSystem3D* PUParticleSystem3D::create( const std::string &filePath, const std::string &materialPath )
{
    PUParticleSystem3D* ps = PUParticleSystem3D::create();
    if (!ps->initSystem(filePath, materialPath)){
        CC_SAFE_DELETE(ps);
    }
    return ps;
}

cocos2d::Vec3 PUParticleSystem3D::getDerivedPosition()
{
    if (_keepLocal) return Vec3::ZERO;

    Mat4 mat = getNodeToWorldTransform();
    return Vec3(mat.m[12], mat.m[13], mat.m[14]);
}

cocos2d::Quaternion PUParticleSystem3D::getDerivedOrientation()
{
    if (_keepLocal) return Quaternion();
    Quaternion q;
    Mat4 mat = getNodeToWorldTransform();
    mat.decompose(nullptr, &q, nullptr);
    return q;
}

cocos2d::Vec3 PUParticleSystem3D::getDerivedScale()
{
    if (_keepLocal) return Vec3::ONE;
    Vec3 s;
    Mat4 mat = getNodeToWorldTransform();
    mat.decompose(&s, nullptr, nullptr);
    return s;
}

float PUParticleSystem3D::getMaxVelocity() const
{
    return _maxVelocity;
}

void PUParticleSystem3D::setMaxVelocity( float maxVelocity )
{
    _maxVelocity = maxVelocity;
    _maxVelocitySet = true;
}

bool PUParticleSystem3D::initSystem( const std::string &filePath, const std::string &materialPath )
{
    std::string data = FileUtils::getInstance()->getStringFromFile(materialPath);
    PUScriptCompiler sc;
    sc.compile(data, materialPath);

    sc.setParticleSystem3D(this);
    data = FileUtils::getInstance()->getStringFromFile(filePath);
    if (!sc.compile(data, filePath)) return false;
    return true;
}
NS_CC_END
