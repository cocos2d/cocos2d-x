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

#include "ParticleObservers/ParticleUniverseOnVelocityObserver.h"
#include "ParticleObservers/ParticleUniverseOnVelocityObserverTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool OnVelocityObserverTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleObserver* ob = any_cast<ParticleObserver*>(prop->parent->context);
		OnVelocityObserver* observer = static_cast<OnVelocityObserver*>(ob);

		if (prop->name == token[TOKEN_ONVELOCITY_THRESHOLD])
		{
			// Property: velocity_threshold
			if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_ONVELOCITY_THRESHOLD], 2))
			{
				String compareType;
				Real val = 0.0f;
				AbstractNodeList::const_iterator i = prop->values.begin();
				if(getString(*i, &compareType))
				{
					if (compareType == token[TOKEN_LESS_THAN])
					{
						observer->setCompare(CO_LESS_THAN);
					}
					else if (compareType == token[TOKEN_GREATER_THAN])
					{
						observer->setCompare(CO_GREATER_THAN);
					}
					else if (compareType == token[TOKEN_EQUALS])
					{
						observer->setCompare(CO_EQUALS);
					}
					++i;
					if(getReal(*i, &val))
					{
						observer->setThreshold(val);
						return true;
					}
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool OnVelocityObserverTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void OnVelocityObserverWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a OnVelocityObserver
		const OnVelocityObserver* observer = static_cast<const OnVelocityObserver*>(element);

		// Write the header of the OnVelocityObserver
		serializer->writeLine(token[TOKEN_OBSERVER], observer->getObserverType(), observer->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleObserverWriter::write(serializer, element);

		// Write own attributes
		String compare = token[TOKEN_GREATER_THAN];
		if (observer->getCompare() == CO_LESS_THAN)
		{
			compare = token[TOKEN_LESS_THAN];
		}
		else if (observer->getCompare() == CO_EQUALS)
		{
			compare = token[TOKEN_EQUALS];
		}
		serializer->writeLine(token[TOKEN_ONVELOCITY_THRESHOLD], compare, StringConverter::toString(observer->getThreshold()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
