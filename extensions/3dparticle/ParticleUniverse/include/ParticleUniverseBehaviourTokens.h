/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_BEHAVIOUR_TOKENS_H__
#define __PU_PARTICLE_BEHAVIOUR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBehaviour.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** The BehaviourTranslator parses 'behaviour' tokens
	*/
	class _ParticleUniverseExport BehaviourTranslator : public ScriptTranslator
	{
		protected:
			ParticleBehaviour* mBehaviour;

		public:
			BehaviourTranslator(void);
			virtual ~BehaviourTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport ParticleBehaviourWriter : public ScriptWriter
	{
		public:

			ParticleBehaviourWriter(void) {};
			virtual ~ParticleBehaviourWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
