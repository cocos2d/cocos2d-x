/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_H__
#define __PU_BOX_H__

#include "ParticleUniversePrerequisites.h"
#include "OgreMemoryAllocatorConfig.h"

namespace ParticleUniverse
{
	class BoxSet;

	/** 
    */
	class _ParticleUniverseExport Box : public FXAlloc
	{
		friend class BoxSet;
		friend class BoxRenderer;

		protected:
			bool mOwnDimensions;
			Real mWidth;
			Real mHeight;
			Real mDepth;
			Real mHalfWidth;
			Real mHalfHeight;
			Real mHalfDepth;
			bool mDimensionsChanged;


			/** Corners of the box in local space.
			*/
			Vector3 mCorners[8];
			Vector3 mTempCorner;

			/** Calculates the corners.
			*/
			void _calculateCorners(void);

		public:
			Vector3 mPosition;
			ColourValue mColour;
			Quaternion mOrientation;
			BoxSet* mParentSet;
			
			/** Default constructor.
			*/
			Box(void);

			/** Default destructor.
			*/
	        virtual ~Box(void);

			/** Constructor as called by BoxSet.
			*/
			Box(const Vector3& position, BoxSet* owner);

			/** Return the boxcorner in local space of a specified corner.
			*/
			const Vector3& getCorner(size_t index);

			/** Return the boxcorner in world space of a specified corner.
			*/
			const Vector3& getWorldspaceCorner(size_t index);

			/** 
			*/
			void setPosition(const Vector3& position);

			/** 
			*/
			void setPosition(Real x, Real y, Real z);

			/** 
			*/
			const Vector3& getPosition(void) const;

			/** Sets the colour of this box.
			*/
			void setColour(const ColourValue& colour);

			/** Get the colour of this box.
			*/
			const ColourValue& getColour(void) const;
		
			/** Resets this box to use the parent BoxSet's dimensions instead of it's own.
			*/
			void resetDimensions(void) { mOwnDimensions = false; }

			/** Sets the width, height and depth for this box.
			*/
			void setDimensions(Real width, Real height, Real depth);

			/** Returns true if this box deviates from the BoxSet's default dimensions.
			@see
				Box::setDimensions
			*/
			bool hasOwnDimensions(void) const;

			/** Retrieves the box's personal width, if hasOwnDimensions is true.
			*/
			Real getOwnWidth(void) const;

			/** Retrieves the box's personal height, if hasOwnDimensions is true.
			*/
			Real getOwnHeight(void) const;

			/** Retrieves the box's personal depth, if hasOwnDimensions is true.
			*/
			Real getOwnDepth(void) const;

			/** Internal method for notifying the box of it's owner.
			*/
			void _notifyOwner(BoxSet* owner);
	};

}
#endif
