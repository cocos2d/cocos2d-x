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

#include "ParticleEmitters/ParticleUniverseMeshSurfaceEmitter.h"
#include "ParticleEmitters/ParticleUniverseMeshSurfaceEmitterTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool MeshSurfaceEmitterTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEmitter* em = any_cast<ParticleEmitter*>(prop->parent->context);
		MeshSurfaceEmitter* emitter = static_cast<MeshSurfaceEmitter*>(em);

		if (prop->name == token[TOKEN_MESH_NAME])
		{
			// Property: mesh_name
			if (passValidateProperty(compiler, prop, token[TOKEN_MESH_NAME], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					emitter->setMeshName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MESH_SURFACE_NAME])
		{
			// Property: mesh_surface_mesh_name (deprecated and replaced by mesh_name)
			if (passValidateProperty(compiler, prop, token[TOKEN_MESH_SURFACE_NAME], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					emitter->setMeshName(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MESH_SURFACE_DISTRIBUTION])
		{
			// Property: mesh_surface_distribution
			if (passValidateProperty(compiler, prop, token[TOKEN_MESH_SURFACE_DISTRIBUTION], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_MESH_SURFACE_EDGE])
					{
						emitter->setDistribution(MeshInfo::MSD_EDGE);
						return true;
					}
					else if (val == token[TOKEN_MESH_SURFACE_HETEROGENEOUS_1])
					{
						emitter->setDistribution(MeshInfo::MSD_HETEROGENEOUS_1);
						return true;
					}
					else if (val == token[TOKEN_MESH_SURFACE_HETEROGENEOUS_2])
					{
						emitter->setDistribution(MeshInfo::MSD_HETEROGENEOUS_2);
						return true;
					}
					else if (val == token[TOKEN_MESH_SURFACE_HOMOGENEOUS])
					{
						emitter->setDistribution(MeshInfo::MSD_HOMOGENEOUS);
						return true;
					}
					else if (val == token[TOKEN_MESH_SURFACE_HOMOGENEOUS])
					{
						emitter->setDistribution(MeshInfo::MSD_HOMOGENEOUS);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_MESH_SURFACE_MESH_SCALE])
		{
			// Property: mesh_surface_scale
			if (passValidateProperty(compiler, prop, token[TOKEN_MESH_SURFACE_MESH_SCALE], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					emitter->setScale(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool MeshSurfaceEmitterTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void MeshSurfaceEmitterWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a MeshSurfaceEmitter
		const MeshSurfaceEmitter* emitter = static_cast<const MeshSurfaceEmitter*>(element);

		// Write the header of the MeshSurfaceEmitter
		serializer->writeLine(token[TOKEN_EMITTER], emitter->getEmitterType(), emitter->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleEmitterWriter::write(serializer, element);

		// Write own attributes
		if (emitter->getMeshName() != StringUtil::BLANK) serializer->writeLine(
			token[TOKEN_MESH_NAME], emitter->getMeshName(), 12);
		if (emitter->getScale() != MeshSurfaceEmitter::DEFAULT_SCALE) serializer->writeLine(
			token[TOKEN_MESH_SURFACE_MESH_SCALE], StringConverter::toString(emitter->getScale()), 12);
		if (emitter->getDistribution() != MeshSurfaceEmitter::DEFAULT_DISTRIBUTION) 
		{
			String distribution = token[TOKEN_MESH_SURFACE_HOMOGENEOUS];
			if (emitter->getDistribution() == MeshInfo::MSD_HOMOGENEOUS) distribution = token[TOKEN_MESH_SURFACE_HOMOGENEOUS];
			else if (emitter->getDistribution() == MeshInfo::MSD_EDGE) distribution = token[TOKEN_MESH_SURFACE_EDGE];
			else if (emitter->getDistribution() == MeshInfo::MSD_HETEROGENEOUS_1) distribution = token[TOKEN_MESH_SURFACE_HETEROGENEOUS_1];
			else if (emitter->getDistribution() == MeshInfo::MSD_HETEROGENEOUS_2) distribution = token[TOKEN_MESH_SURFACE_HETEROGENEOUS_2];
			else if (emitter->getDistribution() == MeshInfo::MSD_VERTEX) distribution = token[TOKEN_VERTEX];
			serializer->writeLine(token[TOKEN_MESH_SURFACE_DISTRIBUTION], distribution, 12);
		}


		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
