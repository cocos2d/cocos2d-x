/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONQUOTA_OBSERVER_FACTORY_H__
#define __PU_ONQUOTA_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnQuotaObserver.h"
#include "ParticleUniverseOnQuotaObserverTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnQuotaObserver.
    */
	class _ParticleUniverseExport OnQuotaObserverFactory : public ParticleObserverFactory
	{
		public:
			OnQuotaObserverFactory(void) {};
	        virtual ~OnQuotaObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnQuota";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnQuotaObserver>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnQuotaObserverWriter.write(serializer, element);
			}

		protected:
			OnQuotaObserverWriter mOnQuotaObserverWriter;
	};

}
#endif
