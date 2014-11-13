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

#include "ParticleUniverseRenderer.h"
#include "OgreTechnique.h"
#include "OgreMaterialManager.h"
#include "OgreHighLevelGpuProgramManager.h"

namespace ParticleUniverse
{
	// Constants
	const uint8 ParticleRenderer::DEFAULT_RENDER_QUEUE_GROUP = Ogre::RENDER_QUEUE_MAIN;
	const bool ParticleRenderer::DEFAULT_SORTED = false;
	const uchar ParticleRenderer::DEFAULT_TEXTURECOORDS_ROWS = 1;
	const uchar ParticleRenderer::DEFAULT_TEXTURECOORDS_COLUMNS = 1;
	const bool ParticleRenderer::DEFAULT_USE_SOFT_PARTICLES = false;
	const Real ParticleRenderer::DEFAULT_SOFT_PARTICLES_CONTRAST_POWER = 0.8f;
	const Real ParticleRenderer::DEFAULT_SOFT_PARTICLES_SCALE = 1.0f;
	const Real ParticleRenderer::DEFAULT_SOFT_PARTICLES_DELTA = -1.0f;
	const String SOFT_PREFIX = "NewSoft_";

	//-----------------------------------------------------------------------
	ParticleRenderer::ParticleRenderer(void) : 
		IAlias(),
		IElement(),
		mParentTechnique(0),
		mCullIndividual(false),
		mHeight(100),
		mWidth(100),
		mDepth(100),
		mSorted(DEFAULT_SORTED),
		mQueueId(DEFAULT_RENDER_QUEUE_GROUP),
		mRendererInitialised(false),
		_mRendererScale(Vector3::UNIT_SCALE),
		mTextureCoordsRows(DEFAULT_TEXTURECOORDS_ROWS),
		mTextureCoordsColumns(DEFAULT_TEXTURECOORDS_COLUMNS),
		mTextureCoordsSet(false),
		mUseSoftParticles(DEFAULT_USE_SOFT_PARTICLES),
		mSoftParticlesContrastPower(DEFAULT_SOFT_PARTICLES_CONTRAST_POWER),
		mSoftParticlesScale(DEFAULT_SOFT_PARTICLES_SCALE),
		mSoftParticlesDelta(DEFAULT_SOFT_PARTICLES_DELTA),
		mNotifiedDepthMap(false),
		mTextureCoordsRowsAndColumnsSet(false),
		mVisible(true)
	{
		mAliasType = AT_RENDERER;
	}
	//-----------------------------------------------------------------------
	ParticleRenderer::~ParticleRenderer(void)
	{
		// Remove texture coordinates
		vector<Ogre::FloatRect*>::iterator it;
		vector<Ogre::FloatRect*>::iterator itEnd = mUVList.end();
		for (it = mUVList.begin(); it != itEnd; ++it)
		{
			delete *it;
		}

		// Unregister
		if (mUseSoftParticles)
		{
			ParticleSystemManager::getSingleton().unregisterSoftParticlesRenderer(this);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::_notifyStart(void)
	{
		setVisible(true);
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::_notifyStop(void)
	{
		setVisible(false);
	}
	//-----------------------------------------------------------------------
	const String& ParticleRenderer::getRendererType(void) const
	{
		return mRendererType;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setRendererType(String rendererType)
	{
		mRendererType = rendererType;
	}
	//-----------------------------------------------------------------------
	ParticleTechnique* ParticleRenderer::getParentTechnique(void) const
	{
		return mParentTechnique;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setParentTechnique(ParticleTechnique* parentTechnique)
	{
		mParentTechnique = parentTechnique;
	}
	//-----------------------------------------------------------------------
	bool ParticleRenderer::isRendererInitialised(void) const
	{
		return mRendererInitialised;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setRendererInitialised(bool rendererInitialised)
	{
		mRendererInitialised = rendererInitialised;
	}
	//-----------------------------------------------------------------------
	uint8 ParticleRenderer::getRenderQueueGroup(void) const
	{
		return mQueueId;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setRenderQueueGroup(uint8 queueId)
	{
		mQueueId = queueId;
	}
	//-----------------------------------------------------------------------
	const bool ParticleRenderer::isSorted(void) const
	{
		return mSorted;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setSorted(bool sorted)
	{
		mSorted = sorted;
	}
	//-----------------------------------------------------------------------
	const uchar ParticleRenderer::getTextureCoordsRows(void) const
	{
		return mTextureCoordsRows;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setTextureCoordsRows(uchar const textureCoordsRows)
	{
		mTextureCoordsRows = textureCoordsRows;
		mTextureCoordsRowsAndColumnsSet = true;
	}
	//-----------------------------------------------------------------------
	const uchar ParticleRenderer::getTextureCoordsColumns(void) const
	{
		return mTextureCoordsColumns;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setTextureCoordsColumns(uchar const textureCoordsColumns)
	{
		mTextureCoordsColumns = textureCoordsColumns;
		mTextureCoordsRowsAndColumnsSet = true;
	}
	//-----------------------------------------------------------------------
	size_t ParticleRenderer::getNumTextureCoords(void)
	{
		// PU 1.4: There is at least one.
		if (mTextureCoordsRowsAndColumnsSet)
		{
			return mTextureCoordsRows * mTextureCoordsColumns;
		}

		size_t num = mUVList.size();
		num = num < 1 ? 1 : num;
		return mTextureCoordsRows * mTextureCoordsColumns;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::_notifyRescaled(const Vector3& scale)
	{
		_mRendererScale = scale;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::addTextureCoords(const Real u, 
		const Real v, 
		const Real width, 
		const Real height)
	{
		mUVList.push_back(new Ogre::FloatRect(u, v, u+width, v+height));
		mTextureCoordsSet = true;
	}
	//-----------------------------------------------------------------------
	const vector<Ogre::FloatRect*>& ParticleRenderer::getTextureCoords(void) const
	{
		return mUVList;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::_updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool)
	{
		/** Notify the Particle System Manager in case soft particles are used. This cannot be done elsewhere, because 
			it isn´t sure whether there is already a camera created.
		*/
		if (mUseSoftParticles && !mNotifiedDepthMap)
		{
			Camera* camera = 0;
			ParticleSystem* sys = mParentTechnique->getParentSystem();
			if (sys->hasMainCamera())
			{
				// Always use the main camera
				camera = sys->getMainCamera();
			}
			else
			{
				// Use the first camera that is encountered
				camera = sys->getCurrentCamera();
			}
			Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
			if (camera && sceneManager)
			{
				mNotifiedDepthMap = ParticleSystemManager::getSingleton().notifyDepthMapNeeded(camera, sceneManager);
				if (mNotifiedDepthMap)
				{
					ParticleSystemManager::getSingleton().registerSoftParticlesRenderer(this);
					_createSoftMaterial();
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	bool ParticleRenderer::getUseSoftParticles(void) const
	{
		return mUseSoftParticles;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setUseSoftParticles(bool useSoftParticles)
	{
		mUseSoftParticles = useSoftParticles;
		if (!mUseSoftParticles)
		{
			// Unregister is always executed if set to false
			ParticleSystemManager::getSingleton().unregisterSoftParticlesRenderer(this);
			String originalMaterialName = mParentTechnique->getMaterialName();
			_stripNameFromSoftPrefix(originalMaterialName);
			mParentTechnique->setMaterialName(originalMaterialName);
			mNotifiedDepthMap = false;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::_stripNameFromSoftPrefix(String& name)
	{
		if (name.find(SOFT_PREFIX) != String::npos)
		{
			// Remove the prefix
			name.erase(0, SOFT_PREFIX.length());
		}
	}
	//-----------------------------------------------------------------------
	Real ParticleRenderer::getSoftParticlesContrastPower(void) const
	{
		return mSoftParticlesContrastPower;
	}
	//-----------------------------------------------------------------------
	Real ParticleRenderer::getSoftParticlesScale(void) const
	{
		return mSoftParticlesScale;
	}
	//-----------------------------------------------------------------------
	Real ParticleRenderer::getSoftParticlesDelta(void) const
	{
		return mSoftParticlesDelta;
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setSoftParticlesContrastPower(Real softParticlesContrastPower)
	{
		mSoftParticlesContrastPower = softParticlesContrastPower;
		if (mUseSoftParticles)
		{
			// Set GPU param
			Ogre::MaterialPtr mat = mParentTechnique->getMaterial();
			if (!mat.isNull())
			{
				if (mat->getBestTechnique() && mat->getBestTechnique()->getPass(0))
				{
					Ogre::Pass* gpuPass = mat->getBestTechnique()->getPass(0);
					if (gpuPass->hasFragmentProgram())
					{
						Ogre::GpuProgramParametersSharedPtr fragmentParams = gpuPass->getFragmentProgramParameters();
						fragmentParams->setNamedConstant("contrastPower", mSoftParticlesContrastPower);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setSoftParticlesScale(Real softParticlesScale)
	{
		mSoftParticlesScale = softParticlesScale;
		if (mUseSoftParticles)
		{
			// Set GPU param
			Ogre::MaterialPtr mat = mParentTechnique->getMaterial();
			if (!mat.isNull())
			{
				if (mat->getBestTechnique() && mat->getBestTechnique()->getPass(0))
				{
					Ogre::Pass* gpuPass = mat->getBestTechnique()->getPass(0);
					if (gpuPass->hasFragmentProgram())
					{
						Ogre::GpuProgramParametersSharedPtr fragmentParams = gpuPass->getFragmentProgramParameters();
						fragmentParams->setNamedConstant("scale", mSoftParticlesScale);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::setSoftParticlesDelta(Real softParticlesDelta)
	{
		mSoftParticlesDelta = softParticlesDelta;
		if (mUseSoftParticles)
		{
			// Set GPU param
			Ogre::MaterialPtr mat = mParentTechnique->getMaterial();
			if (!mat.isNull())
			{
				if (mat->getBestTechnique() && mat->getBestTechnique()->getPass(0))
				{
					Ogre::Pass* gpuPass = mat->getBestTechnique()->getPass(0);
					if (gpuPass->hasFragmentProgram())
					{
						Ogre::GpuProgramParametersSharedPtr fragmentParams = gpuPass->getFragmentProgramParameters();
						fragmentParams->setNamedConstant("delta", mSoftParticlesDelta);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::_createSoftMaterial(void)
	{
		String newMaterialName = SOFT_PREFIX + mParentTechnique->getMaterialName();
		if (!Ogre::MaterialManager::getSingletonPtr()->getByName(newMaterialName).isNull())
		{
			mParentTechnique->setMaterialName(newMaterialName);
			return;
		}

		// Create a new material for soft particles
		if (mUseSoftParticles && mNotifiedDepthMap)
		{
			// Create Vertex program
			String softVertexName = "ParticleUniverse_SoftVP"; // Use ParticleUniverse_ to avoid name conflicts.
			Ogre::HighLevelGpuProgramPtr vertexProgram = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram( 
			softVertexName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			"hlsl",
			Ogre::GPT_VERTEX_PROGRAM);
			vertexProgram->setSourceFile("pu_soft_sm20.hlsl");
			vertexProgram->setParameter("target", "vs_2_0");
			vertexProgram->setParameter("entry_point", "mainVP"); // Must be same name as in pu_soft_sm20.hlsl
			vertexProgram->load();

			String softFragmentName = "ParticleUniverse_SoftFP"; // Use ParticleUniverse_ to avoid name conflicts.
			Ogre::HighLevelGpuProgramPtr fragmentProgram = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram( 
				softFragmentName,
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				"hlsl",
				Ogre::GPT_FRAGMENT_PROGRAM);
			fragmentProgram->setSourceFile("pu_soft_sm20.hlsl");
			fragmentProgram->setParameter("target", "ps_2_0");
			fragmentProgram->setParameter("entry_point", "mainFP"); // Must be same name as in pu_soft_sm20.hlsl
			fragmentProgram->load();

			String resourceGroupName = mParentTechnique->getParentSystem() ? 
				mParentTechnique->getParentSystem()->getResourceGroupName() : 
				Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

			// Create material with depth texture
			Ogre::MaterialPtr newMaterial = Ogre::MaterialManager::getSingleton().getByName(newMaterialName);
			if (!newMaterial.getPointer())
			{
				newMaterial = Ogre::MaterialManager::getSingleton().create(newMaterialName, resourceGroupName);
				Ogre::Pass* newPass = newMaterial->getTechnique(0)->getPass(0);
				newPass->setDepthCheckEnabled(true);
				newPass->setDepthWriteEnabled(false);
				newPass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
				newPass->createTextureUnitState(ParticleSystemManager::getSingleton().getDepthTextureName());

				// Get the first texture from the old material (assume it has at least 1 technique and one pass)
				Ogre::Pass* oldPass = mParentTechnique->getMaterial()->getBestTechnique()->getPass(0);
				newPass->setLightingEnabled(oldPass->getLightingEnabled());
				if (oldPass->getNumTextureUnitStates() > 0)
				{
					Ogre::TextureUnitState* oldTextureUnitState = oldPass->getTextureUnitState(0);
					newPass->createTextureUnitState(oldTextureUnitState->getTextureName());
				}

				// Set the vertex and fragment parameters
				newPass->setVertexProgram(softVertexName);
				newPass->setFragmentProgram(softFragmentName);
				Ogre::GpuProgramParametersSharedPtr vertexParams = newPass->getVertexProgramParameters();
				vertexParams->setNamedAutoConstant("worldViewProj", Ogre::GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX);
				vertexParams->setNamedAutoConstant("depthRange", Ogre::GpuProgramParameters::ACT_SCENE_DEPTH_RANGE);

				// Depth scale must be the same as used in creation of the depth map
				vertexParams->setNamedConstant("depthScale", ParticleSystemManager::getSingleton().getDepthScale());

				Ogre::GpuProgramParametersSharedPtr fragmentParams = newPass->getFragmentProgramParameters();
				fragmentParams->setNamedConstant("contrastPower", mSoftParticlesContrastPower);
				fragmentParams->setNamedConstant("scale", mSoftParticlesScale);
				fragmentParams->setNamedConstant("delta", mSoftParticlesDelta);
			}

			// Set the new material
			mParentTechnique->setMaterialName(newMaterialName);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::copyAttributesTo (ParticleRenderer* renderer)
	{
		copyParentAttributesTo(renderer);
	}
	//-----------------------------------------------------------------------
	void ParticleRenderer::copyParentAttributesTo (ParticleRenderer* renderer)
	{
		renderer->setRenderQueueGroup(mQueueId);
		renderer->setSorted(mSorted);
		renderer->mTextureCoordsRows = mTextureCoordsRows;
		renderer->mTextureCoordsColumns = mTextureCoordsColumns;
		renderer->mTextureCoordsRowsAndColumnsSet = mTextureCoordsRowsAndColumnsSet;
		renderer->mTextureCoordsSet = mTextureCoordsSet;
		renderer->mUseSoftParticles = mUseSoftParticles;
		renderer->mSoftParticlesContrastPower = mSoftParticlesContrastPower;
		renderer->mSoftParticlesScale = mSoftParticlesScale;
		renderer->mSoftParticlesDelta = mSoftParticlesDelta;
		renderer->mNotifiedDepthMap = mNotifiedDepthMap;
		renderer->_mRendererScale = _mRendererScale;

		if (mUVList.empty())
		{
			return;
		}
		vector<Ogre::FloatRect*>::iterator it;
		vector<Ogre::FloatRect*>::iterator itEnd = mUVList.end();
		for (it = mUVList.begin(); it != itEnd; ++it)
		{
			renderer->addTextureCoords((*it)->left, (*it)->top, (*it)->width(), (*it)->height());
		}

	}

}
