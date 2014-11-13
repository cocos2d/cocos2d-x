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

#include "ParticleEventHandlers/ParticleUniverseDoScaleEventHandler.h"

namespace ParticleUniverse
{
	// Constants
	const DoScaleEventHandler::ScaleType DoScaleEventHandler::DEFAULT_SCALE_TYPE = DoScaleEventHandler::ST_TIME_TO_LIVE;
	const Real DoScaleEventHandler::DEFAULT_SCALE_FRACTION = 0.2f;

	//-----------------------------------------------------------------------
	DoScaleEventHandler::DoScaleEventHandler(void) : 
		ParticleEventHandler(),
		mScaleFraction(DEFAULT_SCALE_FRACTION),
		mScaleType(DEFAULT_SCALE_TYPE)
	{
	}
	//-----------------------------------------------------------------------
	const DoScaleEventHandler::ScaleType& DoScaleEventHandler::getScaleType(void) const
	{
		return mScaleType;
	}
	//-----------------------------------------------------------------------
	void DoScaleEventHandler::setScaleType(const DoScaleEventHandler::ScaleType& scaleType)
	{
		mScaleType = scaleType;
	}
	//-----------------------------------------------------------------------
	const Real DoScaleEventHandler::getScaleFraction(void) const
	{
		return mScaleFraction;
	}
	//-----------------------------------------------------------------------
	void DoScaleEventHandler::setScaleFraction(const Real scaleFraction)
	{
		mScaleFraction = scaleFraction;
	}
	//-----------------------------------------------------------------------
	void DoScaleEventHandler::_handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		if (!particle)
			return;

		switch (mScaleType)
		{
			case ST_TIME_TO_LIVE:
				particle->timeToLive -= timeElapsed * mScaleFraction * particle->timeToLive;
			break;

			case ST_VELOCITY:
				particle->direction += timeElapsed * mScaleFraction * particle->direction;
			break;
		}
	}
	//-----------------------------------------------------------------------
	void DoScaleEventHandler::copyAttributesTo (ParticleEventHandler* eventHandler)
	{
		ParticleEventHandler::copyAttributesTo(eventHandler);
		DoScaleEventHandler* doScaleEventHandler = static_cast<DoScaleEventHandler*>(eventHandler);
		doScaleEventHandler->setScaleFraction(mScaleFraction);
		doScaleEventHandler->setScaleType(mScaleType);
	}
}
