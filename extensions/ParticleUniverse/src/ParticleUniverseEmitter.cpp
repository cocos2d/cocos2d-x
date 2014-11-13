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

#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	// Constants
	const bool ParticleEmitter::DEFAULT_ENABLED = true;
	const Vector3 ParticleEmitter::DEFAULT_POSITION(0, 0, 0);
	const bool ParticleEmitter::DEFAULT_KEEP_LOCAL = false;
	const Vector3 ParticleEmitter::DEFAULT_DIRECTION(0, 1, 0);
	const Quaternion ParticleEmitter::DEFAULT_ORIENTATION(1, 0, 0, 0);
	const Quaternion ParticleEmitter::DEFAULT_ORIENTATION_RANGE_START(1, 0, 0, 0);
	const Quaternion ParticleEmitter::DEFAULT_ORIENTATION_RANGE_END(1, 0, 0, 0);
	const Particle::ParticleType ParticleEmitter::DEFAULT_EMITS = VisualParticle::PT_VISUAL;
	const uint16 ParticleEmitter::DEFAULT_START_TEXTURE_COORDS = 0;
	const uint16 ParticleEmitter::DEFAULT_END_TEXTURE_COORDS = 0;
	const uint16 ParticleEmitter::DEFAULT_TEXTURE_COORDS = 0;
	const ColourValue ParticleEmitter::DEFAULT_START_COLOUR_RANGE(0, 0, 0);
	const ColourValue ParticleEmitter::DEFAULT_END_COLOUR_RANGE(1, 1, 1);
	const ColourValue ParticleEmitter::DEFAULT_COLOUR(1, 1, 1);
	const bool ParticleEmitter::DEFAULT_AUTO_DIRECTION = false;
	const bool ParticleEmitter::DEFAULT_FORCE_EMISSION = false;
	const Real ParticleEmitter::DEFAULT_EMISSION_RATE = 10.0f;
	const Real ParticleEmitter::DEFAULT_TIME_TO_LIVE = 3.0f;
	const Real ParticleEmitter::DEFAULT_MASS = 1.0f;
	const Real ParticleEmitter::DEFAULT_VELOCITY = 100.0f;
	const Real ParticleEmitter::DEFAULT_DURATION = 0.0f;
	const Real ParticleEmitter::DEFAULT_REPEAT_DELAY = 0.0f;
	const Real ParticleEmitter::DEFAULT_ANGLE = 20.0f;
	const Real ParticleEmitter::DEFAULT_DIMENSIONS = 0.0f;
	const Real ParticleEmitter::DEFAULT_WIDTH = 0.0f;
	const Real ParticleEmitter::DEFAULT_HEIGHT = 0.0f;
	const Real ParticleEmitter::DEFAULT_DEPTH = 0.0f;

	//-----------------------------------------------------------------------
	ParticleEmitter::ParticleEmitter(void) :
		Particle(),
		IAlias(),
		IElement(),
		mParentTechnique(0),
		mEmitsType(DEFAULT_EMITS),
		mEmitsName(StringUtil::BLANK),
		mRemainder(0),
		mDurationRemain(0),
		mRepeatDelayRemain(0),
		mDynDurationSet(false),
		mDynRepeatDelaySet(false),
		mParticleDirection(DEFAULT_DIRECTION),
		mOriginalParticleDirection(DEFAULT_DIRECTION),
		mParticleOrientation(Quaternion::IDENTITY),
		mParticleOrientationRangeStart(Quaternion::IDENTITY),
		mParticleOrientationRangeEnd(Quaternion::IDENTITY),
		mParticleOrientationRangeSet(false),
		mUpVector(Vector3::ZERO),
		mDynParticleAllDimensionsSet(false),
		mDynParticleWidthSet(false),
		mDynParticleHeightSet(false),
		mDynParticleDepthSet(false),
		mEmissionRateCameraDependency(0),
		mAutoDirection(DEFAULT_AUTO_DIRECTION),
		mForceEmission(DEFAULT_FORCE_EMISSION),
		mOriginalForceEmission(false),
		mForceEmissionExecuted(false),
		mOriginalForceEmissionExecuted(false),
		mName(StringUtil::BLANK),
		_mEmitterScale(Vector3::UNIT_SCALE),
		mParticleColour(DEFAULT_COLOUR),
		mParticleColourRangeStart(DEFAULT_START_COLOUR_RANGE),
		mParticleColourRangeEnd(DEFAULT_END_COLOUR_RANGE),
		mParticleColourRangeSet(false),
		mKeepLocal(false),
		mParticleTextureCoords(DEFAULT_TEXTURE_COORDS),
		mParticleTextureCoordsRangeStart(DEFAULT_START_TEXTURE_COORDS),
		mParticleTextureCoordsRangeEnd(DEFAULT_END_TEXTURE_COORDS),
		mParticleTextureCoordsRangeSet(false)
	{
		particleType = PT_EMITTER;
		mAliasType = AT_EMITTER;
		mDynEmissionRate = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynEmissionRate))->setValue(DEFAULT_EMISSION_RATE);
		mDynTotalTimeToLive = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynTotalTimeToLive))->setValue(DEFAULT_TIME_TO_LIVE);
		mDynParticleMass = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynParticleMass))->setValue(DEFAULT_MASS);
		mDynVelocity = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynVelocity))->setValue(DEFAULT_VELOCITY);
		mDynDuration = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynDuration))->setValue(DEFAULT_DURATION);
		mDynRepeatDelay = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynRepeatDelay))->setValue(DEFAULT_REPEAT_DELAY);
		mDynAngle = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynAngle))->setValue(DEFAULT_ANGLE);

		// Set the dimensions attributes to 0; the default is to use the default dimensions of the ParticleTechnique
		mDynParticleAllDimensions = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynParticleAllDimensions))->setValue(DEFAULT_DIMENSIONS);
		mDynParticleWidth = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynParticleWidth))->setValue(DEFAULT_WIDTH);
		mDynParticleHeight = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynParticleHeight))->setValue(DEFAULT_HEIGHT);
		mDynParticleDepth = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
		(static_cast<DynamicAttributeFixed*>(mDynParticleDepth))->setValue(DEFAULT_DEPTH);
	}
	//-----------------------------------------------------------------------
	ParticleEmitter::~ParticleEmitter(void)
	{
		if (mDynEmissionRate)
			PU_DELETE_T(mDynEmissionRate, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynTotalTimeToLive)
			PU_DELETE_T(mDynTotalTimeToLive, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynParticleMass)
			PU_DELETE_T(mDynParticleMass, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynVelocity)
			PU_DELETE_T(mDynVelocity, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynDuration)
			PU_DELETE_T(mDynDuration, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynRepeatDelay)
			PU_DELETE_T(mDynRepeatDelay, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynParticleAllDimensions)
			PU_DELETE_T(mDynParticleAllDimensions, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynParticleWidth)
			PU_DELETE_T(mDynParticleWidth, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynParticleHeight)
			PU_DELETE_T(mDynParticleHeight, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mDynParticleDepth)
			PU_DELETE_T(mDynParticleDepth, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		if (mEmissionRateCameraDependency)
			mCameraDependencyFactory.destroy(mEmissionRateCameraDependency);

		if (mDynAngle)
			PU_DELETE_T(mDynAngle, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
	}
	//-----------------------------------------------------------------------
	bool ParticleEmitter::isKeepLocal(void) const
	{
		return mKeepLocal;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setKeepLocal(bool keepLocal)
	{
		mKeepLocal = keepLocal;
	}
	//-----------------------------------------------------------------------
	bool ParticleEmitter::makeParticleLocal(Particle* particle)
	{
		if (!particle)
			return true;

		if (!mKeepLocal || hasEventFlags(Particle::PEF_EXPIRED))
			return false;

		Vector3 diff = getDerivedPosition() - latestPosition;
		particle->position += diff;
		return true;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_pushEmitterEvent(EventType eventType)
	{
		// Create the event
		ParticleUniverseEvent evt;
		evt.eventType = eventType;
		evt.componentType = CT_EMITTER;
		evt.componentName = getName();
		evt.technique = 0;
		evt.emitter = this;
		pushEvent(evt);
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::pushEvent(ParticleUniverseEvent& particleUniverseEvent)
	{
		// Forward the event
		if (mParentTechnique)
		{
			mParentTechnique->pushEvent(particleUniverseEvent);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_notifyStart (void)
	{
		latestPosition = getDerivedPosition(); // V1.3.1
		mForceEmission = mOriginalForceEmission;
		mForceEmissionExecuted = mOriginalForceEmissionExecuted;
		mRemainder = 0;
		mDurationRemain = 0;
		mRepeatDelayRemain = 0;
		setEnabled(mOriginalEnabled); // Also calls _initTimeBased

		// Generate the event
		_pushEmitterEvent(PU_EVT_EMITTER_STARTED);
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_notifyStop (void)
	{
		// Generate the event
		_pushEmitterEvent(PU_EVT_EMITTER_STOPPED);
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_notifyRescaled(const Vector3& scale)
	{
		_mEmitterScale = scale;
	}
	//-----------------------------------------------------------------------
	const Vector3& ParticleEmitter::getDerivedPosition(void)
	{
		if (mMarkedForEmission)
		{
			// Use the emitter position, because it is emitted
			// If a particle is emitted, position and derived position are the same
			mDerivedPosition = position;
		}
		else
		{
			// Add the techniques' derived position. Use the emiters' own 'position' as offset.
			mDerivedPosition = mParentTechnique->getDerivedPosition() + mParentTechnique->getParentSystem()->getDerivedOrientation() * 
				(_mEmitterScale * position);
		}
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	const ColourValue& ParticleEmitter::getParticleColour(void) const
	{
		return mParticleColour;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleColour(const ColourValue& particleColour)
	{
		mParticleColour = particleColour;
	}
	//-----------------------------------------------------------------------
	const ColourValue& ParticleEmitter::getParticleColourRangeStart(void) const
	{
		return mParticleColourRangeStart;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleColourRangeStart(const ColourValue& particleColourRangeStart)
	{
		mParticleColourRangeStart = particleColourRangeStart;
		mParticleColourRangeSet = true;
	}
	//-----------------------------------------------------------------------
	const ColourValue& ParticleEmitter::getParticleColourRangeEnd(void) const
	{
		return mParticleColourRangeEnd;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleColourRangeEnd(const ColourValue& particleColourRangeEnd)
	{
		mParticleColourRangeEnd = particleColourRangeEnd;
		mParticleColourRangeSet = true;
	}
	//-----------------------------------------------------------------------
	const uint16& ParticleEmitter::getParticleTextureCoords(void) const
	{
		return mParticleTextureCoords;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleTextureCoords(const uint16& particleTextureCoords)
	{
		mParticleTextureCoords = particleTextureCoords;
	}
	//-----------------------------------------------------------------------
	const uint16& ParticleEmitter::getParticleTextureCoordsRangeStart(void) const
	{
		return mParticleTextureCoordsRangeStart;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleTextureCoordsRangeStart(const uint16& particleTextureCoordsRangeStart)
	{
		mParticleTextureCoordsRangeStart = particleTextureCoordsRangeStart;
		mParticleTextureCoordsRangeSet = true;
	}
	//-----------------------------------------------------------------------
	const uint16& ParticleEmitter::getParticleTextureCoordsRangeEnd(void) const
	{
		return mParticleTextureCoordsRangeEnd;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleTextureCoordsRangeEnd(const uint16& particleTextureCoordsRangeEnd)
	{
		mParticleTextureCoordsRangeEnd = particleTextureCoordsRangeEnd;
		mParticleTextureCoordsRangeSet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::copyAttributesTo(ParticleEmitter* emitter)
	{
		copyParentAttributesTo(emitter);
		emitter->setEmitterType(mEmitterType);
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::copyParentAttributesTo(ParticleEmitter* emitter)
	{
		// Copy Parent attributes
		Particle::copyAttributesTo(emitter);

		emitter->setName(mName);
		emitter->setEmitsName(mEmitsName);
		emitter->setEmitsType(mEmitsType);
		emitter->mParticleDirection = mParticleDirection;
		emitter->mOriginalParticleDirection = mOriginalParticleDirection;
		emitter->mParticleOrientation = mParticleOrientation;
		emitter->mParticleOrientationRangeStart = mParticleOrientationRangeStart;
		emitter->mParticleOrientationRangeEnd = mParticleOrientationRangeEnd;
		emitter->mParticleOrientationRangeSet = mParticleOrientationRangeSet;
		emitter->mMarkedForEmission = mMarkedForEmission;
		emitter->mParentTechnique = mParentTechnique;
		emitter->setEmissionRateCameraDependency (mCameraDependencyFactory.clone(getEmissionRateCameraDependency()));
		emitter->mAutoDirection = mAutoDirection;
		emitter->mForceEmission = mForceEmission;
		emitter->mOriginalForceEmission = mOriginalForceEmission;
		emitter->mForceEmissionExecuted = mForceEmissionExecuted;
		emitter->mOriginalForceEmissionExecuted = mOriginalForceEmissionExecuted;
		emitter->mDynDurationSet = mDynDurationSet;
		emitter->mDynRepeatDelaySet = mDynRepeatDelaySet;
		emitter->mDynParticleAllDimensionsSet = mDynParticleAllDimensionsSet;
		emitter->mDynParticleWidthSet = mDynParticleWidthSet;
		emitter->mDynParticleHeightSet = mDynParticleHeightSet;
		emitter->mDynParticleDepthSet = mDynParticleDepthSet;
		emitter->_mEmitterScale = _mEmitterScale;
		emitter->mParticleColour = mParticleColour;
		emitter->mParticleColourRangeStart = mParticleColourRangeStart;
		emitter->mParticleColourRangeEnd = mParticleColourRangeEnd;
		emitter->mParticleColourRangeSet = mParticleColourRangeSet;
		emitter->mParticleTextureCoords = mParticleTextureCoords;
		emitter->mParticleTextureCoordsRangeStart = mParticleTextureCoordsRangeStart;
		emitter->mParticleTextureCoordsRangeEnd = mParticleTextureCoordsRangeEnd;
		emitter->mParticleTextureCoordsRangeSet = mParticleTextureCoordsRangeSet;
		emitter->mKeepLocal = mKeepLocal;

		// Copy Dyn. Emission rate if available
		emitter->setDynEmissionRate(mDynamicAttributeFactory.cloneDynamicAttribute(getDynEmissionRate()));

		// Copy Dyn. Total time to live if available
		emitter->setDynTotalTimeToLive(mDynamicAttributeFactory.cloneDynamicAttribute(getDynTotalTimeToLive()));

		// Copy Dyn. Velocity if available
		emitter->setDynVelocity(mDynamicAttributeFactory.cloneDynamicAttribute(getDynVelocity()));

		// Copy Dyn. Duration if available
		if (mDynDurationSet)
		{
			emitter->setDynDuration(mDynamicAttributeFactory.cloneDynamicAttribute(getDynDuration()));
		}

		// Copy Dyn. RepeatDelay if available
		if (mDynRepeatDelaySet)
		{
			emitter->setDynRepeatDelay(mDynamicAttributeFactory.cloneDynamicAttribute(getDynRepeatDelay()));
		}

		// Copy Dyn. Particle Mass if available
		emitter->setDynParticleMass(mDynamicAttributeFactory.cloneDynamicAttribute(getDynParticleMass()));

		// Copy Dyn. Angle if available
		emitter->setDynAngle(mDynamicAttributeFactory.cloneDynamicAttribute(getDynAngle()));

		// Copy Dyn. own width, height and depth if available
		if (mDynParticleAllDimensionsSet)
		{
			emitter->setDynParticleAllDimensions(mDynamicAttributeFactory.cloneDynamicAttribute(getDynParticleAllDimensions()));
		}
		if (mDynParticleWidthSet)
		{
			emitter->setDynParticleWidth(mDynamicAttributeFactory.cloneDynamicAttribute(getDynParticleWidth()));
		}
		if (mDynParticleHeightSet)
		{
			emitter->setDynParticleHeight(mDynamicAttributeFactory.cloneDynamicAttribute(getDynParticleHeight()));
		}
		if (mDynParticleDepthSet)
		{
			emitter->setDynParticleDepth(mDynamicAttributeFactory.cloneDynamicAttribute(getDynParticleDepth()));
		}
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParentTechnique(ParticleTechnique* parentTechnique)
	{
		mParentTechnique = parentTechnique;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setEmitsName(const String& emitsName)
	{
		mEmitsName = emitsName;
		if (mEmitsName != StringUtil::BLANK)
		{
			mMarkedForEmission = true;
			if (mParentTechnique)
			{
				// Notify the Technique that something changed
				mParentTechnique->_notifyEmissionChange();
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setEmissionRateCameraDependency(CameraDependency* cameraDependency)
	{
		if (mEmissionRateCameraDependency)
			mCameraDependencyFactory.destroy(mEmissionRateCameraDependency);

		mEmissionRateCameraDependency = cameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setEmissionRateCameraDependency(Real squareDistance, bool inc)
	{
		if (!mEmissionRateCameraDependency)
		{
			mEmissionRateCameraDependency = mCameraDependencyFactory.create(squareDistance, inc);
		}
		else
		{
			mEmissionRateCameraDependency->setThreshold(squareDistance);
			mEmissionRateCameraDependency->setIncrease(inc);
		}
	}
	//-----------------------------------------------------------------------
	CameraDependency* ParticleEmitter::getEmissionRateCameraDependency(void) const
	{
		return mEmissionRateCameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynEmissionRate(DynamicAttribute* dynEmissionRate)
	{
		if (mDynEmissionRate)
			PU_DELETE_T(mDynEmissionRate, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynEmissionRate = dynEmissionRate;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynTotalTimeToLive(DynamicAttribute* dynTotalTimeToLive)
	{
		if (mDynTotalTimeToLive)
			PU_DELETE_T(mDynTotalTimeToLive, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynTotalTimeToLive = dynTotalTimeToLive;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleMass(DynamicAttribute* dynParticleMass)
	{
		if (mDynParticleMass)
			PU_DELETE_T(mDynParticleMass, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynParticleMass = dynParticleMass;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynAngle(DynamicAttribute* dynAngle)
	{
		if (mDynAngle)
			PU_DELETE_T(mDynAngle, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynAngle = dynAngle;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynVelocity(DynamicAttribute* dynVelocity)
	{
		if (mDynVelocity)
			PU_DELETE_T(mDynVelocity, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynVelocity = dynVelocity;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynDuration(DynamicAttribute* dynDuration)
	{
		if (mDynDuration)
			PU_DELETE_T(mDynDuration, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynDuration = dynDuration;
		mDynDurationSet = true;
		_initTimeBased();
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynDurationSet(bool durationSet)
	{
		mDynDurationSet = durationSet;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynRepeatDelay(DynamicAttribute* dynRepeatDelay)
	{
		if (mDynRepeatDelay)
			PU_DELETE_T(mDynRepeatDelay, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynRepeatDelay = dynRepeatDelay;
		mDynRepeatDelaySet = true;
		_initTimeBased();
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynRepeatDelaySet(bool repeatDelaySet)
	{
		mDynRepeatDelaySet = repeatDelaySet;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleAllDimensions(DynamicAttribute* dynParticleAllDimensions)
	{
		if (mDynParticleAllDimensions)
			PU_DELETE_T(mDynParticleAllDimensions, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynParticleAllDimensions = dynParticleAllDimensions;
		mDynParticleAllDimensionsSet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleAllDimensionsSet(bool particleAllDimensionsSet)
	{
		mDynParticleAllDimensionsSet = particleAllDimensionsSet;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleWidth(DynamicAttribute* dynParticleWidth)
	{
		if (mDynParticleWidth)
			PU_DELETE_T(mDynParticleWidth, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynParticleWidth = dynParticleWidth;
		mDynParticleWidthSet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleWidthSet(bool particleWidthSet)
	{
		mDynParticleWidthSet = particleWidthSet;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleHeight(DynamicAttribute* dynParticleHeight)
	{
		if (mDynParticleHeight)
			PU_DELETE_T(mDynParticleHeight, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynParticleHeight = dynParticleHeight;
		mDynParticleHeightSet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleHeightSet(bool particleHeightSet)
	{
		mDynParticleHeightSet = particleHeightSet;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleDepth(DynamicAttribute* dynParticleDepth)
	{
		if (mDynParticleDepth)
			PU_DELETE_T(mDynParticleDepth, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);

		mDynParticleDepth = dynParticleDepth;
		mDynParticleDepthSet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setDynParticleDepthSet(bool particleDepthSet)
	{
		mDynParticleDepthSet = particleDepthSet;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setEnabled(bool enabled)
	{
		Particle::setEnabled(enabled);
		_initTimeBased();
    }
	//-----------------------------------------------------------------------
	const Vector3& ParticleEmitter::getParticleDirection(void)
	{
		return mParticleDirection;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleDirection(const Vector3& direction)
	{
		mParticleDirection = direction;
		mOriginalParticleDirection = direction;
		mParticleDirection.normalise();
		mUpVector = mParticleDirection.perpendicular();
		mUpVector.normalise();
    }
	//-----------------------------------------------------------------------
	const Vector3& ParticleEmitter::getOriginalParticleDirection(void) const
	{
		return mOriginalParticleDirection;
	}
	//-----------------------------------------------------------------------
	const Quaternion& ParticleEmitter::getParticleOrientation(void) const
	{
		return mParticleOrientation;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleOrientation(const Quaternion& orientation)
	{
		mParticleOrientation = orientation;
    }
	//-----------------------------------------------------------------------
	const Quaternion& ParticleEmitter::getParticleOrientationRangeStart(void) const
	{
		return mParticleOrientationRangeStart;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleOrientationRangeStart(const Quaternion& orientationRangeStart)
	{
		mParticleOrientationRangeStart = orientationRangeStart;
		mParticleOrientationRangeSet = true;
    }
	//-----------------------------------------------------------------------
	const Quaternion& ParticleEmitter::getParticleOrientationRangeEnd(void) const
	{
		return mParticleOrientationRangeEnd;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setParticleOrientationRangeEnd(const Quaternion& orientationRangeEnd)
	{
		mParticleOrientationRangeEnd = orientationRangeEnd;
		mParticleOrientationRangeSet = true;
    }
	//-----------------------------------------------------------------------
	bool ParticleEmitter::isAutoDirection(void) const
	{
		return mAutoDirection;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setAutoDirection(bool autoDirection)
	{
		mAutoDirection = autoDirection;
    }
	//-----------------------------------------------------------------------
	bool ParticleEmitter::isForceEmission(void) const
	{
		return mForceEmission;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::setForceEmission(bool forceEmission)
	{
		mForceEmission = forceEmission;
		mOriginalForceEmission = forceEmission;
		mForceEmissionExecuted = false;
		mOriginalForceEmissionExecuted = false;
    }
	//-----------------------------------------------------------------------
	void ParticleEmitter::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		// Calculate the emitters' position so it is safe to use mDerivedPosition).
		getDerivedPosition();
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_postProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		// Added in V1.3.1
		latestPosition = getDerivedPosition();
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initTimeBased(void)
    {
		if (mEnabled)
		{
			if (mDynDurationSet && mParentTechnique)
			{
				mDurationRemain = mDynamicAttributeHelper.calculate(mDynDuration, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
			}

			/** Determine whether duration must be used. If it is used, the emitter should at least be enabled.
			@remarks
				Note, that if the duration has been exceeded, the emitter is disabled. It makes perfect sense to enable 
				the emitter again when the duration is initialised with a valid value (> 0).
			*/
			if (mDurationRemain > 0)
			{
				mEnabled = true;
				mRepeatDelayRemain = 0;
			}
		}
		else
		{
			if (mDynRepeatDelaySet && mParentTechnique)
			{
				mRepeatDelayRemain = mDynamicAttributeHelper.calculate(mDynRepeatDelay, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initForEmission(void)
	{
		// The emitter itself is emitted.
		Particle::_initForEmission();

		// Emitting an emitter is similar as starting one.
		_notifyStart();
    }
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initForExpiration(ParticleTechnique* technique, Real timeElapsed)
	{
		// The emitter itself is expired.
		Particle::_initForExpiration(technique, timeElapsed);

		// Expiring an emitter is similar as stopping one.
		_notifyStop();
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticlePosition(Particle* particle)
	{
		particle->position = getDerivedPosition();
		particle->originalPosition = particle->position;
		particle->latestPosition = particle->position;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticleForEmission(Particle* particle)
	{
		// Initialise the particle position (localspace)
		particle->parentEmitter = this;
		_initParticlePosition(particle);
		_initParticleDirection(particle);
		_initParticleVelocity(particle);
		_initParticleOrientation(particle);
		_initParticleMass(particle);
		_initParticleColour(particle);
		_initParticleTextureCoords(particle);
		particle->totalTimeToLive = _initParticleTimeToLive();
		particle->timeToLive = particle->totalTimeToLive;
		
		// Generate particles' own dimensions if defined.
		_initParticleDimensions(particle);
	}
	//-----------------------------------------------------------------------
    void ParticleEmitter::_initParticleDirection(Particle* particle)
    {
		// Use the default way of initialising the particle direction
		Radian angle;
		_generateAngle(angle);
		if (angle != Radian(0))
		{
			particle->direction = mParticleDirection.randomDeviant(angle, mUpVector);
		}
		else
		{
			particle->direction = mParticleDirection;
		}
		particle->originalDirection = particle->direction;
		particle->originalDirectionLength = particle->direction.length();
    }
	//-----------------------------------------------------------------------
	void ParticleEmitter::_generateAngle(Radian& angle)
	{
		Radian a = Angle(mDynamicAttributeHelper.calculate(mDynAngle, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart()));
		angle = a;
		if (mDynAngle->getType() == DynamicAttribute::DAT_FIXED)
		{
			// Make an exception here and don´t use the fixed angle.
			angle = Math::UnitRandom() * angle;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticleVelocity(Particle* particle)
    {
		Real scalar = mDynamicAttributeHelper.calculate(mDynVelocity, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart(), 1.0f);
		particle->direction *= scalar;
		particle->originalVelocity = scalar;
		particle->originalScaledDirectionLength = particle->direction.length();

		// Don´t change the originalDirection, because the real original value has already been set.
    }
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticleOrientation(Particle* particle)
	{
		if (particle->particleType != Particle::PT_VISUAL)
			return;

		VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
		if (mParticleOrientationRangeSet)
		{
			// Generate random orientation 'between' start en end.
			visualParticle->orientation = Quaternion::nlerp(Math::UnitRandom(), 
				mParticleOrientationRangeStart, 
				mParticleOrientationRangeEnd,
				true);
		}
		else
		{
			visualParticle->orientation = mParticleOrientation;
		}

		// Set original orientation
		visualParticle->originalOrientation = visualParticle->orientation;
    }
	//-----------------------------------------------------------------------
    void ParticleEmitter::_initParticleMass(Particle* particle)
    {
		Real mass = mDynamicAttributeHelper.calculate(mDynParticleMass, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart(), Particle::DEFAULT_MASS);
		particle->mass = mass;
    }
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticleColour(Particle* particle)
    {
		if (particle->particleType != Particle::PT_VISUAL)
			return;

		VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
		if (mParticleColourRangeSet)
		{
			visualParticle->colour.r = Math::RangeRandom(mParticleColourRangeStart.r, mParticleColourRangeEnd.r);
			visualParticle->colour.g = Math::RangeRandom(mParticleColourRangeStart.g, mParticleColourRangeEnd.g);
			visualParticle->colour.b = Math::RangeRandom(mParticleColourRangeStart.b, mParticleColourRangeEnd.b);
			visualParticle->colour.a = Math::RangeRandom(mParticleColourRangeStart.a, mParticleColourRangeEnd.a);
		}
		else
		{
			visualParticle->colour = mParticleColour;
		}

		// Set original colour
		visualParticle->originalColour = visualParticle->colour;
    }
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticleTextureCoords(Particle* particle)
    {
		if (particle->particleType != Particle::PT_VISUAL)
			return;

		VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
		if (mParticleTextureCoordsRangeSet)
		{
			visualParticle->textureCoordsCurrent = (uint16)Math::RangeRandom((Real)mParticleTextureCoordsRangeStart, (Real)mParticleTextureCoordsRangeEnd + 0.999f);
		}
		else
		{
			visualParticle->textureCoordsCurrent = mParticleTextureCoords;
		}
    }
	//-----------------------------------------------------------------------
    Real ParticleEmitter::_initParticleTimeToLive(void)
    {
		/*  Generate a value for totalTimeToLive. Use time since start from the particle system as argument 
			in getValue(). If mDynTotalTimeToLive doesn´t exist, use the default value.
		*/
		return mDynamicAttributeHelper.calculate(mDynTotalTimeToLive, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart(), Particle::DEFAULT_TTL);
    }
    //-----------------------------------------------------------------------
	unsigned short ParticleEmitter::_calculateRequestedParticles(Real timeElapsed)
	{
		unsigned short requestedParticles = 0;
        
		if (mEnabled)
		{
			if (mDynEmissionRate && mParentTechnique && mParentTechnique->getParentSystem())
			{
				Real rate = mDynEmissionRate->getValue(mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
				if (mEmissionRateCameraDependency)
				{
					// Affect the emission rate based on the camera distance
					mEmissionRateCameraDependency->affect(rate, mParentTechnique->getCameraSquareDistance());
				}
				if (mForceEmission)
				{
					if (mForceEmissionExecuted)
					{
						// It is a single-shot system, so there is nothing left anymore.
						requestedParticles = 0;
					}
					else
					{
						// Ignore the time. Just emit everything at once (if you absolutely need it).
						// The emitter cannot be disabled yet, because it needs to emit its particles first.
						requestedParticles = (unsigned short)rate;
						mForceEmissionExecuted = true;
					}
				}
				else
				{
					// Particle emission is time driven
					mRemainder += rate * timeElapsed;
					requestedParticles = (unsigned short)mRemainder;
				}
				
				mRemainder -= requestedParticles;
			}

			// Determine whether the duration period has been exceeded.
			if (mDynDurationSet)
			{
				mDurationRemain -= timeElapsed;
				if (mDurationRemain <= 0)
				{
					setEnabled(false);
				}
			}
		}
		else if (mDynRepeatDelaySet)
		{
			mRepeatDelayRemain -= timeElapsed;
			if (mRepeatDelayRemain <= 0)
			{
				// Initialise again (if stopfade isn't set)
				if (mParentTechnique)
				{
					if (!mParentTechnique->isStopFade())
					{
						setEnabled(true);
					}
				}
				else
				{
					setEnabled(true);
				}
			}
		}

		return requestedParticles;
	}
	//-----------------------------------------------------------------------
	void ParticleEmitter::_initParticleDimensions(Particle* particle)
    {
		if (particle->particleType != Particle::PT_VISUAL)
			return;

		// Only continue if one of them is set
		VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
		if (mDynParticleAllDimensionsSet || mDynParticleWidthSet || mDynParticleHeightSet || mDynParticleDepthSet)
		{
			// Set all dimensions equal ...
			Real extend = 0;
			if (mDynParticleAllDimensionsSet && mDynParticleAllDimensions)
			{
				extend = mDynamicAttributeHelper.calculate(mDynParticleAllDimensions, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
				visualParticle->setOwnDimensions(_mEmitterScale.x * extend, _mEmitterScale.y * extend, _mEmitterScale.z * extend);
				return;
			}

			// ... or set the dimensions independent from each other
			Real width = 0;
			Real height = 0;
			Real depth = 0;
			if (mDynParticleWidthSet && mDynParticleWidth)
			{
				width = mDynamicAttributeHelper.calculate(mDynParticleWidth, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
			}
			if (mDynParticleHeightSet && mDynParticleHeight)
			{
				height = mDynamicAttributeHelper.calculate(mDynParticleHeight, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
			}
			if (mDynParticleDepthSet && mDynParticleDepth)
			{
				depth = mDynamicAttributeHelper.calculate(mDynParticleDepth, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
			}
	
			/** Set the width, height and depth if at least one of them is set.
			@remarks
				If one of the dimensions is 0, it will be overridden by the default value later on.
			*/
			if (mDynParticleWidthSet || mDynParticleHeightSet || mDynParticleDepthSet)
			{
				visualParticle->setOwnDimensions(_mEmitterScale.x * width, _mEmitterScale.y * height, _mEmitterScale.z * depth);
			}
		}
		else
		{
			// Just set the width, height and depth, but these are just the default settings; the particle doesn't
			// have own dimensions. Recalculate the bounding sphere radius.
			visualParticle->width = _mEmitterScale.x * mParentTechnique->getDefaultWidth();
			visualParticle->height = _mEmitterScale.y * mParentTechnique->getDefaultHeight();
			visualParticle->depth = _mEmitterScale.z * mParentTechnique->getDefaultDepth();
			visualParticle->_calculateBoundingSphereRadius();
		}
	}
}
