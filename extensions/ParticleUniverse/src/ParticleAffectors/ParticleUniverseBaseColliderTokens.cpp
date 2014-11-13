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

#include "ParticleAffectors/ParticleUniverseBaseCollider.h"
#include "ParticleAffectors/ParticleUniverseBaseColliderTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool BaseColliderTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		BaseCollider* affector = static_cast<BaseCollider*>(af); // Do not check type; assume the type is correct.

		if (prop->name == token[TOKEN_FRICTION])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_FRICTION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setFriction(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_COLLIDER_FRICTION])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_COLLIDER_FRICTION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setFriction(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_BOUNCYNESS])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_BOUNCYNESS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setBouncyness(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_COLLIDER_BOUNCYNESS])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_COLLIDER_BOUNCYNESS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setBouncyness(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_INTERSECTION] || prop->name == token[TOKEN_COLLIDER_INTERSECTION])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_INTERSECTION], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_COLLIDER_INTERSECTION_POINT])
					{
						affector->setIntersectionType(BaseCollider::IT_POINT);
						return true;
					}
					else if (val == token[TOKEN_COLLIDER_INTERSECTION_BOX])
					{
						affector->setIntersectionType(BaseCollider::IT_BOX);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_COLLIDER_COLLISION_TYPE])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_COLLIDER_COLLISION_TYPE], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_COLLIDER_BOUNCE])
					{
						affector->setCollisionType(BaseCollider::CT_BOUNCE);
						return true;
					}
					else if (val == token[TOKEN_COLLIDER_FLOW])
					{
						affector->setCollisionType(BaseCollider::CT_FLOW);
						return true;
					}
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool BaseColliderTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void BaseColliderWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a BaseCollider
		const BaseCollider* affector = static_cast<const BaseCollider*>(element);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getFriction() != BaseCollider::DEFAULT_FRICTION) serializer->writeLine(
			token[TOKEN_FRICTION], StringConverter::toString(affector->getFriction()), 12);
		if (affector->getBouncyness() != BaseCollider::DEFAULT_BOUNCYNESS) serializer->writeLine(
			token[TOKEN_BOUNCYNESS], StringConverter::toString(affector->getBouncyness()), 12);
		if (affector->getIntersectionType() != BaseCollider::DEFAULT_INTERSECTION_TYPE) 
		{
			String intersectionType = token[TOKEN_COLLIDER_INTERSECTION_POINT];
			if (affector->getIntersectionType() == BaseCollider::IT_BOX) intersectionType = token[TOKEN_COLLIDER_INTERSECTION_BOX];
			serializer->writeLine(token[TOKEN_INTERSECTION], intersectionType, 12);
		}
		if (affector->getCollisionType() != BaseCollider::DEFAULT_COLLISION_TYPE) 
		{
			String collisionType = token[TOKEN_COLLIDER_BOUNCE];
			if (affector->getCollisionType() == BaseCollider::CT_FLOW) collisionType = token[TOKEN_COLLIDER_FLOW];
			else if (affector->getCollisionType() == BaseCollider::CT_NONE) collisionType = token[TOKEN_COLLIDER_NONE];
			serializer->writeLine(token[TOKEN_COLLIDER_COLLISION_TYPE], collisionType, 12);
		}
	}

}
