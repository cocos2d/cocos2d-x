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

#include "ParticleRenderers/ParticleUniverseSphere.h"
#include "ParticleRenderers/ParticleUniverseSphereSet.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	Sphere::Sphere(void):
        mOwnRadius(false),
		mPosition(Vector3::ZERO),
		mColour(ColourValue::White),
        mParentSet(0),
		mRadius(100.0f),
		mRadiusChanged(false)
	{
		mOrientation = Quaternion::IDENTITY;
	}
    //-----------------------------------------------------------------------
    Sphere::Sphere(const Vector3& position, SphereSet* owner) :
        mOwnRadius(false),
		mPosition(Vector3::ZERO),
		mColour(ColourValue::White),
        mParentSet(0),
		mRadius(10.0f),
		mRadiusChanged(false)
	{
		mOrientation = Quaternion::IDENTITY;
	}
	//-----------------------------------------------------------------------
	Sphere::~Sphere(void)
	{
	}
	//-----------------------------------------------------------------------
	void Sphere::setPosition(const Vector3& position)
	{
		mPosition = position;
	}
	//-----------------------------------------------------------------------
	void Sphere::setPosition(Real x, Real y, Real z)
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
	}
	//-----------------------------------------------------------------------
	const Vector3& Sphere::getPosition(void) const
	{
		return mPosition;
	}
	//-----------------------------------------------------------------------
	void Sphere::setRadius(Real radius)
	{
		mOwnRadius = true;
		mRadius = radius;
		if (mParentSet)
			mParentSet->_notifyResized();
		mRadiusChanged = true;
    }
	//-----------------------------------------------------------------------
	bool Sphere::hasOwnRadius(void) const
	{
		return mOwnRadius;
	}
	//-----------------------------------------------------------------------
	void Sphere::_notifyOwner(SphereSet* owner)
	{
		mParentSet = owner;
	}
	//-----------------------------------------------------------------------
	void Sphere::setColour(const ColourValue& colour)
	{
		mColour = colour;
	}
	//-----------------------------------------------------------------------
	const ColourValue& Sphere::getColour(void) const
	{
		return mColour;
	}
	//-----------------------------------------------------------------------
	Real Sphere::getOwnRadius(void) const
	{
		return mRadius;
	}

}
