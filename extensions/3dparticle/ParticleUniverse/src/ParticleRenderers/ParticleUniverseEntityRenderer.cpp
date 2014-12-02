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

#include "ParticleRenderers/ParticleUniverseEntityRenderer.h"
#include "OgreSceneManager.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"

namespace ParticleUniverse
{
	// Constants
	const EntityRenderer::EntityOrientationType EntityRenderer::DEFAULT_ORIENTATION_TYPE = EntityRenderer::ENT_ORIENTED_SHAPE;

	//-----------------------------------------------------------------------
	EntityRenderer::EntityRenderer(void) : 
		ParticleRenderer(),
		mQuota(0),
		mMeshName(StringUtil::BLANK),
		mEntityName(StringUtil::BLANK),
		mBoxWidth(1.0),
		mBoxHeight(1.0),
		mBoxDepth(1.0),
		mZRotated(false),
		mEntityOrientationType(DEFAULT_ORIENTATION_TYPE)
	{
		autoRotate = true; // Because the nodes inherit the orientation from the parent
	}
	//-----------------------------------------------------------------------
	EntityRenderer::~EntityRenderer(void)
	{
		if (!mParentTechnique)
			return;
		
		_destroyAll();
	}
	//-----------------------------------------------------------------------
	const EntityRenderer::EntityOrientationType& EntityRenderer::getEntityOrientationType(void) const
	{
		return mEntityOrientationType;
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::setEntityOrientationType(const EntityRenderer::EntityOrientationType& entityOrientationType)
	{
		mEntityOrientationType = entityOrientationType;
	}
	//-----------------------------------------------------------------------
	const String& EntityRenderer::getMeshName(void) const
	{
		return mMeshName;
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::setMeshName(const String& meshName)
	{
		mMeshName = meshName;
		mRendererInitialised = false; // Retriggers the _prepare function
		_destroyAll(); // Delete all nodes en entities, they will be rebuild
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_unprepare(ParticleTechnique* technique)
	{
		mRendererInitialised = false; // Retriggers the _prepare function
		_destroyAll(); // Delete all nodes, they will be rebuild
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_destroyAll(void)
	{
		if (!mParentTechnique)
			return;


		// Delete the visual data
		vector<EntityRendererVisualData*>::const_iterator it;
		vector<EntityRendererVisualData*>::const_iterator itEnd = mAllVisualData.end();
		for (it = mAllVisualData.begin(); it != itEnd; ++it)
		{
			PU_DELETE_T(*it, EntityRendererVisualData, MEMCATEGORY_SCENE_OBJECTS);
		}

		mAllVisualData.clear();
		mVisualData.clear();

		// V1.5: Destroy the created ChildSceneNodes (which leads to detaching the Entities)
		if (mParentTechnique->getParentSystem())
		{
			Ogre::SceneNode* parentNode = mParentTechnique->getParentSystem()->getParentSceneNode();
			if (parentNode)
			{
				String sceneNodeName;
				std::stringstream ss; 
				unsigned short numChilds = parentNode->numChildren();
				for (unsigned short i = 0; i < numChilds; ++i)
				{
					Ogre::Node* node = parentNode->getChild(i);
					if (node)
					{
						Ogre::String name = node->getName();
						if (name.find("ParticleUniverse") != Ogre::String::npos)
						{
							parentNode->removeAndDestroyChild(i);
						}
					}
				}
			}
		} // V1.5

		// Destroy the Entities. Do it like this, because it must be assured that the entity still exists
		// and has not already been destroyed.
		Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
		for (size_t i = 0; i < mQuota; i++)
		{
			if (sceneManager->hasEntity(mEntityName + StringConverter::toString(i)))
			{
				sceneManager->destroyEntity(mEntityName + StringConverter::toString(i));
			}
		}
		mEntities.clear();

		// Reset the visual data in the pool
		mParentTechnique->initVisualDataInPool();
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::setVisible(bool visible)
	{
		ParticleRenderer::setVisible(visible);

		 // Always make the nodes invisible; they are made visible in the next _updateRenderQueue() call if visible is true.
		_makeNodesVisible(false);
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_makeNodesVisible(bool visible)
	{
		vector<EntityRendererVisualData*>::const_iterator it;
		vector<EntityRendererVisualData*>::const_iterator itEnd = mAllVisualData.end();
		for (it = mAllVisualData.begin(); it != itEnd; ++it)
		{
			(*it)->node->setVisible(visible);
		}
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_prepare(ParticleTechnique* technique)
	{
		/** 
			- This renderer is a ´hacky´ solution to display geometry-based particles. It pre-creates a 
			number of SceneNodes (childs of the parent Node to which the ParticleSystem is attached) and 
			Entities and uses these pools to display the particles. There are better solutions, but 
			this one is simple and fast enough, although it has some drawbacks.
			- Future solutions should rather make use of hardware instancing to display a large number of
			geometry-based particles at once.
		*/

		// Use the given technique, although it should be the same as mParentTechnique (must be set already)
		if (!technique || mRendererInitialised)
			return;

		std::stringstream ss; 
		ss << this;
		mEntityName = mMeshName + ss.str();
		mQuota = technique->getVisualParticleQuota();
		Ogre::SceneNode* parentNode = technique->getParentSystem()->getParentSceneNode();
		Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(mMeshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		Ogre::Mesh* meshPointer = mesh.getPointer();
		Vector3 size = meshPointer->getBounds().getSize();
		mBoxWidth = size.x == 0.0f ? 1.0f : size.x;
		mBoxHeight = size.y == 0.0f ? 1.0f : size.y;
		mBoxDepth = size.z == 0.0f ? 1.0f : size.z;

		if (parentNode)
		{
			// Create number of VisualData objects including SceneNodes
			String sceneNodeName;
			for (size_t i = 0; i < mQuota; i++)
			{
				sceneNodeName = "ParticleUniverse" + ss.str() + StringConverter::toString(i);
				EntityRendererVisualData* visualData = 
					PU_NEW_T(EntityRendererVisualData, MEMCATEGORY_SCENE_OBJECTS)(parentNode->createChildSceneNode(sceneNodeName));

				mAllVisualData.push_back(visualData); // Managed by this renderer
				mVisualData.push_back(visualData); // Used to assign to a particle
			}

			// Create number of Entities
			Ogre::Entity* entity = technique->getParentSystem()->getSceneManager()->createEntity(mEntityName, mMeshName); // Base entity
			vector<EntityRendererVisualData*>::const_iterator it;
			vector<EntityRendererVisualData*>::const_iterator itEnd = mAllVisualData.end();
			size_t j;
			for (it = mAllVisualData.begin(), j = 0; it != itEnd; ++it, ++j)
			{
				Ogre::Entity* clonedEntity = entity->clone(mEntityName + StringConverter::toString(j));
				clonedEntity->setMaterialName(technique->getMaterialName());
				clonedEntity->setRenderQueueGroup(mQueueId);
				mEntities.push_back(clonedEntity);
				(*it)->node->attachObject(clonedEntity);
			}
			technique->getParentSystem()->getSceneManager()->destroyEntity(mEntityName);
		}

		_makeNodesVisible(false);
		mRendererInitialised = true;
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool)
	{
		// Always perform this one
		ParticleRenderer::_updateRenderQueue(queue, pool);

		if (!mVisible)
			return;

		// Fast check to determine whether there are visual particles
		if (pool->isEmpty(Particle::PT_VISUAL))
			return;

		VisualParticle* particle = static_cast<VisualParticle*>(pool->getFirst(Particle::PT_VISUAL));
		while (!pool->end(Particle::PT_VISUAL))
		{
			if (particle)
			{
				if (!particle->visualData && !mVisualData.empty())
				{
					particle->visualData = mVisualData.back();
					mVisualData.pop_back();
				}

				if (particle->visualData)
				{
					Ogre::SceneNode* node = (static_cast<EntityRendererVisualData*>(particle->visualData))->node;
					if (node)
					{
						node->_setDerivedPosition(particle->position);

						if (mEntityOrientationType == ENT_ORIENTED_SHAPE)
						{
							// Use the orientation of the particle itself
							node->setOrientation(particle->orientation);
						}
						else if (mEntityOrientationType == ENT_ORIENTED_SELF)
						{
							// Rotate towards the direction
							node->setOrientation(Vector3::UNIT_X.getRotationTo(particle->direction));
						}
						else if (mEntityOrientationType == ENT_ORIENTED_SELF_MIRRORED)
						{
							// Rotate towards the negative direction
							node->setOrientation(Vector3::UNIT_X.getRotationTo(-particle->direction));
						}

						node->setVisible(true);
						node->setScale(particle->width / mBoxWidth, particle->height / mBoxHeight, particle->depth / mBoxDepth);
						if (mZRotated)
						{
							_rotateTexture(particle, static_cast<Ogre::Entity*>(node->getAttachedObject(0))); // We know for sure there is only one and it is an Entity*
						}
					}
				}
			}
			particle = static_cast<VisualParticle*>(pool->getNext(Particle::PT_VISUAL));
		}
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_notifyAttached(Ogre::Node* parent, bool isTagPoint)
	{
		_makeNodesVisible(parent); // If parent doesn't exist, make everything invisible
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_setMaterialName(const String& materialName)
	{
		if (mEntities.empty())
			return;

		vector<Ogre::Entity*>::const_iterator itEntity = mEntities.begin();
		vector<Ogre::Entity*>::const_iterator itEntityEnd = mEntities.end();
		for (itEntity = mEntities.begin(); itEntity != itEntityEnd; ++itEntity)
		{
			(*itEntity)->setMaterialName(materialName);
		}
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_notifyCurrentCamera(Camera* cam)
	{
		// No implementation
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_notifyParticleQuota(size_t quota)
	{
		mRendererInitialised = false; // Retriggers the _prepare function
		_destroyAll(); // Delete all nodes en entities, they will be rebuild
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_notifyDefaultDimensions(Real width, Real height, Real depth)
	{
		if (mAllVisualData.empty())
			return;

		vector<EntityRendererVisualData*>::const_iterator it;
		vector<EntityRendererVisualData*>::const_iterator itEnd = mAllVisualData.end();
		for (it = mAllVisualData.begin(); it != itEnd; ++it)
		{
			(*it)->node->setScale(width/mBoxWidth, height/mBoxHeight, depth/mBoxDepth);
		}
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_notifyParticleResized(void)
	{
		// This will be taken into account in the next _updateRenderQueue
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_notifyParticleZRotated(void)
	{
		mZRotated = true;
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::_rotateTexture(VisualParticle* particle, Ogre::Entity* entity)
	{
		Ogre::TextureUnitState::EffectMap::const_iterator it;
		// Get the material and rotate it
		unsigned int numberOfSubEntities = entity->getNumSubEntities();
		for (unsigned short u = 0; u < numberOfSubEntities; ++u)
		{
			Ogre::MaterialPtr material = entity->getSubEntity(u)->getMaterial();
			unsigned short numberOfTechniques = material->getNumTechniques();
			for (unsigned short v = 0; v < numberOfTechniques; ++v)
			{
				Ogre::Technique* technique = material->getTechnique(v);
				unsigned short numberOfPasses = technique->getNumPasses();
				for (unsigned short w = 0; w < numberOfPasses; ++w)
				{
					Ogre::Pass* pass = technique->getPass(w);
					unsigned short numberOfTextureUnitStates = pass->getNumTextureUnitStates();
					for (unsigned short x = 0; x < numberOfTextureUnitStates; ++x)
					{
						// Set the rotation if not already available.
						// This can only be done once! Changing the rotationspeed or removing the rotation
						// and resetting it doesn´t seem to work.
						Ogre::TextureUnitState* textureUnitState = pass->getTextureUnitState(x);
						it = textureUnitState->getEffects().find(Ogre::TextureUnitState::ET_ROTATE);
						if (it == textureUnitState->getEffects().end())
						{
							textureUnitState->setRotateAnimation((particle->zRotationSpeed.valueRadians()));
						}
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::setRenderQueueGroup(uint8 queueId)
	{
		mQueueId = queueId;

		if (mEntities.empty())
			return;

		vector<Ogre::Entity*>::const_iterator itEntity = mEntities.begin();
		vector<Ogre::Entity*>::const_iterator itEntityEnd = mEntities.end();
		for (itEntity = mEntities.begin(); itEntity != itEntityEnd; ++itEntity)
		{
			(*itEntity)->setRenderQueueGroup(mQueueId);
		}
	}
	//-----------------------------------------------------------------------
	SortMode EntityRenderer::_getSortMode(void) const
	{
		return SM_DISTANCE; // In fact there is no sorting
	}
	//-----------------------------------------------------------------------
	void EntityRenderer::copyAttributesTo (ParticleRenderer* renderer)
	{
		// First copy parent attributes
		ParticleRenderer::copyAttributesTo(renderer);

		// First cast to EntityRenderer
		EntityRenderer* entityRenderer = static_cast<EntityRenderer*>(renderer);

		// Copy attributes in case there is a entityRenderer (which should be available)
		entityRenderer->mMeshName = mMeshName;
		entityRenderer->mBoxWidth = mBoxWidth;
		entityRenderer->mBoxHeight = mBoxHeight;
		entityRenderer->mBoxDepth = mBoxDepth;
		entityRenderer->mEntityOrientationType = mEntityOrientationType;
	}

}
