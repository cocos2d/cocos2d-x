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

#include "ParticleRenderers/ParticleUniverseBeamRenderer.h"
#include "OgreSceneManager.h"

namespace ParticleUniverse
{
	// Constants
	const bool BeamRenderer::DEFAULT_USE_VERTEX_COLOURS = false;
	const size_t BeamRenderer::DEFAULT_MAX_ELEMENTS = 10;
	const Real BeamRenderer::DEFAULT_UPDATE_INTERVAL = 0.1f;
	const Real BeamRenderer::DEFAULT_DEVIATION = 300;
	const size_t BeamRenderer::DEFAULT_NUMBER_OF_SEGMENTS = 2;
	const Ogre::BillboardChain::TexCoordDirection BeamRenderer::DEFAULT_TEXTURE_DIRECTION = Ogre::BillboardChain::TCD_V;

	//-----------------------------------------------------------------------
	BeamRenderer::BeamRenderer(void) : 
		TechniqueListener(),
		ParticleRenderer(),
		mBillboardChain(0),
		mQuota(0),
		mUseVertexColours(DEFAULT_USE_VERTEX_COLOURS),
		mMaxChainElements(DEFAULT_MAX_ELEMENTS),
		mUpdateInterval(DEFAULT_UPDATE_INTERVAL),
		mDeviation(DEFAULT_DEVIATION),
		mNumberOfSegments(DEFAULT_NUMBER_OF_SEGMENTS),
		mJump(false),
		mTexCoordDirection(DEFAULT_TEXTURE_DIRECTION)
	{
		autoRotate = true; // Because the nodes inherit the orientation from the parent
	}
	//-----------------------------------------------------------------------
	BeamRenderer::~BeamRenderer(void)
	{
		if (!mParentTechnique)
			return;
		
		_destroyAll();
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::particleEmitted(ParticleTechnique* particleTechnique, Particle* particle)
	{
		if (!particle->visualData && !mVisualData.empty() && particle->particleType == Particle::PT_VISUAL)
		{
			particle->visualData = mVisualData.back();
			BeamRendererVisualData* beamRendererVisualData = static_cast<BeamRendererVisualData*>(particle->visualData);
			beamRendererVisualData->setVisible(true, _mRendererScale.x * mParentTechnique->getDefaultWidth()); // PU 1.4
			mVisualData.pop_back();
		}
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::particleExpired(ParticleTechnique* particleTechnique, Particle* particle)
	{
		if (particle->visualData)
		{
			BeamRendererVisualData* beamRendererVisualData = static_cast<BeamRendererVisualData*>(particle->visualData);
			beamRendererVisualData->setVisible(false, 0); // PU 1.4
			mVisualData.push_back(beamRendererVisualData);
			particle->visualData = 0;
		}
	}
	//-----------------------------------------------------------------------
	bool BeamRenderer::isUseVertexColours(void) const
	{
		return mUseVertexColours;
	} 
	//-----------------------------------------------------------------------
	void BeamRenderer::setUseVertexColours(bool useVertexColours)
	{
		mUseVertexColours = useVertexColours;
		if (!mBillboardChain)
			return;

		mBillboardChain->setUseVertexColours(mUseVertexColours);
		mBillboardChain->setUseTextureCoords(!mUseVertexColours);
	} 
	//-----------------------------------------------------------------------
	size_t BeamRenderer::getMaxChainElements(void) const
	{
		return mMaxChainElements;
	} 
	//-----------------------------------------------------------------------
	void BeamRenderer::setMaxChainElements(size_t maxChainElements)
	{
		mMaxChainElements = maxChainElements;
	} 
	//-----------------------------------------------------------------------
	Real BeamRenderer::getUpdateInterval(void) const
	{
		return mUpdateInterval;
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setUpdateInterval(Real updateInterval)
	{
		mUpdateInterval = updateInterval;
	}
	//-----------------------------------------------------------------------
	Real BeamRenderer::getDeviation(void) const
	{
		return mDeviation;
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setDeviation(Real deviation)
	{
		mDeviation = deviation;
	}
	//-----------------------------------------------------------------------
	size_t BeamRenderer::getNumberOfSegments(void) const
	{
		return mNumberOfSegments;
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setNumberOfSegments(size_t numberOfSegments)
	{
		mNumberOfSegments = numberOfSegments;
	}
	//-----------------------------------------------------------------------
	bool BeamRenderer::isJump(void) const
	{
		return mJump;
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setJump(bool jump)
	{
		mJump = jump;
	}
	//-----------------------------------------------------------------------
	Ogre::BillboardChain::TexCoordDirection BeamRenderer::getTexCoordDirection(void) const
	{
		return mTexCoordDirection;
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setTexCoordDirection(Ogre::BillboardChain::TexCoordDirection texCoordDirection)
	{
		mTexCoordDirection = texCoordDirection;
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_prepare(ParticleTechnique* technique)
	{
		if (!technique || mRendererInitialised)
			return;

		// Register itself to the technique
		if (mParentTechnique)
		{
			// Although it is safe to assume that technique == mParentTechnique, use the mParentTechnique, because the mParentTechnique is
			// also used for unregistering.
			mParentTechnique->addTechniqueListener(this);
		}

		mQuota = technique->getVisualParticleQuota();
		Ogre::SceneNode* parentNode = technique->getParentSystem()->getParentSceneNode();

		if (parentNode)
		{
			// Create BillboardChain
			Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
			std::stringstream ss; 
			ss << this;
			mBillboardChainName = "Beam" + ss.str();
			mBillboardChain = sceneManager->createBillboardChain(mBillboardChainName);
			mBillboardChain->setDynamic(true);
			mBillboardChain->setNumberOfChains(mQuota);
			mBillboardChain->setMaxChainElements(mMaxChainElements);
			mBillboardChain->setMaterialName(technique->getMaterialName());
			mBillboardChain->setRenderQueueGroup(mQueueId);
			mBillboardChain->setTextureCoordDirection(mTexCoordDirection);
			setUseVertexColours(mUseVertexColours);
			mBillboardChain->setOtherTextureCoordRange(0.0f, 1.0f);
			mBillboardChain->setVisible(true);

			// Create number of VisualData objects
			for (size_t i = 0; i < mQuota; i++)
			{
				for (size_t j = 0; j < mMaxChainElements; j++)
				{
					Ogre::BillboardChain::Element element;
					element = Ogre::BillboardChain::Element(Vector3::ZERO, _mRendererScale.x * mParentTechnique->getDefaultWidth(), 0.0f, ColourValue::White, Ogre::Quaternion::IDENTITY); // V1.51
					mBillboardChain->addChainElement(i, element);
				}
				BeamRendererVisualData* visualData = PU_NEW_T(BeamRendererVisualData, MEMCATEGORY_SCENE_OBJECTS)(i, mBillboardChain);
				for (size_t numDev = 0; numDev < mNumberOfSegments; ++numDev)
				{
					// Initialise the positions
					visualData->half[numDev] = Vector3::ZERO;
					visualData->destinationHalf[numDev] = Vector3::ZERO;
				}
				mAllVisualData.push_back(visualData); // Managed by this renderer
				mVisualData.push_back(visualData); // Used to assign to a particle
			}
			mRendererInitialised = true;
			parentNode->attachObject(mBillboardChain);
		}
	}

	//-----------------------------------------------------------------------
	void BeamRenderer::_unprepare(ParticleTechnique* technique)
	{
		mRendererInitialised = false; // Retriggers the _prepare function
		_destroyAll();
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool)
	{
		if (!mParentTechnique && mBillboardChain)
			return;

		// Always perform this one
		ParticleRenderer::_updateRenderQueue(queue, pool);

		if (!mVisible)
			return;

		Particle* particle = static_cast<Particle*>(pool->getFirst());
		BeamRendererVisualData* visualData = 0;
		Vector3 basePosition = mParentTechnique->getParentSystem()->getDerivedPosition();
		while (!pool->end())
		{
			if (particle)
			{
				visualData = static_cast<BeamRendererVisualData*>(particle->visualData);
				if (visualData)
				{
					VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
					Vector3 end = visualParticle->position - basePosition;
					SimpleSpline spline;

					// Add points
					spline.addPoint(Vector3::ZERO);
					for (size_t numDev = 0; numDev < mNumberOfSegments; ++numDev)
					{
						spline.addPoint(visualData->half[numDev]);
					}
					spline.addPoint(end);

					// Loop through all chain elements
					for (size_t j = 0; j < mMaxChainElements; ++j)
					{
						Ogre::BillboardChain::Element element = mBillboardChain->getChainElement(visualData->chainIndex, j);

						// 1. Set the width of the chain if required
						if (visualParticle->ownDimensions)
						{
							element.width = _mRendererScale.x * visualParticle->width;
						}

						// 2. Set positions of the elements
						element.position = spline.interpolate((Real)j / (Real)mMaxChainElements);

						// 3. Set the colour
						element.colour = visualParticle->colour;

						// 4. Update
						mBillboardChain->updateChainElement(visualData->chainIndex, j, element);
					}
					visualData->setVisible(true);
				}
			}
			particle = static_cast<Particle*>(pool->getNext());
		}
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_processParticle(ParticleTechnique* particleTechnique, 
		Particle* particle, 
		Real timeElapsed, 
		bool firstParticle)
	{
		if (!particle->visualData)
			return;

		BeamRendererVisualData* beamRendererVisualData = static_cast<BeamRendererVisualData*>(particle->visualData);
		beamRendererVisualData->mTimeSinceLastUpdate -= timeElapsed;

		if (beamRendererVisualData->mTimeSinceLastUpdate < 0)
		{
			// Generate deviation
			ParticleSystem* pSys = particleTechnique->getParentSystem();
			if (!pSys)
				return;

			Vector3 end = particle->position - pSys->getDerivedPosition();
			Vector3 perpendicular;
			Real divide = (Real)mNumberOfSegments + 1.0f;
			for (size_t numDev = 0; numDev < mNumberOfSegments; ++numDev)
			{
				perpendicular = end.crossProduct(Vector3(Math::RangeRandom(-1, 1), 
					Math::RangeRandom(-1, 1), 
					Math::RangeRandom(-1, 1)));
				perpendicular.normalise();
				beamRendererVisualData->destinationHalf[numDev] = (((Real)numDev + 1.0f) / divide) * end + _mRendererScale * mDeviation * perpendicular;
			}
			beamRendererVisualData->mTimeSinceLastUpdate += mUpdateInterval;
		}

		Vector3 diff;
		for (size_t numDev = 0; numDev < mNumberOfSegments; ++numDev)
		{
			if (mJump)
			{
				beamRendererVisualData->half[numDev] = beamRendererVisualData->destinationHalf[numDev];
			}
			else
			{
				diff = beamRendererVisualData->destinationHalf[numDev] - beamRendererVisualData->half[numDev];
				beamRendererVisualData->half[numDev] = beamRendererVisualData->half[numDev] + timeElapsed * diff;
			}
		}
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_destroyAll(void)
	{
		if (!mParentTechnique)
			return;

		// Remove the listener
		mParentTechnique->removeTechniqueListener(this);

		// Detach the billboardchain
		Ogre::SceneNode* parentNode = mParentTechnique->getParentSystem()->getParentSceneNode();
		if (parentNode && mBillboardChain && mBillboardChain->isAttached())
		{
			parentNode->detachObject(mBillboardChain);
		}

		// Delete the BillboardChain
		Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
		if (mBillboardChain && sceneManager && sceneManager->hasBillboardChain(mBillboardChainName))
		{
			sceneManager->destroyBillboardChain(mBillboardChainName);
			mBillboardChain = 0;
		}

		// Delete the visual data
		vector<BeamRendererVisualData*>::const_iterator it;
		vector<BeamRendererVisualData*>::const_iterator itEnd = mAllVisualData.end();
		for (it = mAllVisualData.begin(); it != itEnd; ++it)
		{
			PU_DELETE_T(*it, BeamRendererVisualData, MEMCATEGORY_SCENE_OBJECTS);
		}

		mAllVisualData.clear();
		mVisualData.clear();

		// Reset the visual data in the pool
		mParentTechnique->initVisualDataInPool();
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_setMaterialName(const String& materialName)
	{
		if (mBillboardChain)
		{
			mBillboardChain->setMaterialName(materialName);
		}
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_notifyCurrentCamera(Camera* cam)
	{
		if (mBillboardChain)
		{
			mBillboardChain->_notifyCurrentCamera(cam);
		}
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::_notifyParticleQuota(size_t quota)
	{
		mRendererInitialised = false; // Retriggers the _prepare function
		_destroyAll();
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setRenderQueueGroup(uint8 queueId)
	{
		mQueueId = queueId;
		if (mBillboardChain)
		{
			mBillboardChain->setRenderQueueGroup(queueId);
		}
	}
	//-----------------------------------------------------------------------
	SortMode BeamRenderer::_getSortMode(void) const
	{
		return SM_DISTANCE; // In fact there is no sorting
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::setVisible(bool visible)
	{
		if (mBillboardChain)
		{
			mBillboardChain->setVisible(visible);
		}
	}
	//-----------------------------------------------------------------------
	void BeamRenderer::copyAttributesTo (ParticleRenderer* renderer)
	{
		// First copy parent attributes
		ParticleRenderer::copyAttributesTo(renderer);

		// First cast to BeamRenderer
		BeamRenderer* beamRenderer = static_cast<BeamRenderer*>(renderer);
		beamRenderer->mUseVertexColours = mUseVertexColours;
		beamRenderer->mMaxChainElements = mMaxChainElements;
		beamRenderer->mUpdateInterval = mUpdateInterval;
		beamRenderer->mDeviation = mDeviation;
		beamRenderer->mNumberOfSegments = mNumberOfSegments;
		beamRenderer->mJump = mJump;
		beamRenderer->mTexCoordDirection = mTexCoordDirection;
	}

}
