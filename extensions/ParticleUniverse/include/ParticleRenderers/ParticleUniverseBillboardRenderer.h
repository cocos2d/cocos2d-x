/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BILLBOARD_RENDERER_H__
#define __PU_BILLBOARD_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleUniverseTechnique.h"
#include "OgreBillboard.h"
#include "OgreBillboardSet.h"

namespace ParticleUniverse
{
	/** The BillboardRenderer class is responsible to render particles as a billboard.
    */
	class _ParticleUniverseExport BillboardRenderer : public ParticleRenderer
	{
		public:

			/** Alternative billboard type. 
			@remarks
				This is an extended version of Ogre's billboard type. It has BBT_ORIENTED_SHAPE added
				which basicly means that the billboard orientation is derived from the particle 
				orientation.
			*/
			enum BillboardType
			{
				BBT_POINT,
				BBT_ORIENTED_COMMON,
				BBT_ORIENTED_SELF,
				BBT_ORIENTED_SHAPE,
				BBT_PERPENDICULAR_COMMON,
				BBT_PERPENDICULAR_SELF
			};

			// Constants
			static const BillboardType DEFAULT_BILLBOARD_TYPE;
			static const bool DEFAULT_ACCURATE_FACING;
			static const Ogre::BillboardOrigin DEFAULT_ORIGIN;
			static const Ogre::BillboardRotationType DEFAULT_ROTATION_TYPE;
			static const Vector3 DEFAULT_COMMON_DIRECTION;
			static const Vector3 DEFAULT_COMMON_UP_VECTOR;
			static const bool DEFAULT_POINT_RENDERING;

			BillboardRenderer(void);
	        virtual ~BillboardRenderer(void);

			/** @copydoc ParticleRenderer::_prepare */
			virtual void _prepare(ParticleTechnique* technique);

			/** @copydoc ParticleRenderer::_unprepare */
			virtual void _unprepare(ParticleTechnique* technique);

			/** 
			*/
			void setBillboardType(BillboardType bbt);

			/** 
			*/
			BillboardType getBillboardType(void) const;

			/** 
			*/
			void setUseAccurateFacing(bool acc);

			/** 
			*/
			bool isUseAccurateFacing(void) const;

			/** 
			*/
			void setBillboardOrigin(Ogre::BillboardOrigin origin) { mBillboardSet->setBillboardOrigin(origin); }

			/** 
			*/
			Ogre::BillboardOrigin getBillboardOrigin(void) const { return mBillboardSet->getBillboardOrigin(); }

			/** 
			*/
			void setBillboardRotationType(Ogre::BillboardRotationType rotationType);

			/** 
			*/
			Ogre::BillboardRotationType getBillboardRotationType(void) const;

			/** 
			*/
			void setCommonDirection(const Vector3& vec);

			/** 
			*/
			const Vector3& getCommonDirection(void) const;

			/** 
			*/
			void setCommonUpVector(const Vector3& vec);

			/** 
			*/
			const Vector3& getCommonUpVector(void) const;

			/** 
			*/
			void setPointRenderingEnabled(bool enabled);

			/** 
			*/
			bool isPointRenderingEnabled(void) const;

			/** 
			*/
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool);

			/** 
			*/
			virtual void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false);

			/** @copydoc ParticleRenderer::_setMaterialName */
			virtual void _setMaterialName(const String& materialName);

			/** 
			*/
			virtual void _notifyCurrentCamera(Camera* cam);
	
			/** 
			*/
			virtual void _notifyParticleQuota(size_t quota);

			/** 
			*/
			virtual void _notifyDefaultDimensions(Real width, Real height, Real depth);

			/** 
			*/
			virtual void _notifyParticleResized(void);

			/** 
			*/
			virtual void _notifyParticleZRotated(void);

			/** 
			*/
			virtual void setRenderQueueGroup(uint8 queueId);

			/** 
			*/
			virtual SortMode _getSortMode(void) const;

			/** 
			*/
			virtual void copyAttributesTo (ParticleRenderer* renderer);

			/** 
			*/
			Ogre::BillboardSet* getBillboardSet(void) const { return mBillboardSet; }

			/** @copydoc ParticleRenderer::setVisible */
			virtual void setVisible(bool visible);

		protected:
			/** 
			*/
			Ogre::BillboardSet* mBillboardSet;

			/** 
			*/
			BillboardType mBillboardType;
	};

}
#endif
