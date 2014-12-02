/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_COLLIDER_H__
#define __PU_BOX_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBaseCollider.h"
#include "ParticleUniverseAxisAlignedBox.h"

namespace ParticleUniverse
{
	/** The BoxCollider is a box shape that collides with the particles. The BoxCollider can only collide with
		particles that are created within the same ParticleTechnique as where the BoxCollider is registered.
    */
	class _ParticleUniverseExport BoxCollider : public BaseCollider
	{
		public:
			static const Real DEFAULT_WIDTH;
			static const Real DEFAULT_HEIGHT;
			static const Real DEFAULT_DEPTH;

			BoxCollider(void);
	        virtual ~BoxCollider(void){};

			/** Returns the width of the box
			*/
			const Real getWidth(void) const;

			/** Sets the width of the box
			*/
			void setWidth(const Real width);

			/** Returns the height of the box
			*/
			const Real getHeight(void) const;

			/** Sets the height of the box
			*/
			void setHeight(const Real height);

			/** Returns the depth of the box
			*/
			const Real getDepth(void) const;

			/** Sets the depth of the box
			*/
			void setDepth(const Real depth);

			/** Returns indication whether the collision is inside or outside of the box
			@remarks
				If value is true, the collision is inside of the box.
			*/
			bool isInnerCollision(void) const;

			/** Set indication whether the collision is inside or outside of the box
			@remarks
				If value is set to true, the collision is inside of the box.
			*/
			void setInnerCollision(bool innerCollision);

			/** 
			*/
			void calculateDirectionAfterCollision(Particle* particle);

			/** @copydoc ParticleAffector::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			Real mWidth;
			Real mHeight;
			Real mDepth;
			Real mXmin;
			Real mXmax;
			Real mYmin;
			Real mYmax;
			Real mZmin;
			Real mZmax;
			AxisAlignedBox mBox;
			Vector3 mPredictedPosition;
			bool mInnerCollision;

			/** 
			*/
			void _calculateBounds (void);

			/** 
			*/
			bool _isSmallestValue(Real value, const Vector3& particlePosition);
	};

}
#endif
