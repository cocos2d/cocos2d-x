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

#include "ParticleEventHandlers/ParticleUniverseDoEnableComponentEventHandler.h"
#include "ParticleEventHandlers/ParticleUniverseDoEnableComponentEventHandlerTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool DoEnableComponentEventHandlerTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEventHandler* evt = any_cast<ParticleEventHandler*>(prop->parent->context);
		DoEnableComponentEventHandler* handler = static_cast<DoEnableComponentEventHandler*>(evt);

		if (prop->name == token[TOKEN_DOENABLE_COMPONENT])
		{
			// Property: enable_component
			if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_DOENABLE_COMPONENT], 3))
			{
				String componentType;
				String name;
				bool enabled = true;
				AbstractNodeList::const_iterator i = prop->values.begin();
				if(getString(*i, &componentType))
				{
					if (componentType == token[TOKEN_DOENABLE_EMITTER_COMPONENT])
					{
						handler->setComponentType(CT_EMITTER);
					}
					else if (componentType == token[TOKEN_DOENABLE_AFFECTOR_COMPONENT])
					{
						handler->setComponentType(CT_AFFECTOR);
					}
					else if (componentType == token[TOKEN_DOENABLE_OBSERVER_COMPONENT])
					{
						handler->setComponentType(CT_OBSERVER);
					}
					else if (componentType == token[TOKEN_DOENABLE_TECHNIQUE_COMPONENT])
					{
						handler->setComponentType(CT_TECHNIQUE);
					}
					++i;
					if(getString(*i, &name))
					{
						handler->setComponentName(name);
						++i;
						if (getBoolean(*i, &enabled))
						{
							handler->setComponentEnabled(enabled);
							return true;
						}
					}
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool DoEnableComponentEventHandlerTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void DoEnableComponentEventHandlerWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a DoEnableComponentEventHandler
		const DoEnableComponentEventHandler* eventHandler = static_cast<const DoEnableComponentEventHandler*>(element);

		// Write the header of the DoEnableComponentEventHandler
		serializer->writeLine(token[TOKEN_HANDLER], eventHandler->getEventHandlerType(), eventHandler->getName(), 12);
		serializer->writeLine("{", 12);

		// Write base attributes
		ParticleEventHandlerWriter::write(serializer, element);

		// Write own attributes
		String componentType = token[TOKEN_DOENABLE_EMITTER_COMPONENT];
		if (eventHandler->getComponentType() == CT_AFFECTOR) componentType = token[TOKEN_DOENABLE_AFFECTOR_COMPONENT];
		else if (eventHandler->getComponentType() == CT_TECHNIQUE) componentType = token[TOKEN_DOENABLE_TECHNIQUE_COMPONENT];
		else if (eventHandler->getComponentType() == CT_OBSERVER) componentType = token[TOKEN_DOENABLE_OBSERVER_COMPONENT];
		serializer->writeLine(
			token[TOKEN_DOENABLE_COMPONENT], 
			componentType, 
			eventHandler->getComponentName(), 
			StringConverter::toString(eventHandler->isComponentEnabled()),
			16);

		// Write the close bracket
		serializer->writeLine("}", 12);
	}

}
