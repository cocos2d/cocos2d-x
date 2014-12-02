/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BILLBOARD_RENDERER_TOKENS_H__
#define __PU_BILLBOARD_RENDERER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererTokens.h"

namespace ParticleUniverse
{
	/** The BillboardRendererTranslator parses 'BillboardRenderer' tokens
	*/
	class _ParticleUniverseExport BillboardRendererTranslator : public ScriptTranslator
	{
		public:
			BillboardRendererTranslator(void){};
			~BillboardRendererTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport BillboardRendererWriter : public ParticleRendererWriter
	{
		protected:

		public:

			BillboardRendererWriter(void) {};
			virtual ~BillboardRendererWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
