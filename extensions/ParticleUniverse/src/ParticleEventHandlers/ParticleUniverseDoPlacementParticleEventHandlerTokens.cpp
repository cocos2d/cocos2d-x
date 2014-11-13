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

#include "ParticleEventHandlers/ParticleUniverseDoPlacementParticleEventHandler.h"
#include "ParticleEventHandlers/ParticleUniverseDoPlacementParticleEventHandlerTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool DoPlacementParticleEventHandlerTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEventHandler* evt = any_cast<ParticleEventHandler*>(prop->parent->context);
		DoPlacementParticleEventHandler* handler = static_cast<DoPlacementParticleEventHandler*>(evt);

		if (prop->name == token[TOKEN_DOPLACE_FORCE_EMITTER])
		{
			// Property: force_emitter
			if (passValidateProperty(compiler, prop, token[TOKEN_DOPLACE_FORCE_EMITTER], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					handler->setForceEmitterName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_DOPLACE_NUMBER_OF_PARTICLES])
		{
			// Property: number_of_particles
			if (passValidateProperty(compiler, prop, token[TOKEN_DOPLACE_NUMBER_OF_PARTICLES], VAL_UINT))
			{
				unsigned int val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					handler->setNumberOfParticles(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_POSITION])
		{
			// Property: inherit_position
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_POSITION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritPosition(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_DIRECTION])
		{
			// Property: inherit_direction
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_DIRECTION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritDirection(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_ORIENTATION])
		{
			// Property: inherit_orientation
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_ORIENTATION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritOrientation(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_TIME_TO_LIVE])
		{
			// Property: inherit_time_to_live
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_TIME_TO_LIVE], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritTimeToLive(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_MASS])
		{
			// Property: inherit_mass
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_MASS], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritMass(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_TEXTURE_COORDINATE])
		{
			// Property: inherit_texture_coord
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_TEXTURE_COORDINATE], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritTextureCoordinate(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_COLOUR])
		{
			// Property: inherit_colour
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_COLOUR], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritColour(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_WIDTH])
		{
			// Property: inherit_width
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_WIDTH], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritParticleWidth(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_HEIGHT])
		{
			// Property: inherit_height
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_HEIGHT], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritParticleHeight(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INHERIT_DEPTH])
		{
			// Property: inherit_depth
			if (passValidateProperty(compiler, prop, token[TOKEN_INHERIT_DEPTH], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					handler->setInheritParticleDepth(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool DoPlacementParticleEventHandlerTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void DoPlacementParticleEventHandlerWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a DoPlacementParticleEventHandler
		const DoPlacementParticleEventHandler* eventHandler = static_cast<const DoPlacementParticleEventHandler*>(element);

		// Write the header of the DoPlacementParticleEventHandler
		serializer->writeLine(token[TOKEN_HANDLER], eventHandler->getEventHandlerType(), eventHandler->getName(), 12);
		serializer->writeLine("{", 12);

		// Write base attributes
		ParticleEventHandlerWriter::write(serializer, element);

		// Write own attributes
		if (eventHandler->getForceEmitterName() != StringUtil::BLANK) serializer->writeLine(
			token[TOKEN_DOPLACE_FORCE_EMITTER], eventHandler->getForceEmitterName(), 16);
		if (eventHandler->getNumberOfParticles() != DoPlacementParticleEventHandler::DEFAULT_NUMBER_OF_PARTICLES) serializer->writeLine(
			token[TOKEN_DOPLACE_NUMBER_OF_PARTICLES], StringConverter::toString(eventHandler->getNumberOfParticles()), 16);
		if ((!eventHandler->isInheritPosition())) serializer->writeLine(
			token[TOKEN_INHERIT_POSITION], StringConverter::toString((!eventHandler->isInheritPosition())), 16);
		if (eventHandler->isInheritDirection()) serializer->writeLine(
			token[TOKEN_INHERIT_DIRECTION], StringConverter::toString(eventHandler->isInheritDirection()), 16);
		if (eventHandler->isInheritOrientation()) serializer->writeLine(
			token[TOKEN_INHERIT_ORIENTATION], StringConverter::toString(eventHandler->isInheritOrientation()), 16);
		if (eventHandler->isInheritTimeToLive()) serializer->writeLine(
			token[TOKEN_INHERIT_TIME_TO_LIVE], StringConverter::toString(eventHandler->isInheritTimeToLive()), 16);
		if (eventHandler->isInheritMass()) serializer->writeLine(
			token[TOKEN_INHERIT_MASS], StringConverter::toString(eventHandler->isInheritMass()), 16);
		if (eventHandler->isInheritTextureCoordinate()) serializer->writeLine(
			token[TOKEN_INHERIT_TEXTURE_COORDINATE], StringConverter::toString(eventHandler->isInheritTextureCoordinate()), 16);
		if (eventHandler->isInheritColour()) serializer->writeLine(
			token[TOKEN_INHERIT_COLOUR], StringConverter::toString(eventHandler->isInheritColour()), 16);
		if (eventHandler->isInheritParticleWidth()) serializer->writeLine(
			token[TOKEN_INHERIT_WIDTH], StringConverter::toString(eventHandler->isInheritParticleWidth()), 16);
		if (eventHandler->isInheritParticleHeight()) serializer->writeLine(
			token[TOKEN_INHERIT_HEIGHT], StringConverter::toString(eventHandler->isInheritParticleHeight()), 16);
		if (eventHandler->isInheritParticleDepth()) serializer->writeLine(
			token[TOKEN_INHERIT_DEPTH], StringConverter::toString(eventHandler->isInheritParticleDepth()), 16);


		// Write the close bracket
		serializer->writeLine("}", 12);
	}

}
