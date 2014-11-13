/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CIRCLE_EMITTER_TOKEN_H__
#define __PU_CIRCLE_EMITTER_TOKEN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterTokens.h"

namespace ParticleUniverse
{
	/** The CircleEmitterTranslator parses 'CircleEmitter' tokens
	*/
	class _ParticleUniverseExport CircleEmitterTranslator : public ScriptTranslator
	{
		public:
			CircleEmitterTranslator(void){};
			~CircleEmitterTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport CircleEmitterWriter : public ParticleEmitterWriter
	{
		public:

			CircleEmitterWriter(void) {};
			virtual ~CircleEmitterWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
