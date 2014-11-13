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

#include "ParticleRenderers/ParticleUniverseBeamRendererTokens.h"
#include "ParticleRenderers/ParticleUniverseBeamRenderer.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool BeamRendererTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleRenderer* ren = any_cast<ParticleRenderer*>(prop->parent->context);
		BeamRenderer* renderer = static_cast<BeamRenderer*>(ren);

		if (prop->name == token[TOKEN_UPDATE_INTERVAL])
		{
			// Property: update_interval
			if (passValidateProperty(compiler, prop, token[TOKEN_UPDATE_INTERVAL], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setUpdateInterval(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BEAMRENDERER_UPDATE_INTERVAL])
		{
			// Property: beam_update_interval (deprecated and replaced by 'update_interval')
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_UPDATE_INTERVAL], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setUpdateInterval(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BEAMRENDERER_DEVIATION])
		{
			// Property: beam_deviation
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_DEVIATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					renderer->setDeviation(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_NUMBER_OF_SEGMENTS])
		{
			// Property: number_of_segments
			if (passValidateProperty(compiler, prop, token[TOKEN_NUMBER_OF_SEGMENTS], VAL_UINT))
			{
				uint val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					renderer->setNumberOfSegments(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BEAMRENDERER_NUMBER_OF_SEGMENTS])
		{
			// Property: beam_number_segments (deprecated and replaced by 'number_of_segments')
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_NUMBER_OF_SEGMENTS], VAL_UINT))
			{
				uint val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					renderer->setNumberOfSegments(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BEAMRENDERER_JUMP])
		{
			// Property: beam_jump_segments
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_JUMP], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setJump(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BEAMRENDERER_TEXCOORD_DIRECTION])
		{
			// Property: beam_texcoord_direction
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_TEXCOORD_DIRECTION], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_BEAMRENDERER_TCD_U])
					{
						renderer->setTexCoordDirection(Ogre::BillboardChain::TCD_U);
						return true;
					}
					else if (val == token[TOKEN_BEAMRENDERER_TCD_V])
					{
						renderer->setTexCoordDirection(Ogre::BillboardChain::TCD_V);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_USE_VERTEX_COLOURS])
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
		else if (prop->name == token[TOKEN_BEAMRENDERER_VERTEX_COLOURS])
		{
			// Property: beam_vertex_colours (deprecated and replaced by 'use_vertex_colours')
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_VERTEX_COLOURS], VAL_BOOL))
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
		else if (prop->name == token[TOKEN_BEAMRENDERER_MAX_ELEMENTS])
		{
			// Property: beam_max_elements (deprecated and replaced by 'max_elements')
			if (passValidateProperty(compiler, prop, token[TOKEN_BEAMRENDERER_MAX_ELEMENTS], VAL_UINT))
			{
				uint val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					renderer->setMaxChainElements(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool BeamRendererTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void BeamRendererWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a BeamRenderer
		const BeamRenderer* renderer = static_cast<const BeamRenderer*>(element);

		// Write the header of the LightRenderer
		serializer->writeLine(token[TOKEN_RENDERER], renderer->getRendererType(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleRendererWriter::write(serializer, element);

		// Write own attributes
		if (renderer->isUseVertexColours() != BeamRenderer::DEFAULT_USE_VERTEX_COLOURS) serializer->writeLine(
			token[TOKEN_USE_VERTEX_COLOURS], StringConverter::toString(renderer->isUseVertexColours()), 12);
		if (renderer->getMaxChainElements() != BeamRenderer::DEFAULT_MAX_ELEMENTS) serializer->writeLine(
			token[TOKEN_MAX_ELEMENTS], StringConverter::toString(renderer->getMaxChainElements()), 12);
		if (renderer->getUpdateInterval() != BeamRenderer::DEFAULT_UPDATE_INTERVAL) serializer->writeLine(
			token[TOKEN_UPDATE_INTERVAL], StringConverter::toString(renderer->getUpdateInterval()), 12);
		if (renderer->getDeviation() != BeamRenderer::DEFAULT_DEVIATION) serializer->writeLine(
			token[TOKEN_BEAMRENDERER_DEVIATION], StringConverter::toString(renderer->getDeviation()), 12);
		if (renderer->getNumberOfSegments() != BeamRenderer::DEFAULT_NUMBER_OF_SEGMENTS) serializer->writeLine(
			token[TOKEN_NUMBER_OF_SEGMENTS], StringConverter::toString(renderer->getNumberOfSegments()), 12);
		if (renderer->isJump() != false) serializer->writeLine(
			token[TOKEN_BEAMRENDERER_JUMP], StringConverter::toString(renderer->isJump()), 12);
		if (renderer->getTexCoordDirection() != BeamRenderer::DEFAULT_TEXTURE_DIRECTION)
		{
			serializer->writeLine(token[TOKEN_BEAMRENDERER_TEXCOORD_DIRECTION], token[TOKEN_BEAMRENDERER_TCD_U], 12);
		}

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
