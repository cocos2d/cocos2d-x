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

#include "ParticleAffectors/ParticleUniverseLineAffector.h"
#include "ParticleAffectors/ParticleUniverseLineAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool LineAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		LineAffector* affector = static_cast<LineAffector*>(af);

		if (prop->name == token[TOKEN_MAX_DEVIATION])
		{
			// Property: max_deviation
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_DEVIATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviation(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_LINE_AFF_MAX_DEVIATION])
		{
			// Property: line_aff_max_deviation (deprecated and replaced by 'max_deviation')
			if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_MAX_DEVIATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setMaxDeviation(val);
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
		else if (prop->name == token[TOKEN_LINE_AFF_TIME_STEP])
		{
			// Property: line_aff_time_step (deprecated and replaced by 'time_step')
			if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_TIME_STEP], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setTimeStep(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_END])
		{
			// Property: end
			if (passValidateProperty(compiler, prop, token[TOKEN_END], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setEnd(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_LINE_AFF_END])
		{
			// Property: line_aff_end (deprecated and replaced by 'end')
			if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_END], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setEnd(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_DRIFT])
		{
			// Property: drift
			if (passValidateProperty(compiler, prop, token[TOKEN_DRIFT], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setDrift(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_LINE_AFF_DRIFT])
		{
			// Property: line_aff_drift (deprecated and replaced by 'drift')
			if (passValidateProperty(compiler, prop, token[TOKEN_LINE_AFF_DRIFT], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setDrift(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool LineAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void LineAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a LineAffector
		const LineAffector* affector = static_cast<const LineAffector*>(element);

		// Write the header of the LineAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getMaxDeviation() != LineAffector::DEFAULT_MAX_DEVIATION) serializer->writeLine(
			token[TOKEN_MAX_DEVIATION], StringConverter::toString(affector->getMaxDeviation()), 12);
		if (affector->getTimeStep() != LineAffector::DEFAULT_TIME_STEP) serializer->writeLine(
			token[TOKEN_TIME_STEP], StringConverter::toString(affector->getTimeStep()), 12);
		if (affector->getEnd() != LineAffector::DEFAULT_END) serializer->writeLine(
			token[TOKEN_END], StringConverter::toString(affector->getEnd()), 12);
		if (affector->getDrift() != LineAffector::DEFAULT_DRIFT) serializer->writeLine(
			token[TOKEN_DRIFT], StringConverter::toString(affector->getDrift()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
