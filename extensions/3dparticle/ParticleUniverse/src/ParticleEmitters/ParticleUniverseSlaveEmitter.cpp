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

#include "ParticleEmitters/ParticleUniverseSlaveEmitter.h"
#include "ParticleBehaviours/ParticleUniverseSlaveBehaviour.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	SlaveEmitter::SlaveEmitter(void) : 
		ParticleEmitter(),
		TechniqueListener(),
		mMasterParticle(0),
		mMasterTechniqueName(StringUtil::BLANK),
		mMasterEmitterName(StringUtil::BLANK),
		mMasterPosition(Vector3::ZERO),
		mMasterDirection(Vector3::ZERO),
		mMasterEmitterNameSet(false)
	{
	}
	//-----------------------------------------------------------------------
	const String& SlaveEmitter::getMasterTechniqueName(void) const
	{
		return mMasterTechniqueName;
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::setMasterTechniqueName(const String& masterTechniqueName)
	{
		mMasterTechniqueName = masterTechniqueName;
	}
	//-----------------------------------------------------------------------
	const String& SlaveEmitter::getMasterEmitterName(void) const
	{
		return mMasterEmitterName;
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::setMasterEmitterName(const String& masterEmitterName)
	{
		mMasterEmitterName = masterEmitterName;
		mMasterEmitterNameSet = true;
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::particleEmitted(ParticleTechnique* particleTechnique, Particle* particle)
	{
		if (mMasterEmitterNameSet && mMasterEmitterName != particle->parentEmitter->getName())
		{
			// Ignore particle
			return;
		}

		/** Keep the data of the emitted particle from the master technique/emitter.
			Emission if a particle in this emitter may NOT be done in the main _update() method of the ParticleSystem,
			but only from here (it´s a slave afterall). That is why the emitter is enabled and disabled again.
		*/
		mMasterPosition = particle->position;
		mMasterDirection = particle->direction;
		mMasterParticle = particle;
		mEnabled = true;
		mParentTechnique->forceEmission(this, 1); // Just emit one, to be in sync with the master.
		mEnabled = false;
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::_initParticlePosition(Particle* particle)
	{
		// Remark: Don't take the orientation of the node into account, because the position of the master particle is leading.
		particle->position = mMasterPosition;
		particle->originalPosition = particle->position;
	}
	//-----------------------------------------------------------------------
    void SlaveEmitter::_initParticleDirection(Particle* particle)
    {
		particle->direction = mMasterDirection;
		particle->originalDirection = particle->direction;
		particle->originalDirectionLength = particle->direction.length();

		// Make use of the opportunity to set the master particle in the behaviour object (if available)
		SlaveBehaviour* behaviour = static_cast<SlaveBehaviour*>(particle->getBehaviour("Slave"));
		if (behaviour)
		{
			behaviour->masterParticle = mMasterParticle;
		}
    }
	//-----------------------------------------------------------------------
	void SlaveEmitter::_prepare(ParticleTechnique* particleTechnique)
	{
		ParticleSystem* system = particleTechnique->getParentSystem();
		if (system)
		{
			ParticleTechnique* masterTechnique = system->getTechnique(mMasterTechniqueName);
			if (masterTechnique)
			{
				masterTechnique->addTechniqueListener(this);
			}
			mEnabled = false;
		}
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::_unprepare(ParticleTechnique* particleTechnique)
	{
		ParticleSystem* system = particleTechnique->getParentSystem();
		if (system)
		{
			ParticleTechnique* masterTechnique = system->getTechnique(mMasterTechniqueName);
			if (masterTechnique)
			{
				masterTechnique->removeTechniqueListener(this);
			}
		}
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::_notifyStart (void)
	{
		ParticleEmitter::_notifyStart();
		setEnabled(false);
	}
	//-----------------------------------------------------------------------
	void SlaveEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);

		SlaveEmitter* slaveEmitter = static_cast<SlaveEmitter*>(emitter);
		slaveEmitter->mMasterTechniqueName = mMasterTechniqueName;
		slaveEmitter->mMasterEmitterName = mMasterEmitterName;
		slaveEmitter->mMasterEmitterNameSet = mMasterEmitterNameSet;
	}
}
