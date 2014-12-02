/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_SURFACE_EMITTER_TOKENS_H__
#define __PU_SPHERE_SURFACE_EMITTER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterTokens.h"

namespace ParticleUniverse
{
	/** The SphereSurfaceEmitterTranslator parses 'SphereSurfaceEmitter' tokens
	*/
	class _ParticleUniverseExport SphereSurfaceEmitterTranslator : public ScriptTranslator
	{
		public:
			SphereSurfaceEmitterTranslator(void){};
			~SphereSurfaceEmitterTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport SphereSurfaceEmitterWriter : public ParticleEmitterWriter
	{
		public:

			SphereSurfaceEmitterWriter(void) {};
			virtual ~SphereSurfaceEmitterWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
