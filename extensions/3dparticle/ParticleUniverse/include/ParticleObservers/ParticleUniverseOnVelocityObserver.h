/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONVELOCITY_OBSERVER_H__
#define __PU_ONVELOCITY_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** The OnVelocityObserver determines whether the velocity of a particles is lower or higher than a certain
		threshold value.
    */
	class _ParticleUniverseExport OnVelocityObserver : public ParticleObserver
	{
		protected:
			Real mThreshold;
			ComparisionOperator mCompare;

		public:
			// Constants
			static const Real DEFAULT_VELOCITY_THRESHOLD;

			OnVelocityObserver(void);
	        virtual ~OnVelocityObserver(void) {};

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

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
