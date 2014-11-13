/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONCLEAR_OBSERVER_FACTORY_H__
#define __PU_ONCLEAR_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnClearObserver.h"
#include "ParticleUniverseOnClearObserverTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnClearObserver.
    */
	class _ParticleUniverseExport OnClearObserverFactory : public ParticleObserverFactory
	{
		public:
			OnClearObserverFactory(void) {};
	        virtual ~OnClearObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnClear";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnClearObserver>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnClearObserverWriter.write(serializer, element);
			}

			protected:
				OnClearObserverWriter mOnClearObserverWriter;
	};

}
#endif
