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

#include "CCPUParticle3DEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DUtil.h"

NS_CC_BEGIN

// Constants
const bool PUParticle3DEmitter::DEFAULT_ENABLED = true;
const Vec3 PUParticle3DEmitter::DEFAULT_POSITION(0, 0, 0);
const bool PUParticle3DEmitter::DEFAULT_KEEP_LOCAL = false;
const Vec3 PUParticle3DEmitter::DEFAULT_DIRECTION(0, 1, 0);
const Quaternion PUParticle3DEmitter::DEFAULT_ORIENTATION(1, 0, 0, 0);
const Quaternion PUParticle3DEmitter::DEFAULT_ORIENTATION_RANGE_START(1, 0, 0, 0);
const Quaternion PUParticle3DEmitter::DEFAULT_ORIENTATION_RANGE_END(1, 0, 0, 0);
//const Particle::ParticleType PUParticle3DEmitter::DEFAULT_EMITS = VisualParticle::PT_VISUAL;
const unsigned short PUParticle3DEmitter::DEFAULT_START_TEXTURE_COORDS = 0;
const unsigned short PUParticle3DEmitter::DEFAULT_END_TEXTURE_COORDS = 0;
const unsigned short PUParticle3DEmitter::DEFAULT_TEXTURE_COORDS = 0;
const Vec4 PUParticle3DEmitter::DEFAULT_START_COLOUR_RANGE(0, 0, 0, 1);
const Vec4 PUParticle3DEmitter::DEFAULT_END_COLOUR_RANGE(1, 1, 1, 1);
const Vec4 PUParticle3DEmitter::DEFAULT_COLOUR(1, 1, 1, 1);
const bool PUParticle3DEmitter::DEFAULT_AUTO_DIRECTION = false;
const bool PUParticle3DEmitter::DEFAULT_FORCE_EMISSION = false;
const float PUParticle3DEmitter::DEFAULT_EMISSION_RATE = 10.0f;
const float PUParticle3DEmitter::DEFAULT_TIME_TO_LIVE = 3.0f;
const float PUParticle3DEmitter::DEFAULT_MASS = 1.0f;
const float PUParticle3DEmitter::DEFAULT_VELOCITY = 100.0f;
const float PUParticle3DEmitter::DEFAULT_DURATION = 0.0f;
const float PUParticle3DEmitter::DEFAULT_REPEAT_DELAY = 0.0f;
const float PUParticle3DEmitter::DEFAULT_ANGLE = 20.0f;
const float PUParticle3DEmitter::DEFAULT_DIMENSIONS = 0.0f;
const float PUParticle3DEmitter::DEFAULT_WIDTH = 0.0f;
const float PUParticle3DEmitter::DEFAULT_HEIGHT = 0.0f;
const float PUParticle3DEmitter::DEFAULT_DEPTH = 0.0f;

PUParticle3DEmitter::PUParticle3DEmitter()
: //mEmitsType(DEFAULT_EMITS),
//mEmitsName(StringUtil::BLANK),
_remainder(0),
_durationRemain(0),
_repeatDelayRemain(0),
_dynDurationSet(false),
_dynRepeatDelaySet(false),
_particleDirection(DEFAULT_DIRECTION),
_originalParticleDirection(DEFAULT_DIRECTION),
//mParticleOrientation(Quaternion::IDENTITY),
//mParticleOrientationRangeStart(Quaternion::IDENTITY),
//mParticleOrientationRangeEnd(Quaternion::IDENTITY),
_particleOrientationRangeSet(false),
_upVector(Vec3::ZERO),
_dynParticleAllDimensionsSet(false),
_dynParticleWidthSet(false),
_dynParticleHeightSet(false),
_dynParticleDepthSet(false),
_autoDirection(DEFAULT_AUTO_DIRECTION),
_forceEmission(DEFAULT_FORCE_EMISSION),
_originalForceEmission(false),
_forceEmissionExecuted(false),
_originalForceEmissionExecuted(false),
//mName(StringUtil::BLANK),
_emitterScale(Vec3::ONE),
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
_originEnabledSet(false)
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

PUParticle3DEmitter::~PUParticle3DEmitter()
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

void PUParticle3DEmitter::updateEmitter(Particle3D *particle, float deltaTime)
{
    
}

void PUParticle3DEmitter::emit(int count)
{
    
}

void PUParticle3DEmitter::initParticlePosition( PUParticle3D* particle )
{
    particle->position = getDerivedPosition();
    particle->originalPosition = particle->position;
    particle->latestPosition = particle->position;
}

const Vec3& PUParticle3DEmitter::getDerivedPosition()
{
    PUParticleSystem3D *ps = static_cast<PUParticleSystem3D *>(_particleSystem);
    if (ps){
        Mat4 rotMat;
        Mat4::createRotation(ps->getDerivedOrientation(), &rotMat);
        _derivedPosition = ps->getDerivedPosition() + rotMat * Vec3(_position.x * _emitterScale.x, _position.y * _emitterScale.y, _position.z * _emitterScale.z);
        //_particleSystem->getNodeToWorldTransform().transformPoint(_position, &_derivedPosition);
    }
    else
        _derivedPosition = Vec3::ZERO;

    return _derivedPosition;
}

void PUParticle3DEmitter::initParticleOrientation( PUParticle3D* particle )
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

void PUParticle3DEmitter::initParticleDirection( PUParticle3D* particle )
{
    // Use the default way of initialising the particle direction
    float angle = 0.0f;
    generateAngle(angle);
    if (angle != 0.0f)
    {
        particle->direction = PUParticle3DUtil::randomDeviant(_particleDirection, angle, _upVector);
    }
    else
    {
        particle->direction = _particleDirection;
    }
    particle->originalDirection = particle->direction;
    particle->originalDirectionLength = particle->direction.length();
}

void PUParticle3DEmitter::generateAngle( float &angle )
{
    float a = CC_DEGREES_TO_RADIANS(_dynamicAttributeHelper.calculate(_dynAngle, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart()));
    angle = a;
    if (_dynAngle->getType() == PUDynamicAttribute::DAT_FIXED)
    {
        // Make an exception here and don't use the fixed angle.
        angle = CCRANDOM_0_1() * angle;
    }
}

unsigned short PUParticle3DEmitter::calculateRequestedParticles( float timeElapsed )
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

void PUParticle3DEmitter::setEnabled( bool enabled )
{
    _isEnabled = enabled;
    if (!_originEnabledSet){
        _originEnabled = enabled;
        _originEnabledSet = true;
    }
    initTimeBased();
}

bool PUParticle3DEmitter::isEnabled( void ) const
{
    return _isEnabled;
}

void PUParticle3DEmitter::notifyStart()
{
    _latestPosition = getDerivedPosition(); // V1.3.1
    _forceEmission = _originalForceEmission;
    _forceEmissionExecuted = _originalForceEmissionExecuted;
    _remainder = 0;
    _durationRemain = 0;
    _repeatDelayRemain = 0;
    setEnabled(_originEnabled); // Also calls _initTimeBased
}

void PUParticle3DEmitter::notifyRescaled( const Vec3& scale )
{
    _emitterScale = scale;
}

void PUParticle3DEmitter::notifyStop()
{
    setEnabled(false);
}

void PUParticle3DEmitter::notifyPause()
{

}

void PUParticle3DEmitter::notifyResume()
{

}

void PUParticle3DEmitter::prepare()
{

}

void PUParticle3DEmitter::unPrepare()
{

}

void PUParticle3DEmitter::preUpdateEmitter( float deltaTime )
{

}

void PUParticle3DEmitter::postUpdateEmitter( float deltaTime )
{

}

//-----------------------------------------------------------------------
bool PUParticle3DEmitter::isKeepLocal(void) const
{
    return _keepLocal;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setKeepLocal(bool keepLocal)
{
    _keepLocal = keepLocal;
}
//-----------------------------------------------------------------------
bool PUParticle3DEmitter::makeParticleLocal(PUParticle3D* particle)
{
    if (!particle)
        return true;

    if (!_keepLocal/* || hasEventFlags(PUParticle3D::PEF_EXPIRED)*/)
        return false;

    Vec3 diff = getDerivedPosition() - _latestPosition;
    particle->position += diff;
    return true;
}

//-----------------------------------------------------------------------
const Vec4& PUParticle3DEmitter::getParticleColor(void) const
{
    return _particleColor;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleColor(const Vec4& particleColor)
{
    _particleColor = particleColor;
}
//-----------------------------------------------------------------------
const Vec4& PUParticle3DEmitter::getParticleColorRangeStart(void) const
{
    return _particleColorRangeStart;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleColorRangeStart(const Vec4& particleColorRangeStart)
{
    _particleColorRangeStart = particleColorRangeStart;
    _particleColorRangeSet = true;
}
//-----------------------------------------------------------------------
const Vec4& PUParticle3DEmitter::getParticleColorRangeEnd(void) const
{
    return _particleColorRangeEnd;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleColorRangeEnd(const Vec4& particleColorRangeEnd)
{
    _particleColorRangeEnd = particleColorRangeEnd;
    _particleColorRangeSet = true;
}
//-----------------------------------------------------------------------
const unsigned short& PUParticle3DEmitter::getParticleTextureCoords(void) const
{
    return _particleTextureCoords;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleTextureCoords(const unsigned short& particleTextureCoords)
{
    _particleTextureCoords = particleTextureCoords;
}
//-----------------------------------------------------------------------
const unsigned short& PUParticle3DEmitter::getParticleTextureCoordsRangeStart(void) const
{
    return _particleTextureCoordsRangeStart;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleTextureCoordsRangeStart(const unsigned short& particleTextureCoordsRangeStart)
{
    _particleTextureCoordsRangeStart = particleTextureCoordsRangeStart;
    _particleTextureCoordsRangeSet = true;
}
//-----------------------------------------------------------------------
const unsigned short& PUParticle3DEmitter::getParticleTextureCoordsRangeEnd(void) const
{
    return _particleTextureCoordsRangeEnd;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleTextureCoordsRangeEnd(const unsigned short& particleTextureCoordsRangeEnd)
{
    _particleTextureCoordsRangeEnd = particleTextureCoordsRangeEnd;
    _particleTextureCoordsRangeSet = true;
}

//-----------------------------------------------------------------------
void PUParticle3DEmitter::setEmitsName(const std::string& emitsName)
{
    _emitsName = emitsName;
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
void PUParticle3DEmitter::setDynEmissionRate(PUDynamicAttribute* dynEmissionRate)
{
    if (_dynEmissionRate)
        delete _dynEmissionRate;

    _dynEmissionRate = dynEmissionRate;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynTotalTimeToLive(PUDynamicAttribute* dynTotalTimeToLive)
{
    if (_dynTotalTimeToLive)
        delete _dynTotalTimeToLive;

    _dynTotalTimeToLive = dynTotalTimeToLive;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleMass(PUDynamicAttribute* dynParticleMass)
{
    if (_dynParticleMass)
        delete _dynParticleMass;

    _dynParticleMass = dynParticleMass;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynAngle(PUDynamicAttribute* dynAngle)
{
    if (_dynAngle)
        delete _dynAngle;

    _dynAngle = dynAngle;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynVelocity(PUDynamicAttribute* dynVelocity)
{
    if (_dynVelocity)
        delete _dynVelocity;

    _dynVelocity = dynVelocity;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynDuration(PUDynamicAttribute* dynDuration)
{
    if (_dynDuration)
        delete _dynDuration;

    _dynDuration = dynDuration;
    _dynDurationSet = true;
    initTimeBased();
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynDurationSet(bool durationSet)
{
    _dynDurationSet = durationSet;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynRepeatDelay(PUDynamicAttribute* dynRepeatDelay)
{
    if (_dynRepeatDelay)
        delete _dynRepeatDelay;

    _dynRepeatDelay = dynRepeatDelay;
    _dynRepeatDelaySet = true;
    initTimeBased();
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynRepeatDelaySet(bool repeatDelaySet)
{
    _dynRepeatDelaySet = repeatDelaySet;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleAllDimensions(PUDynamicAttribute* dynParticleAllDimensions)
{
    if (_dynParticleAllDimensions)
        delete _dynParticleAllDimensions;

    _dynParticleAllDimensions = dynParticleAllDimensions;
    _dynParticleAllDimensionsSet = true;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleAllDimensionsSet(bool particleAllDimensionsSet)
{
    _dynParticleAllDimensionsSet = particleAllDimensionsSet;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleWidth(PUDynamicAttribute* dynParticleWidth)
{
    if (_dynParticleWidth)
        delete _dynParticleWidth;

    _dynParticleWidth = dynParticleWidth;
    _dynParticleWidthSet = true;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleWidthSet(bool particleWidthSet)
{
    _dynParticleWidthSet = particleWidthSet;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleHeight(PUDynamicAttribute* dynParticleHeight)
{
    if (_dynParticleHeight)
        delete _dynParticleHeight;

    _dynParticleHeight = dynParticleHeight;
    _dynParticleHeightSet = true;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleHeightSet(bool particleHeightSet)
{
    _dynParticleHeightSet = particleHeightSet;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleDepth(PUDynamicAttribute* dynParticleDepth)
{
    if (_dynParticleDepth)
        delete _dynParticleDepth;

    _dynParticleDepth = dynParticleDepth;
    _dynParticleDepthSet = true;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setDynParticleDepthSet(bool particleDepthSet)
{
    _dynParticleDepthSet = particleDepthSet;
}
//-----------------------------------------------------------------------
const Vec3& PUParticle3DEmitter::getParticleDirection(void)
{
    return _particleDirection;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleDirection(const Vec3& direction)
{
    _particleDirection = direction;
    _originalParticleDirection = direction;
    _particleDirection.normalize();

    _upVector = PUParticle3DUtil::perpendicular(_particleDirection);
    _upVector.normalize();
}
//-----------------------------------------------------------------------
const Vec3& PUParticle3DEmitter::getOriginalParticleDirection(void) const
{
    return _originalParticleDirection;
}
//-----------------------------------------------------------------------
const Quaternion& PUParticle3DEmitter::getParticleOrientation(void) const
{
    return _particleOrientation;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleOrientation(const Quaternion& orientation)
{
    _particleOrientation = orientation;
}
//-----------------------------------------------------------------------
const Quaternion& PUParticle3DEmitter::getParticleOrientationRangeStart(void) const
{
    return _particleOrientationRangeStart;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleOrientationRangeStart(const Quaternion& orientationRangeStart)
{
    _particleOrientationRangeStart = orientationRangeStart;
    _particleOrientationRangeSet = true;
}
//-----------------------------------------------------------------------
const Quaternion& PUParticle3DEmitter::getParticleOrientationRangeEnd(void) const
{
    return _particleOrientationRangeEnd;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setParticleOrientationRangeEnd(const Quaternion& orientationRangeEnd)
{
    _particleOrientationRangeEnd = orientationRangeEnd;
    _particleOrientationRangeSet = true;
}
//-----------------------------------------------------------------------
bool PUParticle3DEmitter::isAutoDirection(void) const
{
    return _autoDirection;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setAutoDirection(bool autoDirection)
{
    _autoDirection = autoDirection;
}
//-----------------------------------------------------------------------
bool PUParticle3DEmitter::isForceEmission(void) const
{
    return _forceEmission;
}
//-----------------------------------------------------------------------
void PUParticle3DEmitter::setForceEmission(bool forceEmission)
{
    _forceEmission = forceEmission;
    _originalForceEmission = forceEmission;
    _forceEmissionExecuted = false;
    _originalForceEmissionExecuted = false;
}

void PUParticle3DEmitter::initTimeBased( void )
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

void PUParticle3DEmitter::initParticleForEmission( PUParticle3D* particle )
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

void PUParticle3DEmitter::initParticleVelocity( PUParticle3D* particle )
{
    float scalar = _dynamicAttributeHelper.calculate(_dynVelocity, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart(), 1.0f);
    particle->direction *= scalar;
    particle->originalVelocity = scalar;
    particle->originalScaledDirectionLength = particle->direction.length();
}

void PUParticle3DEmitter::initParticleMass( PUParticle3D* particle )
{
    float mass = _dynamicAttributeHelper.calculate(_dynParticleMass, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart(), PUParticle3D::DEFAULT_MASS);
    particle->mass = mass;
}

void PUParticle3DEmitter::initParticleColor( PUParticle3D* particle )
{
    if (_particleColorRangeSet)
    {
        particle->color.x = cocos2d::random(_particleColorRangeStart.x, _particleColorRangeEnd.x);
        particle->color.y = cocos2d::random(_particleColorRangeStart.y, _particleColorRangeEnd.y);
        particle->color.z = cocos2d::random(_particleColorRangeStart.z, _particleColorRangeEnd.z);
        particle->color.w = cocos2d::random(_particleColorRangeStart.w, _particleColorRangeEnd.w);
    }
    else
    {
        particle->color = _particleColor;
    }

    // Set original colour
    particle->originalColor = particle->color;
}

void PUParticle3DEmitter::initParticleTextureCoords( PUParticle3D* particle )
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

float PUParticle3DEmitter::initParticleTimeToLive()
{
    return _dynamicAttributeHelper.calculate(_dynTotalTimeToLive, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart(), PUParticle3D::DEFAULT_TTL);
}

void PUParticle3DEmitter::initParticleDimensions( PUParticle3D* particle )
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

bool PUParticle3DEmitter::isEmitterDone() const
{
    return !(_isEnabled || _dynRepeatDelaySet);
}

NS_CC_END
