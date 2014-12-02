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

#include "CCParticle3DEmitter.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const bool Particle3DEmitter::DEFAULT_ENABLED = true;
const Vec3 Particle3DEmitter::DEFAULT_POSITION(0, 0, 0);
const bool Particle3DEmitter::DEFAULT_KEEP_LOCAL = false;
const Vec3 Particle3DEmitter::DEFAULT_DIRECTION(0, 1, 0);
const Quaternion Particle3DEmitter::DEFAULT_ORIENTATION(1, 0, 0, 0);
const Quaternion Particle3DEmitter::DEFAULT_ORIENTATION_RANGE_START(1, 0, 0, 0);
const Quaternion Particle3DEmitter::DEFAULT_ORIENTATION_RANGE_END(1, 0, 0, 0);
//const Particle::ParticleType Particle3DEmitter::DEFAULT_EMITS = VisualParticle::PT_VISUAL;
const unsigned short Particle3DEmitter::DEFAULT_START_TEXTURE_COORDS = 0;
const unsigned short Particle3DEmitter::DEFAULT_END_TEXTURE_COORDS = 0;
const unsigned short Particle3DEmitter::DEFAULT_TEXTURE_COORDS = 0;
const Vec4 Particle3DEmitter::DEFAULT_START_COLOUR_RANGE(0, 0, 0, 1);
const Vec4 Particle3DEmitter::DEFAULT_END_COLOUR_RANGE(1, 1, 1, 1);
const Vec4 Particle3DEmitter::DEFAULT_COLOUR(1, 1, 1, 1);
const bool Particle3DEmitter::DEFAULT_AUTO_DIRECTION = false;
const bool Particle3DEmitter::DEFAULT_FORCE_EMISSION = false;
const float Particle3DEmitter::DEFAULT_EMISSION_RATE = 10.0f;
const float Particle3DEmitter::DEFAULT_TIME_TO_LIVE = 3.0f;
const float Particle3DEmitter::DEFAULT_MASS = 1.0f;
const float Particle3DEmitter::DEFAULT_VELOCITY = 100.0f;
const float Particle3DEmitter::DEFAULT_DURATION = 0.0f;
const float Particle3DEmitter::DEFAULT_REPEAT_DELAY = 0.0f;
const float Particle3DEmitter::DEFAULT_ANGLE = 20.0f;
const float Particle3DEmitter::DEFAULT_DIMENSIONS = 0.0f;
const float Particle3DEmitter::DEFAULT_WIDTH = 0.0f;
const float Particle3DEmitter::DEFAULT_HEIGHT = 0.0f;
const float Particle3DEmitter::DEFAULT_DEPTH = 0.0f;

Particle3DEmitter::Particle3DEmitter()
: _particleSystem(nullptr),
//mEmitsType(DEFAULT_EMITS),
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
_isEnabled(true)
{
    //particleType = PT_EMITTER;
    //mAliasType = AT_EMITTER;
    _dynEmissionRate = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynEmissionRate))->setValue(DEFAULT_EMISSION_RATE);
    _dynTotalTimeToLive = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynTotalTimeToLive))->setValue(DEFAULT_TIME_TO_LIVE);
    _dynParticleMass = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynParticleMass))->setValue(DEFAULT_MASS);
    _dynVelocity = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynVelocity))->setValue(DEFAULT_VELOCITY);
    _dynDuration = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynDuration))->setValue(DEFAULT_DURATION);
    _dynRepeatDelay = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynRepeatDelay))->setValue(DEFAULT_REPEAT_DELAY);
    _dynAngle = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynAngle))->setValue(DEFAULT_ANGLE);

    // Set the dimensions attributes to 0; the default is to use the default dimensions of the ParticleTechnique
    _dynParticleAllDimensions = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynParticleAllDimensions))->setValue(DEFAULT_DIMENSIONS);
    _dynParticleWidth = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynParticleWidth))->setValue(DEFAULT_WIDTH);
    _dynParticleHeight = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynParticleHeight))->setValue(DEFAULT_HEIGHT);
    _dynParticleDepth = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynParticleDepth))->setValue(DEFAULT_DEPTH);
}

Particle3DEmitter::~Particle3DEmitter()
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

void Particle3DEmitter::updateEmitter(Particle3D *particle, float deltaTime)
{
    
}

void Particle3DEmitter::emit(int count)
{
    
}

void Particle3DEmitter::initParticlePosition( Particle3D* particle )
{
    particle->position = getDerivedPosition();
    particle->originalPosition = particle->position;
    particle->latestPosition = particle->position;
}

const Vec3& Particle3DEmitter::getDerivedPosition()
{
    return _derivedPosition;
}

void Particle3DEmitter::initParticleOrientation( Particle3D* particle )
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

void Particle3DEmitter::initParticleDirection( Particle3D* particle )
{
    // Use the default way of initialising the particle direction
    float angle = 0.0f;
    generateAngle(angle);
    if (angle != 0.0f)
    {
        //particle->direction = _particleDirection.randomDeviant(angle, _upVector);
        // Rotate up vector by random amount around this
        Mat4 mat;
        Mat4::createRotation(_particleDirection, CCRANDOM_0_1() * M_PI * 2.0f, &mat);
        Vec3 newUp = mat * _upVector;
        Mat4::createRotation(newUp, angle, &mat);
        particle->direction = mat * _particleDirection;
    }
    else
    {
        particle->direction = _particleDirection;
    }
    particle->originalDirection = particle->direction;
    particle->originalDirectionLength = particle->direction.length();
}

void Particle3DEmitter::generateAngle( float &angle )
{
    float a = _dynamicAttributeHelper.calculate(_dynAngle, _particleSystem->getTimeElapsedSinceStart());
    angle = a;
    if (_dynAngle->getType() == DynamicAttribute::DAT_FIXED)
    {
        // Make an exception here and don´t use the fixed angle.
        angle = CCRANDOM_0_1() * angle;
    }
}

unsigned short Particle3DEmitter::calculateRequestedParticles( float timeElapsed )
{
    unsigned short requestedParticles = 0;

    //FIXME
    if (_isEnabled)
    {
        if (_dynEmissionRate)
        {
            float rate = _dynEmissionRate->getValue(_particleSystem->getTimeElapsedSinceStart());
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

void Particle3DEmitter::setEnabled( bool enabled )
{
    _isEnabled = enabled;
    initTimeBased();
}

bool Particle3DEmitter::isEnabled( void ) const
{
    return _isEnabled;
}

void Particle3DEmitter::notifyStart()
{
    _latestPosition = getDerivedPosition(); // V1.3.1
    _forceEmission = _originalForceEmission;
    _forceEmissionExecuted = _originalForceEmissionExecuted;
    _remainder = 0;
    _durationRemain = 0;
    _repeatDelayRemain = 0;
    setEnabled(true/*mOriginalEnabled*/); // Also calls _initTimeBased
}

void Particle3DEmitter::notifyRescaled( const Vec3& scale )
{
    _emitterScale = scale;
}

void Particle3DEmitter::notifyStop()
{

}

void Particle3DEmitter::notifyPause()
{

}

void Particle3DEmitter::notifyResume()
{

}

void Particle3DEmitter::prepare()
{

}

void Particle3DEmitter::unPrepare()
{

}

void Particle3DEmitter::preUpdateEmitter( float deltaTime )
{

}

void Particle3DEmitter::postUpdateEmitter( float deltaTime )
{

}

//-----------------------------------------------------------------------
bool Particle3DEmitter::isKeepLocal(void) const
{
    return _keepLocal;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setKeepLocal(bool keepLocal)
{
    _keepLocal = keepLocal;
}
//-----------------------------------------------------------------------
bool Particle3DEmitter::makeParticleLocal(Particle3D* particle)
{
    if (!particle)
        return true;

    if (!_keepLocal/* || hasEventFlags(Particle3D::PEF_EXPIRED)*/)
        return false;

    Vec3 diff = getDerivedPosition() - _latestPosition;
    particle->position += diff;
    return true;
}

//-----------------------------------------------------------------------
const Vec4& Particle3DEmitter::getParticleColor(void) const
{
    return _particleColor;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleColor(const Vec4& particleColor)
{
    _particleColor = particleColor;
}
//-----------------------------------------------------------------------
const Vec4& Particle3DEmitter::getParticleColorRangeStart(void) const
{
    return _particleColorRangeStart;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleColorRangeStart(const Vec4& particleColorRangeStart)
{
    _particleColorRangeStart = particleColorRangeStart;
    _particleColorRangeSet = true;
}
//-----------------------------------------------------------------------
const Vec4& Particle3DEmitter::getParticleColorRangeEnd(void) const
{
    return _particleColorRangeEnd;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleColorRangeEnd(const Vec4& particleColorRangeEnd)
{
    _particleColorRangeEnd = particleColorRangeEnd;
    _particleColorRangeSet = true;
}
//-----------------------------------------------------------------------
const unsigned short& Particle3DEmitter::getParticleTextureCoords(void) const
{
    return _particleTextureCoords;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleTextureCoords(const unsigned short& particleTextureCoords)
{
    _particleTextureCoords = particleTextureCoords;
}
//-----------------------------------------------------------------------
const unsigned short& Particle3DEmitter::getParticleTextureCoordsRangeStart(void) const
{
    return _particleTextureCoordsRangeStart;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleTextureCoordsRangeStart(const unsigned short& particleTextureCoordsRangeStart)
{
    _particleTextureCoordsRangeStart = particleTextureCoordsRangeStart;
    _particleTextureCoordsRangeSet = true;
}
//-----------------------------------------------------------------------
const unsigned short& Particle3DEmitter::getParticleTextureCoordsRangeEnd(void) const
{
    return _particleTextureCoordsRangeEnd;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleTextureCoordsRangeEnd(const unsigned short& particleTextureCoordsRangeEnd)
{
    _particleTextureCoordsRangeEnd = particleTextureCoordsRangeEnd;
    _particleTextureCoordsRangeSet = true;
}

//-----------------------------------------------------------------------
void Particle3DEmitter::setEmitsName(const std::string& emitsName)
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
void Particle3DEmitter::setDynEmissionRate(DynamicAttribute* dynEmissionRate)
{
    if (_dynEmissionRate)
        delete _dynEmissionRate;

    _dynEmissionRate = dynEmissionRate;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynTotalTimeToLive(DynamicAttribute* dynTotalTimeToLive)
{
    if (_dynTotalTimeToLive)
        delete _dynTotalTimeToLive;

    _dynTotalTimeToLive = dynTotalTimeToLive;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleMass(DynamicAttribute* dynParticleMass)
{
    if (_dynParticleMass)
        delete _dynParticleMass;

    _dynParticleMass = dynParticleMass;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynAngle(DynamicAttribute* dynAngle)
{
    if (_dynAngle)
        delete _dynAngle;

    _dynAngle = dynAngle;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynVelocity(DynamicAttribute* dynVelocity)
{
    if (_dynVelocity)
        delete _dynVelocity;

    _dynVelocity = dynVelocity;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynDuration(DynamicAttribute* dynDuration)
{
    if (_dynDuration)
        delete _dynDuration;

    _dynDuration = dynDuration;
    _dynDurationSet = true;
    initTimeBased();
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynDurationSet(bool durationSet)
{
    _dynDurationSet = durationSet;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynRepeatDelay(DynamicAttribute* dynRepeatDelay)
{
    if (_dynRepeatDelay)
        delete _dynRepeatDelay;

    _dynRepeatDelay = dynRepeatDelay;
    _dynRepeatDelaySet = true;
    initTimeBased();
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynRepeatDelaySet(bool repeatDelaySet)
{
    _dynRepeatDelaySet = repeatDelaySet;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleAllDimensions(DynamicAttribute* dynParticleAllDimensions)
{
    if (_dynParticleAllDimensions)
        delete _dynParticleAllDimensions;

    _dynParticleAllDimensions = dynParticleAllDimensions;
    _dynParticleAllDimensionsSet = true;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleAllDimensionsSet(bool particleAllDimensionsSet)
{
    _dynParticleAllDimensionsSet = particleAllDimensionsSet;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleWidth(DynamicAttribute* dynParticleWidth)
{
    if (_dynParticleWidth)
        delete _dynParticleWidth;

    _dynParticleWidth = dynParticleWidth;
    _dynParticleWidthSet = true;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleWidthSet(bool particleWidthSet)
{
    _dynParticleWidthSet = particleWidthSet;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleHeight(DynamicAttribute* dynParticleHeight)
{
    if (_dynParticleHeight)
        delete _dynParticleHeight;

    _dynParticleHeight = dynParticleHeight;
    _dynParticleHeightSet = true;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleHeightSet(bool particleHeightSet)
{
    _dynParticleHeightSet = particleHeightSet;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleDepth(DynamicAttribute* dynParticleDepth)
{
    if (_dynParticleDepth)
        delete _dynParticleDepth;

    _dynParticleDepth = dynParticleDepth;
    _dynParticleDepthSet = true;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setDynParticleDepthSet(bool particleDepthSet)
{
    _dynParticleDepthSet = particleDepthSet;
}
//-----------------------------------------------------------------------
const Vec3& Particle3DEmitter::getParticleDirection(void)
{
    return _particleDirection;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleDirection(const Vec3& direction)
{
    _particleDirection = direction;
    _originalParticleDirection = direction;
    _particleDirection.normalize();

    //temp method to implement perpendicular function
    //_upVector = _particleDirection.perpendicular();
    //_upVector.normalize();
    {
        static const float fSquareZero = (float)(1e-06 * 1e-06);
        Vec3 perp;
        Vec3::cross(_particleDirection, Vec3::UNIT_X, &perp);
        // Check length
        if( perp.lengthSquared() < fSquareZero )
        {
            /* This vector is the Y axis multiplied by a scalar, so we have
                to use another axis.
            */
            Vec3::cross(_particleDirection, Vec3::UNIT_Y, &perp);
        }
        perp.normalize();
        _upVector = perp;
    }
}
//-----------------------------------------------------------------------
const Vec3& Particle3DEmitter::getOriginalParticleDirection(void) const
{
    return _originalParticleDirection;
}
//-----------------------------------------------------------------------
const Quaternion& Particle3DEmitter::getParticleOrientation(void) const
{
    return _particleOrientation;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleOrientation(const Quaternion& orientation)
{
    _particleOrientation = orientation;
}
//-----------------------------------------------------------------------
const Quaternion& Particle3DEmitter::getParticleOrientationRangeStart(void) const
{
    return _particleOrientationRangeStart;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleOrientationRangeStart(const Quaternion& orientationRangeStart)
{
    _particleOrientationRangeStart = orientationRangeStart;
    _particleOrientationRangeSet = true;
}
//-----------------------------------------------------------------------
const Quaternion& Particle3DEmitter::getParticleOrientationRangeEnd(void) const
{
    return _particleOrientationRangeEnd;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setParticleOrientationRangeEnd(const Quaternion& orientationRangeEnd)
{
    _particleOrientationRangeEnd = orientationRangeEnd;
    _particleOrientationRangeSet = true;
}
//-----------------------------------------------------------------------
bool Particle3DEmitter::isAutoDirection(void) const
{
    return _autoDirection;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setAutoDirection(bool autoDirection)
{
    _autoDirection = autoDirection;
}
//-----------------------------------------------------------------------
bool Particle3DEmitter::isForceEmission(void) const
{
    return _forceEmission;
}
//-----------------------------------------------------------------------
void Particle3DEmitter::setForceEmission(bool forceEmission)
{
    _forceEmission = forceEmission;
    _originalForceEmission = forceEmission;
    _forceEmissionExecuted = false;
    _originalForceEmissionExecuted = false;
}

void Particle3DEmitter::initTimeBased( void )
{
    if (_isEnabled)
    {
        if (_dynDurationSet)
        {
            _durationRemain = _dynamicAttributeHelper.calculate(_dynDuration, _particleSystem->getTimeElapsedSinceStart());
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
            _repeatDelayRemain = _dynamicAttributeHelper.calculate(_dynRepeatDelay, _particleSystem->getTimeElapsedSinceStart());
        }
    }
}

void Particle3DEmitter::initParticleForEmission( Particle3D* particle )
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

void Particle3DEmitter::initParticleVelocity( Particle3D* particle )
{
    float scalar = _dynamicAttributeHelper.calculate(_dynVelocity, _particleSystem->getTimeElapsedSinceStart(), 1.0f);
    particle->direction *= scalar;
    particle->originalVelocity = scalar;
    particle->originalScaledDirectionLength = particle->direction.length();
}

void Particle3DEmitter::initParticleMass( Particle3D* particle )
{
    float mass = _dynamicAttributeHelper.calculate(_dynParticleMass, _particleSystem->getTimeElapsedSinceStart(), Particle3D::DEFAULT_MASS);
    particle->mass = mass;
}

void Particle3DEmitter::initParticleColor( Particle3D* particle )
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

void Particle3DEmitter::initParticleTextureCoords( Particle3D* particle )
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

float Particle3DEmitter::initParticleTimeToLive()
{
    return _dynamicAttributeHelper.calculate(_dynTotalTimeToLive, _particleSystem->getTimeElapsedSinceStart(), Particle3D::DEFAULT_TTL);
}

void Particle3DEmitter::initParticleDimensions( Particle3D* particle )
{
    // Only continue if one of them is set
    if (_dynParticleAllDimensionsSet || _dynParticleWidthSet || _dynParticleHeightSet || _dynParticleDepthSet)
    {
        // Set all dimensions equal ...
        float extend = 0;
        if (_dynParticleAllDimensionsSet && _dynParticleAllDimensions)
        {
            extend = _dynamicAttributeHelper.calculate(_dynParticleAllDimensions, _particleSystem->getTimeElapsedSinceStart());
            particle->setOwnDimensions(_emitterScale.x * extend, _emitterScale.y * extend, _emitterScale.z * extend);
            return;
        }

        // ... or set the dimensions independent from each other
        float width = 0;
        float height = 0;
        float depth = 0;
        if (_dynParticleWidthSet && _dynParticleWidth)
        {
            width = _dynamicAttributeHelper.calculate(_dynParticleWidth, _particleSystem->getTimeElapsedSinceStart());
        }
        if (_dynParticleHeightSet && _dynParticleHeight)
        {
            height = _dynamicAttributeHelper.calculate(_dynParticleHeight, _particleSystem->getTimeElapsedSinceStart());
        }
        if (_dynParticleDepthSet && _dynParticleDepth)
        {
            depth = _dynamicAttributeHelper.calculate(_dynParticleDepth, _particleSystem->getTimeElapsedSinceStart());
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
        particle->width = _emitterScale.x * _particleSystem->getDefaultWidth();
        particle->height = _emitterScale.y * _particleSystem->getDefaultHeight();
        particle->depth = _emitterScale.z * _particleSystem->getDefaultDepth();
        particle->calculateBoundingSphereRadius();
    }
}

NS_CC_END
