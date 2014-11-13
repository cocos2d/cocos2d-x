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

#include "ParticleUniverseAttachable.h"

namespace ParticleUniverse
{
	// Constants
	String Attachable::PU_ATTACHABLE = "PUAttachable";
	//-----------------------------------------------------------------------
	Attachable::Attachable(void) :
		Extern(),
		MovableObject(),
		mAABB(),
		mDistanceThreshold(std::numeric_limits<float>::max()),
		mDistanceThresholdSet(false)
	{
		// The Movableobject name is auto generated to prevent a clash in Ogre
		mBoundingRadius = 1;
		std::stringstream ss; 
		ss << this;
		MovableObject::mName = "PUExtern" + ss.str();
	}
	//-----------------------------------------------------------------------
	void Attachable::_notifyAttached(Ogre::Node* parent, bool isTagPoint)
	{
		MovableObject::_notifyAttached(parent, isTagPoint);
	}
	//-----------------------------------------------------------------------
	void Attachable::_notifyCurrentCamera(Camera* cam)
	{
		Ogre::MovableObject::_notifyCurrentCamera(cam);
	}
	//-----------------------------------------------------------------------
	const String& Attachable::getMovableType(void) const
	{
		return PU_ATTACHABLE;
	}
	//-----------------------------------------------------------------------
	const AxisAlignedBox& Attachable::getBoundingBox(void) const
	{
		return mAABB;
	}
	//-----------------------------------------------------------------------
	Real Attachable::getBoundingRadius(void) const
	{
		return mBoundingRadius;
	}
	//-----------------------------------------------------------------------
	const Real Attachable::getDistanceThreshold(void) const
	{
		return mDistanceThreshold;
	}
	//-----------------------------------------------------------------------
	void Attachable::setDistanceThreshold(const Real distanceThreshold)
	{
		mDistanceThresholdSet = true;
		mDistanceThreshold = distanceThreshold;
	}
	//-----------------------------------------------------------------------
	void Attachable::_updateRenderQueue(Ogre::RenderQueue* queue)
	{
		// Nothing to do here.
	}
	//-----------------------------------------------------------------------
	void Attachable::copyAttributesTo (Extern* externObject)
	{
		Extern::copyAttributesTo(externObject);
		Attachable* attachable = static_cast<Attachable*>(externObject);
		attachable->setDistanceThreshold(mDistanceThreshold);
	}
	//-----------------------------------------------------------------------
	void Attachable::_prepare(ParticleTechnique* technique)
	{
		// Nothing to do here.
	}
	//-----------------------------------------------------------------------
	void Attachable::_unprepare(ParticleTechnique* technique)
	{
		// Nothing to do here.
	}
	//-----------------------------------------------------------------------
	void Attachable::_interface(ParticleTechnique* technique, 
		Particle* particle, 
		Real timeElapsed)
	{
		// Nothing to do here.
	}

}
