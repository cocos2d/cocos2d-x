/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_RENDERER_TOKENS_H__
#define __PU_RENDERER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** The RendererSetTranslator parses 'Renderer Set' tokens
	*/
	class _ParticleUniverseExport RendererSetTranslator : public ScriptTranslator
	{
		public:
			RendererSetTranslator(void){};
			virtual ~RendererSetTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	/** The RendererTranslator parses 'Renderer' tokens
	*/
	class _ParticleUniverseExport RendererTranslator : public ScriptTranslator
	{
		protected:
			ParticleRenderer* mRenderer;

		public:
			RendererTranslator(void);
			virtual ~RendererTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	/** 
    */
	class _ParticleUniverseExport ParticleRendererWriter : public ScriptWriter
	{
		protected:

		public:

			ParticleRendererWriter(void) {};
			virtual ~ParticleRendererWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);

	};

}
#endif
