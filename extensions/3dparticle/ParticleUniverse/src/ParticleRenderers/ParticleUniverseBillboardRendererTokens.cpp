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

#include "ParticleRenderers/ParticleUniverseBillboardRendererTokens.h"
#include "ParticleRenderers/ParticleUniverseBillboardRenderer.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool BillboardRendererTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleRenderer* ren = any_cast<ParticleRenderer*>(prop->parent->context);
		BillboardRenderer* renderer = static_cast<BillboardRenderer*>(ren);

		if (prop->name == token[TOKEN_BILLBOARD_TYPE])
		{
			// Property: billboard_type
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_TYPE], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_POINT])
					{
						renderer->setBillboardType(BillboardRenderer::BBT_POINT);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_ORIENTED_COMMON])
					{
						renderer->setBillboardType(BillboardRenderer::BBT_ORIENTED_COMMON);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_ORIENTED_SELF])
					{
						renderer->setBillboardType(BillboardRenderer::BBT_ORIENTED_SELF);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_ORIENTED_SHAPE])
					{
						renderer->setBillboardType(BillboardRenderer::BBT_ORIENTED_SHAPE);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_PERPENDICULAR_COMMON])
					{
						renderer->setBillboardType(BillboardRenderer::BBT_PERPENDICULAR_COMMON);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_PERPENDICULAR_SELF])
					{
						renderer->setBillboardType(BillboardRenderer::BBT_PERPENDICULAR_SELF);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_BILLBOARD_ORIGIN])
		{
			// Property: billboard_origin
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_ORIGIN], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_BILLBOARD_CENTER])
					{
						renderer->setBillboardOrigin(Ogre::BBO_CENTER);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_BOTTOM_CENTER])
					{
						renderer->setBillboardOrigin(Ogre::BBO_BOTTOM_CENTER);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_BOTTON_LEFT])
					{
						renderer->setBillboardOrigin(Ogre::BBO_BOTTOM_LEFT);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_BOTTOM_RIGHT])
					{
						renderer->setBillboardOrigin(Ogre::BBO_BOTTOM_RIGHT);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_CENTER_LEFT])
					{
						renderer->setBillboardOrigin(Ogre::BBO_CENTER_LEFT);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_CENTER_RIGHT])
					{
						renderer->setBillboardOrigin(Ogre::BBO_CENTER_RIGHT);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_TOP_CENTER])
					{
						renderer->setBillboardOrigin(Ogre::BBO_TOP_CENTER);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_TOP_LEFT])
					{
						renderer->setBillboardOrigin(Ogre::BBO_TOP_LEFT);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_TOP_RIGHT])
					{
						renderer->setBillboardOrigin(Ogre::BBO_TOP_RIGHT);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_BILLBOARD_ROTATION_TYPE])
		{
			// Property: billboard_rotation_type
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_ROTATION_TYPE], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_VERTEX])
					{
						renderer->setBillboardRotationType(Ogre::BBR_VERTEX);
						return true;
					}
					else if (val == token[TOKEN_BILLBOARD_TEXCOORD])
					{
						renderer->setBillboardRotationType(Ogre::BBR_TEXCOORD);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_BILLBOARD_COMMON_DIRECTION])
		{
			// Property: common_direction
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_COMMON_DIRECTION], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setCommonDirection(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BILLBOARD_COMMON_UP_VECTOR])
		{
			// Property: common_up_vector
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_COMMON_UP_VECTOR], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					renderer->setCommonUpVector(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BILLBOARD_POINT_RENDERING])
		{
			// Property: point_rendering
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_POINT_RENDERING], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setPointRenderingEnabled(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BILLBOARD_ACCURATE_FACING])
		{
			// Property: accurate_facing
			if (passValidateProperty(compiler, prop, token[TOKEN_BILLBOARD_ACCURATE_FACING], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					renderer->setUseAccurateFacing(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool BillboardRendererTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void BillboardRendererWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a BillboardRenderer
		const BillboardRenderer* renderer = static_cast<const BillboardRenderer*>(element);

		// Write the header of the BillboardRenderer
		serializer->writeLine(token[TOKEN_RENDERER], renderer->getRendererType(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleRendererWriter::write(serializer, element);

		// Write own attributes
		if (renderer->getBillboardType() != BillboardRenderer::DEFAULT_BILLBOARD_TYPE)
		{
			String billboardType = token[TOKEN_POINT];
			if (renderer->getBillboardType() == BillboardRenderer::BBT_ORIENTED_COMMON) billboardType = token[TOKEN_BILLBOARD_ORIENTED_COMMON];
			else if (renderer->getBillboardType() == BillboardRenderer::BBT_ORIENTED_SELF) billboardType = token[TOKEN_BILLBOARD_ORIENTED_SELF];
			else if (renderer->getBillboardType() == BillboardRenderer::BBT_ORIENTED_SHAPE) billboardType = token[TOKEN_BILLBOARD_ORIENTED_SHAPE];
			else if (renderer->getBillboardType() == BillboardRenderer::BBT_PERPENDICULAR_COMMON) billboardType = token[TOKEN_BILLBOARD_PERPENDICULAR_COMMON];
			else if (renderer->getBillboardType() == BillboardRenderer::BBT_PERPENDICULAR_SELF) billboardType = token[TOKEN_BILLBOARD_PERPENDICULAR_SELF];
			serializer->writeLine(token[TOKEN_BILLBOARD_TYPE], billboardType, 12);
		}

		if (renderer->getBillboardOrigin() != BillboardRenderer::DEFAULT_ORIGIN)
		{
			String origin = token[TOKEN_BILLBOARD_CENTER];
			if (renderer->getBillboardOrigin() == Ogre::BBO_BOTTOM_CENTER) origin = token[TOKEN_BILLBOARD_BOTTOM_CENTER];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_BOTTOM_LEFT) origin = token[TOKEN_BILLBOARD_BOTTON_LEFT];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_BOTTOM_RIGHT) origin = token[TOKEN_BILLBOARD_BOTTOM_RIGHT];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_CENTER_LEFT) origin = token[TOKEN_BILLBOARD_CENTER_LEFT];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_CENTER_RIGHT) origin = token[TOKEN_BILLBOARD_CENTER_RIGHT];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_TOP_CENTER) origin = token[TOKEN_BILLBOARD_TOP_CENTER];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_TOP_LEFT) origin = token[TOKEN_BILLBOARD_TOP_LEFT];
			else if (renderer->getBillboardOrigin() == Ogre::BBO_TOP_RIGHT) origin = token[TOKEN_BILLBOARD_TOP_RIGHT];
			serializer->writeLine(token[TOKEN_BILLBOARD_ORIGIN], origin, 12);
		}

		if (renderer->getBillboardRotationType() != BillboardRenderer::DEFAULT_ROTATION_TYPE)
		{
			String rotationType = token[TOKEN_VERTEX];
			if (renderer->getBillboardRotationType() == Ogre::BBR_TEXCOORD) rotationType = token[TOKEN_BILLBOARD_TEXCOORD];
			serializer->writeLine(token[TOKEN_BILLBOARD_ROTATION_TYPE], rotationType, 12);
		}

		if (renderer->getCommonDirection() != BillboardRenderer::DEFAULT_COMMON_DIRECTION) serializer->writeLine(
			token[TOKEN_BILLBOARD_COMMON_DIRECTION], StringConverter::toString(renderer->getCommonDirection()), 12);
		if (renderer->getCommonUpVector() != BillboardRenderer::DEFAULT_COMMON_UP_VECTOR) serializer->writeLine(
			token[TOKEN_BILLBOARD_COMMON_UP_VECTOR], StringConverter::toString(renderer->getCommonUpVector()), 12);
		if (renderer->isPointRenderingEnabled() != BillboardRenderer::DEFAULT_POINT_RENDERING) serializer->writeLine(
			token[TOKEN_BILLBOARD_POINT_RENDERING], StringConverter::toString(renderer->isPointRenderingEnabled()), 12);
		if (renderer->isUseAccurateFacing() != BillboardRenderer::DEFAULT_ACCURATE_FACING) serializer->writeLine(
			token[TOKEN_BILLBOARD_ACCURATE_FACING], StringConverter::toString(renderer->isUseAccurateFacing()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
