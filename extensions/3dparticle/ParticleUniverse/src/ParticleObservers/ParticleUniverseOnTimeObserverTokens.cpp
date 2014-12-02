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

#include "ParticleObservers/ParticleUniverseOnTimeObserver.h"
#include "ParticleObservers/ParticleUniverseOnTimeObserverTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool OnTimeObserverTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleObserver* ob = any_cast<ParticleObserver*>(prop->parent->context);
		OnTimeObserver* observer = static_cast<OnTimeObserver*>(ob);

		if (prop->name == token[TOKEN_ONTIME])
		{
			// Property: on_time
			if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_ONTIME], 2))
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
		else if (prop->name == token[TOKEN_SINCE_START_SYSTEM])
		{
			// Property: since_start_system
			if (passValidateProperty(compiler, prop, token[TOKEN_SINCE_START_SYSTEM], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					observer->setSinceStartSystem(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool OnTimeObserverTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void OnTimeObserverWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a OnTimeObserver
		const OnTimeObserver* observer = static_cast<const OnTimeObserver*>(element);

		// Write the header of the OnTimeObserver
		serializer->writeLine(token[TOKEN_OBSERVER], observer->getObserverType(), observer->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleObserverWriter::write(serializer, element);

		// Write own attributes
		if (observer->isSinceStartSystem() != OnTimeObserver::DEFAULT_SINCE_START_SYSTEM) serializer->writeLine(
			token[TOKEN_SINCE_START_SYSTEM], StringConverter::toString(observer->isSinceStartSystem()), 12);
		String compare = token[TOKEN_GREATER_THAN];
		if (observer->getCompare() == CO_LESS_THAN)
		{
			compare = token[TOKEN_LESS_THAN];
		}
		else if (observer->getCompare() == CO_EQUALS)
		{
			compare = token[TOKEN_EQUALS];
		}
		serializer->writeLine(token[TOKEN_ONTIME], compare, StringConverter::toString(observer->getThreshold()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
