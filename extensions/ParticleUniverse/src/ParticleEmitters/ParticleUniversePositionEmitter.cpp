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

#include "ParticleEmitters/ParticleUniversePositionEmitter.h"

namespace ParticleUniverse
{
	// Constants
	const bool PositionEmitter::DEFAULT_RANDOMIZE = true;

	//-----------------------------------------------------------------------
	PositionEmitter::PositionEmitter(void) : 
		ParticleEmitter(),
		mRandomized(DEFAULT_RANDOMIZE),
		mIndex(0)
	{
	}
	//-----------------------------------------------------------------------
	bool PositionEmitter::isRandomized() const
	{
		return mRandomized;
	}
	//-----------------------------------------------------------------------
	void PositionEmitter::setRandomized(bool randomized)
	{
		mRandomized = randomized;
	}
	//-----------------------------------------------------------------------
	const vector<Vector3>& PositionEmitter::getPositions(void) const
	{
		return mPositionList;
	}
	//-----------------------------------------------------------------------
	void PositionEmitter::addPosition(const Vector3& position)
	{
		mPositionList.push_back(position);
	}
	//-----------------------------------------------------------------------
	void PositionEmitter::_notifyStart(void)
	{
		ParticleEmitter::_notifyStart();
		mIndex = 0;
	}
	//-----------------------------------------------------------------------
	void PositionEmitter::removeAllPositions(void)
	{
		mIndex = 0;
		mPositionList.clear();
	}
	//-----------------------------------------------------------------------
	unsigned short PositionEmitter::_calculateRequestedParticles(Real timeElapsed)
	{
		// Fast rejection
		if (mPositionList.empty())
			return 0;

		if (mRandomized)
		{
			return ParticleEmitter::_calculateRequestedParticles(timeElapsed);
		}
		else if (mIndex < mPositionList.size())
		{
			unsigned short requested = ParticleEmitter::_calculateRequestedParticles(timeElapsed);
			unsigned short size = static_cast<unsigned short>(mPositionList.size() - mIndex);
			if (requested > size)
			{
				return size;
			}
			else
			{
				return requested;
			}
		}

		return 0;
	}
	//-----------------------------------------------------------------------
	void PositionEmitter::_initParticlePosition(Particle* particle)
	{
		// Fast rejection
		if (mPositionList.empty())
			return;

		/** Remark: Don't take the orientation of the node into account, because the positions shouldn't be affected by the rotated node.
		*/
		if (mRandomized)
		{
			size_t i = (size_t)(Math::UnitRandom() * (mPositionList.size() - 1));
			particle->position = getDerivedPosition() + _mEmitterScale * mPositionList[i];
		}
		else if (mIndex < mPositionList.size())
		{
			particle->position = getDerivedPosition() + _mEmitterScale * mPositionList[mIndex];
			mIndex++;
		}

		particle->originalPosition = particle->position;
	}
	//-----------------------------------------------------------------------
	void PositionEmitter::copyAttributesTo (ParticleEmitter* emitter)
	{
		ParticleEmitter::copyAttributesTo(emitter);
		PositionEmitter* positionEmitter = static_cast<PositionEmitter*>(emitter);
		positionEmitter->mRandomized = mRandomized;
		positionEmitter->mPositionList = mPositionList;
	}
}
