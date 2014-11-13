/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_RENDERER_H__
#define __PU_BOX_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleRenderers/ParticleUniverseBoxSet.h"

namespace ParticleUniverse
{
	/** The BoxRenderer class is responsible to render particles as a box.
    */
	class _ParticleUniverseExport BoxRenderer : public ParticleRenderer
	{
		protected:
			/** The Box set that's doing the rendering */
			BoxSet* mBoxSet;

		public:
			BoxRenderer(void);
	        virtual ~BoxRenderer(void);

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

			/** Access BoxSet in use */
			BoxSet* getBoxSet(void) const { return mBoxSet; }

			/** @copydoc ParticleRenderer::setVisible */
			virtual void setVisible(bool visible);
	};

}
#endif
