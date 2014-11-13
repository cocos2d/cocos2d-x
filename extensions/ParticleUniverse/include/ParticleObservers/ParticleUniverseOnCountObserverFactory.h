/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONCOUNT_OBSERVER_FACTORY_H__
#define __PU_ONCOUNT_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnCountObserverTokens.h"
#include "ParticleUniverseOnCountObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnCountObserver.
    */
	class _ParticleUniverseExport OnCountObserverFactory : public ParticleObserverFactory
	{
		public:
			OnCountObserverFactory(void) {};
	        virtual ~OnCountObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnCount";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnCountObserver>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnCountObserverTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnCountObserverTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnCountObserverWriter.write(serializer, element);
			}

		protected:
			OnCountObserverWriter mOnCountObserverWriter;
			OnCountObserverTranslator mOnCountObserverTranslator;
	};

}
#endif
