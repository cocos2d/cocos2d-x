/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_FLOCK_CENTER_AFFECTOR_TOKENS_H__
#define __PU_FLOCK_CENTER_AFFECTOR_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseForceAffectorTokens.h"

namespace ParticleUniverse
{
	/** The LinearForceAffectorTranslator parses 'LinearForceAffector' tokens
	*/
	class _ParticleUniverseExport LinearForceAffectorTranslator : public ScriptTranslator
	{
		public:
			LinearForceAffectorTranslator(void){};
			~LinearForceAffectorTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport LinearForceAffectorWriter : public BaseForceAffectorWriter
	{
		public:
			LinearForceAffectorWriter(void) {};
			virtual ~LinearForceAffectorWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
