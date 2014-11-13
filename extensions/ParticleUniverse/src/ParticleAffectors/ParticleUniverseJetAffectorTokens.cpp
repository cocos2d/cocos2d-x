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

#include "ParticleAffectors/ParticleUniverseJetAffector.h"
#include "ParticleAffectors/ParticleUniverseJetAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool JetAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		JetAffector* affector = static_cast<JetAffector*>(af);

		if (prop->name == token[TOKEN_ACCELERATION])
		{
			// Property: acceleration
			if (passValidateProperty(compiler, prop, token[TOKEN_ACCELERATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
					dynamicAttributeFixed->setValue(val);
					affector->setDynAcceleration(dynamicAttributeFixed);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_JET_ACCELERATION])
		{
			// Property: jet_aff_accel (deprecated and replaced by 'acceleration')
			if (passValidateProperty(compiler, prop, token[TOKEN_JET_ACCELERATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
					dynamicAttributeFixed->setValue(val);
					affector->setDynAcceleration(dynamicAttributeFixed);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool JetAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(child->parent->context);
		JetAffector* affector = static_cast<JetAffector*>(af);

		DynamicAttributeTranslator dynamicAttributeTranslator;
		if (child->cls == token[TOKEN_ACCELERATION])
		{
			// Property: acceleration
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setDynAcceleration(dynamicAttribute);
			return true;
		}
		else if (child->cls == token[TOKEN_JET_ACCELERATION])
		{
			// Property: jet_aff_accel (deprecated and replaced by 'acceleration')
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setDynAcceleration(dynamicAttribute);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void JetAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a JetAffector
		const JetAffector* affector = static_cast<const JetAffector*>(element);

		// Write the header of the JetAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		DynamicAttributeFactory dynamicAttributeFactory;
		if (dynamicAttributeFactory._getDefaultValue(affector->getDynAcceleration()) != JetAffector::DEFAULT_ACCELERATION)
		{
			serializer->setKeyword(token[TOKEN_ACCELERATION]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, affector->getDynAcceleration());
		}

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
