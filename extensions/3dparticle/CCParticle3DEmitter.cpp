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

Particle3DEmitter::Particle3DEmitter()
: _particleSystem(nullptr)
, _dynAngle(nullptr)
{
    
}

Particle3DEmitter::~Particle3DEmitter()
{
    _particleSystem = nullptr;
}

void Particle3DEmitter::updateEmitter(float deltaTime)
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
    if (_ParticleOrientationRangeSet)
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
        //FIXME
        //particle->direction = _particleDirection.randomDeviant(angle, _upVector);
    }
    else
    {
        particle->direction = _particleDirection;
    }
    particle->originalDirection = particle->direction;
    particle->originalDirectionLength = particle->direction.length();
}

void Particle3DEmitter::generateAngle( float angle )
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
    //if (mEnabled)
    //{
    //	if (mDynEmissionRate && mParentTechnique && mParentTechnique->getParentSystem())
    //	{
    //		Real rate = mDynEmissionRate->getValue(mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
    //		if (mEmissionRateCameraDependency)
    //		{
    //			// Affect the emission rate based on the camera distance
    //			mEmissionRateCameraDependency->affect(rate, mParentTechnique->getCameraSquareDistance());
    //		}
    //		if (mForceEmission)
    //		{
    //			if (mForceEmissionExecuted)
    //			{
    //				// It is a single-shot system, so there is nothing left anymore.
    //				requestedParticles = 0;
    //			}
    //			else
    //			{
    //				// Ignore the time. Just emit everything at once (if you absolutely need it).
    //				// The emitter cannot be disabled yet, because it needs to emit its particles first.
    //				requestedParticles = (unsigned short)rate;
    //				mForceEmissionExecuted = true;
    //			}
    //		}
    //		else
    //		{
    //			// Particle emission is time driven
    //			mRemainder += rate * timeElapsed;
    //			requestedParticles = (unsigned short)mRemainder;
    //		}

    //		mRemainder -= requestedParticles;
    //	}

    //	// Determine whether the duration period has been exceeded.
    //	if (mDynDurationSet)
    //	{
    //		mDurationRemain -= timeElapsed;
    //		if (mDurationRemain <= 0)
    //		{
    //			setEnabled(false);
    //		}
    //	}
    //}
    //else if (mDynRepeatDelaySet)
    //{
    //	mRepeatDelayRemain -= timeElapsed;
    //	if (mRepeatDelayRemain <= 0)
    //	{
    //		// Initialise again (if stopfade isn't set)
    //		if (mParentTechnique)
    //		{
    //			if (!mParentTechnique->isStopFade())
    //			{
    //				setEnabled(true);
    //			}
    //		}
    //		else
    //		{
    //			setEnabled(true);
    //		}
    //	}
    //}

    return requestedParticles;
}

void Particle3DEmitter::setEnabled( bool enabled )
{
    _isEnabled = enabled;
}

void Particle3DEmitter::notifyStart()
{

}

void Particle3DEmitter::notifyRescaled( const Vec3& scale )
{

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

void Particle3DEmitter::preUpdateAffector( float deltaTime )
{

}

void Particle3DEmitter::postUpdateAffector( float deltaTime )
{

}

NS_CC_END
