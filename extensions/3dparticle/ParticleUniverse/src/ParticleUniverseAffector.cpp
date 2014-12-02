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

#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	// Constants
	const bool ParticleAffector::DEFAULT_ENABLED = true;
	const Vector3 ParticleAffector::DEFAULT_POSITION(0, 0, 0);
	const ParticleAffector::AffectSpecialisation ParticleAffector::DEFAULT_SPECIALISATION = ParticleAffector::AFSP_DEFAULT;

	//-----------------------------------------------------------------------
	ParticleAffector::ParticleAffector(void) :
		Particle(),
		IAlias(),
		IElement(),
		mParentTechnique(0),
		mName(StringUtil::BLANK),
		_mAffectorScale(Vector3::UNIT_SCALE),
		mAffectSpecialisation(ParticleAffector::AFSP_DEFAULT)
	{
		particleType = PT_AFFECTOR;
		mAliasType = AT_AFFECTOR;
	};
	//-----------------------------------------------------------------------
	void ParticleAffector::_notifyStart (void)
	{
		setEnabled(mOriginalEnabled);
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::_notifyRescaled(const Vector3& scale)
	{
		_mAffectorScale = scale;
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::_initForEmission(void)
	{
		// The affector itself is emitted.
		Particle::_initForEmission();

		// Emitting an affector is similar as starting one.
		_notifyStart();
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::_initForExpiration(ParticleTechnique* technique, Real timeElapsed)
	{
		// The affector itself is expired.
		Particle::_initForExpiration(technique, timeElapsed);

		// Expiring an affector is similar as stopping one.
		_notifyStop();
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::copyAttributesTo(ParticleAffector* affector)
	{
		copyParentAttributesTo(affector);
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::copyParentAttributesTo(ParticleAffector* affector)
	{
		// Copy Parent attributes
		Particle::copyAttributesTo(affector);

		affector->setName(mName);
		affector->mParentTechnique = mParentTechnique;
		affector->_mAffectorScale = _mAffectorScale;
		affector->mAffectSpecialisation = mAffectSpecialisation;
		affector->mExcludedEmitters = list<String>(mExcludedEmitters); // Use copy constructor
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::setParentTechnique(ParticleTechnique* parentTechnique)
	{
		mParentTechnique = parentTechnique;
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::_processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle)
	{
		// Call the _firstParticle() function if the first particle in the update loop is encountered.
		if (firstParticle)
		{
			// Perform a precalculation at the first particle
			_firstParticle(particleTechnique, particle, timeElapsed);
		}

		if (!mExcludedEmitters.empty() && particle->parentEmitter)
		{
			// Return if the emitter which emits this particle is part of the list
			String emitterName = particle->parentEmitter->getName();
			list<String>::iterator it;
			it = std::find(mExcludedEmitters.begin(), mExcludedEmitters.end(), emitterName);
			if (it != mExcludedEmitters.end())
			{
				return;
			}
		}

		_affect(particleTechnique, particle, timeElapsed);
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::addEmitterToExclude(const String& emitterName)
	{
		list<String>::iterator it;
		it = std::find(mExcludedEmitters.begin(), mExcludedEmitters.end(), emitterName);
		if (it == mExcludedEmitters.end())
		{
			mExcludedEmitters.push_back(emitterName);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::removeEmitterToExclude(const String& emitterName)
	{
		list<String>::iterator it;
		it = std::find(mExcludedEmitters.begin(), mExcludedEmitters.end(), emitterName);
		if (it != mExcludedEmitters.end())
		{
			mExcludedEmitters.erase(it);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleAffector::removeAllEmittersToExclude(void)
	{
		mExcludedEmitters.clear();
	}
	//-----------------------------------------------------------------------
	const list<String>& ParticleAffector::getEmittersToExclude(void) const
	{
		return mExcludedEmitters;
	}
	//-----------------------------------------------------------------------
	bool ParticleAffector::hasEmitterToExclude(const String& emitterName)
	{
		list<String>::iterator it;
		it = std::find(mExcludedEmitters.begin(), mExcludedEmitters.end(), emitterName);
		return (it != mExcludedEmitters.end());
	}
	//-----------------------------------------------------------------------
	const Vector3& ParticleAffector::getDerivedPosition(void)
	{
		if (mMarkedForEmission)
		{
			// Use the affector position, because it is emitted
			// If a particle is emitted, position and derived position are the same
			mDerivedPosition = position;
		}
		else
		{
			// Add the techniques' derived position
			mDerivedPosition = mParentTechnique->getDerivedPosition() + 
				mParentTechnique->getParentSystem()->getDerivedOrientation() * (_mAffectorScale * position);
		}
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	Real ParticleAffector::_calculateAffectSpecialisationFactor (const Particle* particle)
	{
		// Assume that particle->totalTimeToLive != 0, which is reasonable
		switch (mAffectSpecialisation)
		{
			case AFSP_DEFAULT:
				return 1.0f;
				break;

			// This means that older particles will be affected MORE than just emitted particles
			case AFSP_TTL_INCREASE:
				{
					if (particle)
					{
						return particle->timeFraction;
					}
					else
					{
						return 1.0f;
					}
				}
				break;

			// This means that older particles will be affected LESS than just emitted particles
			case AFSP_TTL_DECREASE:
				{
					if (particle)
					{
						return 1.0f - particle->timeFraction;
					}
					else
					{
						return 1.0f;
					}
				}
				break;

			default:
				return 1.0f;
				break;
		}
	}
}
