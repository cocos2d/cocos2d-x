/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ONPOSITION_OBSERVER_H__
#define __PU_ONPOSITION_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether a Particle reaches a certain position.
    */
	class _ParticleUniverseExport OnPositionObserver : public ParticleObserver
	{
		protected:
			Real mPositionXThreshold;
			Real mPositionYThreshold;
			Real mPositionZThreshold;
			bool mPositionXThresholdSet;
			bool mPositionYThresholdSet;
			bool mPositionZThresholdSet;
			ComparisionOperator mComparePositionX;
			ComparisionOperator mComparePositionY;
			ComparisionOperator mComparePositionZ;

		public:
			// Constants
			static const Vector3 DEFAULT_POSITION_THRESHOLD;

			OnPositionObserver(void);
	        virtual ~OnPositionObserver(void) {};

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
			 */
			void setPositionXThreshold(Real threshold){mPositionXThreshold = threshold; mPositionXThresholdSet = true;};
			void setPositionYThreshold(Real threshold){mPositionYThreshold = threshold; mPositionYThresholdSet = true;};
			void setPositionZThreshold(Real threshold){mPositionZThreshold = threshold; mPositionZThresholdSet = true;};

			/** 
			 */
			Real getPositionXThreshold(void) const {return mPositionXThreshold;};
			Real getPositionYThreshold(void) const {return mPositionYThreshold;};
			Real getPositionZThreshold(void) const {return mPositionZThreshold;};

			/** 
			 */
			bool isPositionXThresholdSet(void) const {return mPositionXThresholdSet;};
			bool isPositionYThresholdSet(void) const {return mPositionYThresholdSet;};
			bool isPositionZThresholdSet(void) const {return mPositionZThresholdSet;};

			/** 
			 */
			void resetPositionXThreshold(void) {mPositionXThresholdSet = false;};
			void resetPositionYThreshold(void) {mPositionYThresholdSet = false;};
			void resetPositionZThreshold(void) {mPositionZThresholdSet = false;};

			/** 
			 */
			void setComparePositionX(ComparisionOperator op){mComparePositionX = op;};
			void setComparePositionY(ComparisionOperator op){mComparePositionY = op;};
			void setComparePositionZ(ComparisionOperator op){mComparePositionZ = op;};

			/** 
			 */
			const ComparisionOperator getComparePositionX(void) const {return mComparePositionX;};
			const ComparisionOperator getComparePositionY(void) const {return mComparePositionY;};
			const ComparisionOperator getComparePositionZ(void) const {return mComparePositionZ;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
