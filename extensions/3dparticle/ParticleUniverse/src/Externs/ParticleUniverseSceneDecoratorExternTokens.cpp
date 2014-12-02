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

#include "Externs/ParticleUniverseSceneDecoratorExtern.h"
#include "Externs/ParticleUniverseSceneDecoratorExternTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool SceneDecoratorExternTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		Extern* ex = any_cast<Extern*>(prop->parent->context);
		SceneDecoratorExtern* externObject = static_cast<SceneDecoratorExtern*>(ex);

		if (prop->name == token[TOKEN_MESH_NAME])
		{
			// Property: mesh_name
			if (passValidateProperty(compiler, prop, token[TOKEN_MESH_NAME], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					externObject->setMeshName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SCENE_MESH_NAME])
		{
			// Property: scene_mesh_name (deprecated and replaced by mesh_name)
			if (passValidateProperty(compiler, prop, token[TOKEN_SCENE_MESH_NAME], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					externObject->setMeshName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MATERIAL])
		{
			// Property: material
			if (passValidateProperty(compiler, prop, token[TOKEN_MATERIAL], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					externObject->setMaterialName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SCENE_MATERIAL_NAME])
		{
			// Property: scene_material_name (deprecated and replaced by 'material')
			if (passValidateProperty(compiler, prop, token[TOKEN_SCENE_MATERIAL_NAME], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					externObject->setMaterialName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SCENE_SCALE])
		{
			// Property: scene_node_scale
			if (passValidateProperty(compiler, prop, token[TOKEN_SCENE_SCALE], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					externObject->setScale(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SCENE_POSITION])
		{
			// Property: scene_node_position
			if (passValidateProperty(compiler, prop, token[TOKEN_SCENE_POSITION], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					externObject->setPosition(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool SceneDecoratorExternTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void SceneDecoratorExternWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a SceneDecoratorExtern
		const Extern* externObject = static_cast<const Extern*>(element);
		const SceneDecoratorExtern* sceneDecoratorExtern = static_cast<const SceneDecoratorExtern*>(externObject);
		serializer->writeLine(token[TOKEN_EXTERN], externObject->getExternType(), externObject->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ExternWriter::write(serializer, element);

		// Write own attributes
		if (!sceneDecoratorExtern->getMeshName().empty()) serializer->writeLine(
			token[TOKEN_MESH_NAME], sceneDecoratorExtern->getMeshName(), 12);
		if (!sceneDecoratorExtern->getMaterialName().empty()) serializer->writeLine(
			token[TOKEN_MATERIAL], sceneDecoratorExtern->getMaterialName(), 12);
		if (sceneDecoratorExtern->getScale() != Vector3::UNIT_SCALE) serializer->writeLine(
			token[TOKEN_SCENE_SCALE], StringConverter::toString(sceneDecoratorExtern->getScale()), 12);
		if (sceneDecoratorExtern->getPosition() != Vector3::ZERO) serializer->writeLine(
			token[TOKEN_SCENE_POSITION], StringConverter::toString(sceneDecoratorExtern->getPosition()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
