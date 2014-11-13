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

#include "ParticleRenderers/ParticleUniverseLightRendererTokens.h"
#include "ParticleRenderers/ParticleUniverseLightRenderer.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool LightRendererTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleRenderer* ren = any_cast<ParticleRenderer*>(prop->parent->context);
		LightRenderer* renderer = static_cast<LightRenderer*>(ren);

		if (prop->name == token[TOKEN_LIGHT_TYPE])
		{
			// Property: light_renderer_light_type
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_TYPE], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_POINT])
					{
						renderer->setLightType(Ogre::Light::LT_POINT);
						return true;
					}
					else if (val == token[TOKEN_LIGHT_SPOT])
					{
						renderer->setLightType(Ogre::Light::LT_SPOTLIGHT);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_SPECULAR])
		{
			// Property: light_renderer_specular
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_SPECULAR], VAL_COLOURVALUE))
			{
				ColourValue val;
				if(getColour(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setSpecularColour(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_ATT_RANGE])
		{
			// Property: light_renderer_att_range
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_ATT_RANGE], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setAttenuationRange(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_ATT_CONSTANT])
		{
			// Property: light_renderer_att_constant
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_ATT_CONSTANT], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setAttenuationConstant(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_ATT_LINEAR])
		{
			// Property: light_renderer_att_linear
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_ATT_LINEAR], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setAttenuationLinear(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_ATT_QUADRATIC])
		{
			// Property: light_renderer_att_quadratic
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_ATT_QUADRATIC], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setAttenuationQuadratic(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_SPOT_INNER])
		{
			// Property: light_renderer_spot_inner
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_SPOT_INNER], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setSpotlightInnerAngle(Radian(val));
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_SPOT_OUTER])
		{
			// Property: light_renderer_spot_outer
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_SPOT_OUTER], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setSpotlightOuterAngle(Radian(val));
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_FALLOFF])
		{
			// Property: light_renderer_falloff
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_FALLOFF], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setSpotlightFalloff(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_LIGHT_POWERSCALE])
		{
			// Property: light_renderer_powerscale
			if (passValidateProperty(compiler, prop, token[TOKEN_LIGHT_POWERSCALE], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setPowerScale(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_FLASH_FREQUENCY])
		{
			// Property: flash_frequency
			if (passValidateProperty(compiler, prop, token[TOKEN_FLASH_FREQUENCY], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setFlashFrequency(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_FLASH_LENGTH])
		{
			// Property: flash_length
			if (passValidateProperty(compiler, prop, token[TOKEN_FLASH_LENGTH], VAL_REAL))
			{
				Real val;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setFlashLength(val);
				}
			}
		}
		else if (prop->name == token[TOKEN_FLASH_RANDOM])
		{
			// Property: flash_random
			if (passValidateProperty(compiler, prop, token[TOKEN_FLASH_RANDOM], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setFlashRandom(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool LightRendererTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void LightRendererWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a LightRenderer
		const LightRenderer* renderer = static_cast<const LightRenderer*>(element);

		// Write the header of the LightRenderer
		serializer->writeLine(token[TOKEN_RENDERER], renderer->getRendererType(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleRendererWriter::write(serializer, element);

		// Write own attributes
		if (renderer->getLightType() != LightRenderer::DEFAULT_LIGHT_TYPE)
		{
			String lightType = token[TOKEN_POINT];
			if (renderer->getLightType() == Ogre::Light::LT_SPOTLIGHT) lightType = token[TOKEN_LIGHT_SPOT];
			serializer->writeLine(token[TOKEN_LIGHT_TYPE], lightType, 12);
		}
		if (renderer->getRenderQueueGroup() != LightRenderer::DEFAULT_RENDER_QUEUE_GROUP) serializer->writeLine(
			token[TOKEN_LIGHT_RENDER_QUEUE], StringConverter::toString(renderer->getRenderQueueGroup()), 12);
		if (renderer->getSpecularColour() != LightRenderer::DEFAULT_SPECULAR) serializer->writeLine(
			token[TOKEN_LIGHT_SPECULAR], StringConverter::toString(renderer->getSpecularColour()), 12);
		if (renderer->getAttenuationRange() != LightRenderer::DEFAULT_ATT_RANGE) serializer->writeLine(
			token[TOKEN_LIGHT_ATT_RANGE], StringConverter::toString(renderer->getAttenuationRange()), 12);
		if (renderer->getAttenuationConstant() != LightRenderer::DEFAULT_ATT_CONSTANT) serializer->writeLine(
			token[TOKEN_LIGHT_ATT_CONSTANT], StringConverter::toString(renderer->getAttenuationConstant()), 12);
		if (renderer->getAttenuationLinear() != LightRenderer::DEFAULT_ATT_LINEAR) serializer->writeLine(
			token[TOKEN_LIGHT_ATT_LINEAR], StringConverter::toString(renderer->getAttenuationLinear()), 12);
		if (renderer->getAttenuationQuadratic() != LightRenderer::DEFAULT_ATT_QUADRATIC) serializer->writeLine(
			token[TOKEN_LIGHT_ATT_QUADRATIC], StringConverter::toString(renderer->getAttenuationQuadratic()), 12);
		if (renderer->getSpotlightInnerAngle() != LightRenderer::DEFAULT_SPOT_INNER_ANGLE) serializer->writeLine(
			token[TOKEN_LIGHT_SPOT_INNER], StringConverter::toString(renderer->getSpotlightInnerAngle().valueDegrees()), 12);
		if (renderer->getSpotlightOuterAngle() != LightRenderer::DEFAULT_SPOT_OUTER_ANGLE) serializer->writeLine(
			token[TOKEN_LIGHT_SPOT_OUTER], StringConverter::toString(renderer->getSpotlightOuterAngle().valueDegrees()), 12);
		if (renderer->getSpotlightFalloff() != LightRenderer::DEFAULT_FALLOFF) serializer->writeLine(
			token[TOKEN_LIGHT_FALLOFF], StringConverter::toString(renderer->getSpotlightFalloff()), 12);
		if (renderer->getPowerScale() != LightRenderer::DEFAULT_POWER_SCALE) serializer->writeLine(
			token[TOKEN_LIGHT_POWERSCALE], StringConverter::toString(renderer->getPowerScale()), 12);
		if (renderer->getFlashFrequency() != 0.0f) serializer->writeLine(
			token[TOKEN_FLASH_FREQUENCY], StringConverter::toString(renderer->getFlashFrequency()), 12);
		if (renderer->getFlashLength() != 0.0f) serializer->writeLine(
			token[TOKEN_FLASH_LENGTH], StringConverter::toString(renderer->getFlashLength()), 12);
		if (renderer->isFlashRandom()) serializer->writeLine(
			token[TOKEN_FLASH_RANDOM], StringConverter::toString(renderer->isFlashRandom()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
