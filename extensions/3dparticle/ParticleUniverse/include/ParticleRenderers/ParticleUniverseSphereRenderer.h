/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_RENDERER_H__
#define __PU_SPHERE_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleRenderers/ParticleUniverseSphereSet.h"

namespace ParticleUniverse
{
	/** The SphereRenderer class is responsible to render particles as a sphere.
    */
	class _ParticleUniverseExport SphereRenderer : public ParticleRenderer
	{
		protected:
			/** The sphere set that's doing the rendering */
			SphereSet* mSphereSet;

		public:
			SphereRenderer(void);
	        virtual ~SphereRenderer(void);

			/** @copydoc ParticleRenderer::_prepare */
			virtual void _prepare(ParticleTechnique* technique);

			/** @copydoc ParticleRenderer::_unprepare */
			virtual void _unprepare(ParticleTechnique* technique);

			/** @copydoc ParticleRenderer::_updateRenderQueue */
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool);

			/** @copydoc ParticleRenderer::_notifyAttached */
			virtual void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false);

			/** @copydoc ParticleRenderer::_setMaterialName */
			void _setMaterialName(const String& materialName);

			/** @copydoc ParticleRenderer::_notifyCurrentCamera */
			virtual void _notifyCurrentCamera(Camera* cam);
	
			/** @copydoc ParticleRenderer::_notifyParticleQuota */
			virtual void _notifyParticleQuota(size_t quota);

			/** @copydoc ParticleRenderer::_notifyDefaultDimensions */
			virtual void _notifyDefaultDimensions(Real width, Real height, Real depth);

			/** @copydoc ParticleRenderer::_notifyParticleResized */
			virtual void _notifyParticleResized(void);

			/** @copydoc ParticleRenderer::_notifyParticleZRotated */
			virtual void _notifyParticleZRotated(void);

			/** @copydoc ParticleRenderer::setRenderQueueGroup */
			virtual void setRenderQueueGroup(uint8 queueId);

			/** @copydoc ParticleRenderer::_getSortMode */
			virtual SortMode _getSortMode(void) const {return SM_DISTANCE;};

			/** @copydoc ParticleRenderer::copyAttributesTo */
			virtual void copyAttributesTo (ParticleRenderer* renderer);

			/** Access SphereSet in use */
			SphereSet* getSphereSet(void) const { return mSphereSet; }

			/** @copydoc ParticleRenderer::setVisible */
			virtual void setVisible(bool visible);
	};

}
#endif
