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

#include "ParticleAffectors/ParticleUniverseRandomiser.h"
#include "ParticleAffectors/ParticleUniverseRandomiserTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool RandomiserTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		Randomiser* affector = static_cast<Randomiser*>(af);

		if (prop->name == token[TOKEN_MAX_DEVIATION_X])
		{
			// Property: max_deviation_x
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION_X], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviationX(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RND_MAX_DEVIATION_X])
		{
			// Property: rand_aff_max_deviation_x (depreacted and replaced by 'max_deviation_x')
			if (passValidateProperty(compiler, prop, token[TOKEN_RND_MAX_DEVIATION_X], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviationX(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MAX_DEVIATION_Y])
		{
			// Property: max_deviation_y
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION_Y], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviationY(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RND_MAX_DEVIATION_Y])
		{
			// Property: rand_aff_max_deviation_y (deprecated and replaced by 'max_deviation_y')
			if (passValidateProperty(compiler, prop, token[TOKEN_RND_MAX_DEVIATION_Y], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviationY(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MAX_DEVIATION_Z])
		{
			// Property: max_deviation_z
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION_Z], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviationZ(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RND_MAX_DEVIATION_Z])
		{
			// Property: rand_aff_max_deviation_z (deprecated and replaced by 'max_deviation_z')
			if (passValidateProperty(compiler, prop, token[TOKEN_RND_MAX_DEVIATION_Z], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviationZ(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_TIME_STEP])
		{
			// Property: time_step
			if (passValidateProperty(compiler, prop, token[TOKEN_TIME_STEP], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setTimeStep(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RND_TIME_STEP])
		{
			// Property: rand_aff_time_step (deprecated and replaced by 'time_step')
			if (passValidateProperty(compiler, prop, token[TOKEN_RND_TIME_STEP], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setTimeStep(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_USE_DIRECTION])
		{
			// Property: use_direction
			if (passValidateProperty(compiler, prop, token[TOKEN_USE_DIRECTION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setRandomDirection(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RND_DIRECTION])
		{
			// Property: rand_aff_direction (deprecated and replaced by 'use_direction')
			if (passValidateProperty(compiler, prop, token[TOKEN_RND_DIRECTION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setRandomDirection(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool RandomiserTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void RandomiserWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a Randomiser
		const Randomiser* affector = static_cast<const Randomiser*>(element);

		// Write the header of the Randomiser
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getMaxDeviationX() != Randomiser::DEFAULT_MAX_DEVIATION.x) serializer->writeLine(
			token[TOKEN_MAX_DEVIATION_X], StringConverter::toString(affector->getMaxDeviationX()), 12);
		if (affector->getMaxDeviationY() != Randomiser::DEFAULT_MAX_DEVIATION.y) serializer->writeLine(
			token[TOKEN_MAX_DEVIATION_Y], StringConverter::toString(affector->getMaxDeviationY()), 12);
		if (affector->getMaxDeviationZ() != Randomiser::DEFAULT_MAX_DEVIATION.z) serializer->writeLine(
			token[TOKEN_MAX_DEVIATION_Z], StringConverter::toString(affector->getMaxDeviationZ()), 12);
		if (affector->getTimeStep() != Randomiser::DEFAULT_TIME_STEP) serializer->writeLine(
			token[TOKEN_TIME_STEP], StringConverter::toString(affector->getTimeStep()), 12);
		if (affector->isRandomDirection() != Randomiser::DEFAULT_RANDOM_DIRECTION) serializer->writeLine(
			token[TOKEN_USE_DIRECTION], StringConverter::toString(affector->isRandomDirection()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
