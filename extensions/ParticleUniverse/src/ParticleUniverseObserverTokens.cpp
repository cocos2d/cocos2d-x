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

#include "ParticleUniverseObserver.h"
#include "ParticleUniverseObserverTokens.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseEventHandlerFactory.h"

namespace ParticleUniverse
{
	/**************************************************************************
	 * ObserverTranslator
	 *************************************************************************/
	ObserverTranslator::ObserverTranslator()
		:mObserver(0)
	{
	}
	//-------------------------------------------------------------------------
	void ObserverTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ObjectAbstractNode* parent = obj->parent ? reinterpret_cast<ObjectAbstractNode*>(obj->parent) : 0;

		// The name of the obj is the type of the Observer
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
		ParticleObserverFactory* particleObserverFactory = ParticleSystemManager::getSingletonPtr()->getObserverFactory(type);
		if (!particleObserverFactory)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		// Create the Observer
		mObserver = ParticleSystemManager::getSingletonPtr()->createObserver(type);
		if (!mObserver)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		if (!obj->parent->context.isEmpty())
		{
			ParticleTechnique* technique = any_cast<ParticleTechnique*>(obj->parent->context);
			technique->addObserver(mObserver);
		}
		else
		{
			// It is an alias
			mObserver->setAliasName(parent->name);
			ParticleSystemManager::getSingletonPtr()->addAlias(mObserver);
		}

		// The first value is the (optional) name
		String name;
		if(!obj->values.empty())
		{
			getString(obj->values.front(), &name);
			mObserver->setName(name);
		}

		// Set it in the context
		obj->context = Any(mObserver);

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
							mObserver->setEnabled(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_OBSERVE_PARTICLE_TYPE])
				{
					// Property: observe_particle_type
					if (passValidateProperty(compiler, prop, token[TOKEN_OBSERVE_PARTICLE_TYPE], VAL_STRING))
					{
						String val;
						if(getString(prop->values.front(), &val))
						{
							if (val == token[TOKEN_VISUAL_PARTICLE])
							{
								mObserver->setParticleTypeToObserve(Particle::PT_VISUAL);
							}
							else if (val == token[TOKEN_EMITTER_PARTICLE])
							{
								mObserver->setParticleTypeToObserve(Particle::PT_EMITTER);
							}
							else if (val == token[TOKEN_AFFECTOR_PARTICLE])
							{
								mObserver->setParticleTypeToObserve(Particle::PT_AFFECTOR);
							}
							else if (val == token[TOKEN_TECHNIQUE_PARTICLE])
							{
								mObserver->setParticleTypeToObserve(Particle::PT_TECHNIQUE);
							}
							else if (val == token[TOKEN_SYSTEM_PARTICLE])
							{
								mObserver->setParticleTypeToObserve(Particle::PT_SYSTEM);
							}
						}
					}
				}
				else if (prop->name == token[TOKEN_OBSERVE_INTERVAL])
				{
					// Property: observe_interval
					if (passValidateProperty(compiler, prop, token[TOKEN_OBSERVE_INTERVAL], VAL_REAL))
					{
						Real val;
						if(getReal(prop->values.front(), &val))
						{
							mObserver->setObserverInterval(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_OBSERVE_UNTIL_EVENT])
				{
					// Property: observe_until_event
					if (passValidateProperty(compiler, prop, token[TOKEN_OBSERVE_UNTIL_EVENT], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mObserver->setObserveUntilEvent(val);
						}
					}
				}
				else if (particleObserverFactory->translateChildProperty(compiler, *i))
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
				if (particleObserverFactory->translateChildObject(compiler, *i))
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

	void ParticleObserverWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a ParticleObserver
		const ParticleObserver* observer = static_cast<const ParticleObserver*>(element);

		// Write own attributes
		if (observer->_getOriginalEnabled() != ParticleObserver::DEFAULT_ENABLED) serializer->writeLine(
			token[TOKEN_ENABLED], StringConverter::toString(observer->_getOriginalEnabled()), 12);
		if (observer->isParticleTypeToObserveSet())
		{
			String particleType = token[TOKEN_VISUAL_PARTICLE];
			if (observer->getParticleTypeToObserve() == Particle::PT_EMITTER)
			{
				particleType = token[TOKEN_EMITTER_PARTICLE];
			}
			else if (observer->getParticleTypeToObserve() == Particle::PT_TECHNIQUE)
			{
				particleType = token[TOKEN_TECHNIQUE_PARTICLE];
			}
			else if (observer->getParticleTypeToObserve() == Particle::PT_AFFECTOR)
			{
				particleType = token[TOKEN_AFFECTOR_PARTICLE];
			}
			else if (observer->getParticleTypeToObserve() == Particle::PT_SYSTEM)
			{
				particleType = token[TOKEN_SYSTEM_PARTICLE];
			}
			serializer->writeLine(token[TOKEN_OBSERVE_PARTICLE_TYPE], particleType, 12);
		}
		if (observer->getObserverInterval() != ParticleObserver::DEFAULT_INTERVAL) serializer->writeLine(
			token[TOKEN_OBSERVE_INTERVAL], StringConverter::toString(observer->getObserverInterval()), 12);
		if (observer->getObserveUntilEvent() != ParticleObserver::DEFAULT_UNTIL_EVENT) serializer->writeLine(
			token[TOKEN_OBSERVE_UNTIL_EVENT], StringConverter::toString(observer->getObserveUntilEvent()), 12);

		// Write eventHandlers
		serializer->context.beginSection(HANDLER, 0); // Don´t set the event handler
		size_t numerOfEventHandlers = observer->getNumEventHandlers();
		for (size_t i = 0; i < numerOfEventHandlers; ++i)
		{
			ParticleEventHandler* eventHandler = observer->getEventHandler(i);
			ParticleEventHandlerFactory* particleEventHandlerFactory = ParticleSystemManager::getSingletonPtr()->getEventHandlerFactory(eventHandler->getEventHandlerType());
			if (particleEventHandlerFactory)
			{
				particleEventHandlerFactory->write(serializer, eventHandler);
			}
		}
		serializer->context.endSection();
	}

}
