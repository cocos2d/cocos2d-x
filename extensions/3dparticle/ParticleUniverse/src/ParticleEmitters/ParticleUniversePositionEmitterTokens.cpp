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
#include "ParticleEmitters/ParticleUniversePositionEmitterTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool PositionEmitterTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEmitter* em = any_cast<ParticleEmitter*>(prop->parent->context);
		PositionEmitter* emitter = static_cast<PositionEmitter*>(em);

		if (prop->name == token[TOKEN_POS_ADD_POSITION])
		{
			// Property: add_position
			if (passValidateProperty(compiler, prop, token[TOKEN_POS_ADD_POSITION], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					emitter->addPosition(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_POS_RANDOMIZE])
		{
			// Property: random_position
			if (passValidateProperty(compiler, prop, token[TOKEN_POS_RANDOMIZE], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					emitter->setRandomized(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool PositionEmitterTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void PositionEmitterWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a PositionEmitter
		const PositionEmitter* emitter = static_cast<const PositionEmitter*>(element);

		// Write the header of the PositionEmitter
		serializer->writeLine(token[TOKEN_EMITTER], emitter->getEmitterType(), emitter->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleEmitterWriter::write(serializer, element);

		// Write own attributes
		if (emitter->isRandomized() != PositionEmitter::DEFAULT_RANDOMIZE) serializer->writeLine(
			token[TOKEN_POS_RANDOMIZE], StringConverter::toString(emitter->isRandomized()), 12);

		// List of positions
		vector<Vector3> positionList = emitter->getPositions();
		if(!positionList.empty())
		{
			vector<Vector3>::const_iterator it;
			vector<Vector3>::const_iterator itEnd = positionList.end();
			for (it = positionList.begin(); it != itEnd; ++it)
			{
				serializer->writeLine(token[TOKEN_POS_ADD_POSITION], StringConverter::toString(*it), 12);
			}
		}

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
