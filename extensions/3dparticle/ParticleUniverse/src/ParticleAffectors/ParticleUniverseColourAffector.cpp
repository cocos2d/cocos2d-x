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

#include "ParticleAffectors/ParticleUniverseColourAffector.h"

namespace ParticleUniverse
{
	// Constants
	const ColourAffector::ColourOperation ColourAffector::DEFAULT_COLOUR_OPERATION = ColourAffector::CAO_SET;

	//-----------------------------------------------------------------------
	ColourAffector::ColourAffector(void) : 
		ParticleAffector(),
		mColourOperation(DEFAULT_COLOUR_OPERATION)
	{
	}
	//-----------------------------------------------------------------------
	void ColourAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		ColourAffector* colourAffector = static_cast<ColourAffector*>(affector);
		colourAffector->mColourMap = mColourMap;
		colourAffector->mColourOperation = mColourOperation;
	}
	//-----------------------------------------------------------------------
	const ColourAffector::ColourOperation& ColourAffector::getColourOperation (void) const
	{
		return mColourOperation;
	}
	//-----------------------------------------------------------------------
	void ColourAffector::setColourOperation (const ColourAffector::ColourOperation& colourOperation)
	{
		mColourOperation = colourOperation;
	}
	//-----------------------------------------------------------------------
	void ColourAffector::addColour (Real timeFraction, const ColourValue& colour)
	{
		mColourMap[timeFraction] = colour;
	}
    //-----------------------------------------------------------------------
	const ColourAffector::ColourMap& ColourAffector::getTimeAndColour(void) const
	{
		return mColourMap;
	}
	//-----------------------------------------------------------------------
	void ColourAffector::clearColourMap (void)
	{
		mColourMap.clear();
	}
	//-----------------------------------------------------------------------
	void ColourAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		// Fast rejection
		if (mColourMap.empty())
			return;

		// Only continue if the particle is a visual particle
		if (particle->particleType != Particle::PT_VISUAL)
			return;

		VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
		
		// Linear interpolation of the colour
		ColourValue colour = ColourValue::White;
		Real timeFraction = (visualParticle->totalTimeToLive - visualParticle->timeToLive) / visualParticle->totalTimeToLive;
		ColourMapIterator it1 = _findNearestColourMapIterator(timeFraction);
		ColourMapIterator it2 = it1;
		it2++;
		if (it2 != mColourMap.end())
		{
			// Interpolate colour
			colour = it1->second + ((it2->second - it1->second) * ((timeFraction - it1->first)/(it2->first - it1->first)));
		}
		else
		{
			colour = it1->second;
		}

		// Determine operation
		if (mColourOperation == CAO_SET)
		{
			// No operation, so just set the colour
			visualParticle->colour = colour;
		}
		else
		{
			// Multiply
			visualParticle->colour = colour * visualParticle->originalColour;
		}
	}
    //-----------------------------------------------------------------------
    ColourAffector::ColourMapIterator ColourAffector::_findNearestColourMapIterator(Real timeFraction)
    {
		ColourMapIterator it;
		for (it = mColourMap.begin(); it != mColourMap.end(); ++it)
		{
			if (timeFraction < it->first)
			{
				if (it == mColourMap.begin())
					return it;
				else
					return --it;
			}
		}

		// If not found return the last valid iterator
		return --it;
    }
}
