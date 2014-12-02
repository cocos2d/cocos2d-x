/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONEXPIRE_OBSERVER_H__
#define __PU_ONEXPIRE_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether a Particle has been expired.
    */
	class _ParticleUniverseExport OnExpireObserver : public ParticleObserver
	{
		protected:

		public:
			OnExpireObserver(void) : ParticleObserver()
			{
			};
	        virtual ~OnExpireObserver(void) {};

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);
	};

}
#endif
