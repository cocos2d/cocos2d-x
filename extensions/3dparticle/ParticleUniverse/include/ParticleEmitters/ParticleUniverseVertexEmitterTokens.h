/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_VERTEX_EMITTER_TOKEN_H__
#define __PU_VERTEX_EMITTER_TOKEN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterTokens.h"

namespace ParticleUniverse
{
	/** The VertexEmitterTranslator parses 'VertexEmitter' tokens
	*/
	class _ParticleUniverseExport VertexEmitterTranslator : public ScriptTranslator
	{
		public:
			VertexEmitterTranslator(void){};
			~VertexEmitterTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport VertexEmitterWriter : public ParticleEmitterWriter
	{
		public:

			VertexEmitterWriter(void) {};
			virtual ~VertexEmitterWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
