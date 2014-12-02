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

#include "ParticleAffectors/ParticleUniverseTextureRotator.h"
#include "ParticleAffectors/ParticleUniverseTextureRotatorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool TextureRotatorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		TextureRotator* affector = static_cast<TextureRotator*>(af);

		if (prop->name == token[TOKEN_USE_OWN_ROTATION])
		{
			// Property: use_own_rotation
			if (passValidateProperty(compiler, prop, token[TOKEN_USE_OWN_ROTATION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setUseOwnRotationSpeed(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_TEXROT_USE_OWN_ROTATION])
		{
			// Property: tex_rot_use_own_rotation (deprecated and replaced by 'use_own_rotation')
			if (passValidateProperty(compiler, prop, token[TOKEN_TEXROT_USE_OWN_ROTATION], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setUseOwnRotationSpeed(val);
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
		else if (prop->name == token[TOKEN_TEXROT_ROTATION_SPEED])
		{
			// Property: tex_rot_speed (deprecated and replaced by 'rotation_speed')
			if (passValidateProperty(compiler, prop, token[TOKEN_TEXROT_ROTATION_SPEED], VAL_REAL))
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
		else if (prop->name == token[TOKEN_ROTATION])
		{
			// Property: rotation
			if (passValidateProperty(compiler, prop, token[TOKEN_ROTATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
					dynamicAttributeFixed->setValue(val);
					affector->setRotation(dynamicAttributeFixed);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_TEXROT_ROTATION])
		{
			// Property: tex_rot_rotation (deprecated and replaced by 'rotation')
			if (passValidateProperty(compiler, prop, token[TOKEN_TEXROT_ROTATION], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
					dynamicAttributeFixed->setValue(val);
					affector->setRotation(dynamicAttributeFixed);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool TextureRotatorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(child->parent->context);
		TextureRotator* affector = static_cast<TextureRotator*>(af);

		DynamicAttributeTranslator dynamicAttributeTranslator;
		if (child->cls == token[TOKEN_ROTATION_SPEED])
		{
			// Property: rotation_speed
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setRotationSpeed(dynamicAttribute);
			return true;
		}
		else if (child->cls == token[TOKEN_TEXROT_ROTATION_SPEED])
		{
			// Property: tex_rot_speed (deprecated and replaced by 'rotation_speed')
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setRotationSpeed(dynamicAttribute);
			return true;
		}
		else if (child->cls == token[TOKEN_ROTATION])
		{
			// Property: rotation
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setRotation(dynamicAttribute);
			return true;
		}
		else if (child->cls == token[TOKEN_TEXROT_ROTATION])
		{
			// Property: tex_rot_rotation (deprecated and replaced by 'rotation')
			dynamicAttributeTranslator.translate(compiler, node);
			DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
			affector->setRotation(dynamicAttribute);
			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void TextureRotatorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a TextureRotator
		const TextureRotator* affector = static_cast<const TextureRotator*>(element);

		// Write the header of the TextureRotator
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->useOwnRotationSpeed() != TextureRotator::DEFAULT_USE_OWN_SPEED) serializer->writeLine(
			token[TOKEN_USE_OWN_ROTATION], StringConverter::toString(affector->useOwnRotationSpeed()), 12);
		DynamicAttributeFactory dynamicAttributeFactory;
		if (dynamicAttributeFactory._getDefaultValue(affector->getRotation()) != TextureRotator::DEFAULT_ROTATION)
		{
			serializer->setKeyword(token[TOKEN_ROTATION]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, affector->getRotation());
		}
		if (dynamicAttributeFactory._getDefaultValue(affector->getRotationSpeed()) != TextureRotator::DEFAULT_ROTATION_SPEED)
		{
			serializer->setKeyword(token[TOKEN_ROTATION_SPEED]);
			dynamicAttributeFactory.write(serializer, affector->getRotationSpeed());
		}

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
