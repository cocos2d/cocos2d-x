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

#include "ParticleEventHandlers/ParticleUniverseDoAffectorEventHandler.h"
#include "ParticleEventHandlers/ParticleUniverseDoAffectorEventHandlerTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool DoAffectorEventHandlerTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEventHandler* evt = any_cast<ParticleEventHandler*>(prop->parent->context);
		DoAffectorEventHandler* handler = static_cast<DoAffectorEventHandler*>(evt);

		if (prop->name == token[TOKEN_FORCE_AFFECTOR])
		{
			// Property: force_affector
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFFECTOR], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					handler->setAffectorName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FORCE_AFFECTOR_PRE_POST])
		{
			// Property: pre_post
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFFECTOR_PRE_POST], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setPrePost(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool DoAffectorEventHandlerTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void DoAffectorEventHandlerWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a DoAffectorEventHandler
		const DoAffectorEventHandler* eventHandler = static_cast<const DoAffectorEventHandler*>(element);

		// Write the header of the DoAffectorEventHandler
		serializer->writeLine(token[TOKEN_HANDLER], eventHandler->getEventHandlerType(), eventHandler->getName(), 12);
		serializer->writeLine("{", 12);

		// Write base attributes
		ParticleEventHandlerWriter::write(serializer, element);

		// Write own attributes
		if (eventHandler->getAffectorName() != StringUtil::BLANK) serializer->writeLine(
			token[TOKEN_FORCE_AFFECTOR], eventHandler->getAffectorName(), 16);
		if (eventHandler->getPrePost() != DoAffectorEventHandler::DEFAULT_PRE_POST) serializer->writeLine(
			token[TOKEN_FORCE_AFFECTOR_PRE_POST], StringConverter::toString(eventHandler->getPrePost()), 16);

		// Write the close bracket
		serializer->writeLine("}", 12);
	}

}
