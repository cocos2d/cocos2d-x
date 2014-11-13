/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_GRAVITY_AFFECTOR_H__
#define __PU_GRAVITY_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector applies Newton's law of universal gravitation. The distance between a particle
		and the GravityAffector is important in the calculation of the gravity. Therefor, this affector needs
		to have its position set.
    */
	class _ParticleUniverseExport GravityAffector : public ParticleAffector
	{
		public:
			// Constants
			static const Real DEFAULT_GRAVITY;
			
			GravityAffector(void);
	        virtual ~GravityAffector(void) {};

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
			Real getGravity(void) const;
			void setGravity(Real gravity);

	protected:
			Real mGravity;
	};

}
#endif
