/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONRANDOM_OBSERVER_H__
#define __PU_ONRANDOM_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether a random generated number is within a specified interval.
    */
	class _ParticleUniverseExport OnRandomObserver : public ParticleObserver
	{
		protected:
			Real mThreshold; // Value between 0..1

		public:
			// Constants
			static const Real DEFAULT_THRESHOLD;

			OnRandomObserver(void);
	        virtual ~OnRandomObserver(void) {};

			/** See ParticleObserver::_preProcessParticles()
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Real timeElapsed);

			/** See ParticleObserver::_processParticle()
	        */
			virtual void _processParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed, bool firstParticle);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			Real getThreshold(void) const {return mThreshold;};
			void setThreshold(Real threshold){mThreshold = threshold;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
