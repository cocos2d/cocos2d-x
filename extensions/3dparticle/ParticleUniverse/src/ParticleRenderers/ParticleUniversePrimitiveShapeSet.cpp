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

#include "ParticleRenderers/ParticleUniversePrimitiveShapeSet.h"
#include "OgreMaterialManager.h"
#include "OgreSceneManager.h"
#include "OgreNode.h"
#include "OgreTechnique.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	PrimitiveShapeSet::PrimitiveShapeSet(void) :
		mBoundingRadius(0.0f), 
		mWorldSpace(false),
		mCullIndividual(false),
		mZRotated(false),
		mAllDefaultSize(true)
	{
		setMaterialName("BaseWhite");
		mCastShadows = false;
	}
	//-----------------------------------------------------------------------
	PrimitiveShapeSet::PrimitiveShapeSet(const String& name, unsigned int poolSize, bool externalData) :
		MovableObject(name),
		mBoundingRadius(0.0f), 
		mWorldSpace(false),
		mCullIndividual(false),
		mZRotated(false),
		mAllDefaultSize(true)
	{
		setMaterialName("BaseWhite");
		mCastShadows = false;
	}
	//-----------------------------------------------------------------------
	PrimitiveShapeSet::~PrimitiveShapeSet(void)
	{
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::setMaterialName(const String& name)
	{
		mMaterialName = name;

		if (ParticleSystemManager::getSingletonPtr()->isAutoLoadMaterials())
		{
			mpMaterial = Ogre::MaterialManager::getSingleton().getByName(name);

			if (mpMaterial.isNull())
				EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Could not find material " + name,
				"PrimitiveShapeSet::setMaterialName" );
	
			/** Load material if not already loaded
			*/
			mpMaterial->load();
		}
	}
	//-----------------------------------------------------------------------
	const String& PrimitiveShapeSet::getMaterialName(void) const
	{
		return mMaterialName;
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::_notifyCurrentCamera(Camera* cam)
    {
		Ogre::MovableObject::_notifyCurrentCamera(cam);
		mCurrentCamera = cam;
    }
	//-----------------------------------------------------------------------
	const AxisAlignedBox& PrimitiveShapeSet::getBoundingBox(void) const
	{
		return mAABB;
	}
	//-----------------------------------------------------------------------
	const Ogre::MaterialPtr& PrimitiveShapeSet::getMaterial(void) const
	{
		return mpMaterial;
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::_notifyResized(void)
	{
		mAllDefaultSize = false;
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::getWorldTransforms(Ogre::Matrix4* xform) const
	{
		if (mWorldSpace)
		{
			*xform = Ogre::Matrix4::IDENTITY;
		}
		else
		{
			*xform = _getParentNodeFullTransform();
		}
	}
	//-----------------------------------------------------------------------
    const Quaternion& PrimitiveShapeSet::getWorldOrientation(void) const
	{
		return mParentNode->_getDerivedOrientation();
	}
	//-----------------------------------------------------------------------
	const Vector3& PrimitiveShapeSet::getWorldPosition(void) const
	{
		return mParentNode->_getDerivedPosition();
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::setZRotated(bool zRotated)
	{
		mZRotated = zRotated;
	}
	//-----------------------------------------------------------------------
	bool PrimitiveShapeSet::isZRotated(void) const
	{
		return mZRotated;
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::_notifyZRotated(void)
	{
		mZRotated = true;
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::rotateTexture(Real speed)
	{
		// Get the material and rotate it, assume the material is loaded already, otherwise skip.
		Ogre::MaterialPtr material = getMaterial();
		if (material.isNull())
			return;

		Ogre::TextureUnitState::EffectMap::const_iterator it;
		unsigned short numberOfTechniques = material->getNumTechniques();
		for (unsigned short u = 0; u < numberOfTechniques; ++u)
		{
			Ogre::Technique* technique = material->getTechnique(u);
			unsigned short numberOfPasses = technique->getNumPasses();
			for (unsigned short v = 0; v < numberOfPasses; ++v)
			{
				Ogre::Pass* pass = technique->getPass(v);
				unsigned short numberOfTextureUnitStates = pass->getNumTextureUnitStates();
				for (unsigned short w = 0; w < numberOfTextureUnitStates; ++w)
				{
					// Set the rotation if not already available.
					// This can only be done once! Changing the rotationspeed or removing the rotation
					// and resetting it doesn´t seem to work.
					Ogre::TextureUnitState* textureUnitState = pass->getTextureUnitState(w);
					it = textureUnitState->getEffects().find(Ogre::TextureUnitState::ET_ROTATE);
					if (it == textureUnitState->getEffects().end())
					{
						textureUnitState->setRotateAnimation(speed);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	bool PrimitiveShapeSet::isCullIndividually(void) const
	{
		return mCullIndividual;
	}
	//-----------------------------------------------------------------------
	void PrimitiveShapeSet::setCullIndividually(bool cullIndividual)
	{
		mCullIndividual = cullIndividual;
	}
	//-----------------------------------------------------------------------
	uint32 PrimitiveShapeSet::getTypeFlags(void) const
	{
		return Ogre::SceneManager::FX_TYPE_MASK;
	}
	//-----------------------------------------------------------------------
	Real PrimitiveShapeSet::getSquaredViewDepth(const Camera* const cam) const
	{
		assert(mParentNode);
		return mParentNode->getSquaredViewDepth(cam);
	}
	//-----------------------------------------------------------------------
	Real PrimitiveShapeSet::getBoundingRadius(void) const
	{
		return mBoundingRadius;
	}
	//-----------------------------------------------------------------------
	const Ogre::LightList& PrimitiveShapeSet::getLights(void) const
	{
		return queryLights();
	}

}
