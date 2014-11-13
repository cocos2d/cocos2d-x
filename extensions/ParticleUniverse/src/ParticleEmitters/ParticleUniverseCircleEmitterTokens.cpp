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

#include "ParticleEmitters/ParticleUniverseCircleEmitter.h"
#include "ParticleEmitters/ParticleUniverseCircleEmitterTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool CircleEmitterTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleEmitter* em = any_cast<ParticleEmitter*>(prop->parent->context);
		CircleEmitter* emitter = static_cast<CircleEmitter*>(em);

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
		else if (prop->name == token[TOKEN_CIRCLE_RADIUS])
		{
			// Property: circle_em_radius (deprecated and replaced by radius)
			if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_RADIUS], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setRadius(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_STEP])
		{
			// Property: step
			if (passValidateProperty(compiler, prop, token[TOKEN_STEP], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setStep(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_CIRCLE_STEP])
		{
			// Property: circle_em_step (deprecated and replaced by 'step')
			if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_STEP], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setStep(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_ANGLE])
		{
			// Property: angle
			if (passValidateProperty(compiler, prop, token[TOKEN_ANGLE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setCircleAngle(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_CIRCLE_ANGLE])
		{
			// Property: circle_em_angle
			if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_ANGLE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					emitter->setCircleAngle(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_EMIT_RANDOM])
		{
			// Property: emit_random
			if (passValidateProperty(compiler, prop, token[TOKEN_EMIT_RANDOM], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					emitter->setRandom(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_CIRCLE_RANDOM])
		{
			// Property: circle_em_random (deprecated and replaced by 'emit_random'))
			if (passValidateProperty(compiler, prop, token[TOKEN_CIRCLE_RANDOM], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					emitter->setRandom(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_NORMAL])
		{
			// Property: normal
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					emitter->setNormal(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_CIRCLE_NORMAL])
		{
			// Property: circle_em_normal (deprecated and replaced by 'normal')
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					emitter->setNormal(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool CircleEmitterTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void CircleEmitterWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a CircleEmitter
		const CircleEmitter* emitter = static_cast<const CircleEmitter*>(element);

		// Write the header of the CircleEmitter
		serializer->writeLine(token[TOKEN_EMITTER], emitter->getEmitterType(), emitter->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleEmitterWriter::write(serializer, element);

		// Write own attributes
		if (emitter->getRadius() != CircleEmitter::DEFAULT_RADIUS) serializer->writeLine(
			token[TOKEN_RADIUS], StringConverter::toString(emitter->getRadius()), 12);
		if (emitter->getStep() != CircleEmitter::DEFAULT_STEP) serializer->writeLine(
			token[TOKEN_STEP], StringConverter::toString(emitter->getStep()), 12);
		if (emitter->getCircleAngle() != CircleEmitter::DEFAULT_ANGLE) serializer->writeLine(
			token[TOKEN_ANGLE], StringConverter::toString(emitter->getCircleAngle()), 12);
		if (emitter->isRandom() != CircleEmitter::DEFAULT_RANDOM) serializer->writeLine(
			token[TOKEN_EMIT_RANDOM], StringConverter::toString(emitter->isRandom()), 12);
		if (emitter->getNormal() != CircleEmitter::DEFAULT_NORMAL) serializer->writeLine(
			token[TOKEN_NORMAL], StringConverter::toString(emitter->getNormal()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
