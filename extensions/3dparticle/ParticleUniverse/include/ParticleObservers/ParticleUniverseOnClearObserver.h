/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONCLEAR_OBSERVER_H__
#define __PU_ONCLEAR_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether all particles of a technique are no longer emitted.
    */
	class _ParticleUniverseExport OnClearObserver : public ParticleObserver
	{
		protected:
			bool mContinue;

		public:
			OnClearObserver(void) : ParticleObserver(),
				mContinue(false)
			{
			};
	        virtual ~OnClearObserver(void) {};

			/** 
	        */
			virtual void _notifyStart (void);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique,
				Particle* particle, 
				Real timeElapsed);

			/** The _processParticle() function is overridden, because we don´t observe an individual particle.
				even if there isn´t a particle left anymore (and that is the situation we want to validate).
	        */
			virtual void _processParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Real timeElapsed, 
				bool firstParticle);

			/** Instead of the _processParticle(), the _postProcessParticles() is used because it is called
				even if there isn´t a particle left anymore (and that is the situation we want to validate).
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Real timeElapsed);
	};

}
#endif
