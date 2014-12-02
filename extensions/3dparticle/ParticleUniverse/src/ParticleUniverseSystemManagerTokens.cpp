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

#include "ParticleUniverseSystemManagerTokens.h"

namespace ParticleUniverse
{
	//-------------------------------------------------------------------------
	BuiltinScriptTranslatorManager::BuiltinScriptTranslatorManager()
	{
	}
	//-------------------------------------------------------------------------
	size_t BuiltinScriptTranslatorManager::getNumTranslators() const
	{
		return 9;
	}
	//-------------------------------------------------------------------------
	ScriptTranslator* BuiltinScriptTranslatorManager::getTranslator(const AbstractNodePtr &node)
	{
		ScriptTranslator* translator = 0;

		if(node->type == ANT_OBJECT)
		{
			ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
			ObjectAbstractNode* parent = obj->parent ? reinterpret_cast<ObjectAbstractNode*>(obj->parent) : 0;
			if(obj->cls == token[TOKEN_SYSTEM])
			{
				// Parse Particle System
				translator = &mSystemTranslator;
			}
			else if(obj->cls == token[TOKEN_ALIAS])
			{
				// Parse the Alias
				translator = &mAliasTranslator;
			}
			else if(obj->cls == token[TOKEN_TECHNIQUE] && parent && (parent->cls == token[TOKEN_SYSTEM] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Technique
				translator = &mTechniqueTranslator;
			}
			else if(obj->cls == token[TOKEN_RENDERER] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Renderer
				translator = &mRendererTranslator;
			}
			else if(obj->cls == token[TOKEN_EMITTER] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Emitter
				translator = &mEmitterTranslator;
			}
			else if(obj->cls == token[TOKEN_AFFECTOR] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Affector
				translator = &mAffectorTranslator;
			}
			else if(obj->cls == token[TOKEN_BEHAVIOUR] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Behaviour
				translator = &mBehaviourTranslator;
			}
			else if(obj->cls == token[TOKEN_OBSERVER] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Observer
				translator = &mObserverTranslator;
			}
			else if(obj->cls == token[TOKEN_HANDLER] && parent && (parent->cls == token[TOKEN_OBSERVER] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Particle Event Handler
				translator = &mParticleEventHandlerTranslator;
			}
			else if(obj->cls == token[TOKEN_EXTERN] && parent && (parent->cls == token[TOKEN_TECHNIQUE] || parent->cls == token[TOKEN_ALIAS]))
			{
				// Parse Extern
				translator = &mExternTranslator;
			}
		}

		return translator;
	}
}
