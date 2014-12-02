/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SINE_FORCE_AFFECTOR_TOKENS_H__
#define __PU_SINE_FORCE_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseForceAffectorTokens.h"

namespace ParticleUniverse
{
	/** The SineForceAffectorTranslator parses 'SineForceAffector' tokens
	*/
	class _ParticleUniverseExport SineForceAffectorTranslator : public ScriptTranslator
	{
		public:
			SineForceAffectorTranslator(void){};
			~SineForceAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport SineForceAffectorWriter : public BaseForceAffectorWriter
	{
		public:

			SineForceAffectorWriter(void) {};
			virtual ~SineForceAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element);
	};

}
#endif
