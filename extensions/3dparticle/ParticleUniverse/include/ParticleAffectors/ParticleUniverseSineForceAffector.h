/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SINE_FORCE_AFFECTOR_H__
#define __PU_SINE_FORCE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseForceAffector.h"

namespace ParticleUniverse
{
	/** Applies a sine force to a particle.
    */
	class _ParticleUniverseExport SineForceAffector : public BaseForceAffector
	{
		public:
			// Constants
			static const Real DEFAULT_FREQ_MIN;
			static const Real DEFAULT_FREQ_MAX;

			SineForceAffector(void);
	        virtual ~SineForceAffector(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			const Real getFrequencyMin(void) const;
			void setFrequencyMin(const Real frequencyMin);

			/** 
	        */
			const Real getFrequencyMax(void) const;
			void setFrequencyMax(const Real frequencyMax);

		protected:
			Real mAngle;
			Real mFrequencyMin;
			Real mFrequencyMax;
			Real mFrequency;
	};

}
#endif
