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

#include "ParticleAffectors/ParticleUniverseScaleAffector.h"

namespace ParticleUniverse
{
	// Constants
	const Real ScaleAffector::DEFAULT_X_SCALE = 1.0f;
	const Real ScaleAffector::DEFAULT_Y_SCALE = 1.0f;
	const Real ScaleAffector::DEFAULT_Z_SCALE = 1.0f;
	const Real ScaleAffector::DEFAULT_XYZ_SCALE = 1.0f;

	//-----------------------------------------------------------------------
	ScaleAffector::ScaleAffector(void) : 
		ParticleAffector(),
		mDynScaleXSet(false),
		mDynScaleYSet(false),
		mDynScaleZSet(false),
		mDynScaleXYZSet(false),
		mSinceStartSystem(false)
	{
		mDynScaleX = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		mDynScaleY = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		mDynScaleZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		mDynScaleXYZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynScaleX))->setValue(DEFAULT_X_SCALE);
		(static_cast<DynamicAttributeFixed*>(mDynScaleY))->setValue(DEFAULT_Y_SCALE);
		(static_cast<DynamicAttributeFixed*>(mDynScaleZ))->setValue(DEFAULT_Z_SCALE);
		(static_cast<DynamicAttributeFixed*>(mDynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
		mLatestTimeElapsed = 1.0f;
	}
	//-----------------------------------------------------------------------
	ScaleAffector::~ScaleAffector(void)
	{
		if (mDynScaleX)
		{
			PU_DELETE_T(mDynScaleX, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleX = 0;
		}
		if (mDynScaleY)
		{
			PU_DELETE_T(mDynScaleY, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleY = 0;
		}
		if (mDynScaleZ)
		{
			PU_DELETE_T(mDynScaleZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleZ = 0;
		}
		if (mDynScaleXYZ)
		{
			PU_DELETE_T(mDynScaleXYZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleXYZ = 0;
		}
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		// Only continue if the particle is a visual particle
		if (particle->particleType != Particle::PT_VISUAL)
			return;

		VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
		Real ds = 0;
		Real width = 0;
		Real height = 0;
		Real depth = 0;
		Real dimension = 0; // Added in V1.4

		if (mDynScaleXYZSet)
		{
			ds = _calculateScale(mDynScaleXYZ, particle) * timeElapsed * _calculateAffectSpecialisationFactor(particle);
			dimension = visualParticle->width + ds * _mAffectorScale.x;
			if (dimension > 0)
			{
				width = dimension;
			}
			dimension = visualParticle->height + ds * _mAffectorScale.y;
			if (dimension > 0)
			{
				height = dimension;
			}
			dimension = visualParticle->depth + ds * _mAffectorScale.z;
			if (dimension > 0)
			{
				depth = dimension;
			}
			visualParticle->setOwnDimensions(width, height, depth);
		}
		else
		{
			if (mDynScaleXSet)
			{
				ds = _calculateScale(mDynScaleX, particle) * timeElapsed;
				dimension = visualParticle->width + ds * _mAffectorScale.x;
				if (dimension > 0)
				{
					width = dimension;
				}
			}
			if (mDynScaleYSet)
			{
				ds = _calculateScale(mDynScaleY, particle) * timeElapsed;
				dimension = visualParticle->height + ds * _mAffectorScale.y;
				if (dimension > 0)
				{
					height = dimension;
				}
			}
			if (mDynScaleZSet)
			{
				ds = _calculateScale(mDynScaleZ, particle) * timeElapsed;
				dimension = visualParticle->depth + ds * _mAffectorScale.z;
				if (dimension > 0)
				{
					depth = dimension;
				}
			}
			visualParticle->setOwnDimensions(width, height, depth);
		}
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::setDynScaleX(DynamicAttribute* dynScaleX)
	{
		if (mDynScaleX)
			PU_DELETE_T(mDynScaleX, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynScaleX = dynScaleX;
		mDynScaleXSet = true;
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::resetDynScaleX(bool resetToDefault)
	{
		if (resetToDefault)
		{
			PU_DELETE_T(mDynScaleX, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleX = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
			(static_cast<DynamicAttributeFixed*>(mDynScaleX))->setValue(DEFAULT_X_SCALE);
			mDynScaleXSet = false;
		}
		else
		{
			mDynScaleXSet = true;
		}
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::setDynScaleY(DynamicAttribute* dynScaleY)
	{
		if (mDynScaleY)
			PU_DELETE_T(mDynScaleY, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynScaleY = dynScaleY;
		mDynScaleYSet = true;
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::resetDynScaleY(bool resetToDefault)
	{
		if (resetToDefault)
		{
			PU_DELETE_T(mDynScaleY, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleY = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
			(static_cast<DynamicAttributeFixed*>(mDynScaleY))->setValue(DEFAULT_X_SCALE);
			mDynScaleYSet = false;
		}
		else
		{
			mDynScaleYSet = true;
		}
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::setDynScaleZ(DynamicAttribute* dynScaleZ)
	{
		if (mDynScaleZ)
			PU_DELETE_T(mDynScaleZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynScaleZ = dynScaleZ;
		mDynScaleZSet = true;
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::resetDynScaleZ(bool resetToDefault)
	{
		if (resetToDefault)
		{
			PU_DELETE_T(mDynScaleZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
			(static_cast<DynamicAttributeFixed*>(mDynScaleZ))->setValue(DEFAULT_X_SCALE);
			mDynScaleYSet = false;
		}
		else
		{
			mDynScaleYSet = true;
		}
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::setDynScaleXYZ(DynamicAttribute* dynScaleXYZ)
	{
		if (mDynScaleXYZ)
			PU_DELETE_T(mDynScaleXYZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynScaleXYZ = dynScaleXYZ;
		mDynScaleXYZSet = true;
	}
	//-----------------------------------------------------------------------
	void ScaleAffector::resetDynScaleXYZ(bool resetToDefault)
	{
		if (resetToDefault)
		{
			PU_DELETE_T(mDynScaleXYZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			mDynScaleXYZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
			(static_cast<DynamicAttributeFixed*>(mDynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
			mDynScaleXYZSet = false;
		}
		else
		{
			mDynScaleXYZSet = true;
		}
	}
	//-----------------------------------------------------------------------
	Real ScaleAffector::_calculateScale(DynamicAttribute* dynScale, Particle* particle)
    {
		if (!particle)
			return 0.0f;

		if (mSinceStartSystem)
		{
			// If control points are used (curved type), the first value of each control point is seconds from the start of the system
			return mDynamicAttributeHelper.calculate(dynScale, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
		}
		else
		{
			// If control points are used (curved type), the first value of each control point is the fraction of the particle lifetime [0..1]
			return mDynamicAttributeHelper.calculate(dynScale, particle->timeFraction);
		}
    }
	//-----------------------------------------------------------------------
	void ScaleAffector::copyAttributesTo (ParticleAffector* affector)
	{
		ParticleAffector::copyAttributesTo(affector);

		ScaleAffector* scaleAffector = static_cast<ScaleAffector*>(affector);
		scaleAffector->setDynScaleX(mDynamicAttributeFactory.cloneDynamicAttribute(getDynScaleX()));
		scaleAffector->setDynScaleY(mDynamicAttributeFactory.cloneDynamicAttribute(getDynScaleY()));
		scaleAffector->setDynScaleZ(mDynamicAttributeFactory.cloneDynamicAttribute(getDynScaleZ()));
		scaleAffector->setDynScaleXYZ(mDynamicAttributeFactory.cloneDynamicAttribute(getDynScaleXYZ()));
		scaleAffector->mDynScaleXSet = mDynScaleXSet;
		scaleAffector->mDynScaleYSet = mDynScaleYSet;
		scaleAffector->mDynScaleZSet = mDynScaleZSet;
		scaleAffector->mDynScaleXYZSet = mDynScaleXYZSet;
		scaleAffector->mSinceStartSystem = mSinceStartSystem;
	}
}
