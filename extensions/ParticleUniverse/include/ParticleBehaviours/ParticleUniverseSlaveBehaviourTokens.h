/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SLAVE_BEHAVIOUR_TOKENS_H__
#define __PU_SLAVE_BEHAVIOUR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBehaviourTokens.h"

namespace ParticleUniverse
{
	/** 
    */
	class _ParticleUniverseExport SlaveBehaviourWriter : public ParticleBehaviourWriter
	{
		public:
			SlaveBehaviourWriter(void) {};
			virtual ~SlaveBehaviourWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
