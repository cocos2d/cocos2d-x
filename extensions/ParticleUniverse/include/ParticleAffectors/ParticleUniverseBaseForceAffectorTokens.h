/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BASE_ATTRACTOR_TOKENS_H__
#define __PU_BASE_ATTRACTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** The BaseForceAffectorTranslator parses 'BaseForceAffector' tokens
	*/
	class _ParticleUniverseExport BaseForceAffectorTranslator : public ScriptTranslator
	{
		public:
			BaseForceAffectorTranslator(void){};
			~BaseForceAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport BaseForceAffectorWriter : public ParticleAffectorWriter
	{
		public:

			BaseForceAffectorWriter(void) {};
			virtual ~BaseForceAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
