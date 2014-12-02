/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_TOKENS_H__
#define __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandlerTokens.h"

namespace ParticleUniverse
{
	/** The DoPlacementParticleEventHandlerTranslator parses 'DoPlacementParticleEventHandler' tokens
	*/
	class _ParticleUniverseExport DoPlacementParticleEventHandlerTranslator : public ScriptTranslator
	{
		public:
			DoPlacementParticleEventHandlerTranslator(void){};
			~DoPlacementParticleEventHandlerTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport DoPlacementParticleEventHandlerWriter : public ParticleEventHandlerWriter
	{
		public:

			DoPlacementParticleEventHandlerWriter(void) {};
			virtual ~DoPlacementParticleEventHandlerWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
