/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SLAVE_BEHAVIOUR_H__
#define __PU_SLAVE_BEHAVIOUR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBehaviour.h"
#include "ParticleUniverseTechniqueListener.h"

namespace ParticleUniverse
{
	/** The SlaveBehaviour makes the particle act as a slave, so it follows another particle to which it is related.
    */
	class _ParticleUniverseExport SlaveBehaviour : public ParticleBehaviour
	{
		protected:

		public:
			Particle* masterParticle;

			SlaveBehaviour(void);
	        virtual ~SlaveBehaviour(void){};

			/** See ParticleBehaviour.
	        */
			virtual void _processParticle(ParticleTechnique* technique, Particle* particle, Real timeElapsed);

			/** 
	        */
			virtual void copyAttributesTo (ParticleBehaviour* behaviour);
	};

}
#endif
