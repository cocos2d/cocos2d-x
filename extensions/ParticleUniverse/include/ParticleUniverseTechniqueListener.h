/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TECHNIQUE_LISTENER_H__
#define __PU_TECHNIQUE_LISTENER_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/*  TechniqueListener establishes a channel between a ParticleTechnique and some other object, which is a 
	    type of TechniqueListener.
	*/
	class _ParticleUniverseExport TechniqueListener
	{
		public:
			TechniqueListener(void) {};
			virtual ~TechniqueListener(void) {};

			/*  Callback function, which is called as soon as a particle is emitted.
			*/
			virtual void particleEmitted(ParticleTechnique* particleTechnique, Particle* particle) = 0;

			/*  Callback function, which is called as soon as a particle is expired.
			*/
			virtual void particleExpired(ParticleTechnique* particleTechnique, Particle* particle) = 0;
	};

}
#endif
