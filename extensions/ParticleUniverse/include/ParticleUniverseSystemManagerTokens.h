/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SYSTEM_MANAGER_TOKENS_H__
#define __PU_SYSTEM_MANAGER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseSystemTokens.h"
#include "ParticleUniverseAliasTokens.h"
#include "ParticleUniverseTechniqueTokens.h"
#include "ParticleUniverseRendererTokens.h"
#include "ParticleUniverseEmitterTokens.h"
#include "ParticleUniverseAffectorTokens.h"
#include "ParticleUniverseBehaviourTokens.h"
#include "ParticleUniverseObserverTokens.h"
#include "ParticleUniverseEventHandlerTokens.h"
#include "ParticleUniverseExternTokens.h"

namespace ParticleUniverse
{
	/** The BuiltinScriptTranslatorManager contains all Translators that are used by the compiler.
	*/
	class _ParticleUniverseExport BuiltinScriptTranslatorManager : public Ogre::ScriptTranslatorManager
	{
		private:
			SystemTranslator mSystemTranslator;
			AliasTranslator mAliasTranslator;
			TechniqueTranslator mTechniqueTranslator;
			RendererTranslator mRendererTranslator;
			EmitterTranslator mEmitterTranslator;
			AffectorTranslator mAffectorTranslator;
			BehaviourTranslator mBehaviourTranslator;
			ObserverTranslator mObserverTranslator;
			ParticleEventHandlerTranslator mParticleEventHandlerTranslator;
			ExternTranslator mExternTranslator;

		public:
			BuiltinScriptTranslatorManager(void);

			/** 
			*/ 
			virtual size_t getNumTranslators(void) const;

			/** 
			*/ 
			virtual ScriptTranslator* getTranslator(const AbstractNodePtr &node);
	};
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport ParticleSystemManagerWriter : public ScriptWriter
	{
		protected:

		public:

			ParticleSystemManagerWriter(void) {};
			virtual ~ParticleSystemManagerWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element) {}
	};

}
#endif
