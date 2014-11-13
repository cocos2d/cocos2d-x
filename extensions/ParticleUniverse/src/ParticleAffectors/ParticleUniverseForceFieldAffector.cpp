/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"
#include "ParticleAffectors/ParticleUniverseForceFieldAffector.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

namespace ParticleUniverse
{
	// Constants
	const ForceField::ForceFieldType ForceFieldAffector::DEFAULT_FORCEFIELD_TYPE = ForceField::FF_REALTIME_CALC;
	const Real ForceFieldAffector::DEFAULT_DELTA = 1.0f;
	const Real ForceFieldAffector::DEFAULT_FORCE = 400.0f;
	const ushort ForceFieldAffector::DEFAULT_OCTAVES = 2;
	const double ForceFieldAffector::DEFAULT_FREQUENCY = 1.0f;
	const double ForceFieldAffector::DEFAULT_AMPLITUDE = 1.0f;
	const double ForceFieldAffector::DEFAULT_PERSISTENCE = 3.0f;
	const unsigned int ForceFieldAffector::DEFAULT_FORCEFIELDSIZE = 64;
	const Vector3 ForceFieldAffector::DEFAULT_WORLDSIZE = Vector3(500.0f, 500.0f, 500.0f);
	const Vector3 ForceFieldAffector::DEFAULT_MOVEMENT = Vector3(500.0f, 0.0f, 0.0f);
	const Real ForceFieldAffector::DEFAULT_MOVEMENT_FREQUENCY = 5.0f;
	
	//-----------------------------------------------------------------------
	ForceFieldAffector::ForceFieldAffector(void) :
		mForceFieldType(ForceField::FF_REALTIME_CALC),
		mDelta(DEFAULT_DELTA),
		mForce(Vector3::ZERO),
		mScaleForce(DEFAULT_FORCE),
		mOctaves(DEFAULT_OCTAVES),
		mFrequency(DEFAULT_FREQUENCY),
		mAmplitude(DEFAULT_AMPLITUDE),
		mPersistence(DEFAULT_PERSISTENCE),
		mForceFieldSize(DEFAULT_FORCEFIELDSIZE),
		mWorldSize(DEFAULT_WORLDSIZE),
		mPrepared(true),
		mIgnoreNegativeX(false),
		mIgnoreNegativeY(false),
		mIgnoreNegativeZ(false),
		mMovement(DEFAULT_MOVEMENT),
		mMovementSet(false),
		mMovementFrequency(DEFAULT_MOVEMENT_FREQUENCY),
		mMovementFrequencyCount(0.0f),
		mDisplacement(Vector3::ZERO),
		mBasePosition(Vector3::ZERO),
		mSuppressGeneration(false)
	{
	};
	//-----------------------------------------------------------------------
	ForceFieldAffector::~ForceFieldAffector(void)
	{
	};
	//-----------------------------------------------------------------------
	void ForceFieldAffector::_prepare(ParticleTechnique* particleTechnique)
	{
		if (particleTechnique->getParentSystem())
		{
			// Forcefield position is same position as particle system position
			mForceField.initialise(mForceFieldType,
				particleTechnique->getParentSystem()->getDerivedPosition(),
				mForceFieldSize,
				mOctaves,
				mFrequency,
				mAmplitude,
				mPersistence,
				mWorldSize);

			mBasePosition = mForceField.getForceFieldPositionBase();
			mPrepared = true;
		}
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		if (mMovementSet)
		{
			if (timeElapsed > mMovementFrequency)
			{
				// Ignore too large times, because it just blows things up
				return;
			}

			mMovementFrequencyCount += timeElapsed;
			if (mMovementFrequencyCount > mMovementFrequency)
			{
				mMovementFrequencyCount -= mMovementFrequency;
			}

			mDisplacement = Math::Sin(Math::TWO_PI * mMovementFrequencyCount/mMovementFrequency) * mMovement;
			mForceField.setForceFieldPositionBase(mBasePosition + mDisplacement);
		}
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::_notifyStart(void)
	{
		ParticleAffector::_notifyStart();
		mMovementFrequencyCount = 0.0f;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		mForceField.determineForce(particle->position, mForce, mDelta);

		// If negative values are ignored, set the force to 0.
		if (mIgnoreNegativeX)
		{
			mForce.x = 0.0f;
		}
		if (mIgnoreNegativeY)
		{
			mForce.y = 0.0f;
		}
		if (mIgnoreNegativeZ)
		{
			mForce.z = 0.0f;
		}
		particle->direction += timeElapsed * mScaleForce * mForce;
	}
	//-----------------------------------------------------------------------
	const ForceField::ForceFieldType ForceFieldAffector::getForceFieldType(void) const
	{
		return mForceFieldType;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setForceFieldType(const ForceField::ForceFieldType forceFieldType)
	{
		mForceFieldType = forceFieldType;
		if (mSuppressGeneration)
			return;

		mForceField.setForceFieldType(forceFieldType);
	}
	//-----------------------------------------------------------------------
	Real ForceFieldAffector::getDelta(void) const
	{
		return mDelta;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setDelta(Real delta)
	{
		mDelta = delta;
	}
	//-----------------------------------------------------------------------
	Real ForceFieldAffector::getScaleForce(void) const
	{
		return mScaleForce;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setScaleForce(Real scaleForce)
	{
		mScaleForce = scaleForce;
	}
	//-----------------------------------------------------------------------
	ushort ForceFieldAffector::getOctaves(void) const
	{
		return mOctaves;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setOctaves(ushort octaves)
	{
		mOctaves = octaves;
		if (mSuppressGeneration)
			return;

		mForceField.setOctaves(octaves);
	}
	//-----------------------------------------------------------------------
	double ForceFieldAffector::getFrequency(void) const
	{
		return mFrequency;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setFrequency(double frequency)
	{
		mFrequency = frequency;
		if (mSuppressGeneration)
			return;

		mForceField.setFrequency(frequency);
	}
	//-----------------------------------------------------------------------
	double ForceFieldAffector::getAmplitude(void) const
	{
		return mAmplitude;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setAmplitude(double amplitude)
	{
		mAmplitude = amplitude;
		if (mSuppressGeneration)
			return;

		mForceField.setAmplitude(amplitude);
	}
	//-----------------------------------------------------------------------
	double ForceFieldAffector::getPersistence(void) const
	{
		return mPersistence;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setPersistence(double persistence)
	{
		mPersistence = persistence;
		if (mSuppressGeneration)
			return;

		mForceField.setPersistence(persistence);
	}
	//-----------------------------------------------------------------------
	unsigned int ForceFieldAffector::getForceFieldSize(void) const
	{
		return mForceFieldSize;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setForceFieldSize(unsigned int forceFieldSize)
	{
		mForceFieldSize = forceFieldSize;
		if (mSuppressGeneration)
			return;

		mForceField.setForceFieldSize(forceFieldSize);
	}
	//-----------------------------------------------------------------------
	Vector3 ForceFieldAffector::getWorldSize(void) const
	{
		return mWorldSize;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setWorldSize(const Vector3& worldSize)
	{
		mWorldSize = worldSize;
		if (mSuppressGeneration)
			return;

		mForceField.setWorldSize(worldSize);
	}
	//-----------------------------------------------------------------------
	bool ForceFieldAffector::getIgnoreNegativeX(void) const
	{
		return mIgnoreNegativeX;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setIgnoreNegativeX(bool ignoreNegativeX)
	{
		mIgnoreNegativeX = ignoreNegativeX;
	}
	//-----------------------------------------------------------------------
	bool ForceFieldAffector::getIgnoreNegativeY(void) const
	{
		return mIgnoreNegativeY;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setIgnoreNegativeY(bool ignoreNegativeY)
	{
		mIgnoreNegativeY = ignoreNegativeY;
	}
	//-----------------------------------------------------------------------
	bool ForceFieldAffector::getIgnoreNegativeZ(void) const
	{
		return mIgnoreNegativeZ;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setIgnoreNegativeZ(bool ignoreNegativeZ)
	{
		mIgnoreNegativeZ = ignoreNegativeZ;
	}
	//-----------------------------------------------------------------------
	Real ForceFieldAffector::getMovementFrequency(void) const
	{
		return mMovementFrequency;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setMovementFrequency(Real movementFrequency)
	{
		mMovementFrequency = movementFrequency;
		mMovementSet = (movementFrequency > 0.0f);
	}
	//-----------------------------------------------------------------------
	const Vector3& ForceFieldAffector::getMovement(void) const
	{
		return mMovement;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::setMovement(const Vector3& movement)
	{
		mMovement = movement;
		mMovementSet = (movement != Vector3::ZERO);
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::suppressGeneration(bool suppress)
	{
		mSuppressGeneration = suppress;
	}
	//-----------------------------------------------------------------------
	void ForceFieldAffector::copyAttributesTo(ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		ForceFieldAffector* forceFieldAffector = static_cast<ForceFieldAffector*>(affector);
		forceFieldAffector->mForceFieldType = mForceFieldType;
		forceFieldAffector->mDelta = mDelta;
		forceFieldAffector->mScaleForce = mScaleForce;
		forceFieldAffector->mOctaves = mOctaves;
		forceFieldAffector->mFrequency = mFrequency;
		forceFieldAffector->mAmplitude = mAmplitude;
		forceFieldAffector->mPersistence = mPersistence;
		forceFieldAffector->mForceFieldSize = mForceFieldSize;
		forceFieldAffector->mWorldSize = mWorldSize;
		forceFieldAffector->mIgnoreNegativeX = mIgnoreNegativeX;
		forceFieldAffector->mIgnoreNegativeY = mIgnoreNegativeY;
		forceFieldAffector->mIgnoreNegativeZ = mIgnoreNegativeZ;
		forceFieldAffector->mMovementSet = mMovementSet;
		forceFieldAffector->mMovementFrequency = mMovementFrequency;
		forceFieldAffector->mMovement = mMovement;
	}

}
