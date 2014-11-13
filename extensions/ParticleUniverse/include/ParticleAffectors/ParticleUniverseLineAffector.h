/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_LINE_AFFECTOR_H__
#define __PU_LINE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Affects a particle depending on a line shape. Particles are getting a new position along the line.
    */
	class _ParticleUniverseExport LineAffector : public ParticleAffector
	{
		protected:
			Real mMaxDeviation;
			Real _mScaledMaxDeviation;
			Vector3 mEnd;
			Real mTimeSinceLastUpdate;
			Real mTimeStep;
			Real mDrift;
			Real mOneMinusDrift;
			bool mUpdate;
			bool mFirst;

		public:
			// Constants
			static const Real DEFAULT_MAX_DEVIATION;
			static const Real DEFAULT_TIME_STEP;
			static const Vector3 DEFAULT_END;
			static const Real DEFAULT_DRIFT;
			
			LineAffector(void);
	        virtual ~LineAffector(void) {};

			/** 
	        */
			Real getMaxDeviation(void) const;
			void setMaxDeviation(Real maxDeviation);

			/** 
	        */
			const Vector3& getEnd(void) const;
			void setEnd(const Vector3& end);

			/** 
	        */
			Real getTimeStep(void) const;
			void setTimeStep(Real timeStep);

			/** 
	        */
			Real getDrift(void) const;
			void setDrift(Real drift);

			/**
	        */
			virtual void _notifyRescaled(const Vector3& scale);

			/** 
	        */
			virtual void _firstParticle(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);
			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** 
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
	};

}
#endif
