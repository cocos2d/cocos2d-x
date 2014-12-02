/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONPOSITION_OBSERVER_TOKENS_H__
#define __PU_ONPOSITION_OBSERVER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverTokens.h"

namespace ParticleUniverse
{
	/** The OnPositionObserverTranslator parses 'OnPositionObserver' tokens
	*/
	class _ParticleUniverseExport OnPositionObserverTranslator : public ScriptTranslator
	{
		public:
			OnPositionObserverTranslator(void){};
			~OnPositionObserverTranslator(void){};
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node);
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport OnPositionObserverWriter : public ParticleObserverWriter
	{
		public:

			OnPositionObserverWriter(void) {};
			virtual ~OnPositionObserverWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
