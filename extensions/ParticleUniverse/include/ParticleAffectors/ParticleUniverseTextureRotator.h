/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TEXTURE_ROTATOR_H__
#define __PU_TEXTURE_ROTATOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"

namespace ParticleUniverse
{
	/** The TextureRotator rotates the texture(s) of a particle. In general it is possible to support individual
		rotation of each particle texture-set - the same as in the geometry rotator, setting 
		mUseOwnRotationSpeed to true -, but in practice this isn't really usable, because usually all particles
		share the same material.
    */
	class _ParticleUniverseExport TextureRotator : public ParticleAffector
	{
		public:
			// Constants
			static const bool DEFAULT_USE_OWN_SPEED;
			static const Real DEFAULT_ROTATION_SPEED;
			static const Real DEFAULT_ROTATION;

			TextureRotator(void);
	        virtual ~TextureRotator(void);

			/** Returns an indication whether the 2D rotation speed is the same for all particles in this 
				particle technique, or whether the 2D rotation speed of the particle itself is used.
	        */
			bool useOwnRotationSpeed (void) const;

			/** Set the indication whether the 2D rotation speed of the particle itself is used.
	        */
			void setUseOwnRotationSpeed (bool useOwnRotationSpeed);

			/** Returns the rotation speed. This is the speed controlled by the affector.
	        */
			DynamicAttribute* getRotationSpeed(void) const;

			/** 
	        */
			void setRotationSpeed(DynamicAttribute* dynRotationSpeed);

			/** Returns the rotation defined in the the affector.
	        */
			DynamicAttribute* getRotation(void) const;

			/** 
	        */
			void setRotation(DynamicAttribute* dynRotation);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** Returns a rotation set in the affector, depending on the type of dynamic attribute.
	        */
			Radian _calculateRotation (void);

			/** Returns a rotation speed value, depending on the type of dynamic attribute.
	        */
			Radian _calculateRotationSpeed (Particle* particle);

			/** @copydoc ParticleAffector::_initParticleForEmission */
			virtual void _initParticleForEmission(Particle* particle);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

		protected:
			bool mUseOwnRotationSpeed;
			Radian mScaledRotationSpeed;
			Radian twoPiRad;
			DynamicAttribute* mDynRotation;
			DynamicAttribute* mDynRotationSpeed;

			/** Helper factory
			*/
			DynamicAttributeFactory mDynamicAttributeFactory;
			DynamicAttributeHelper mDynamicAttributeHelper;
	};

}
#endif
