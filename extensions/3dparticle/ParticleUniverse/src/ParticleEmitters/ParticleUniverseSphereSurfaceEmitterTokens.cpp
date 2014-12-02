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

#include "ParticleEmitters/ParticleUniverseSphereSurfaceEmitter.h"
#include "ParticleEmitters/ParticleUniverseSphereSurfaceEmitterTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool SphereSurfaceEmitterTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEmitter* em = any_cast<ParticleEmitter*>(prop->parent->context);
		SphereSurfaceEmitter* emitter = static_cast<SphereSurfaceEmitter*>(em);

		if (prop->name == token[TOKEN_RADIUS])
		{
			// Property: radius
			if (passValidateProperty(compiler, prop, token[TOKEN_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setRadius(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_SPHERE_RADIUS])
		{
			// Property: sphere_surface_em_radius (deprecated and replaced by 'radius')
			if (passValidateProperty(compiler, prop, token[TOKEN_SPHERE_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setRadius(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool SphereSurfaceEmitterTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void SphereSurfaceEmitterWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a SphereSurfaceEmitter
		const SphereSurfaceEmitter* emitter = static_cast<const SphereSurfaceEmitter*>(element);

		// Write the header of the SphereSurfaceEmitter
		serializer->writeLine(token[TOKEN_EMITTER], emitter->getEmitterType(), emitter->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleEmitterWriter::write(serializer, element);

		// Write own attributes
		if (emitter->getRadius() != SphereSurfaceEmitter::DEFAULT_RADIUS) serializer->writeLine(
			token[TOKEN_RADIUS], StringConverter::toString(emitter->getRadius()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
