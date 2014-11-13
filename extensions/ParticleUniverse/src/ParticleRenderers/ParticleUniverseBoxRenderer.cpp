/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleRenderers/ParticleUniverseBoxRenderer.h"
#include "ParticleRenderers/ParticleUniverseBox.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	BoxRenderer::BoxRenderer(void) : ParticleRenderer()
	{
		// Create Box set
		mBoxSet = PU_NEW BoxSet("", 0, true);

		// World-relative axes
		mBoxSet->setBoxesInWorldSpace(true);

		autoRotate = false;
	}
	//-----------------------------------------------------------------------
	BoxRenderer::~BoxRenderer(void)
	{
		if (mBoxSet)
		{
			PU_DELETE mBoxSet;
			mBoxSet = 0;
		}
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_prepare(ParticleTechnique* technique)
	{
		// Use the given technique, although it should be the same as mParentTechnique (must be set already)
		if (!technique || mRendererInitialised)
			return;

		_notifyParticleQuota(technique->getVisualParticleQuota());

		// Notify attached, but only if the parentnode exists
		if (technique->getParentSystem()->getParentNode())
		{		
			_notifyAttached(technique->getParentSystem()->getParentNode(), 
							technique->getParentSystem()->isParentIsTagPoint());
		}
		_notifyDefaultDimensions(_mRendererScale.x * technique->getDefaultWidth(),
								_mRendererScale.y * technique->getDefaultHeight(),
								_mRendererScale.z * technique->getDefaultDepth());
		_setMaterialName(technique->getMaterialName());
		mBoxSet->setRenderQueueGroup(mQueueId);
		mRendererInitialised = true;
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_unprepare(ParticleTechnique* technique)
	{
		_notifyAttached(0); // Bugfix V1.5: If detached from scenenode, do not use the pointer to it
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool)
	{
		// Always perform this one
		ParticleRenderer::_updateRenderQueue(queue, pool);

		if (!mVisible)
			return;

		// Fast check to determine whether there are visual particles
		if (pool->isEmpty(Particle::PT_VISUAL))
			return;

		mBoxSet->setCullIndividually(mCullIndividual);

		mBoxSet->beginBoxes(pool->getSize(Particle::PT_VISUAL));
		Box box;
		
		VisualParticle* particle = static_cast<VisualParticle*>(pool->getFirst(Particle::PT_VISUAL));

		// Activate texture rotation if needed and use the speed of the first particle.
		// The implementation of the texture rotation is low-profile, because its value is limited. For 3d
		// particles the geometry rotation is more interesting.
		if (mBoxSet->isZRotated())
		{
			mBoxSet->rotateTexture(particle->zRotationSpeed.valueRadians());
		}

		// Loop through the particles
		while (!pool->end(Particle::PT_VISUAL))
		{
			if (particle)
			{
				box.mPosition = particle->position;
				box.mColour = particle->colour;
				box.mOrientation = particle->orientation;

				if (box.mOwnDimensions = particle->ownDimensions)
				{
					box.mOwnDimensions = true;
					box.setDimensions (particle->width, particle->height, particle->depth);
				}
					
				mBoxSet->injectBox(box);
			}
			
			particle = static_cast<VisualParticle*>(pool->getNext(Particle::PT_VISUAL));
		}

        mBoxSet->endBoxes();

		// Update the queue
		mBoxSet->_updateRenderQueue(queue);
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_notifyAttached(Ogre::Node* parent, bool isTagPoint)
	{
		mBoxSet->_notifyAttached(parent, isTagPoint);
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_setMaterialName(const String& materialName)
	{
		mBoxSet->setMaterialName(materialName);
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_notifyCurrentCamera(Camera* cam)
	{
		mBoxSet->_notifyCurrentCamera(cam);
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_notifyParticleQuota(size_t quota)
	{
		mBoxSet->setPoolSize(static_cast<unsigned int>(quota));
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_notifyDefaultDimensions(Real width, Real height, Real depth)
	{
		mBoxSet->setDefaultDimensions(width, height, depth);
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_notifyParticleResized(void)
	{
		mBoxSet->_notifyResized();
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::_notifyParticleZRotated(void)
	{
		mBoxSet->_notifyZRotated();
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::setRenderQueueGroup(uint8 queueId)
	{
		mQueueId = queueId;
		if (mBoxSet)
		{
			mBoxSet->setRenderQueueGroup(queueId);
		}
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::setVisible(bool visible)
	{
		ParticleRenderer::setVisible(visible);
		mBoxSet->setVisible(visible);
	}
	//-----------------------------------------------------------------------
	void BoxRenderer::copyAttributesTo (ParticleRenderer* renderer)
	{
		// First copy parent attributes
		ParticleRenderer::copyAttributesTo(renderer);

		// First cast to BoxRenderer
		BoxRenderer* boxRenderer = static_cast<BoxRenderer*>(renderer);

		// Copy attributes in case there is a BoxSet (which should be available)
		if (!boxRenderer->getBoxSet())
			return;
	}

}
