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

#include "ParticleAffectors/ParticleUniverseParticleFollower.h"
#include "ParticleAffectors/ParticleUniverseParticleFollowerTokens.h"
#include "Externs/ParticleUniverseGravityExtern.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool ParticleFollowerTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		ParticleFollower* affector = static_cast<ParticleFollower*>(af);

		if (prop->name == token[TOKEN_MIN_DISTANCE])
		{
			// Property: min_distance
			if (passValidateProperty(compiler, prop, token[TOKEN_MIN_DISTANCE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMinDistance(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FOLLOW_MIN_DISTANCE])
		{
			// Property: follower_min_distance (deprecated and replaced by 'min_distance')
			if (passValidateProperty(compiler, prop, token[TOKEN_FOLLOW_MIN_DISTANCE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMinDistance(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MAX_DISTANCE])
		{
			// Property: max_distance
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DISTANCE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDistance(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FOLLOW_MAX_DISTANCE])
		{
			// Property: follower_max_distance (deprecated and replaced by 'TOKEN_MAX_DISTANCE')
			if (passValidateProperty(compiler, prop, token[TOKEN_FOLLOW_MAX_DISTANCE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDistance(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool ParticleFollowerTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void ParticleFollowerWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a ParticleFollower
		const ParticleFollower* affector = static_cast<const ParticleFollower*>(element);

		// Write the header of the ParticleFollower
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getMinDistance() != ParticleFollower::DEFAULT_MIN_DISTANCE) serializer->writeLine(
			token[TOKEN_MIN_DISTANCE], StringConverter::toString(affector->getMinDistance()), 12);
		if (affector->getMaxDistance() != ParticleFollower::DEFAULT_MAX_DISTANCE) serializer->writeLine(
			token[TOKEN_MAX_DISTANCE], StringConverter::toString(affector->getMaxDistance()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
