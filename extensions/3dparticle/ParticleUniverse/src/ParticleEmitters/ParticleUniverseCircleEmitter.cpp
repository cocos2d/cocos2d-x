/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleEmitters/ParticleUniverseCircleEmitter.h"

namespace ParticleUniverse
{
	// Constants
	const Real CircleEmitter::DEFAULT_RADIUS = 100.0f;
	const Real CircleEmitter::DEFAULT_STEP = 0.1f;
	const Real CircleEmitter::DEFAULT_ANGLE = 0.0f;
	const bool CircleEmitter::DEFAULT_RANDOM = true;
	const Vector3 CircleEmitter::DEFAULT_NORMAL(0, 0, 0);

	//-----------------------------------------------------------------------
	CircleEmitter::CircleEmitter(void) : 
		ParticleEmitter(),
		mRadius(DEFAULT_RADIUS),
		mCircleAngle(DEFAULT_ANGLE),
		mOriginalCircleAngle(DEFAULT_ANGLE),
		mStep(DEFAULT_STEP),
		mRandom(DEFAULT_RANDOM),
		mOrientation(Quaternion::IDENTITY),
		mNormal(DEFAULT_NORMAL),
		mX(0.0f),
		mZ(0.0f)
	{
	}
	//-----------------------------------------------------------------------
	const Real CircleEmitter::getRadius(void) const
	{
		return mRadius;
	}
	//-----------------------------------------------------------------------
	void CircleEmitter::setRadius(const Real radius)
	{
		mRadius = radius;
	}
	//-----------------------------------------------------------------------
	const Real CircleEmitter::getCircleAngle(void) const
	{
		return mOriginalCircleAngle;
	}
	//-----------------------------------------------------------------------
	void CircleEmitter::setCircleAngle(const Real circleAngle)
	{
		mOriginalCircleAngle = circleAngle;
		mCircleAngle = circleAngle;
	}
	//-----------------------------------------------------------------------
	const Real CircleEmitter::getStep(void) const
	{
		return mStep;
	}
	//-----------------------------------------------------------------------
	void CircleEmitter::setStep(const Real step)
	{
		mStep = step;
	}
	//-----------------------------------------------------------------------
	const bool CircleEmitter::isRandom(void) const
	{
		return mRandom;
	}
	//-----------------------------------------------------------------------
	void CircleEmitter::setRandom(const bool random)
	{
		mRandom = random;
	}
	//-----------------------------------------------------------------------
	const Quaternion& CircleEmitter::getOrientation(void) const
	{
		return mOrientation;
	}
	//----------------------------------------------------------------------- 
	const Vector3& CircleEmitter::getNormal(void) const
	{ 
		return mNormal;
	} 
	//----------------------------------------------------------------------- 
	void CircleEmitter::setNormal(const Vector3& normal) 
	{ 
		mOrientation = Vector3::UNIT_Y.getRotationTo(normal, Vector3::UNIT_X);
		mNormal = normal;
	}
	//-----------------------------------------------------------------------
	void CircleEmitter::_notifyStart (void)
	{
		// Reset the attributes to allow a restart.
		ParticleEmitter::_notifyStart();
		mCircleAngle = mOriginalCircleAngle;
	}
	//----------------------------------------------------------------------- 
	void CircleEmitter::_initParticlePosition(Particle* particle)
	{
		Real angle = 0;
		if (mRandom)
		{
			// Choose a random position on the circle.
			angle = Math::RangeRandom(0, Math::TWO_PI);
		}
		else
		{
			// Follow the contour of the circle.
			mCircleAngle += mStep;
			mCircleAngle = mCircleAngle > Math::TWO_PI ? mCircleAngle - Math::TWO_PI : mCircleAngle;
			angle = mCircleAngle;
		}

		mX = Math::Cos(angle);
		mZ = Math::Sin(angle);
		ParticleSystem* sys = mParentTechnique->getParentSystem();
		if (sys)
		{
			// Take both orientation of the node and its own orientation, based on the normal, into account
			particle->position = getDerivedPosition() + 
				sys->getDerivedOrientation() * mOrientation * (_mEmitterScale * Vector3(mX * mRadius, 0, mZ * mRadius));
		}
		else
		{
			particle->position = getDerivedPosition() + _mEmitterScale * ( mOrientation * Vector3(mX * mRadius, 0, mZ * mRadius) );
		}
		particle->originalPosition = particle->position;
	}
	//-----------------------------------------------------------------------
    void CircleEmitter::_initParticleDirection(Particle* particle)
    {
		if (mAutoDirection)
		{
			// The value of the direction vector that has been set does not have a meaning for
			// the circle emitter.
			Radian angle;
			_generateAngle(angle);
			if (angle != Radian(0))
			{
				particle->direction = (mOrientation * Vector3(mX, 0, mZ) ).randomDeviant(angle, mUpVector);
				particle->originalDirection = particle->direction;
			}
			else
			{
				particle->direction = Vector3(mX, 0, mZ);
				particle->direction = mOrientation * Vector3(mX, 0, mZ);
			}
		}
		else
		{
			// Use the standard way
			ParticleEmitter::_initParticleDirection(particle);
		}
    }
	//-----------------------------------------------------------------------
	void CircleEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);

		CircleEmitter* circleEmitter = static_cast<CircleEmitter*>(emitter);
		circleEmitter->mRadius = mRadius;
		circleEmitter->mCircleAngle = mCircleAngle;
		circleEmitter->mOriginalCircleAngle = mOriginalCircleAngle;
		circleEmitter->mStep = mStep;
		circleEmitter->mRandom = mRandom;
		circleEmitter->mNormal = mNormal;
		circleEmitter->mOrientation = mOrientation; 
	}
}
