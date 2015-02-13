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

#include "CCPUParticle3DLineEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DUtil.h"

NS_CC_BEGIN
// Constants
const Vec3 PUParticle3DLineEmitter::DEFAULT_END(0, 0, 0);
const float PUParticle3DLineEmitter::DEFAULT_MIN_INCREMENT = 0.0f;
const float PUParticle3DLineEmitter::DEFAULT_MAX_INCREMENT = 0.0f;
const float PUParticle3DLineEmitter::DEFAULT_MAX_DEVIATION = 0.0f;

//-----------------------------------------------------------------------
PUParticle3DLineEmitter::PUParticle3DLineEmitter(void) : 
    PUParticle3DEmitter(),
    _end(DEFAULT_END),
    _perpendicular(Vec3::ZERO),
    _maxDeviation(DEFAULT_MAX_DEVIATION),
    _minIncrement(DEFAULT_MIN_INCREMENT),
    _maxIncrement(DEFAULT_MAX_INCREMENT),
    _increment(0.0f),
    _length(0.0f),
    _incrementsLeft(true),
    _first(true),
    _scaledEnd(Vec3::ZERO),
    _scaledMaxDeviation(0.0f),
    _scaledMinIncrement(0.0f),
    _scaledMaxIncrement(0.0f),
    _scaledLength(0.0f)
{
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::notifyStart (void)
{
    // Reset the incremental attributes to allow a restart.
    PUParticle3DEmitter::notifyStart();
    _increment = 0.0f;
    _incrementsLeft = true;
    _first = true;
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::notifyRescaled(const Vec3& scale)
{
    // Scale the internal attributes and use them, otherwise this results in too many calculations per particle
    PUParticle3DEmitter::notifyRescaled(scale);
    float scaleLength = scale.length();
    _scaledEnd = Vec3(_end.x * scale.x, _end.y * scale.y, _end.z * scale.z);
    _scaledMaxDeviation = _maxDeviation * scaleLength;
    _scaledMinIncrement = _minIncrement * scaleLength;
    _scaledMaxIncrement = (_maxIncrement - _minIncrement) * scaleLength;
    _scaledLength = _scaledEnd.length();
}
//-----------------------------------------------------------------------
unsigned short PUParticle3DLineEmitter::calculateRequestedParticles(float timeElapsed)
{
    unsigned short requested = PUParticle3DEmitter::calculateRequestedParticles(timeElapsed);

    if (_scaledMaxIncrement > 0)
    {
        // Do not create particles if there are no increments left
        if (!_incrementsLeft)
        {
            // Set back to 0 again
            requested = 0;
        }

        ////FIXME
        //// For duration + repeat/delay: Clear the particles and start all over again.
        //if (!_isEnabled)
        //{
        //	notifyStart();
        //	mParentTechnique->lockAllParticles(); // Needed to set the first generated particle also first in the list with particles
        //}
    }

    return requested;
}
//-----------------------------------------------------------------------
const Vec3& PUParticle3DLineEmitter::getEnd(void) const
{
    return _end;
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::setEnd(const Vec3& end)
{
    _end = end;
    _scaledEnd = Vec3(_end.x * _emitterScale.x, _end.y * _emitterScale.y, _end.z * _emitterScale.z);
    _length = _end.length();
}
//-----------------------------------------------------------------------
float PUParticle3DLineEmitter::getMaxIncrement(void) const
{
    return _maxIncrement;
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::setMaxIncrement(float maxIncrement)
{
    _maxIncrement = maxIncrement;
    _scaledMaxIncrement = _maxIncrement * _emitterScale.length();
}
//-----------------------------------------------------------------------
float PUParticle3DLineEmitter::getMinIncrement(void) const
{
    return _minIncrement;
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::setMinIncrement(float minIncrement)
{
    _minIncrement = minIncrement;
    _scaledMinIncrement = _minIncrement * _emitterScale.length();
}
//-----------------------------------------------------------------------
float PUParticle3DLineEmitter::getMaxDeviation(void) const
{
    return _maxDeviation;
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::setMaxDeviation(float maxDeviation)
{
    _maxDeviation = maxDeviation;
    _scaledMaxDeviation = _maxDeviation * _emitterScale.length();
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::initParticlePosition(PUParticle3D* particle)
{
    // Remark: Don't take the orientation of the node into account. The mEnd position is leading.
    if (_autoDirection || (_scaledMaxDeviation > 0.0f && !_first))
    {
        // Generate a random vector perpendicular on the line if this is required
        Vec3::cross(_end, Vec3(CCRANDOM_MINUS1_1(), 
            CCRANDOM_MINUS1_1(), 
            CCRANDOM_MINUS1_1()), &_perpendicular);
        _perpendicular.normalize();
    }

    // If mMaxIncrement has been set, the particle emission follows a trajectory path along the line
    float fraction = 0.0f;
    if (_scaledMaxIncrement > 0.0f)
    {
        if (!_first)
        {
            _increment += (_scaledMinIncrement + CCRANDOM_0_1() * _scaledMaxIncrement);
            if (_increment >= _scaledLength)
            {
                _incrementsLeft = false;
            }
            fraction = _increment / _scaledLength;
        }
    }
    else
    {
        fraction = CCRANDOM_0_1();
    }

    // If the deviation has been set, generate a position with a certain distance from the line
    getDerivedPosition();
    if (_scaledMaxDeviation > 0.0f && _incrementsLeft)
    {
        if (!_first)
        {
            Vec3 basePosition = _derivedPosition + fraction * _scaledEnd;
            particle->position = basePosition + _scaledMaxDeviation * CCRANDOM_0_1() * _perpendicular;
            particle->originalPosition = basePosition;	// Position is without deviation from the line,
            // to make affectors a bit faster/easier.
        }
        else
        {
            particle->position = _derivedPosition;
            particle->originalPosition = particle->position;
        }
    }
    else
    {
        particle->position = _derivedPosition + fraction * _scaledEnd;
        particle->originalPosition = particle->position;
    }

    _first = false;
}
//-----------------------------------------------------------------------
void PUParticle3DLineEmitter::initParticleDirection(PUParticle3D* particle)
{
    if (_autoDirection)
    {
        float angle = 0.0f;
        generateAngle(angle);
        if (angle != 0.0f)
        {
            //particle->direction = _perpendicular.randomDeviant(angle, mUpVector);
            particle->direction = PUParticle3DUtil::randomDeviant(_perpendicular, angle, _upVector);
            particle->originalDirection = particle->direction;
        }
        else
        {
            particle->direction = _perpendicular;
            particle->originalDirection = particle->direction;
        }
    }
    else
    {
        // Use the standard way
        PUParticle3DEmitter::initParticleDirection(particle);
    }
}

PUParticle3DLineEmitter* PUParticle3DLineEmitter::create()
{
    auto pe = new (std::nothrow) PUParticle3DLineEmitter();
    pe->autorelease();
    return pe;
}

NS_CC_END