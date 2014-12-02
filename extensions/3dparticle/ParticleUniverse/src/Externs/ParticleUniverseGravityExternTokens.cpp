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

#include "Externs/ParticleUniverseGravityExtern.h"
#include "Externs/ParticleUniverseGravityExternTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool GravityExternTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		Extern* ex = any_cast<Extern*>(prop->parent->context);
		GravityExtern* externObject = static_cast<GravityExtern*>(ex);

		if (prop->name == token[TOKEN_GRAVITY])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_GRAVITY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					externObject->setGravity(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_DISTANCE_THRESHOLD])
		{
			// Property: distance_threshold
			if (passValidateProperty(compiler, prop, token[TOKEN_DISTANCE_THRESHOLD], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					externObject->setDistanceThreshold(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_EXTERN_DISTANCE_THRESHOLD])
		{
			// Property: attachable_distance_threshold (deprecated and replaced by 'distance_threshold')
			if (passValidateProperty(compiler, prop, token[TOKEN_EXTERN_DISTANCE_THRESHOLD], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					externObject->setDistanceThreshold(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool GravityExternTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void GravityExternWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a GravityExtern
		const Extern* externObject = static_cast<const Extern*>(element);
		const GravityExtern* gravityExtern = static_cast<const GravityExtern*>(externObject);
		serializer->writeLine(token[TOKEN_EXTERN], externObject->getExternType(), externObject->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ExternWriter::write(serializer, element);
		AttachableWriter::write(serializer, element);

		// Write own attributes
		if (gravityExtern->getGravity() != GravityAffector::DEFAULT_GRAVITY) serializer->writeLine(
			token[TOKEN_GRAVITY], StringConverter::toString(gravityExtern->getGravity()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
