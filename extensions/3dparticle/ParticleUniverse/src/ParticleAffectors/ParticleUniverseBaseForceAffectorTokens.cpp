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

#include "ParticleAffectors/ParticleUniverseBaseForceAffector.h"
#include "ParticleAffectors/ParticleUniverseBaseForceAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool BaseForceAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		BaseForceAffector* affector = static_cast<BaseForceAffector*>(af); // Do not check type; assume the type is correct.

		if (prop->name == token[TOKEN_FORCE_VECTOR])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_VECTOR], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setForceVector(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FORCE_AFF_VECTOR])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFF_VECTOR], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->setForceVector(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_FORCE_APPLICATION])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_APPLICATION], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_FORCE_ADD])
					{
						affector->setForceApplication(BaseForceAffector::FA_ADD);
						return true;
					}
					else if (val == token[TOKEN_FORCE_AVERAGE])
					{
						affector->setForceApplication(BaseForceAffector::FA_AVERAGE);
						return true;
					}
				}
			}
		}
		else if (prop->name == token[TOKEN_FORCE_AFF_APPLICATION])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_FORCE_AFF_APPLICATION], VAL_STRING))
			{
				String val;
				if(getString(prop->values.front(), &val))
				{
					if (val == token[TOKEN_FORCE_ADD])
					{
						affector->setForceApplication(BaseForceAffector::FA_ADD);
						return true;
					}
					else if (val == token[TOKEN_FORCE_AVERAGE])
					{
						affector->setForceApplication(BaseForceAffector::FA_AVERAGE);
						return true;
					}
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool BaseForceAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void BaseForceAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a BaseForceAffector
		const BaseForceAffector* affector = static_cast<const BaseForceAffector*>(element);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->getForceVector() != BaseForceAffector::DEFAULT_FORCE_VECTOR) serializer->writeLine(
			token[TOKEN_FORCE_VECTOR], StringConverter::toString(affector->getForceVector()), 12);

		if (affector->getForceApplication() != BaseForceAffector::DEFAULT_FORCE_APPL) 
		{
			String application = token[TOKEN_FORCE_ADD];
			if (affector->getForceApplication() == BaseForceAffector::FA_AVERAGE) application = token[TOKEN_FORCE_AVERAGE];
			serializer->writeLine(token[TOKEN_FORCE_APPLICATION], application, 12);
		}
	}

}
