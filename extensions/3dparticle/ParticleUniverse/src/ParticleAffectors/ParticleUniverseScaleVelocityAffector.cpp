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

#include "ParticleAffectors/ParticleUniverseScaleVelocityAffector.h"

namespace ParticleUniverse
{
	// Constants
	const Real ScaleVelocityAffector::DEFAULT_VELOCITY_SCALE = 1.0f;

	//-----------------------------------------------------------------------
	ScaleVelocityAffector::ScaleVelocityAffector(void) : 
		ParticleAffector(),
		mSinceStartSystem(false),
		mStopAtFlip(false)
	{
		mDynScaleVelocity = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynScaleVelocity))->setValue(DEFAULT_VELOCITY_SCALE);
	}
	//-----------------------------------------------------------------------
	ScaleVelocityAffector::~ScaleVelocityAffector(void)
	{
		if (mDynScaleVelocity)
		{
			PU_DELETE_T(mDynScaleVelocity, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleVelocity = 0;
		}
	}
	//-----------------------------------------------------------------------
	void ScaleVelocityAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		Real ds = 0;
		if (mSinceStartSystem)
		{
			// If control points are used (curved type), the first value of each control point is seconds from the start of the system
			ds = timeElapsed * mDynamicAttributeHelper.calculate(mDynScaleVelocity, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
		}
		else
		{
			// If control points are used (curved type), the first value of each control point is the fraction of the particle lifetime [0..1]
			ds = timeElapsed * mDynamicAttributeHelper.calculate(mDynScaleVelocity, particle->timeFraction);
		}
		Real length = particle->direction.length(); // Use length for a better delta direction value
		Vector3 calculated = particle->direction;
		//particle->direction.x += ds * (particle->direction.x / length);
		//particle->direction.y += ds * (particle->direction.y / length);
		//particle->direction.z += ds * (particle->direction.z / length);
		calculated.x += ds * (particle->direction.x / length);
		calculated.y += ds * (particle->direction.y / length);
		calculated.z += ds * (particle->direction.z / length);

		if (mStopAtFlip)
		{
			if (calculated.x > 0.0f && particle->direction.x < 0.0f ||
				calculated.y > 0.0f && particle->direction.y < 0.0f ||
				calculated.z > 0.0f && particle->direction.z < 0.0f ||
				calculated.x < 0.0f && particle->direction.x > 0.0f ||
				calculated.y < 0.0f && particle->direction.y > 0.0f ||
				calculated.z < 0.0f && particle->direction.z > 0.0f)
			return;
		}

		particle->direction = calculated;
	}
	//-----------------------------------------------------------------------
	void ScaleVelocityAffector::setDynScaleVelocity(DynamicAttribute* dynScaleVelocity)
	{
		if (mDynScaleVelocity)
			PU_DELETE_T(mDynScaleVelocity, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynScaleVelocity = dynScaleVelocity;
	}
	//-----------------------------------------------------------------------
	void ScaleVelocityAffector::resetDynScaleVelocity(bool resetToDefault)
	{
		if (resetToDefault)
		{
			PU_DELETE_T(mDynScaleVelocity, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleVelocity = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
			(static_cast<DynamicAttributeFixed*>(mDynScaleVelocity))->setValue(DEFAULT_VELOCITY_SCALE);
		}
	}
	//-----------------------------------------------------------------------
	void ScaleVelocityAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		ScaleVelocityAffector* scaleVelocityAffector = static_cast<ScaleVelocityAffector*>(affector);
		scaleVelocityAffector->setDynScaleVelocity(mDynamicAttributeFactory.cloneDynamicAttribute(getDynScaleVelocity()));
		scaleVelocityAffector->mSinceStartSystem = mSinceStartSystem;
		scaleVelocityAffector->mStopAtFlip = mStopAtFlip;
	}
}
