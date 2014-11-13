/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_VORTEX_AFFECTOR_H__
#define __PU_VORTEX_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"

namespace ParticleUniverse
{
	/** The VortexAffector rotates particles around a given rotation axis.
    */
	class _ParticleUniverseExport VortexAffector : public ParticleAffector
	{
		public:
			// Constants
			static const Vector3 DEFAULT_ROTATION_VECTOR;
			static const Real DEFAULT_ROTATION_SPEED;
		
			VortexAffector(void);
	        virtual ~VortexAffector(void);

			/** 
	        */
			const Vector3& getRotationVector(void) const;

			/** 
	        */
			void setRotationVector(const Vector3& rotationVector);

			/** 
	        */
			DynamicAttribute* getRotationSpeed(void) const;

			/** 
	        */
			void setRotationSpeed(DynamicAttribute* dynRotationSpeed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

		protected:
			Vector3 mRotationVector;
			Quaternion mRotation;
			DynamicAttribute* mDynRotationSpeed;
			DynamicAttributeHelper mDynamicAttributeHelper;
			DynamicAttributeFactory mDynamicAttributeFactory;

			/** 
	        */
			Radian _calculateRotationSpeed(void);
	};

}
#endif
