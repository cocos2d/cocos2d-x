/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CAMERA_DEPENDENCY_H__
#define __PU_CAMERA_DEPENDENCY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIDependency.h"

namespace ParticleUniverse
{
	/** The CameraDependency class is used to define a relation between an attribute (for example the emission
		rate of a ParticleEmitter) and the camera. The camera distance influences the value of the attribute.
	@remarks
		In case of the emission rate for example, it can be defined that that number of emitted particles 
		decreases if the camera gets further away.
    */
	class _ParticleUniverseExport CameraDependency : public IDependency
	{
		protected:
			Real mThreshold;
			bool mIncrease;

		public:
			// Constants
			static const Real DEFAULT_DISTANCE_THRESHOLD;
			static const bool DEFAULT_INCREASE;

			CameraDependency(void);
			CameraDependency(Real threshold, bool inc);
			virtual ~CameraDependency(void){};

			/** Todo
	        */
			virtual bool affect(Real& baseValue, Real dependencyValue);

			/** Todo
	        */
			const Real getThreshold(void) const {return mThreshold;};
			void setThreshold(const Real threshold) {mThreshold = threshold;};

			/** Todo
	        */
			bool isIncrease(void) const {return mIncrease;};
			void setIncrease(bool increase) {mIncrease = increase;};

			/** Copy attributes to another camera dependency.
	        */
			virtual void copyAttributesTo (CameraDependency* cameraDependency);

	};
}
#endif
