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

#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleAffectors/ParticleUniverseSphereColliderTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool SphereColliderTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		SphereCollider* affector = static_cast<SphereCollider*>(af);

		if (prop->name == token[TOKEN_RADIUS])
		{
			// Property: radius
			if (passValidateProperty(compiler, prop, token[TOKEN_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setRadius(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SPHERE_COLLIDER_RADIUS])
		{
			// Property: sphere_collider_radius (Deprecated; replaced by radius)
			if (passValidateProperty(compiler, prop, token[TOKEN_SPHERE_COLLIDER_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->setRadius(val);
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
	bool SphereColliderTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void SphereColliderWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a SphereCollider
		const SphereCollider* affector = static_cast<const SphereCollider*>(element);

		// Write the header of the SphereCollider
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		BaseColliderWriter::write(serializer, element);

		// Write own attributes
		if (affector->getRadius() != SphereCollider::DEFAULT_RADIUS) serializer->writeLine(
			token[TOKEN_RADIUS], StringConverter::toString(affector->getRadius()), 12);
		if (affector->isInnerCollision() != false) serializer->writeLine(
			token[TOKEN_INNER_COLLISION], StringConverter::toString(affector->isInnerCollision()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
