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

#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "extensions/Particle3D/CCParticle3DRender.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DScriptCompiler.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DMaterialManager.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DTranslateManager.h"
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
    textureAnimationDirectionUp(true),
    depthInView(0.0f),
    zRotation(0.0f),
    widthInWorld(width),
    heightInWorld(height),
    depthInWorld(depth)
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

    //release all emitters
    for (auto it : _emitters) {
        it->release();
    }
    _emitters.clear();
}

PUParticleSystem3D* PUParticleSystem3D::create()
{
    auto pups = new (std::nothrow) PUParticleSystem3D();
    pups->autorelease();
    return pups;
}

PUParticleSystem3D* PUParticleSystem3D::create( const std::string &filePath, const std::string &materialPath )
{
    std::string matfullPath = FileUtils::getInstance()->fullPathForFilename(materialPath);
    convertToUnixStylePath(matfullPath);
    PUParticle3DMaterialCache::Instance()->loadMaterials(matfullPath);
    PUParticleSystem3D* ps = PUParticleSystem3D::create();
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    convertToUnixStylePath(fullPath);
    if (!ps->initSystem(fullPath)){
        CC_SAFE_DELETE(ps);
    }
    return ps;
}

PUParticleSystem3D* PUParticleSystem3D::create( const std::string &filePath )
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    convertToUnixStylePath(fullPath);
    std::string::size_type pos = fullPath.find_last_of("/");
    std::string materialFolder = "materials";
    if (pos != std::string::npos){
        std::string temp = fullPath.substr(0, pos);
        pos = temp.find_last_of("/");
        if (pos != std::string::npos){
            materialFolder = temp.substr(0, pos + 1) + materialFolder;
        }
    }
    static std::vector<std::string> loadedFolder;
    if (std::find(loadedFolder.begin(), loadedFolder.end(), materialFolder) == loadedFolder.end())
    {
        PUParticle3DMaterialCache::Instance()->loadMaterialsFromSearchPaths(materialFolder);
        loadedFolder.push_back(materialFolder);
    }
    
    PUParticleSystem3D* ps = PUParticleSystem3D::create();
    if (!ps->initSystem(fullPath)){
        CC_SAFE_DELETE(ps);
    }
    return ps;
}

void PUParticleSystem3D::startParticleSystem()
{
    stopParticleSystem();
    if (!_emitters.empty()){
        if (_state != State::RUNNING)
        {
            //if (_emitter)
            //{
            //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            //    emitter->notifyStart();
            //}

            for (auto& it : _emitters) {
                auto emitter = static_cast<PUParticle3DEmitter*>(it);
                emitter->notifyStart();
            }

            for (auto& it : _affectors) {
                auto affector = static_cast<PUParticle3DAffector*>(it);
                affector->notifyStart();
            }

            if (_render)
                _render->notifyStart();

            scheduleUpdate();
            _state = State::RUNNING;
            _timeElapsedSinceStart = 0.0f;
        }
    }
    _state = State::RUNNING;

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->startParticleSystem();
    }
}

void PUParticleSystem3D::stopParticleSystem()
{
    if (!_emitters.empty()){
        if (_state != State::STOP)
        {
            //if (_emitter)
            //{
            //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
            //    emitter->notifyStop();
            //}

            for (auto& it : _emitters) {
                auto emitter = static_cast<PUParticle3DEmitter*>(it);
                emitter->notifyStop();
            }

            for (auto& it : _affectors) {
                auto affector = static_cast<PUParticle3DAffector*>(it);
                affector->notifyStop();
            }

//            if (_render)
//                _render->notifyStop();
//
//            unscheduleUpdate();
//            _particlePool.lockAllParticles();
            _state = State::STOP;
        }
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->stopParticleSystem();
    }
}

void PUParticleSystem3D::pauseParticleSystem()
{
    if (_state == State::RUNNING)
    {
        //if (_emitter)
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->notifyPause();
        //}

        for (auto& it : _emitters) {
            auto emitter = static_cast<PUParticle3DEmitter*>(it);
            emitter->notifyPause();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyPause();
        }

        _state = State::PAUSE;
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->pauseParticleSystem();
    }
}

void PUParticleSystem3D::resumeParticleSystem()
{
    if (_state == State::PAUSE)
    {
        //if (_emitter)
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->notifyResume();
        //}

        for (auto& it : _emitters) {
            auto emitter = static_cast<PUParticle3DEmitter*>(it);
            emitter->notifyResume();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyResume();
        }

        _state = State::RUNNING;
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->resumeParticleSystem();
    }
}

int PUParticleSystem3D::getAliveParticleCount() const
{
    return (int)_particlePool.getActiveParticleList().size();
}

void PUParticleSystem3D::update(float delta)
{
    if (_state != State::RUNNING)
    {
        if (_state == State::PAUSE)
            return;
        else if (_state == State::STOP && getAliveParticleCount() == 0)
        {
            //
            if (_render)
                _render->notifyStop();
            
            unscheduleUpdate();
            return;
        }
    }
    
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
        //if (_emitter && _emitter->isEnabled())
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->prepare();
        //}

        for (auto it : _emitters) {
            if (it->isEnabled())
                (static_cast<PUParticle3DEmitter*>(it))->prepare();
        }

        for (auto it : _affectors) {
            if (it->isEnabled())
                (static_cast<PUParticle3DAffector*>(it))->prepare();
        }
        
        for (unsigned short i = 0; i < _particleQuota; ++i){
            _particlePool.addParticle(new (std::nothrow) PUParticle3D());
        }
        _prepared = true;
    }
}

void PUParticleSystem3D::unPrepared()
{
    //if (_emitter && _emitter->isEnabled())
    //{
    //     auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
    //    emitter->unPrepare();
    //}

    for (auto it : _emitters) {
        if (it->isEnabled())
            (static_cast<PUParticle3DEmitter*>(it))->unPrepare();
    }

    for (auto it : _affectors) {
        if (it->isEnabled())
            (static_cast<PUParticle3DAffector*>(it))->unPrepare();
    }

    _particlePool.removeAllParticles(true);
}

void PUParticleSystem3D::preUpdator( float elapsedTime )
{
    //if (_emitter && _emitter->isEnabled())
    //{
    //     auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
    //    emitter->preUpdateEmitter(elapsedTime);
    //}
    bool hasNoEmitted = true;
    for (auto it : _emitters) {
        if (!it->isEmitterDone()){
            (static_cast<PUParticle3DEmitter*>(it))->preUpdateEmitter(elapsedTime);
            hasNoEmitted = false;
        }
    }

    if (hasNoEmitted){
        if (_particlePool.getActiveParticleList().empty())
            stopParticleSystem();
    }

    for (auto it : _affectors) {
        if (it->isEnabled()){
            (static_cast<PUParticle3DAffector*>(it))->preUpdateAffector(elapsedTime);
        }
    }
}

void PUParticleSystem3D::updator( float elapsedTime )
{
    bool firstActiveParticle = true; // The first non-expired particle
    PUParticle3D *particle = static_cast<PUParticle3D *>(_particlePool.getFirst());
    Mat4 ltow = getNodeToWorldTransform();
    Vec3 scl;
    Quaternion rot;
    ltow.decompose(&scl, &rot, nullptr);
    while (particle){

        if (!isExpired(particle, elapsedTime)){
            particle->timeFraction = (particle->totalTimeToLive - particle->timeToLive) / particle->totalTimeToLive;

            //if (_emitter && _emitter->isEnabled())
            //    _emitter->updateEmitter(particle, elapsedTime);

            for (auto it : _emitters) {
                if (it->isEnabled()){
                    (static_cast<PUParticle3DEmitter*>(it))->updateEmitter(particle, elapsedTime);
                }
            }

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
            particle->orientationInWorld = particle->orientation;
            particle->widthInWorld = particle->width;
            particle->heightInWorld = particle->height;
            particle->depthInWorld = particle->depth;

            bool keepLocal = _keepLocal;
            PUParticleSystem3D *parent = dynamic_cast<PUParticleSystem3D *>(getParent());
            if (parent) keepLocal = keepLocal || parent->isKeepLocal();

            if (keepLocal){
                ltow.transformPoint(particle->positionInWorld, &particle->positionInWorld);
                Vec3 ori;
                ltow.transformVector(Vec3(particle->orientation.x, particle->orientation.y, particle->orientation.z), &ori);
                particle->orientationInWorld.x = ori.x; particle->orientationInWorld.y = ori.y; particle->orientationInWorld.z = ori.z;
                particle->widthInWorld = scl.x * particle->width;
                particle->heightInWorld = scl.y * particle->height;
                particle->depthInWorld = scl.z * particle->depth;
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
    //if (_emitter && _emitter->isEnabled())
    //{
    //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
    //    emitter->postUpdateEmitter(elapsedTime);
    //}

    for (auto it : _emitters) {
        if (it->isEnabled()){
            (static_cast<PUParticle3DEmitter*>(it))->postUpdateEmitter(elapsedTime);
        }
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
    Vec3 scale = getDerivedScale();
    Mat4 rotMat;
    Mat4::createRotation(getDerivedOrientation(), &rotMat);
    for (auto iter : _emitters){
        //if (!_emitter) return;
        //auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        auto emitter = iter;
        emitter->notifyRescaled(scale);
        unsigned short requested = emitter->calculateRequestedParticles(elapsedTime);
        float timePoint = 0.0f;
        float timeInc = elapsedTime / requested;
        for (unsigned short i = 0; i < requested; ++i)
        {
            PUParticle3D *particle = static_cast<PUParticle3D *>(_particlePool.createParticle());
            if (particle){
                particle->initForEmission();
                emitter->initParticleForEmission(particle);

                particle->direction = (rotMat * Vec3(particle->direction.x * scale.x, particle->direction.y * scale.y, particle->direction.z * scale.z));
                particle->originalDirection = (rotMat * Vec3(particle->originalDirection.x * scale.x, particle->originalDirection.y * scale.y, particle->originalDirection.z * scale.z));

                for (auto& it : _affectors) {
                    if (it->isEnabled())
                    {
                        (static_cast<PUParticle3DAffector*>(it))->notifyRescaled(scale);
                        (static_cast<PUParticle3DAffector*>(it))->initParticleForEmission(particle);
                    }
                }

                particle->position += (particle->direction * _particleSystemScaleVelocity * timePoint);
                // Increment time fragment
                timePoint += timeInc;
            }
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

cocos2d::Vec3 PUParticleSystem3D::getDerivedPosition()
{
    PUParticleSystem3D *parent = dynamic_cast<PUParticleSystem3D *>(getParent());
    if (parent && parent->isKeepLocal()) return Vec3::ZERO; 
    if (_keepLocal) return Vec3::ZERO;

    Mat4 mat = getNodeToWorldTransform();
    return Vec3(mat.m[12], mat.m[13], mat.m[14]);
}

cocos2d::Quaternion PUParticleSystem3D::getDerivedOrientation()
{
    PUParticleSystem3D *parent = dynamic_cast<PUParticleSystem3D *>(getParent());
    if (parent && parent->isKeepLocal()) return Quaternion(); 
    if (_keepLocal) return Quaternion();
    Quaternion q;
    Mat4 mat = getNodeToWorldTransform();
    mat.decompose(nullptr, &q, nullptr);
    return q;
}

cocos2d::Vec3 PUParticleSystem3D::getDerivedScale()
{
    PUParticleSystem3D *parent = dynamic_cast<PUParticleSystem3D *>(getParent());
    if (parent && parent->isKeepLocal()) return Vec3::ONE; 
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

bool PUParticleSystem3D::initSystem( const std::string &filePath )
{
    bool isFirstCompile = true;
    auto list = PUScriptCompiler::Instance()->compile(filePath, isFirstCompile);
    if (list == nullptr || list->empty()) return false;
    PUParticle3DTranslateManager::Instance()->translateParticleSystem(this, list);
    //std::string  data = FileUtils::getInstance()->getStringFromFile(filePath);
    return true;
}

void PUParticleSystem3D::addEmitter( PUParticle3DEmitter* emitter )
{
    if (emitter && std::find(_emitters.begin(), _emitters.end(), emitter) == _emitters.end()){
        emitter->_particleSystem = this;
        emitter->retain();
        _emitters.push_back(emitter);
    }
}

void PUParticleSystem3D::convertToUnixStylePath( std::string &path )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    for (auto &iter : path){
        if (iter == '\\') iter = '/';
    }
#endif
}

NS_CC_END
