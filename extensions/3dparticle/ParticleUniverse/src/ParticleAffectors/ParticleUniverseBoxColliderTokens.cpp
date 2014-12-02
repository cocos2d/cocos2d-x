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

#include "ParticleAffectors/ParticleUniverseBoxCollider.h"
#include "ParticleAffectors/ParticleUniverseBoxColliderTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool BoxColliderTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		BoxCollider* affector = static_cast<BoxCollider*>(af);
		if (prop->name == token[TOKEN_BOX_WIDTH])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_BOX_WIDTH], VAL_REAL))
			{
				// Property: box_width
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setWidth(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BOXCOLL_WIDTH])
		{
			// Property: box_collider_width (deprecated and replaced by 'box_width')
			if (passValidateProperty(compiler, prop, token[TOKEN_BOXCOLL_WIDTH], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setWidth(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BOX_HEIGHT])
		{
			// Property: box_height
			if (passValidateProperty(compiler, prop, token[TOKEN_BOX_HEIGHT], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setHeight(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BOXCOLL_HEIGHT])
		{
			// Property: box_collider_height (deprecated and replaced by 'box_height')
			if (passValidateProperty(compiler, prop, token[TOKEN_BOXCOLL_HEIGHT], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setHeight(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BOX_DEPTH])
		{
			// Property: box_depth
			if (passValidateProperty(compiler, prop, token[TOKEN_BOX_DEPTH], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setDepth(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BOXCOLL_DEPTH])
		{
			// Property: box_collider_depth (deprecated and replaced by 'box_depth')
			if (passValidateProperty(compiler, prop, token[TOKEN_BOXCOLL_DEPTH], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setDepth(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INNER_COLLISION])
		{
			// Property: inner_collision
			if (passValidateProperty(compiler, prop, token[TOKEN_INNER_COLLISION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setInnerCollision(val);
					return true;
				}
			}
		}
		else
		{
			// Parse the BaseCollider
			BaseColliderTranslator baseColliderTranslator;
			return baseColliderTranslator.translateChildProperty(compiler, node);
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool BoxColliderTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void BoxColliderWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a BoxCollider
		const BoxCollider* affector = static_cast<const BoxCollider*>(element);

		// Write the header of the BoxCollider
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		BaseColliderWriter::write(serializer, element);

		// Write own attributes
		if (affector->getWidth() != BoxCollider::DEFAULT_WIDTH) serializer->writeLine(
			token[TOKEN_BOX_WIDTH], StringConverter::toString(affector->getWidth()), 12);
		if (affector->getHeight() != BoxCollider::DEFAULT_HEIGHT) serializer->writeLine(
			token[TOKEN_BOX_HEIGHT], StringConverter::toString(affector->getHeight()), 12);
		if (affector->getDepth() != BoxCollider::DEFAULT_DEPTH) serializer->writeLine(
			token[TOKEN_BOX_DEPTH], StringConverter::toString(affector->getDepth()), 12);
		if (affector->isInnerCollision() != false) serializer->writeLine(
			token[TOKEN_INNER_COLLISION], StringConverter::toString(affector->isInnerCollision()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
