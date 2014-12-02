/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BASE_COLLIDER_H__
#define __PU_BASE_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** The BaseCollider is the abstract class for Particle Colliders. A collider is a shape that can collide with a particle.
		In fact, particles can also be considered colliders, which allows particle-particle collision.
    */
	class _ParticleUniverseExport BaseCollider : public ParticleAffector
	{
		public:
			/** Determines how a particle collision should be determined. IT_POINT means that the position of 
				the particle will be validated against the Colliders' shape. IT_BOX means that the dimensions
				(width, height and depth) are used to determine whether the particle collides.
			*/
			enum IntersectionType
			{
				IT_POINT,
				IT_BOX
			};

			/** Determines how a particle behaves after collision with this collider. The behaviour of the
				particle is solved in the collider and only behaviour that needs the colliders´ data is taken
				into account. The fact that a particle expires for example, can be achieved by using an 
				Observer in combination with an EventHandler (DoExpireEventHandler).
				CT_NONE means that the particle doesn´t do anything. This value should be set if the behaviour 
				of the particle is determined outside the collider (for example, expiring the particle).
				CT_BOUNCE means that the particle bounces off the collider.
				CT_FLOW means that the particle flows around the contours of the collider.
			*/
			enum CollisionType
			{
				CT_NONE,
				CT_BOUNCE,
				CT_FLOW,
			};

			// Constants
			static const Real DEFAULT_BOUNCYNESS;
			static const Real DEFAULT_FRICTION;
			static const IntersectionType DEFAULT_INTERSECTION_TYPE;
			static const CollisionType DEFAULT_COLLISION_TYPE;

			BaseCollider(void);
	        virtual ~BaseCollider(void){};

			/** @copydoc ParticleAffector::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);

			/** Returns the type of intersection.
	        */
			const IntersectionType getIntersectionType(void) const;

			/** Sets the type of intersection.
	        */
			void setIntersectionType(const IntersectionType& intersectionType);

			/** Returns the type of collision.
	        */
			const CollisionType getCollisionType(void) const;

			/** Sets the type of collision.
	        */
			void setCollisionType(const CollisionType& collisionType);

			/** Returns the friction value.
	        */
			const Real getFriction(void) const;

			/** Sets the friction value.
	        */
			void setFriction(const Real friction);

			/** Returns the bouncyness value.
	        */
			const Real getBouncyness(void) const;

			/** Sets the bouncyness value.
	        */
			void setBouncyness(const Real bouncyness);

			/** Fill the AxisAlignedBox with data derived from the other arguments.
	        */
			void populateAlignedBox(AxisAlignedBox& box,
				const Vector3& position, 
				const Real width,
				const Real height,
				const Real depth);

			/** Recalculates the rotation speed after collision.
				This function must be explicitly called in the _affect() function of the class that inherits from 
				BaseCollider.
	        */
			void calculateRotationSpeedAfterCollision(Particle* particle);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			Real mFriction; // Physics characteristic that influences particle rotation speed.
			Real mBouncyness; // Physics characteristic that influences particle velocity.
			IntersectionType mIntersectionType;
			CollisionType mCollisionType;
			Real mVelocityScale; // Value set in the particle system, but stored in the collider for convenience.
	};

}
#endif
