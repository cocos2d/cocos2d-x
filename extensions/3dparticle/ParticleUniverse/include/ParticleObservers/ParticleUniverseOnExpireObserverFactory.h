/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONEXPIRE_OBSERVER_FACTORY_H__
#define __PU_ONEXPIRE_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnExpireObserver.h"
#include "ParticleUniverseOnExpireObserverTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnExpireObserver.
    */
	class _ParticleUniverseExport OnExpireObserverFactory : public ParticleObserverFactory
	{
		public:
			OnExpireObserverFactory(void) {};
	        virtual ~OnExpireObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnExpire";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnExpireObserver>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnExpireObserverWriter.write(serializer, element);
			};

		protected:
			OnExpireObserverWriter mOnExpireObserverWriter;
	};

}
#endif
