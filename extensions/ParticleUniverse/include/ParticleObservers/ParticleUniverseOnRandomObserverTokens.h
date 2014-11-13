/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONRANDOM_OBSERVER_TOKENS_H__
#define __PU_ONRANDOM_OBSERVER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverTokens.h"

namespace ParticleUniverse
{
	/** The OnRandomObserverTranslator parses 'OnRandomObserver' tokens
	*/
	class _ParticleUniverseExport OnRandomObserverTranslator : public ScriptTranslator
	{
		public:
			OnRandomObserverTranslator(void){};
			~OnRandomObserverTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport OnRandomObserverWriter : public ParticleObserverWriter
	{
		public:

			OnRandomObserverWriter(void) {};
			virtual ~OnRandomObserverWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
