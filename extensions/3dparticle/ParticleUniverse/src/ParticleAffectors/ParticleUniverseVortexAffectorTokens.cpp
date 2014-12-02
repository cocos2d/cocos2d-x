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

#include "ParticleAffectors/ParticleUniverseVortexAffector.h"
#include "ParticleAffectors/ParticleUniverseVortexAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool VortexAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		VortexAffector* affector = static_cast<VortexAffector*>(af);

		if (prop->name == token[TOKEN_ROTATION_AXIS])
		{
			// Property: rotation_axis
			if (passValidateProperty(compiler, prop, token[TOKEN_ROTATION_AXIS], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setRotationVector(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_VORTEX_ROTATION_VECTOR])
		{
			// Property: vortex_aff_vector (deprecated and replaced by 'rotation_axis')
			if (passValidateProperty(compiler, prop, token[TOKEN_VORTEX_ROTATION_VECTOR], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setRotationVector(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_ROTATION_SPEED])
		{
			// Property: rotation_speed
			if (passValidateProperty(compiler, prop, token[TOKEN_ROTATION_SPEED], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
					dynamicAttributeFixed->setValue(val);
					affector->setRotationSpeed(dynamicAttributeFixed);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_VORTEX_ROTATION_SPEED])
		{
			// Property: vortex_aff_speed (deprecated and replaced by 'rotation_speed')
			if (passValidateProperty(compiler, prop, token[TOKEN_VORTEX_ROTATION_SPEED], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
					dynamicAttributeFixed->setValue(val);
					affector->setRotationSpeed(dynamicAttributeFixed);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool VortexAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(child->parent->context);
		VortexAffector* affector = static_cast<VortexAffector*>(af);

		DynamicAttributeTranslator dynamicAttributeTranslator;
		if (child->cls == token[TOKEN_ROTATION_SPEED])
		{
			// Property: rotation_speed
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setRotationSpeed(dynamicAttribute);
			return true;
		}
		else if (child->cls == token[TOKEN_VORTEX_ROTATION_SPEED])
		{
			// Property: vortex_aff_speed (deprecated and replaced by 'rotation_speed')
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setRotationSpeed(dynamicAttribute);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void VortexAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a VortexAffector
		const VortexAffector* affector = static_cast<const VortexAffector*>(element);

		// Write the header of the VortexAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getRotationVector() != VortexAffector::DEFAULT_ROTATION_VECTOR) serializer->writeLine(
			token[TOKEN_ROTATION_AXIS], StringConverter::toString(affector->getRotationVector()), 12);
		DynamicAttributeFactory dynamicAttributeFactory;
		if (dynamicAttributeFactory._getDefaultValue(affector->getRotationSpeed()) != VortexAffector::DEFAULT_ROTATION_SPEED)
		{
			serializer->setKeyword(token[TOKEN_ROTATION_SPEED]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, affector->getRotationSpeed());
		}

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
