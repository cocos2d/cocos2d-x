/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SYSTEM_LISTENER_H__
#define __PU_SYSTEM_LISTENER_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/*  ParticleSystemListener establishes a channel between a ParticleSystem and some other object, which is a 
	    type of ParticleSystemListener.
	*/
	class _ParticleUniverseExport ParticleSystemListener
	{
		public:

			ParticleSystemListener(void) {};
			virtual ~ParticleSystemListener(void) {};

			/*  Callback function, called for all event types.
			*/
			virtual void handleParticleSystemEvent(ParticleSystem* particleSystem, ParticleUniverseEvent& particleUniverseEvent) = 0;

	};

}
#endif
