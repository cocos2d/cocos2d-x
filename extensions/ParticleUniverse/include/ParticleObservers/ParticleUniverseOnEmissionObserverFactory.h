/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONEMISSION_OBSERVER_FACTORY_H__
#define __PU_ONEMISSION_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnEmissionObserver.h"
#include "ParticleUniverseOnEmissionObserverTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnEmissionObserver.
    */
	class _ParticleUniverseExport OnEmissionObserverFactory : public ParticleObserverFactory
	{
		public:
			OnEmissionObserverFactory(void) {};
	        virtual ~OnEmissionObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual String getObserverType(void) const
			{
				return "OnEmission";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnEmissionObserver>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mOnEmissionObserverWriter.write(serializer, element);
			}

		protected:
			OnEmissionObserverWriter mOnEmissionObserverWriter;
	};

}
#endif
