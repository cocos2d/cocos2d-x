/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONEVENTFLAG_OBSERVER_FACTORY_H__
#define __PU_ONEVENTFLAG_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnEventFlagObserverTokens.h"
#include "ParticleUniverseOnEventFlagObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnEventFlagObserver.
    */
	class _ParticleUniverseExport OnEventFlagObserverFactory : public ParticleObserverFactory
	{
		public:
			OnEventFlagObserverFactory(void) {};
	        virtual ~OnEventFlagObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnEventFlag";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnEventFlagObserver>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnEventFlagObserverTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnEventFlagObserverTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnEventFlagObserverWriter.write(serializer, element);
			}

		protected:
			OnEventFlagObserverWriter mOnEventFlagObserverWriter;
			OnEventFlagObserverTranslator mOnEventFlagObserverTranslator;
	};

}
#endif
