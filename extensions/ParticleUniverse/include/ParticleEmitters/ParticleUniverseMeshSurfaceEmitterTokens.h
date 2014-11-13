/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_MESH_SURFACE_EMITTER_TOKENS_H__
#define __PU_MESH_SURFACE_EMITTER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterTokens.h"

namespace ParticleUniverse
{
	/** The MeshSurfaceEmitterTranslator parses 'MeshSurfaceEmitter' tokens
	*/
	class _ParticleUniverseExport MeshSurfaceEmitterTranslator : public ScriptTranslator
	{
		public:
			MeshSurfaceEmitterTranslator(void){};
			~MeshSurfaceEmitterTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport MeshSurfaceEmitterWriter : public ParticleEmitterWriter
	{
		public:

			MeshSurfaceEmitterWriter(void) {};
			virtual ~MeshSurfaceEmitterWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
