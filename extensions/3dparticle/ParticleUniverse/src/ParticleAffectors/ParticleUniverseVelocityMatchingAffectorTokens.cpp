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

#include "ParticleAffectors/ParticleUniverseVelocityMatchingAffector.h"
#include "ParticleAffectors/ParticleUniverseVelocityMatchingAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool VelocityMatchingAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		VelocityMatchingAffector* affector = static_cast<VelocityMatchingAffector*>(af);

		if (prop->name == token[TOKEN_RADIUS])
		{
			// Property: radius
			if (passValidateProperty(compiler, prop, token[TOKEN_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setRadius(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_VELO_MATCHING_RADIUS])
		{
			// Property: velocity_matching_radius (deprecated and replaced by radius)
			if (passValidateProperty(compiler, prop, token[TOKEN_VELO_MATCHING_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setRadius(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool VelocityMatchingAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void VelocityMatchingAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a VelocityMatchingAffector
		const VelocityMatchingAffector* affector = static_cast<const VelocityMatchingAffector*>(element);

		// Write the header of the VelocityMatchingAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getRadius() != VelocityMatchingAffector::DEFAULT_RADIUS) serializer->writeLine(
			token[TOKEN_RADIUS], StringConverter::toString(affector->getRadius()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
