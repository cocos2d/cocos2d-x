/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_EVENT_HANDLER_TOKENS_H__
#define __PU_PARTICLE_EVENT_HANDLER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** The ParticleEventHandlerTranslator parses 'ParticleEventHandler' tokens
	*/
	class _ParticleUniverseExport ParticleEventHandlerTranslator : public ScriptTranslator
	{
		protected:
			ParticleEventHandler* mParticleEventHandler;

		public:
			ParticleEventHandlerTranslator(void);
			virtual ~ParticleEventHandlerTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport ParticleEventHandlerWriter : public ScriptWriter
	{
		public:

			ParticleEventHandlerWriter(void) {};
			virtual ~ParticleEventHandlerWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
