/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONTIME_OBSERVER_FACTORY_H__
#define __PU_ONTIME_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnTimeObserverTokens.h"
#include "ParticleUniverseOnTimeObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnTimeObserver.
    */
	class _ParticleUniverseExport OnTimeObserverFactory : public ParticleObserverFactory
	{
		public:
			OnTimeObserverFactory(void) {};
	        virtual ~OnTimeObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnTime";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnTimeObserver>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnTimeObserverTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mOnTimeObserverTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnTimeObserverWriter.write(serializer, element);
			}


		protected:
			OnTimeObserverWriter mOnTimeObserverWriter;
			OnTimeObserverTranslator mOnTimeObserverTranslator;
	};

}
#endif
