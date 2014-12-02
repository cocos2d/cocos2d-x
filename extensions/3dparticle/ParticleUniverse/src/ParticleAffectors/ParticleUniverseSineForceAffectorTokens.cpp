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

#include "ParticleAffectors/ParticleUniverseSineForceAffector.h"
#include "ParticleAffectors/ParticleUniverseSineForceAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool SineForceAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		SineForceAffector* affector = static_cast<SineForceAffector*>(af);

		if (prop->name == token[TOKEN_MIN_FREQUENCY])
		{
			// Property: min_frequency
			if (passValidateProperty(compiler, prop, token[TOKEN_MIN_FREQUENCY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setFrequencyMin(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SINE_MIN_FREQUENCY])
		{
			// Property: sinef_aff_frequency_min (deprecated and replaced by 'min_frequency')
			if (passValidateProperty(compiler, prop, token[TOKEN_SINE_MIN_FREQUENCY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setFrequencyMin(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MAX_FREQUENCY])
		{
			// Property: max_frequency
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_FREQUENCY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setFrequencyMax(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SINE_MAX_FREQUENCY])
		{
			// Property: sinef_aff_frequency_max (deprecated and replaced by 'max_frequency')
			if (passValidateProperty(compiler, prop, token[TOKEN_SINE_MAX_FREQUENCY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setFrequencyMax(val);
					return true;
				}
			}
		}
		else
		{
			// Parse the BaseForceAffector
			BaseForceAffectorTranslator BaseForceAffectorTranslator;
			return BaseForceAffectorTranslator.translateChildProperty(compiler, node); // Must be the last
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool SineForceAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void SineForceAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a SineForceAffector
		const SineForceAffector* affector = static_cast<const SineForceAffector*>(element);

		// Write the header of the SineForceAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		BaseForceAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getFrequencyMin() != SineForceAffector::DEFAULT_FREQ_MIN) serializer->writeLine(
			token[TOKEN_MIN_FREQUENCY], StringConverter::toString(affector->getFrequencyMin()), 12);
		if (affector->getFrequencyMax() != SineForceAffector::DEFAULT_FREQ_MAX) serializer->writeLine(
			token[TOKEN_MAX_FREQUENCY], StringConverter::toString(affector->getFrequencyMax()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
