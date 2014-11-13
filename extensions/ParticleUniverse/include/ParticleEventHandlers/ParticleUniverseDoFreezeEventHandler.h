/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DOFREEZE_EVENT_HANDLER_H__
#define __PU_DOFREEZE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"

namespace ParticleUniverse
{
	/** The DoFreezeEventHandler freezes a particle.
    */
	class _ParticleUniverseExport DoFreezeEventHandler : public ParticleEventHandler
	{
		protected:

		public:
			DoFreezeEventHandler(void) : ParticleEventHandler()
			{
			};
	        virtual ~DoFreezeEventHandler(void) {};

			/** 
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);
	};

}
#endif
