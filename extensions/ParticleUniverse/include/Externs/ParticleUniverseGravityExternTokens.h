/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_GRAVITY_EXTERN_TOKENS_H__
#define __PU_GRAVITY_EXTERN_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExternTokens.h"
#include "ParticleUniverseAttachableTokens.h"

namespace ParticleUniverse
{
	/** The GravityExternTranslator parses 'GravityExtern' tokens
	*/
	class _ParticleUniverseExport GravityExternTranslator : public ScriptTranslator
	{
		public:
			GravityExternTranslator(void){};
			~GravityExternTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport GravityExternWriter : public AttachableWriter, ExternWriter
	{
		public:
			GravityExternWriter(void) {};
			virtual ~GravityExternWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
