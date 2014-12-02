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

#include "ParticleUniverseBehaviourTokens.h"

namespace ParticleUniverse
{
	/**************************************************************************
	 * BehaviourTranslator
	 *************************************************************************/
	BehaviourTranslator::BehaviourTranslator()
		:mBehaviour(0)
	{
	}
	//-------------------------------------------------------------------------
	void BehaviourTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ObjectAbstractNode* parent = obj->parent ? reinterpret_cast<ObjectAbstractNode*>(obj->parent) : 0;

		// The name of the obj is the type of the Behaviour
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
		ParticleBehaviourFactory* behaviourFactory = ParticleSystemManager::getSingletonPtr()->getBehaviourFactory(type);
		if (!behaviourFactory)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		// Create the Behaviour
		mBehaviour = ParticleSystemManager::getSingletonPtr()->createBehaviour(type);
		if (!mBehaviour)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		if (!obj->parent->context.isEmpty())
		{
			ParticleTechnique* technique = any_cast<ParticleTechnique*>(obj->parent->context);
			technique->_addBehaviourTemplate(mBehaviour);
		}
		else
		{
			// It is an alias
			mBehaviour->setAliasName(parent->name);
			ParticleSystemManager::getSingletonPtr()->addAlias(mBehaviour);
		}

		// Set it in the context
		obj->context = Any(mBehaviour);

		// Run through properties
		for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
		{
			// No properties of its own
			if((*i)->type == ANT_PROPERTY)
			{
				PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>((*i).get());
				if (behaviourFactory->translateChildProperty(compiler, *i))
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
				if (behaviourFactory->translateChildObject(compiler, *i))
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

	void ParticleBehaviourWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Nothing yet
	}

}
