/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_FORCE_FIELD_AFFECTOR_TOKENS_H__
#define __PU_FORCE_FIELD_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseForceFieldAffectorTokens.h"

namespace ParticleUniverse
{
	/** The ForceFieldAffectorTranslator parses 'ForceFieldAffector' tokens
	*/
	class _ParticleUniverseExport ForceFieldAffectorTranslator : public ScriptTranslator
	{
		public:
			ForceFieldAffectorTranslator(void){};
			~ForceFieldAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport ForceFieldAffectorWriter : public ParticleAffectorWriter
	{
		public:

			ForceFieldAffectorWriter(void) {};
			virtual ~ForceFieldAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
