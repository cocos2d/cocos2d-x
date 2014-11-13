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

#include "ParticleEventHandlers/ParticleUniverseDoEnableComponentEventHandler.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	DoEnableComponentEventHandler::DoEnableComponentEventHandler(void) : 
		ParticleEventHandler(),
		mComponentName(StringUtil::BLANK),
		mComponentType(CT_EMITTER),
		mComponentEnabled(true)
	{
	}
	//-----------------------------------------------------------------------
	void DoEnableComponentEventHandler::_handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		/** Search for the component.
		*/
		ParticleTechnique* technique = 0;
		switch (mComponentType)
		{
			case CT_EMITTER:
			{
				ParticleEmitter* emitter = particleTechnique->getEmitter(mComponentName);
				if (!emitter)
				{
					// Search all techniques in this ParticleSystem for an emitter with the correct name
					ParticleSystem* system = particleTechnique->getParentSystem();
					size_t size = system->getNumTechniques();
					for(size_t i = 0; i < size; ++i)		
					{
						technique = system->getTechnique(i);
						emitter = technique->getEmitter(mComponentName);
						if (emitter)
						{
							break;
						}
					}
				}
				if (emitter)
				{
					emitter->setEnabled(mComponentEnabled);
				}
			}
			break;

			case CT_AFFECTOR:
			{
				ParticleAffector* affector = particleTechnique->getAffector(mComponentName);
				if (!affector)
				{
					// Search all techniques in this ParticleSystem for an affector with the correct name
					ParticleSystem* system = particleTechnique->getParentSystem();
					size_t size = system->getNumTechniques();
					for(size_t i = 0; i < size; ++i)
					{
						technique = system->getTechnique(i);
						affector = technique->getAffector(mComponentName);
						if (affector)
						{
							break;
						}
					}
				}
				if (affector)
				{
					affector->setEnabled(mComponentEnabled);
				}
			}
			break;

			case CT_OBSERVER:
			{
				ParticleObserver* observer = particleTechnique->getObserver(mComponentName);
				if (!observer)
				{
					// Search all techniques in this ParticleSystem for an observer with the correct name
					ParticleSystem* system = particleTechnique->getParentSystem();
					size_t size = system->getNumTechniques();
					for(size_t i = 0; i < size; ++i)		
					{
						technique = system->getTechnique(i);
						observer = technique->getObserver(mComponentName);
						if (observer)
						{
							break;
						}
					}
				}
				if (observer)
				{
					observer->setEnabled(mComponentEnabled);
				}
			}
			break;

			case CT_TECHNIQUE:
			{
				// Search in this ParticleSystem for a technique with the correct name
				ParticleSystem* system = particleTechnique->getParentSystem();
				technique = system->getTechnique(mComponentName);
				if (technique)
				{
					technique->setEnabled(mComponentEnabled);
				}
			}
			break;
		}
	}
	//-----------------------------------------------------------------------
	void DoEnableComponentEventHandler::copyAttributesTo (ParticleEventHandler* eventHandler)
	{
		ParticleEventHandler::copyAttributesTo(eventHandler);
		DoEnableComponentEventHandler* doEnableComponentEventHandler = static_cast<DoEnableComponentEventHandler*>(eventHandler);
		doEnableComponentEventHandler->setComponentType(mComponentType);
		doEnableComponentEventHandler->setComponentName(mComponentName);
		doEnableComponentEventHandler->setComponentEnabled(mComponentEnabled);
	}

}
