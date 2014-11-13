/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_H__
#define __PU_SPHERE_H__

#include "ParticleUniversePrerequisites.h"
#include "OgreMemoryAllocatorConfig.h"

namespace ParticleUniverse
{
	class SphereSet;

	/** 
    */
	class _ParticleUniverseExport Sphere : public FXAlloc
	{
		friend class SphereSet;
		friend class SphereRenderer;

		protected:
			bool mOwnRadius;
			Real mRadius;
			bool mRadiusChanged;

		public:
			Vector3 mPosition;
			ColourValue mColour;
			Quaternion mOrientation;
			SphereSet* mParentSet;
			
			/** Default constructor.
			*/
			Sphere(void);

			/** Default destructor.
			*/
	        virtual ~Sphere(void);

			/** Constructor as called by SphereSet.
			*/
			Sphere(const Vector3& position, SphereSet* owner);

			/** 
			*/
			void setPosition(const Vector3& position);

			/** 
			*/
			void setPosition(Real x, Real y, Real z);

			/** 
			*/
			const Vector3& getPosition(void) const;

			/** Sets the colour of this sphere.
			*/
			void setColour(const ColourValue& colour);

			/** Get the colour of this sphere.
			*/
			const ColourValue& getColour(void) const;
		
			/** Resets this sphere to use the parent SphereSet's radius instead of it's own.
			*/
			void resetRadius(void) { mOwnRadius = false; }

			/** Sets the radius for this sphere.
			*/
			void setRadius(Real radius);

			/** Returns true if this box deviates from the SphereSet's default radius.
			*/
			bool hasOwnRadius(void) const;

			/** Retrieves the sphere's personal radius, if hasOwnRadius is true.
			*/
			Real getOwnRadius(void) const;

			/** Internal method for notifying the box of it's owner.
			*/
			void _notifyOwner(SphereSet* owner);
	};

}
#endif
