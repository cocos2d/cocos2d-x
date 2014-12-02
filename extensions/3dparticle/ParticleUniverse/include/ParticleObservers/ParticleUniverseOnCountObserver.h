/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONCOUNT_OBSERVER_H__
#define __PU_ONCOUNT_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe if an x number of Particles have been emitted.
	@remarks
		OnCountObserver supports 2 possible situations. If the comparison operator is set to 
		'less than', the _observe() function returns true until the counter exceeds the threshold.
		If the comparison operator is set to 'greater than', the _observe() function only returns 
		true if the counter exceeds the threshold.
    */
	class _ParticleUniverseExport OnCountObserver : public ParticleObserver
	{
		protected:
			uint mCount;
			uint mThreshold;
			ComparisionOperator mCompare;

		public:
			// Constants
			static const uint DEFAULT_THRESHOLD;
			static const ComparisionOperator DEFAULT_COMPARE;

			OnCountObserver(void);
	        virtual ~OnCountObserver(void) {};

			/** 
	        */
			virtual void _notifyStart (void);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			uint getThreshold(void) const {return mThreshold;};
			void setThreshold(uint threshold){mThreshold = threshold;};

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
