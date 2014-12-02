/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONQUOTA_OBSERVER_H__
#define __PU_ONQUOTA_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether all particles or all particles of a specific type are emitted.
    */
	class _ParticleUniverseExport OnQuotaObserver : public ParticleObserver
	{
		protected:
			bool mResult;

		public:
			OnQuotaObserver(void) : ParticleObserver(),
				mResult(false)
			{
			};
	        virtual ~OnQuotaObserver(void) {};

			/** @copydoc ParticleObserver::_notifyStart */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleObserver::_notifyStart */
			virtual void _postProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);
	};

}
#endif
