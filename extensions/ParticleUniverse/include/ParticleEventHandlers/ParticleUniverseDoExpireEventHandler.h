/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DOEXPIRE_EVENT_HANDLER_H__
#define __PU_DOEXPIRE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"

namespace ParticleUniverse
{
	/** The DoExpireEventHandler expires a particle.
    */
	class _ParticleUniverseExport DoExpireEventHandler : public ParticleEventHandler
	{
		protected:

		public:
			DoExpireEventHandler(void) : ParticleEventHandler()
			{
			};
	        virtual ~DoExpireEventHandler(void) {};

			/** Get indication that all particles are expired
	        */
			bool getExpireAll(void);

			/** Set indication that all particles are expired
	        */
			void setExpireAll(bool expireAll);

			/** 
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);
	};

}
#endif
