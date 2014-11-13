/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONEVENTFLAG_OBSERVER_H__
#define __PU_ONEVENTFLAG_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** The OnEventFlagObserver looks at each particle is one or more eventflags are set.
    */
	class _ParticleUniverseExport OnEventFlagObserver : public ParticleObserver
	{
		protected:
			uint32 mEventFlag;

		public:
			// Constants
			static const uint32 DEFAULT_EVENT_FLAG;

			OnEventFlagObserver(void);
	        virtual ~OnEventFlagObserver(void) {};

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			uint32 getEventFlag(void) const {return mEventFlag;};
			void setEventFlag(uint32 eventFlag){mEventFlag = eventFlag;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
