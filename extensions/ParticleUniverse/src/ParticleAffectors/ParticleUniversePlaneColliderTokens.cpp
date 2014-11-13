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

#include "ParticleAffectors/ParticleUniversePlaneCollider.h"
#include "ParticleAffectors/ParticleUniversePlaneColliderTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool PlaneColliderTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		PlaneCollider* affector = static_cast<PlaneCollider*>(af);

		if (prop->name == token[TOKEN_NORMAL])
		{
			// Property: normal
			if (passValidateProperty(compiler, prop, token[TOKEN_NORMAL], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setNormal(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_PLANECOLL_NORMAL])
		{
			// Property: plane_collider_normal (deprecated and replaced by 'normal')
			if (passValidateProperty(compiler, prop, token[TOKEN_PLANECOLL_NORMAL], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setNormal(val);
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
	bool PlaneColliderTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void PlaneColliderWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a PlaneCollider
		const PlaneCollider* affector = static_cast<const PlaneCollider*>(element);

		// Write the header of the PlaneCollider
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		BaseColliderWriter::write(serializer, element);

		// Write own attributes
		if (affector->getNormal() != PlaneCollider::DEFAULT_NORMAL) serializer->writeLine(
			token[TOKEN_NORMAL], StringConverter::toString(affector->getNormal()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
