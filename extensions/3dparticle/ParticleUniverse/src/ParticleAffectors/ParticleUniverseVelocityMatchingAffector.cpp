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

#include "ParticleAffectors/ParticleUniverseVelocityMatchingAffector.h"

namespace ParticleUniverse
{
	// Constants
	const Real VelocityMatchingAffector::DEFAULT_RADIUS = 100.0f;

	//-----------------------------------------------------------------------
	VelocityMatchingAffector::VelocityMatchingAffector(void) : 
		ParticleAffector(),
		mRadius(DEFAULT_RADIUS)
	{
	}
	//-----------------------------------------------------------------------
	Real VelocityMatchingAffector::getRadius(void) const
	{
		return mRadius;
	}
	//-----------------------------------------------------------------------
	void VelocityMatchingAffector::setRadius(Real radius)
	{
		mRadius = radius;
	}
	//-----------------------------------------------------------------------
	void VelocityMatchingAffector::_prepare(ParticleTechnique* particleTechnique)
	{
		// Activate spatial hashing
		particleTechnique->setSpatialHashingUsed(true);
	}
	//-----------------------------------------------------------------------
	void VelocityMatchingAffector::_unprepare(ParticleTechnique* particleTechnique)
	{
		// Activate spatial hashing
		particleTechnique->setSpatialHashingUsed(false);
	}
	//-----------------------------------------------------------------------
	void VelocityMatchingAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		// Determine neighbouring particles.
		SpatialHashTable<Particle*>* hashtable = particleTechnique->getSpatialHashTable();
		if (hashtable)
		{
			SpatialHashTable<Particle*>::HashTableCell cell = hashtable->getCell(particle->position);
			if (cell.empty())
				return;

			unsigned int size = static_cast<unsigned int>(cell.size());
			Vector3 sumDirection = Vector3::ZERO;
			Vector3 diff = Vector3::ZERO;
			unsigned int count = 0;
			for (unsigned int i = 0; i < size; ++i)
			{
				Particle* p = cell[i];

				// Don't check if it is the same particle
				if (particle != p)
				{
					// Validate whether the neighbouring particle is within range
					diff = p->position - particle->position;
					if (diff.length() < mRadius)
					{
						sumDirection += p->direction;
						count++;
					}
				}
			}

			// Adjust direction
			if (count > 0)
			{
				sumDirection /= (Real)count;
				particle->direction += (sumDirection - particle->direction) * timeElapsed;
			}
		}
	}
	//-----------------------------------------------------------------------
	void VelocityMatchingAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);
		VelocityMatchingAffector* velocityMatchingAffector = static_cast<VelocityMatchingAffector*>(affector);
		velocityMatchingAffector->mRadius = mRadius;
	}
}
