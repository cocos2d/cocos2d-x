/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONTIME_OBSERVER_TOKENS_H__
#define __PU_ONTIME_OBSERVER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverTokens.h"

namespace ParticleUniverse
{
	/** The OnTimeObserverTranslator parses 'OnTimeObserver' tokens
	*/
	class _ParticleUniverseExport OnTimeObserverTranslator : public ScriptTranslator
	{
		public:
			OnTimeObserverTranslator(void){};
			~OnTimeObserverTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport OnTimeObserverWriter : public ParticleObserverWriter
	{
		public:

			OnTimeObserverWriter(void) {};
			virtual ~OnTimeObserverWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
