/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_EMITTER_TOKENS_H__
#define __PU_EMITTER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The EmitterTranslator parses 'emitter' tokens
	*/
	class _ParticleUniverseExport EmitterTranslator : public ScriptTranslator
	{
		protected:
			ParticleEmitter* mEmitter;
		public:
			EmitterTranslator(void);
			virtual ~EmitterTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** The ParticleEmitterWriter writes 'emitter' tokens
    */
	class _ParticleUniverseExport ParticleEmitterWriter : public ScriptWriter
	{
		public:

			ParticleEmitterWriter(void) {};
			virtual ~ParticleEmitterWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);

		protected:
	};

}
#endif
