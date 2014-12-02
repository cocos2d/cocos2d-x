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

#include "ParticleObservers/ParticleUniverseOnEventFlagObserver.h"
#include "ParticleObservers/ParticleUniverseOnEventFlagObserverTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool OnEventFlagObserverTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleObserver* ob = any_cast<ParticleObserver*>(prop->parent->context);
		OnEventFlagObserver* observer = static_cast<OnEventFlagObserver*>(ob);

		if (prop->name == token[TOKEN_ONEVENT_FLAG])
		{
			// Property: event_flag
			if (passValidateProperty(compiler, prop, token[TOKEN_ONEVENT_FLAG], VAL_UINT))
			{
				uint32 val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					observer->setEventFlag(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool OnEventFlagObserverTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void OnEventFlagObserverWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a OnEventFlagObserver
		const OnEventFlagObserver* observer = static_cast<const OnEventFlagObserver*>(element);

		// Write the header of the OnEventFlagObserver
		serializer->writeLine(token[TOKEN_OBSERVER], observer->getObserverType(), observer->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleObserverWriter::write(serializer, element);

		// Write own attributes
		if (observer->getEventFlag() != OnEventFlagObserver::DEFAULT_EVENT_FLAG) serializer->writeLine(
			token[TOKEN_ONEVENT_FLAG], StringConverter::toString(observer->getEventFlag()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
