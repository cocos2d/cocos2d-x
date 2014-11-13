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

#include "Externs/ParticleUniverseSceneDecoratorExtern.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	SceneDecoratorExtern::SceneDecoratorExtern(void) :  
		Extern(),
		mEntity(0),
		mEntitySet(false),
		mMeshName(StringUtil::BLANK),
		mEntityName(StringUtil::BLANK),
		mMaterialName("BaseWhite"),
		mMaterialNameSet(false),
		mScale(Vector3::UNIT_SCALE),
		mSubnode(0),
		mPosition(Vector3::ZERO),
		mCount(0)
	{
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::_prepare(ParticleTechnique* technique)
	{
		if (mEntitySet)
		{
			if (!mParentTechnique->getParentSystem())
			{
				return;
			}
			
			// Attach entity to a child scenenode. If the parent system is attached to a TagPoint, the entity cannot be attached.
			Ogre::SceneNode* sceneNode = mParentTechnique->getParentSystem()->getParentSceneNode();
			if (sceneNode)
			{
				std::stringstream ss; 
				ss << this;
				String sceneNodeName = "ParticleUniverse" + ss.str() + StringConverter::toString(mCount++);
				mSubnode = sceneNode->createChildSceneNode(sceneNodeName);
				mSubnode->setScale(mScale);
				mSubnode->setPosition(mPosition);
				if (!mEntity)
				{
					createEntity();
					mSubnode->attachObject(mEntity);
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::_unprepare(ParticleTechnique* technique)
	{
		// Todo
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::_interface(ParticleTechnique* technique, 
		Particle* particle, 
		Real timeElapsed)
	{
		// Nothing to do yet
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::_notifyStart (void)
	{
		// Scale the node
		if (!mSubnode && mParentTechnique->getParentSystem())
		{
			std::stringstream ss; 
			ss << this;
			String sceneNodeName = "ParticleUniverse" + ss.str() + StringConverter::toString(mCount++);
			Ogre::SceneNode* sceneNode = mParentTechnique->getParentSystem()->getParentSceneNode();
			mSubnode = sceneNode->createChildSceneNode(sceneNodeName);
		}

		if (!mEntity)
		{
			createEntity();
			mSubnode->attachObject(mEntity);
		}

		mSubnode->setScale(mScale);
		mSubnode->setPosition(mPosition);
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::_notifyStop (void)
	{
		if (mSubnode && mParentTechnique->getParentSystem())
		{
			Ogre::SceneNode* sceneNode = mParentTechnique->getParentSystem()->getParentSceneNode();
			Ogre::SceneNode::ChildNodeIterator it = sceneNode->getChildIterator();
			unsigned int i = 0;
			while (it.hasMoreElements()) 
			{ 
				Ogre::SceneNode* child = static_cast<Ogre::SceneNode*>(it.getNext());
				if (child == mSubnode)
				{
					mSubnode->detachAllObjects();
					sceneNode->removeAndDestroyChild(i);
					mSubnode = 0;
				}
				++i;
			}

			destroyEntity();
		}
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::createEntity(void)
	{
		if (!mEntity)
		{
			Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
			if (sceneManager)
			{
				std::stringstream ss;
				ss << this;
				mEntityName = mMeshName + ss.str();
				mEntity = sceneManager->createEntity(mEntityName, mMeshName);
				if (mMaterialNameSet)
				{
					mEntity->setMaterialName(mMaterialName);
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::destroyEntity(void)
	{
		if (mEntity)
		{
			Ogre::SceneManager* sceneManager = mParentTechnique->getParentSystem()->getSceneManager();
			if (sceneManager)
			{
				sceneManager->destroyEntity(mEntityName);
				mEntity = 0;
				mEntityName = StringUtil::BLANK;
			}
		}
	}
	//-----------------------------------------------------------------------
	const String& SceneDecoratorExtern::getMeshName(void) const
	{
		return mMeshName;
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::setMeshName(const String& meshName)
	{
		mMeshName = meshName;
		mEntitySet = true;
	}
	//-----------------------------------------------------------------------
	const String& SceneDecoratorExtern::getMaterialName(void) const
	{
		return mMaterialName;
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::setMaterialName(const String& materialName)
	{
		mMaterialName = materialName;
		mMaterialNameSet = true;
	}
	//-----------------------------------------------------------------------
	const Vector3& SceneDecoratorExtern::getScale(void) const
	{
		return mScale;
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::setScale(Vector3& scale)
	{
		mScale = scale;
	}
	//-----------------------------------------------------------------------
	const Vector3& SceneDecoratorExtern::getPosition(void) const
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::setPosition(Vector3& position)
	{
		mPosition = position;
	}
	//-----------------------------------------------------------------------
	void SceneDecoratorExtern::copyAttributesTo (Extern* externObject)
	{
		Extern::copyAttributesTo(externObject);
		SceneDecoratorExtern* sceneDecoratorExtern = static_cast<SceneDecoratorExtern*>(externObject);
		sceneDecoratorExtern->setMaterialName(mMaterialName);
		sceneDecoratorExtern->setMeshName(mMeshName);
		sceneDecoratorExtern->mScale = mScale;
		sceneDecoratorExtern->mPosition = mPosition;
	}
}
