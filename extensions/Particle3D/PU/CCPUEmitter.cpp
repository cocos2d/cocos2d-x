/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUUtil.h"

NS_CC_BEGIN

// Constants
const bool PUEmitter::DEFAULT_ENABLED = true;
const Vec3 PUEmitter::DEFAULT_POSITION(0, 0, 0);
const bool PUEmitter::DEFAULT_KEEP_LOCAL = false;
const Vec3 PUEmitter::DEFAULT_DIRECTION(0, 1, 0);
const Quaternion PUEmitter::DEFAULT_ORIENTATION(1, 0, 0, 0);
const Quaternion PUEmitter::DEFAULT_ORIENTATION_RANGE_START(1, 0, 0, 0);
const Quaternion PUEmitter::DEFAULT_ORIENTATION_RANGE_END(1, 0, 0, 0);
//const Particle::ParticleType PUEmitter::DEFAULT_EMITS = VisualParticle::PT_VISUAL;
const unsigned short PUEmitter::DEFAULT_START_TEXTURE_COORDS = 0;
const unsigned short PUEmitter::DEFAULT_END_TEXTURE_COORDS = 0;
const unsigned short PUEmitter::DEFAULT_TEXTURE_COORDS = 0;
const Vec4 PUEmitter::DEFAULT_START_COLOUR_RANGE(0, 0, 0, 1);
const Vec4 PUEmitter::DEFAULT_END_COLOUR_RANGE(1, 1, 1, 1);
const Vec4 PUEmitter::DEFAULT_COLOUR(1, 1, 1, 1);
const bool PUEmitter::DEFAULT_AUTO_DIRECTION = false;
const bool PUEmitter::DEFAULT_FORCE_EMISSION = false;
const float PUEmitter::DEFAULT_EMISSION_RATE = 10.0f;
const float PUEmitter::DEFAULT_TIME_TO_LIVE = 3.0f;
const float PUEmitter::DEFAULT_MASS = 1.0f;
const float PUEmitter::DEFAULT_VELOCITY = 100.0f;
const float PUEmitter::DEFAULT_DURATION = 0.0f;
const float PUEmitter::DEFAULT_REPEAT_DELAY = 0.0f;
const float PUEmitter::DEFAULT_ANGLE = 20.0f;
const float PUEmitter::DEFAULT_DIMENSIONS = 0.0f;
const float PUEmitter::DEFAULT_WIDTH = 0.0f;
const float PUEmitter::DEFAULT_HEIGHT = 0.0f;
const float PUEmitter::DEFAULT_DEPTH = 0.0f;

PUEmitter::PUEmitter()
: //mEmitsType(DEFAULT_EMITS),
//mEmitsName(StringUtil::BLANK),
_emitterScale(Vec3::ONE),
_particleDirection(DEFAULT_DIRECTION),
_originalParticleDirection(DEFAULT_DIRECTION),
//mParticleOrientation(Quaternion::IDENTITY),
//mParticleOrientationRangeStart(Quaternion::IDENTITY),
//mParticleOrientationRangeEnd(Quaternion::IDENTITY),
_particleOrientationRangeSet(false),
_dynParticleAllDimensionsSet(false),
_dynParticleWidthSet(false),
_dynParticleHeightSet(false),
_dynParticleDepthSet(false),
_remainder(0),
_durationRemain(0),
_dynDurationSet(false),
_repeatDelayRemain(0),
_dynRepeatDelaySet(false),
_autoDirection(DEFAULT_AUTO_DIRECTION),
_forceEmission(DEFAULT_FORCE_EMISSION),
_originalForceEmission(false),
_forceEmissionExecuted(false),
_originalForceEmissionExecuted(false),
//mName(StringUtil::BLANK),
_particleColor(DEFAULT_COLOUR),
_particleColorRangeStart(DEFAULT_START_COLOUR_RANGE),
_particleColorRangeEnd(DEFAULT_END_COLOUR_RANGE),
_particleColorRangeSet(false),
_keepLocal(false),
_particleTextureCoords(DEFAULT_TEXTURE_COORDS),
_particleTextureCoordsRangeStart(DEFAULT_START_TEXTURE_COORDS),
_particleTextureCoordsRangeEnd(DEFAULT_END_TEXTURE_COORDS),
_particleTextureCoordsRangeSet(false),
_originEnabled(true),
_originEnabledSet(false),
_emitsType(PUParticle3D::PT_VISUAL),
_emitsEntity(nullptr),
_isMarkedForEmission(false)
{
    //particleType = PT_EMITTER;
    //mAliasType = AT_EMITTER;
    _dynEmissionRate = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynEmissionRate))->setValue(DEFAULT_EMISSION_RATE);
    _dynTotalTimeToLive = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynTotalTimeToLive))->setValue(DEFAULT_TIME_TO_LIVE);
    _dynParticleMass = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynParticleMass))->setValue(DEFAULT_MASS);
    _dynVelocity = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynVelocity))->setValue(DEFAULT_VELOCITY);
    _dynDuration = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynDuration))->setValue(DEFAULT_DURATION);
    _dynRepeatDelay = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynRepeatDelay))->setValue(DEFAULT_REPEAT_DELAY);
    _dynAngle = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynAngle))->setValue(DEFAULT_ANGLE);

    // Set the dimensions attributes to 0; the default is to use the default dimensions of the ParticleTechnique
    _dynParticleAllDimensions = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynParticleAllDimensions))->setValue(DEFAULT_DIMENSIONS);
    _dynParticleWidth = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynParticleWidth))->setValue(DEFAULT_WIDTH);
    _dynParticleHeight = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynParticleHeight))->setValue(DEFAULT_HEIGHT);
    _dynParticleDepth = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynParticleDepth))->setValue(DEFAULT_DEPTH);
}

PUEmitter::~PUEmitter()
{
    _particleSystem = nullptr;

    if (_dynEmissionRate)
        delete _dynEmissionRate;

    if (_dynTotalTimeToLive)
        delete _dynTotalTimeToLive;

    if (_dynParticleMass)
        delete _dynParticleMass;

    if (_dynVelocity)
        delete _dynVelocity;

    if (_dynDuration)
        delete _dynDuration;

    if (_dynRepeatDelay)
        delete _dynRepeatDelay;

    if (_dynParticleAllDimensions)
        delete _dynParticleAllDimensions;

    if (_dynParticleWidth)
        delete _dynParticleWidth;

    if (_dynParticleHeight)
        delete _dynParticleHeight;

    if (_dynParticleDepth)
        delete _dynParticleDepth;

    //if (mEmissionRateCameraDependency)
    //	mCameraDependencyFactory.destroy(mEmissionRateCameraDependency);

    if (_dynAngle)
        delete _dynAngle;
}

void PUEmitter::updateEmitter(Particle3D* /*particle*/, float /*deltaTime*/)
{
    
}

void PUEmitter::emit(int /*count*/)
{
    
}

void PUEmitter::initParticlePosition( PUParticle3D* particle )
{
    particle->position = getDerivedPosition();
    particle->originalPosition = particle->position;
    particle->latestPosition = particle->position;
}

const Vec3& PUEmitter::getDerivedPosition()
{
    if (_isMarkedForEmission){
        _derivedPosition = _position;
    }else {
        PUParticleSystem3D *ps = static_cast<PUParticleSystem3D *>(_particleSystem);
        Mat4 rotMat;
        Mat4::createRotation(ps->getDerivedOrientation(), &rotMat);
        _derivedPosition = ps->getDerivedPosition() + rotMat * Vec3(_position.x * _emitterScale.x, _position.y * _emitterScale.y, _position.z * _emitterScale.z);
        //_particleSystem->getNodeToWorldTransform().transformPoint(_position, &_derivedPosition);
    }
    return _derivedPosition;
}

void PUEmitter::initParticleOrientation( PUParticle3D* particle )
{
    if (_particleOrientationRangeSet)
    {
        // Generate random orientation 'between' start en end.
        Quaternion::lerp(_particleOrientationRangeStart, _particleOrientationRangeEnd, CCRANDOM_0_1(), &particle->orientation);
    }
    else
    {
        particle->orientation = _particleOrientation;
    }

    // Set original orientation
    particle->originalOrientation = particle->orientation;
}

void PUEmitter::initParticleDirection( PUParticle3D* particle )
{
    // Use the default way of initialising the particle direction
    float angle = 0.0f;
    generateAngle(angle);
    if (angle != 0.0f)
    {
        particle->direction = PUUtil::randomDeviant(_particleDirection, angle, _upVector);
    }
    else
    {
        particle->direction = _particleDirection;
    }
    particle->originalDirection = particle->direction;
    particle->originalDirectionLength = particle->direction.length();
}

void PUEmitter::generateAngle( float &angle )
{
    float a = CC_DEGREES_TO_RADIANS(_dynamicAttributeHelper.calculate(_dynAngle, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart()));
    angle = a;
    if (_dynAngle->getType() == PUDynamicAttribute::DAT_FIXED)
    {
        // Make an exception here and don't use the fixed angle.
        angle = CCRANDOM_0_1() * angle;
    }
}

unsigned short PUEmitter::calculateRequestedParticles( float timeElapsed )
{
    unsigned short requestedParticles = 0;

    //FIXME
    if (_isEnabled)
    {
        if (_dynEmissionRate)
        {
            float rate = _dynEmissionRate->getValue((static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
            //if (_emissionRateCameraDependency)
            //{
            //	// Affect the emission rate based on the camera distance
            //	mEmissionRateCameraDependency->affect(rate, mParentTechnique->getCameraSquareDistance());
            //}
            if (_forceEmission)
            {
                if (_forceEmissionExecuted)
                {
                    // It is a single-shot system, so there is nothing left anymore.
                    requestedParticles = 0;
                }
                else
                {
                    // Ignore the time. Just emit everything at once (if you absolutely need it).
                    // The emitter cannot be disabled yet, because it needs to emit its particles first.
                    requestedParticles = (unsigned short)rate;
                    _forceEmissionExecuted = true;
                }
            }
            else
            {
                // Particle emission is time driven
                _remainder += rate * timeElapsed;
                requestedParticles = (unsigned short)_remainder;
            }

            _remainder -= requestedParticles;
        }

        // Determine whether the duration period has been exceeded.
        if (_dynDurationSet)
        {
            _durationRemain -= timeElapsed;
            if (_durationRemain <= 0)
            {
                setEnabled(false);
            }
        }
    }
    else if (_dynRepeatDelaySet)
    {
        _repeatDelayRemain -= timeElapsed;
        if (_repeatDelayRemain <= 0)
        {
            //// Initialise again (if stopfade isn't set)
            //if (mParentTechnique)
            //{
            //	if (!mParentTechnique->isStopFade())
            //	{
            //		setEnabled(true);
            //	}
            //}
            //else
            //{
            //	setEnabled(true);
            //}

            setEnabled(true);
        }
    }

    return requestedParticles;
}

void PUEmitter::setEnabled( bool enabled )
{
    _isEnabled = enabled;
    if (!_originEnabledSet){
        _originEnabled = enabled;
        _originEnabledSet = true;
    }
    initTimeBased();
}

bool PUEmitter::isEnabled( void ) const
{
    return _isEnabled;
}

void PUEmitter::notifyStart()
{
    _forceEmission = _originalForceEmission;
    _forceEmissionExecuted = _originalForceEmissionExecuted;
    _remainder = 0;
    _durationRemain = 0;
    _repeatDelayRemain = 0;
    setEnabled(_originEnabled); // Also calls _initTimeBased
}

void PUEmitter::notifyRescaled( const Vec3& scale )
{
    _emitterScale = scale;
}

void PUEmitter::notifyStop()
{

}

void PUEmitter::notifyPause()
{

}

void PUEmitter::notifyResume()
{

}

void PUEmitter::prepare()
{
    if (!_emitsEntity){
        if (_emitsType == PUParticle3D::PT_EMITTER){
            auto emitter = static_cast<PUParticleSystem3D *>(_particleSystem)->getEmitter(_emitsName);
            if (emitter){
                emitter->setMarkedForEmission(true);
                _emitsEntity = emitter;
            }
        }
        else if (_emitsType == PUParticle3D::PT_TECHNIQUE){
            PUParticleSystem3D *system = static_cast<PUParticleSystem3D *>(_particleSystem)->getParentParticleSystem();
            if (system){
                auto children = system->getChildren();
                for (auto it : children){
                    if (it->getName() == _emitsName)
                    {
                        static_cast<PUParticleSystem3D *>(it)->setMarkedForEmission(true);
                        _emitsEntity = it;
                        break;
                    }
                }
            }
        }
    }

    _latestPosition = getDerivedPosition(); // V1.3.1
}

void PUEmitter::unPrepare()
{
    setForceEmission(_forceEmission);
}

void PUEmitter::preUpdateEmitter( float /*deltaTime*/ )
{

}

void PUEmitter::postUpdateEmitter( float /*deltaTime*/ )
{
    Vec3 currentPos = getDerivedPosition();
    _latestPositionDiff = currentPos - _latestPosition;
    _latestPosition = currentPos;
}

//-----------------------------------------------------------------------
bool PUEmitter::isKeepLocal(void) const
{
    return _keepLocal;
}
//-----------------------------------------------------------------------
void PUEmitter::setKeepLocal(bool keepLocal)
{
    _keepLocal = keepLocal;
}
//-----------------------------------------------------------------------
bool PUEmitter::makeParticleLocal(PUParticle3D* particle)
{
    if (!particle)
        return true;

    if (!_keepLocal/* || hasEventFlags(PUParticle3D::PEF_EXPIRED)*/)
        return false;

    particle->position += _latestPositionDiff;
    return true;
}

//-----------------------------------------------------------------------
const Vec4& PUEmitter::getParticleColor(void) const
{
    return _particleColor;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleColor(const Vec4& particleColor)
{
    _particleColor = particleColor;
}
//-----------------------------------------------------------------------
const Vec4& PUEmitter::getParticleColorRangeStart(void) const
{
    return _particleColorRangeStart;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleColorRangeStart(const Vec4& particleColorRangeStart)
{
    _particleColorRangeStart = particleColorRangeStart;
    _particleColorRangeSet = true;
}
//-----------------------------------------------------------------------
const Vec4& PUEmitter::getParticleColorRangeEnd(void) const
{
    return _particleColorRangeEnd;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleColorRangeEnd(const Vec4& particleColorRangeEnd)
{
    _particleColorRangeEnd = particleColorRangeEnd;
    _particleColorRangeSet = true;
}
//-----------------------------------------------------------------------
const unsigned short& PUEmitter::getParticleTextureCoords(void) const
{
    return _particleTextureCoords;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleTextureCoords(const unsigned short& particleTextureCoords)
{
    _particleTextureCoords = particleTextureCoords;
}
//-----------------------------------------------------------------------
const unsigned short& PUEmitter::getParticleTextureCoordsRangeStart(void) const
{
    return _particleTextureCoordsRangeStart;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleTextureCoordsRangeStart(const unsigned short& particleTextureCoordsRangeStart)
{
    _particleTextureCoordsRangeStart = particleTextureCoordsRangeStart;
    _particleTextureCoordsRangeSet = true;
}
//-----------------------------------------------------------------------
const unsigned short& PUEmitter::getParticleTextureCoordsRangeEnd(void) const
{
    return _particleTextureCoordsRangeEnd;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleTextureCoordsRangeEnd(const unsigned short& particleTextureCoordsRangeEnd)
{
    _particleTextureCoordsRangeEnd = particleTextureCoordsRangeEnd;
    _particleTextureCoordsRangeSet = true;
}

//-----------------------------------------------------------------------
void PUEmitter::setEmitsName(const std::string& emitsName)
{
    _emitsName = emitsName;
    _emitsEntity = nullptr;
    //if (!_emitsName.empty())
    //{
    //	markedForEmission = true;
    //	if (mParentTechnique)
    //	{
    //		// Notify the Technique that something changed
    //		mParentTechnique->_notifyEmissionChange();
    //	}
    //}
}

//-----------------------------------------------------------------------
void PUEmitter::setDynEmissionRate(PUDynamicAttribute* dynEmissionRate)
{
    if (_dynEmissionRate)
        delete _dynEmissionRate;

    _dynEmissionRate = dynEmissionRate;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynTotalTimeToLive(PUDynamicAttribute* dynTotalTimeToLive)
{
    if (_dynTotalTimeToLive)
        delete _dynTotalTimeToLive;

    _dynTotalTimeToLive = dynTotalTimeToLive;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleMass(PUDynamicAttribute* dynParticleMass)
{
    if (_dynParticleMass)
        delete _dynParticleMass;

    _dynParticleMass = dynParticleMass;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynAngle(PUDynamicAttribute* dynAngle)
{
    if (_dynAngle)
        delete _dynAngle;

    _dynAngle = dynAngle;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynVelocity(PUDynamicAttribute* dynVelocity)
{
    if (_dynVelocity)
        delete _dynVelocity;

    _dynVelocity = dynVelocity;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynDuration(PUDynamicAttribute* dynDuration)
{
    if (_dynDuration)
        delete _dynDuration;

    _dynDuration = dynDuration;
    _dynDurationSet = true;
    initTimeBased();
}
//-----------------------------------------------------------------------
void PUEmitter::setDynDurationSet(bool durationSet)
{
    _dynDurationSet = durationSet;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynRepeatDelay(PUDynamicAttribute* dynRepeatDelay)
{
    if (_dynRepeatDelay)
        delete _dynRepeatDelay;

    _dynRepeatDelay = dynRepeatDelay;
    _dynRepeatDelaySet = true;
    initTimeBased();
}
//-----------------------------------------------------------------------
void PUEmitter::setDynRepeatDelaySet(bool repeatDelaySet)
{
    _dynRepeatDelaySet = repeatDelaySet;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleAllDimensions(PUDynamicAttribute* dynParticleAllDimensions)
{
    if (_dynParticleAllDimensions)
        delete _dynParticleAllDimensions;

    _dynParticleAllDimensions = dynParticleAllDimensions;
    _dynParticleAllDimensionsSet = true;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleAllDimensionsSet(bool particleAllDimensionsSet)
{
    _dynParticleAllDimensionsSet = particleAllDimensionsSet;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleWidth(PUDynamicAttribute* dynParticleWidth)
{
    if (_dynParticleWidth)
        delete _dynParticleWidth;

    _dynParticleWidth = dynParticleWidth;
    _dynParticleWidthSet = true;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleWidthSet(bool particleWidthSet)
{
    _dynParticleWidthSet = particleWidthSet;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleHeight(PUDynamicAttribute* dynParticleHeight)
{
    if (_dynParticleHeight)
        delete _dynParticleHeight;

    _dynParticleHeight = dynParticleHeight;
    _dynParticleHeightSet = true;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleHeightSet(bool particleHeightSet)
{
    _dynParticleHeightSet = particleHeightSet;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleDepth(PUDynamicAttribute* dynParticleDepth)
{
    if (_dynParticleDepth)
        delete _dynParticleDepth;

    _dynParticleDepth = dynParticleDepth;
    _dynParticleDepthSet = true;
}
//-----------------------------------------------------------------------
void PUEmitter::setDynParticleDepthSet(bool particleDepthSet)
{
    _dynParticleDepthSet = particleDepthSet;
}
//-----------------------------------------------------------------------
const Vec3& PUEmitter::getParticleDirection(void)
{
    return _particleDirection;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleDirection(const Vec3& direction)
{
    _particleDirection = direction;
    _originalParticleDirection = direction;
    _particleDirection.normalize();

    _upVector = PUUtil::perpendicular(_particleDirection);
    _upVector.normalize();
}
//-----------------------------------------------------------------------
const Vec3& PUEmitter::getOriginalParticleDirection(void) const
{
    return _originalParticleDirection;
}
//-----------------------------------------------------------------------
const Quaternion& PUEmitter::getParticleOrientation(void) const
{
    return _particleOrientation;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleOrientation(const Quaternion& orientation)
{
    _particleOrientation = orientation;
}
//-----------------------------------------------------------------------
const Quaternion& PUEmitter::getParticleOrientationRangeStart(void) const
{
    return _particleOrientationRangeStart;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleOrientationRangeStart(const Quaternion& orientationRangeStart)
{
    _particleOrientationRangeStart = orientationRangeStart;
    _particleOrientationRangeSet = true;
}
//-----------------------------------------------------------------------
const Quaternion& PUEmitter::getParticleOrientationRangeEnd(void) const
{
    return _particleOrientationRangeEnd;
}
//-----------------------------------------------------------------------
void PUEmitter::setParticleOrientationRangeEnd(const Quaternion& orientationRangeEnd)
{
    _particleOrientationRangeEnd = orientationRangeEnd;
    _particleOrientationRangeSet = true;
}
//-----------------------------------------------------------------------
bool PUEmitter::isAutoDirection(void) const
{
    return _autoDirection;
}
//-----------------------------------------------------------------------
void PUEmitter::setAutoDirection(bool autoDirection)
{
    _autoDirection = autoDirection;
}
//-----------------------------------------------------------------------
bool PUEmitter::isForceEmission(void) const
{
    return _forceEmission;
}
//-----------------------------------------------------------------------
void PUEmitter::setForceEmission(bool forceEmission)
{
    _forceEmission = forceEmission;
    _originalForceEmission = forceEmission;
    _forceEmissionExecuted = false;
    _originalForceEmissionExecuted = false;
}

void PUEmitter::initTimeBased( void )
{
    if (_isEnabled)
    {
        if (_dynDurationSet)
        {
            _durationRemain = _dynamicAttributeHelper.calculate(_dynDuration, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
        }

        /** Determine whether duration must be used. If it is used, the emitter should at least be enabled.
        @remarks
            Note, that if the duration has been exceeded, the emitter is disabled. It makes perfect sense to enable 
            the emitter again when the duration is initialised with a valid value (> 0).
        */
        if (_durationRemain > 0)
        {
            _isEnabled = true;
            _repeatDelayRemain = 0;
        }
    }
    else
    {
        if (_dynRepeatDelaySet)
        {
            _repeatDelayRemain = _dynamicAttributeHelper.calculate(_dynRepeatDelay, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
        }
    }
}

void PUEmitter::initParticleForEmission( PUParticle3D* particle )
{
    // Initialise the particle position (localspace)
    particle->parentEmitter = this;
    initParticlePosition(particle);
    initParticleDirection(particle);
    initParticleVelocity(particle);
    initParticleOrientation(particle);
    initParticleMass(particle);
    initParticleColor(particle);
    initParticleTextureCoords(particle);
    particle->totalTimeToLive = initParticleTimeToLive();
    particle->timeToLive = particle->totalTimeToLive;

    // Generate particles' own dimensions if defined.
    initParticleDimensions(particle);
}

void PUEmitter::initParticleVelocity( PUParticle3D* particle )
{
    float scalar = _dynamicAttributeHelper.calculate(_dynVelocity, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart(), 1.0f);
    particle->direction *= scalar;
    particle->originalVelocity = scalar;
    particle->originalScaledDirectionLength = particle->direction.length();
}

void PUEmitter::initParticleMass( PUParticle3D* particle )
{
    float mass = _dynamicAttributeHelper.calculate(_dynParticleMass, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart(), PUParticle3D::DEFAULT_MASS);
    particle->mass = mass;
}

void PUEmitter::initParticleColor( PUParticle3D* particle )
{
    if (_particleColorRangeSet)
    {
        if (_particleColorRangeStart.x < _particleColorRangeEnd.x)
            particle->color.x = cocos2d::random(_particleColorRangeStart.x, _particleColorRangeEnd.x);
        else
            particle->color.x = cocos2d::random(_particleColorRangeEnd.x, _particleColorRangeStart.x);
        if (_particleColorRangeStart.y < _particleColorRangeEnd.y)
            particle->color.y = cocos2d::random(_particleColorRangeStart.y, _particleColorRangeEnd.y);
        else
            particle->color.y = cocos2d::random(_particleColorRangeEnd.y, _particleColorRangeStart.y);
        if (_particleColorRangeStart.z < _particleColorRangeEnd.z)
            particle->color.z = cocos2d::random(_particleColorRangeStart.z, _particleColorRangeEnd.z);
        else
            particle->color.z = cocos2d::random(_particleColorRangeEnd.z, _particleColorRangeStart.z);
        if (_particleColorRangeStart.w < _particleColorRangeEnd.w)
            particle->color.w = cocos2d::random(_particleColorRangeStart.w, _particleColorRangeEnd.w);
        else
            particle->color.w = cocos2d::random(_particleColorRangeEnd.w, _particleColorRangeStart.w);
    }
    else
    {
        particle->color = _particleColor;
    }

    // Set original colour
    particle->originalColor = particle->color;
}

void PUEmitter::initParticleTextureCoords( PUParticle3D* particle )
{
    if (_particleTextureCoordsRangeSet)
    {
        particle->textureCoordsCurrent = (unsigned short)cocos2d::random((float)_particleTextureCoordsRangeStart, (float)_particleTextureCoordsRangeEnd + 0.999f);
    }
    else
    {
        particle->textureCoordsCurrent = _particleTextureCoords;
    }
}

float PUEmitter::initParticleTimeToLive()
{
    return _dynamicAttributeHelper.calculate(_dynTotalTimeToLive, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart(), PUParticle3D::DEFAULT_TTL);
}

void PUEmitter::initParticleDimensions( PUParticle3D* particle )
{
    // Only continue if one of them is set
    if (_dynParticleAllDimensionsSet || _dynParticleWidthSet || _dynParticleHeightSet || _dynParticleDepthSet)
    {
        // Set all dimensions equal ...
        float extend = 0;
        if (_dynParticleAllDimensionsSet && _dynParticleAllDimensions)
        {
            extend = _dynamicAttributeHelper.calculate(_dynParticleAllDimensions, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
            particle->setOwnDimensions(_emitterScale.x * extend, _emitterScale.y * extend, _emitterScale.z * extend);
            return;
        }

        // ... or set the dimensions independent from each other
        float width = 0;
        float height = 0;
        float depth = 0;
        if (_dynParticleWidthSet && _dynParticleWidth)
        {
            width = _dynamicAttributeHelper.calculate(_dynParticleWidth, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
        }
        if (_dynParticleHeightSet && _dynParticleHeight)
        {
            height = _dynamicAttributeHelper.calculate(_dynParticleHeight, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
        }
        if (_dynParticleDepthSet && _dynParticleDepth)
        {
            depth = _dynamicAttributeHelper.calculate(_dynParticleDepth, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
        }
    
        /** Set the width, height and depth if at least one of them is set.
        @remarks
            If one of the dimensions is 0, it will be overridden by the default value later on.
        */
        if (_dynParticleWidthSet || _dynParticleHeightSet || _dynParticleDepthSet)
        {
            particle->setOwnDimensions(_emitterScale.x * width, _emitterScale.y * height, _emitterScale.z * depth);
        }
    }
    else
    {
        // Just set the width, height and depth, but these are just the default settings; the particle doesn't
        // have own dimensions. Recalculate the bounding sphere radius.
        particle->width = _emitterScale.x * (static_cast<PUParticleSystem3D *>(_particleSystem))->getDefaultWidth();
        particle->height = _emitterScale.y * (static_cast<PUParticleSystem3D *>(_particleSystem))->getDefaultHeight();
        particle->depth = _emitterScale.z * (static_cast<PUParticleSystem3D *>(_particleSystem))->getDefaultDepth();
        particle->calculateBoundingSphereRadius();
    }
}

bool PUEmitter::isEmitterDone() const
{
    return !(_isEnabled || _dynRepeatDelaySet);
}

Ref* PUEmitter::getEmitsEntityPtr() const
{
    return _emitsEntity;
}

void PUEmitter::copyAttributesTo( PUEmitter* emitter )
{
    emitter->setName(_name);
    emitter->setEmitterType(_emitterType);
    emitter->setEmitsName(_emitsName);
    emitter->setEmitsType(_emitsType);
    emitter->_position = _position;
    emitter->_isEnabled = _isEnabled;
    emitter->_originEnabled = _originEnabled;
    emitter->_originEnabledSet = _originEnabledSet;
    emitter->_particleDirection = _particleDirection;
    emitter->_originalParticleDirection = _originalParticleDirection;
    emitter->_particleOrientation = _particleOrientation;
    emitter->_particleOrientationRangeStart = _particleOrientationRangeStart;
    emitter->_particleOrientationRangeEnd = _particleOrientationRangeEnd;
    emitter->_particleOrientationRangeSet = _particleOrientationRangeSet;
    emitter->_isMarkedForEmission = _isMarkedForEmission;
    emitter->_particleSystem = _particleSystem;
    emitter->_autoDirection = _autoDirection;
    emitter->setForceEmission(_forceEmission);
    emitter->_dynDurationSet = _dynDurationSet;
    emitter->_dynRepeatDelaySet = _dynRepeatDelaySet;
    emitter->_dynParticleAllDimensionsSet = _dynParticleAllDimensionsSet;
    emitter->_dynParticleWidthSet = _dynParticleWidthSet;
    emitter->_dynParticleHeightSet = _dynParticleHeightSet;
    emitter->_dynParticleDepthSet = _dynParticleDepthSet;
    emitter->_emitterScale = _emitterScale;
    emitter->_particleColor = _particleColor;
    emitter->_particleColorRangeStart = _particleColorRangeStart;
    emitter->_particleColorRangeEnd = _particleColorRangeEnd;
    emitter->_particleColorRangeSet = _particleColorRangeSet;
    emitter->_particleTextureCoords = _particleTextureCoords;
    emitter->_particleTextureCoordsRangeStart = _particleTextureCoordsRangeStart;
    emitter->_particleTextureCoordsRangeEnd = _particleTextureCoordsRangeEnd;
    emitter->_particleTextureCoordsRangeSet = _particleTextureCoordsRangeSet;
    emitter->_keepLocal = _keepLocal;

    // Copy Dyn. Emission rate if available
    emitter->setDynEmissionRate(getDynEmissionRate()->clone());

    // Copy Dyn. Total time to live if available
    emitter->setDynTotalTimeToLive(getDynTotalTimeToLive()->clone());

    // Copy Dyn. Velocity if available
    emitter->setDynVelocity(getDynVelocity()->clone());

    // Copy Dyn. Duration if available
    if (_dynDurationSet)
    {
        emitter->setDynDuration(getDynDuration()->clone());
    }

    // Copy Dyn. RepeatDelay if available
    if (_dynRepeatDelaySet)
    {
        emitter->setDynRepeatDelay(getDynRepeatDelay()->clone());
    }

    // Copy Dyn. Particle Mass if available
    emitter->setDynParticleMass(getDynParticleMass()->clone());

    // Copy Dyn. Angle if available
    emitter->setDynAngle(getDynAngle()->clone());

    // Copy Dyn. own width, height and depth if available
    if (_dynParticleAllDimensionsSet)
    {
        emitter->setDynParticleAllDimensions(getDynParticleAllDimensions()->clone());
    }
    if (_dynParticleWidthSet)
    {
        emitter->setDynParticleWidth(getDynParticleWidth()->clone());
    }
    if (_dynParticleHeightSet)
    {
        emitter->setDynParticleHeight(getDynParticleHeight()->clone());
    }
    if (_dynParticleDepthSet)
    {
        emitter->setDynParticleDepth(getDynParticleDepth()->clone());
    }
}

NS_CC_END
