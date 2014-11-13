/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONRANDOM_OBSERVER_FACTORY_H__
#define __PU_ONRANDOM_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnRandomObserverTokens.h"
#include "ParticleUniverseOnRandomObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnRandomObserver.
    */
	class _ParticleUniverseExport OnRandomObserverFactory : public ParticleObserverFactory
	{
		public:
			OnRandomObserverFactory(void) {};
	        virtual ~OnRandomObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnRandom";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnRandomObserver>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnRandomObserverTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnRandomObserverTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnRandomObserverWriter.write(serializer, element);
			}

		protected:
			OnRandomObserverWriter mOnRandomObserverWriter;
			OnRandomObserverTranslator mOnRandomObserverTranslator;
	};

}
#endif
