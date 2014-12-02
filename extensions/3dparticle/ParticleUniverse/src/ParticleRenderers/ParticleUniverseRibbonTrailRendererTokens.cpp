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

#include "ParticleRenderers/ParticleUniverseRibbonTrailRendererTokens.h"
#include "ParticleRenderers/ParticleUniverseRibbonTrailRenderer.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool RibbonTrailRendererTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleRenderer* ren = any_cast<ParticleRenderer*>(prop->parent->context);
		RibbonTrailRenderer* renderer = static_cast<RibbonTrailRenderer*>(ren);

		if (prop->name == token[TOKEN_USE_VERTEX_COLOURS])
		{
			// Property: use_vertex_colours
			if (passValidateProperty(compiler, prop, token[TOKEN_USE_VERTEX_COLOURS], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setUseVertexColours(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_VERTEX_COLOURS])
		{
			// Property: ribbontrail_vertex_colours (deprecated and replaced by 'use_vertex_colours')
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_VERTEX_COLOURS], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setUseVertexColours(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MAX_ELEMENTS])
		{
			// Property: max_elements
			if (passValidateProperty(compiler, prop, token[TOKEN_MAX_ELEMENTS], VAL_UINT))
			{
				uint val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					renderer->setMaxChainElements(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_MAX_ELEMENTS])
		{
			// Property: ribbontrail_max_elements (deprecated and replaced by 'max_elements')
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_MAX_ELEMENTS], VAL_UINT))
			{
				uint val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					renderer->setMaxChainElements(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_LENGTH])
		{
			// Property: ribbontrail_length
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_MAX_ELEMENTS], VAL_REAL))
			{
				Real val = 0;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setTrailLength(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_WIDTH])
		{
			// Property: ribbontrail_width
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_WIDTH], VAL_REAL))
			{
				Real val = 0;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setTrailWidth(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RANDOM_INITIAL_COLOUR])
		{
			// Property: random_initial_colour
			if (passValidateProperty(compiler, prop, token[TOKEN_RANDOM_INITIAL_COLOUR], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setRandomInitialColour(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_RANDOM_INITIAL_COLOUR])
		{
			// Property: ribbontrail_random_initial_colour (deprecated and replaced by 'random_initial_colour'))
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_RANDOM_INITIAL_COLOUR], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setRandomInitialColour(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INITIAL_COLOUR])
		{
			// Property: initial_colour
			if (passValidateProperty(compiler, prop, token[TOKEN_INITIAL_COLOUR], VAL_COLOURVALUE))
			{
				ColourValue val;
				if(getColour(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setInitialColour(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_INITIAL_COLOUR])
		{
			// Property: ribbontrail_initial_colour (deprecated and replaced by 'initial_colour')
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_INITIAL_COLOUR], VAL_COLOURVALUE))
			{
				ColourValue val;
				if(getColour(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setInitialColour(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_COLOUR_CHANGE])
		{
			// Property: colour_change
			if (passValidateProperty(compiler, prop, token[TOKEN_COLOUR_CHANGE], VAL_COLOURVALUE))
			{
				ColourValue val;
				if(getColour(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setColourChange(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_RIBBONTRAIL_COLOUR_CHANGE])
		{
			// Property: ribbontrail_colour_change (deprecated and replaced by 'colour_change')
			if (passValidateProperty(compiler, prop, token[TOKEN_RIBBONTRAIL_COLOUR_CHANGE], VAL_COLOURVALUE))
			{
				ColourValue val;
				if(getColour(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setColourChange(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool RibbonTrailRendererTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void RibbonTrailRendererWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a RibbonTrailRenderer
		const RibbonTrailRenderer* renderer = static_cast<const RibbonTrailRenderer*>(element);

		// Write the header of the LightRenderer
		serializer->writeLine(token[TOKEN_RENDERER], renderer->getRendererType(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleRendererWriter::write(serializer, element);

		// Write own attributes
		if (renderer->isUseVertexColours() != RibbonTrailRenderer::DEFAULT_USE_VERTEX_COLOURS) serializer->writeLine(
			token[TOKEN_USE_VERTEX_COLOURS], StringConverter::toString(renderer->isUseVertexColours()), 12);
		if (renderer->getMaxChainElements() != RibbonTrailRenderer::DEFAULT_MAX_ELEMENTS) serializer->writeLine(
			token[TOKEN_MAX_ELEMENTS], StringConverter::toString(renderer->getMaxChainElements()), 12);
		if (renderer->getTrailLength() != RibbonTrailRenderer::DEFAULT_LENGTH) serializer->writeLine(
			token[TOKEN_RIBBONTRAIL_LENGTH], StringConverter::toString(renderer->getTrailLength()), 12);
		if (renderer->getTrailWidth() != RibbonTrailRenderer::DEFAULT_WIDTH) serializer->writeLine(
			token[TOKEN_RIBBONTRAIL_WIDTH], StringConverter::toString(renderer->getTrailWidth()), 12);
		if (renderer->isRandomInitialColour() != RibbonTrailRenderer::DEFAULT_RANDOM_INITIAL_COLOUR) serializer->writeLine(
			token[TOKEN_RANDOM_INITIAL_COLOUR], StringConverter::toString(renderer->isRandomInitialColour()), 12);
		if (renderer->getInitialColour() != RibbonTrailRenderer::DEFAULT_INITIAL_COLOUR) serializer->writeLine(
			token[TOKEN_INITIAL_COLOUR], StringConverter::toString(renderer->getInitialColour()), 12);
		if (renderer->getColourChange() != RibbonTrailRenderer::DEFAULT_COLOUR_CHANGE) serializer->writeLine(
			token[TOKEN_COLOUR_CHANGE], StringConverter::toString(renderer->getColourChange()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
