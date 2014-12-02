/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_RANDOMISER_H__
#define __PU_RANDOMISER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Randomises the position or the direction of a particle.
    */
	class _ParticleUniverseExport Randomiser : public ParticleAffector
	{
		protected:
			Real mMaxDeviationX;
			Real mMaxDeviationY;
			Real mMaxDeviationZ;
			Real mTimeSinceLastUpdate;
			Real mTimeStep;
			bool mRandomDirection;
			bool mUpdate;

		public:
			// Constants
			static const Vector3 DEFAULT_MAX_DEVIATION;
			static const Real DEFAULT_TIME_STEP;
			static const bool DEFAULT_RANDOM_DIRECTION;

			Randomiser(void);
	        virtual ~Randomiser(void) {};

			/** 
	        */
			Real getMaxDeviationX(void) const;
			void setMaxDeviationX(const Real maxDeviationX);

			/** 
	        */
			Real getMaxDeviationY(void) const;
			void setMaxDeviationY(const Real maxDeviationZ);

			/** 
	        */
			Real getMaxDeviationZ(void) const;
			void setMaxDeviationZ(const Real maxDeviationZ);

			/** 
	        */
			Real getTimeStep(void) const;
			void setTimeStep(const Real timeStep);

			/** 
	        */
			bool isRandomDirection(void) const;
			void setRandomDirection(bool randomDirection);

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
