/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONTIME_OBSERVER_H__
#define __PU_ONTIME_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** The OnTimeObserver observers how much time has been elapsed. This can be both the particles own time
		and the time since the ParticleSystem was started.
    */
	class _ParticleUniverseExport OnTimeObserver : public ParticleObserver
	{
		protected:
			Real mThreshold;
			ComparisionOperator mCompare;
			bool mSinceStartSystem;

		public:
			// Constants
			static const Real DEFAULT_THRESHOLD;
			static const bool DEFAULT_SINCE_START_SYSTEM;

			OnTimeObserver(void);
	        virtual ~OnTimeObserver(void) {};

			/** In case there are no particles, but the observation returns true, the event handlers must still be
				called.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Real timeElapsed);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			Real getThreshold(void) const {return mThreshold;};
			void setThreshold(Real threshold){mThreshold = threshold;};

			/** 
	        */
			const ComparisionOperator getCompare(void) const {return mCompare;};
			void setCompare(ComparisionOperator op){mCompare = op;};

			/** 
	        */
			bool isSinceStartSystem(void) const {return mSinceStartSystem;};
			void setSinceStartSystem(bool sinceStartSystem){mSinceStartSystem = sinceStartSystem;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
