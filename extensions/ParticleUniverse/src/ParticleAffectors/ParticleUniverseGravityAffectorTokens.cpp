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

#include "ParticleAffectors/ParticleUniverseGravityAffector.h"
#include "ParticleAffectors/ParticleUniverseGravityAffectorTokens.h"
#include "Externs/ParticleUniverseGravityExtern.h"


namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool GravityAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		GravityAffector* affector = static_cast<GravityAffector*>(af);

		if (prop->name == token[TOKEN_GRAVITY])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_GRAVITY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setGravity(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool GravityAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void GravityAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a GravityAffector
		const GravityAffector* affector = static_cast<const GravityAffector*>(element);

		// Write the header of the GravityAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getGravity() != GravityAffector::DEFAULT_GRAVITY) serializer->writeLine(
			token[TOKEN_GRAVITY], StringConverter::toString(affector->getGravity()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
