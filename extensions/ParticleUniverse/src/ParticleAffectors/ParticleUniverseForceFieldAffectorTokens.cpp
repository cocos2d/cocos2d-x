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

#include "ParticleAffectors/ParticleUniverseForceFieldAffector.h"
#include "ParticleAffectors/ParticleUniverseForceFieldAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool ForceFieldAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		ForceFieldAffector* affector = static_cast<ForceFieldAffector*>(af);

		if (prop->name == token[TOKEN_FORCEFIELD_TYPE])
		{
			// Property: forcefield_type
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCEFIELD_TYPE], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					if (val == token[TOKEN_REALTIME])
					{
						affector->setForceFieldType(ForceField::FF_REALTIME_CALC);
						return true;
					}
					else if (val == token[TOKEN_MATRIX])
					{
						affector->setForceFieldType(ForceField::FF_MATRIX_CALC);
						return true;
					}
					affector->suppressGeneration(false);
				}
			}
		}
		else if (prop->name == token[TOKEN_DELTA])
		{
			// Property: delta
			if (passValidateProperty(compiler, prop, token[TOKEN_DELTA], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setDelta(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FORCE])
		{
			// Property: force
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setScaleForce(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_OCTAVES])
		{
			// Property: octaves
			if (passValidateProperty(compiler, prop, token[TOKEN_OCTAVES], VAL_UINT))
			{
				unsigned int val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setOctaves(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FREQUENCY])
		{
			// Property: frequency
			if (passValidateProperty(compiler, prop, token[TOKEN_FREQUENCY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setFrequency(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_AMPLITUDE])
		{
			// Property: amplitude
			if (passValidateProperty(compiler, prop, token[TOKEN_AMPLITUDE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setAmplitude(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_PERSISTENCE])
		{
			// Property: persistence
			if (passValidateProperty(compiler, prop, token[TOKEN_PERSISTENCE], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setPersistence(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FORCEFIELDSIZE])
		{
			// Property: forcefield_size
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCEFIELDSIZE], VAL_UINT))
			{
				unsigned int val = 0;
				if(getUInt(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setForceFieldSize(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_WORLDSIZE])
		{
			// Property: worldsize
			if (passValidateProperty(compiler, prop, token[TOKEN_WORLDSIZE], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->suppressGeneration(true);
					affector->setWorldSize(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_IGNORE_NEGATIVE_X])
		{
			// Property: ignore_negative_x
			if (passValidateProperty(compiler, prop, token[TOKEN_IGNORE_NEGATIVE_X], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setIgnoreNegativeX(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_IGNORE_NEGATIVE_Y])
		{
			// Property: ignore_negative_y
			if (passValidateProperty(compiler, prop, token[TOKEN_IGNORE_NEGATIVE_Y], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setIgnoreNegativeY(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_IGNORE_NEGATIVE_Z])
		{
			// Property: ignore_negative_z
			if (passValidateProperty(compiler, prop, token[TOKEN_IGNORE_NEGATIVE_Z], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setIgnoreNegativeZ(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MOVEMENT])
		{
			// Property: movement
			if (passValidateProperty(compiler, prop, token[TOKEN_MOVEMENT], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->suppressGeneration(true);
					affector->setMovement(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_MOVEMENT_FREQUENCY])
		{
			// Property: movement_frequency
			if (passValidateProperty(compiler, prop, token[TOKEN_MOVEMENT_FREQUENCY], VAL_REAL))
			{
				Real val = 0.0f;
				if(getReal(prop->values.front(), &val))
				{
					affector->suppressGeneration(true);
					affector->setMovementFrequency(val);
					affector->suppressGeneration(false);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool ForceFieldAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void ForceFieldAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a ForceFieldAffector
		const ForceFieldAffector* affector = static_cast<const ForceFieldAffector*>(element);

		// Write the header of the ForceFieldAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getForceFieldType() != ForceFieldAffector::DEFAULT_FORCEFIELD_TYPE) 
		{
			String type;
			if (affector->getForceFieldType() == ForceField::FF_MATRIX_CALC)
			{
				type = token[TOKEN_MATRIX];
			}
			serializer->writeLine(token[TOKEN_FORCEFIELD_TYPE], type, 12);
		}
		if (affector->getDelta() != ForceFieldAffector::DEFAULT_DELTA) serializer->writeLine(
			token[TOKEN_DELTA], StringConverter::toString(affector->getDelta()), 12);
		if (affector->getScaleForce() != ForceFieldAffector::DEFAULT_FORCE) serializer->writeLine(
			token[TOKEN_FORCE], StringConverter::toString(affector->getScaleForce()), 12);
		if (affector->getOctaves() != ForceFieldAffector::DEFAULT_OCTAVES) serializer->writeLine(
			token[TOKEN_OCTAVES], StringConverter::toString(affector->getOctaves()), 12);
		if (affector->getFrequency() != ForceFieldAffector::DEFAULT_FREQUENCY) serializer->writeLine(
			token[TOKEN_FREQUENCY], StringConverter::toString((Real)affector->getFrequency()), 12);
		if (affector->getAmplitude() != ForceFieldAffector::DEFAULT_AMPLITUDE) serializer->writeLine(
			token[TOKEN_AMPLITUDE], StringConverter::toString((Real)affector->getAmplitude()), 12);
		if (affector->getPersistence() != ForceFieldAffector::DEFAULT_PERSISTENCE) serializer->writeLine(
			token[TOKEN_PERSISTENCE], StringConverter::toString((Real)affector->getPersistence()), 12);
		if (affector->getForceFieldSize() != ForceFieldAffector::DEFAULT_FORCEFIELDSIZE) serializer->writeLine(
			token[TOKEN_FORCEFIELDSIZE], StringConverter::toString(affector->getForceFieldSize()), 12);
		if (affector->getWorldSize() != ForceFieldAffector::DEFAULT_WORLDSIZE) serializer->writeLine(
			token[TOKEN_WORLDSIZE], StringConverter::toString(affector->getWorldSize()), 12);
		if (affector->getIgnoreNegativeX()) serializer->writeLine(
			token[TOKEN_IGNORE_NEGATIVE_X], StringConverter::toString(affector->getIgnoreNegativeX()), 12);
		if (affector->getIgnoreNegativeY()) serializer->writeLine(
			token[TOKEN_IGNORE_NEGATIVE_Y], StringConverter::toString(affector->getIgnoreNegativeY()), 12);
		if (affector->getIgnoreNegativeZ()) serializer->writeLine(
			token[TOKEN_IGNORE_NEGATIVE_Z], StringConverter::toString(affector->getIgnoreNegativeZ()), 12);
		if (affector->getMovement() != ForceFieldAffector::DEFAULT_MOVEMENT) serializer->writeLine(
			token[TOKEN_MOVEMENT], StringConverter::toString(affector->getMovement()), 12);
		if (affector->getMovementFrequency() != ForceFieldAffector::DEFAULT_MOVEMENT_FREQUENCY) serializer->writeLine(
			token[TOKEN_MOVEMENT_FREQUENCY], StringConverter::toString(affector->getMovementFrequency()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
