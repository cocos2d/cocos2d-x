/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#include "CCPULineEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUUtil.h"

NS_CC_BEGIN
// Constants
const Vec3 PULineEmitter::DEFAULT_END(0, 0, 0);
const float PULineEmitter::DEFAULT_MIN_INCREMENT = 0.0f;
const float PULineEmitter::DEFAULT_MAX_INCREMENT = 0.0f;
const float PULineEmitter::DEFAULT_MAX_DEVIATION = 0.0f;

//-----------------------------------------------------------------------
PULineEmitter::PULineEmitter(void) : 
    PUEmitter(),
    _end(DEFAULT_END),
    _maxDeviation(DEFAULT_MAX_DEVIATION),
    _minIncrement(DEFAULT_MIN_INCREMENT),
    _maxIncrement(DEFAULT_MAX_INCREMENT),
    _increment(0.0f),
    _length(0.0f),
    _incrementsLeft(true),
    _first(true),
    _scaledMaxDeviation(0.0f),
    _scaledMinIncrement(0.0f),
    _scaledMaxIncrement(0.0f),
    _scaledLength(0.0f)
{
}
//-----------------------------------------------------------------------
void PULineEmitter::notifyStart (void)
{
    // Reset the incremental attributes to allow a restart.
    PUEmitter::notifyStart();
    _increment = 0.0f;
    _incrementsLeft = true;
    _first = true;
}
//-----------------------------------------------------------------------
void PULineEmitter::notifyRescaled(const Vec3& scale)
{
    // Scale the internal attributes and use them, otherwise this results in too many calculations per particle
    PUEmitter::notifyRescaled(scale);
    float scaleLength = scale.length();
    _scaledEnd.set(_end.x * scale.x, _end.y * scale.y, _end.z * scale.z);
    _scaledMaxDeviation = _maxDeviation * scaleLength;
    _scaledMinIncrement = _minIncrement * scaleLength;
    _scaledMaxIncrement = (_maxIncrement - _minIncrement) * scaleLength;
    _scaledLength = _scaledEnd.length();
}
//-----------------------------------------------------------------------
unsigned short PULineEmitter::calculateRequestedParticles(float timeElapsed)
{
    unsigned short requested = PUEmitter::calculateRequestedParticles(timeElapsed);

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
const Vec3& PULineEmitter::getEnd(void) const
{
    return _end;
}
//-----------------------------------------------------------------------
void PULineEmitter::setEnd(const Vec3& end)
{
    _end = end;
    _scaledEnd.set(_end.x * _emitterScale.x, _end.y * _emitterScale.y, _end.z * _emitterScale.z);
    _length = _end.length();
}
//-----------------------------------------------------------------------
float PULineEmitter::getMaxIncrement(void) const
{
    return _maxIncrement;
}
//-----------------------------------------------------------------------
void PULineEmitter::setMaxIncrement(float maxIncrement)
{
    _maxIncrement = maxIncrement;
    _scaledMaxIncrement = _maxIncrement * _emitterScale.length();
}
//-----------------------------------------------------------------------
float PULineEmitter::getMinIncrement(void) const
{
    return _minIncrement;
}
//-----------------------------------------------------------------------
void PULineEmitter::setMinIncrement(float minIncrement)
{
    _minIncrement = minIncrement;
    _scaledMinIncrement = _minIncrement * _emitterScale.length();
}
//-----------------------------------------------------------------------
float PULineEmitter::getMaxDeviation(void) const
{
    return _maxDeviation;
}
//-----------------------------------------------------------------------
void PULineEmitter::setMaxDeviation(float maxDeviation)
{
    _maxDeviation = maxDeviation;
    _scaledMaxDeviation = _maxDeviation * _emitterScale.length();
}
//-----------------------------------------------------------------------
void PULineEmitter::initParticlePosition(PUParticle3D* particle)
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
void PULineEmitter::initParticleDirection(PUParticle3D* particle)
{
    if (_autoDirection)
    {
        float angle = 0.0f;
        generateAngle(angle);
        if (angle != 0.0f)
        {
            //particle->direction = _perpendicular.randomDeviant(angle, mUpVector);
            particle->direction = PUUtil::randomDeviant(_perpendicular, angle, _upVector);
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
        PUEmitter::initParticleDirection(particle);
    }
}

PULineEmitter* PULineEmitter::create()
{
    auto pe = new (std::nothrow) PULineEmitter();
    pe->autorelease();
    return pe;
}

void PULineEmitter::copyAttributesTo( PUEmitter* emitter )
{
    PUEmitter::copyAttributesTo(emitter);

    PULineEmitter* lineEmitter = static_cast<PULineEmitter*>(emitter);
    lineEmitter->setEnd(_end); // Force calculation of the length
    lineEmitter->_length = _length;
    lineEmitter->setMinIncrement(_minIncrement);
    lineEmitter->setMaxIncrement(_maxIncrement);
    lineEmitter->setMaxDeviation(_maxDeviation);
}

PULineEmitter* PULineEmitter::clone()
{
    auto be = PULineEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END