/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ENTITY_RENDERER_TOKENS_H__
#define __PU_ENTITY_RENDERER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererTokens.h"

namespace ParticleUniverse
{
	/** The EntityRendererTranslator parses 'EntityRenderer' tokens
	*/
	class _ParticleUniverseExport EntityRendererTranslator : public ScriptTranslator
	{
		public:
			EntityRendererTranslator(void){};
			~EntityRendererTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport EntityRendererWriter : public ParticleRendererWriter
	{
		protected:

		public:

			EntityRendererWriter(void) {};
			virtual ~EntityRendererWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
