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

#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/**************************************************************************
	 * AffectorTranslator
	 *************************************************************************/
	AffectorTranslator::AffectorTranslator()
		:mAffector(0)
	{
	}
	//-------------------------------------------------------------------------
	void AffectorTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ObjectAbstractNode* parent = obj->parent ? reinterpret_cast<ObjectAbstractNode*>(obj->parent) : 0;

		// The name of the obj is the type of the affector
		// Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
		String type;
		if(!obj->name.empty())
		{
			type = obj->name;
		}
		else
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		// Get the factory
		ParticleAffectorFactory* particleAffectorFactory = ParticleSystemManager::getSingletonPtr()->getAffectorFactory(type);
		if (!particleAffectorFactory)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		// Create the affector
		mAffector = ParticleSystemManager::getSingletonPtr()->createAffector(type);
		if (!mAffector)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		if (!obj->parent->context.isEmpty())
		{
			ParticleTechnique* technique = any_cast<ParticleTechnique*>(obj->parent->context);
			technique->addAffector(mAffector);
		}
		else
		{
			// It is an alias
			mAffector->setAliasName(parent->name);
			ParticleSystemManager::getSingletonPtr()->addAlias(mAffector);
		}

		// The first value is the (optional) name
		String name;
		if(!obj->values.empty())
		{
			getString(obj->values.front(), &name);
			mAffector->setName(name);
		}

		// Set it in the context
		obj->context = Any(mAffector);

		// Run through properties
		for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
		{
			if((*i)->type == ANT_PROPERTY)
			{
				PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>((*i).get());
				if (prop->name == token[TOKEN_ENABLED])
				{
					// Property: enabled
					if (passValidateProperty(compiler, prop, token[TOKEN_ENABLED], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mAffector->setEnabled(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_POSITION])
				{
					// Property: positon
					if (passValidateProperty(compiler, prop, token[TOKEN_POSITION], VAL_VECTOR3))
					{
						Vector3 val;
						if(getVector3(prop->values.begin(), prop->values.end(), &val))
						{
							mAffector->position = val;
							mAffector->originalPosition = val;
						}
					}
				}
				else if (prop->name == token[TOKEN_AFFECTOR_MASS])
				{
					if (passValidateProperty(compiler, prop, token[TOKEN_AFFECTOR_MASS], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							mAffector->mass = val;
						}
					}
				}
				else if (prop->name == token[TOKEN_AFFECTOR_SPECIALISATION])
				{
					if (passValidateProperty(compiler, prop, token[TOKEN_AFFECTOR_SPECIALISATION], VAL_STRING))
					{
						String val;
						if(getString(prop->values.front(), &val))
						{
							if (val == token[TOKEN_AFFECTOR_SPEC_DEFAULT])
							{
								mAffector->setAffectSpecialisation(ParticleAffector::AFSP_DEFAULT);
							}
							else if (val == token[TOKEN_AFFECTOR_SPEC_TTL_INCREASE])
							{
								mAffector->setAffectSpecialisation(ParticleAffector::AFSP_TTL_INCREASE);
							}
							else if (val == token[TOKEN_AFFECTOR_SPEC_TTL_DECREASE])
							{
								mAffector->setAffectSpecialisation(ParticleAffector::AFSP_TTL_DECREASE);
							}
						}
					}
				}
				else if (prop->name == token[TOKEN_AFFECTOR_EXCLUDE_EMITTER])
				{
					if (passValidatePropertyNoValues(compiler, prop, token[TOKEN_AFFECTOR_EXCLUDE_EMITTER]))
					{
						for(AbstractNodeList::iterator j = prop->values.begin(); j != prop->values.end(); ++j)
						{
							String val;
							if(getString(*j, &val))
							{
								mAffector->addEmitterToExclude(val);
							}
							else
							{
								compiler->addError(ScriptCompiler::CE_NUMBEREXPECTED, prop->file, prop->line,
									"PU Compiler: Error in exclude_emitter arguments");
							}
						}
					}
				}
				else if (particleAffectorFactory->translateChildProperty(compiler, *i))
				{
					// Parsed the property by another translator; do nothing
				}
				else
				{
					errorUnexpectedProperty(compiler, prop);
				}
			}
			else if((*i)->type == ANT_OBJECT)
			{
				if (particleAffectorFactory->translateChildObject(compiler, *i))
				{
					// Parsed the object by another translator; do nothing
				}
				else
				{
					processNode(compiler, *i);
				}
			}
            else
			{
				errorUnexpectedToken(compiler, *i);
			}
		}
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	
	void ParticleAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a ParticleAffector
		const ParticleAffector* affector = static_cast<const ParticleAffector*>(element);

		// Write base attributes
		if (affector->_getOriginalEnabled() != ParticleAffector::DEFAULT_ENABLED) serializer->writeLine(
			token[TOKEN_ENABLED], StringConverter::toString(affector->_getOriginalEnabled()), 12);
		if (affector->position != ParticleAffector::DEFAULT_POSITION) serializer->writeLine(
			token[TOKEN_POSITION], StringConverter::toString(affector->position), 12);
		if (affector->mass != ParticleAffector::DEFAULT_MASS) serializer->writeLine(
			token[TOKEN_AFFECTOR_MASS], StringConverter::toString(affector->mass), 12);
		String affectSpecialisation = token[TOKEN_AFFECTOR_SPEC_DEFAULT];
		if (affector->getAffectSpecialisation() == ParticleAffector::AFSP_TTL_INCREASE)
		{
			affectSpecialisation = token[TOKEN_AFFECTOR_SPEC_TTL_INCREASE];
		}
		else if (affector->getAffectSpecialisation() == ParticleAffector::AFSP_TTL_DECREASE)
		{
			affectSpecialisation = token[TOKEN_AFFECTOR_SPEC_TTL_DECREASE];
		}
		if (affector->getAffectSpecialisation() != ParticleAffector::DEFAULT_SPECIALISATION) serializer->writeLine(
			token[TOKEN_AFFECTOR_SPECIALISATION], affectSpecialisation, 12);

		const list<String> excludedEmitters = affector->getEmittersToExclude();
		String emitterList = StringUtil::BLANK;
		if (!excludedEmitters.empty())
		{
			list<String>::const_iterator it;
			list<String>::const_iterator itEnd = excludedEmitters.end();
			for (it = excludedEmitters.begin(); it != itEnd; ++it)
			{
				emitterList.append(*it + " ");
			}
			serializer->writeLine(token[TOKEN_AFFECTOR_EXCLUDE_EMITTER], emitterList, 12);
		}
	}

}
