/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_I_ALIAS_H__
#define __PU_I_ALIAS_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** Abstract (pure virtual) alias class
	@remarks
		The IAlias class acts as an interface and is used to represent all other classes that are a child of the
		IAlias class. This typically concerns entities that are used in the Particle Universe scripts and for
		which it is possible to define an alias (i.e. ParticleTechnique, ParticleEmitter and ParticleAffector).
	*/
	class _ParticleUniverseExport IAlias
	{
		public:
			enum AliasType
			{
				AT_UNDEFINED,
				AT_TECHNIQUE,
				AT_RENDERER,
				AT_EMITTER,
				AT_AFFECTOR,
				AT_OBSERVER,
				AT_EXTERN,
				AT_HANDLER,
				AT_BEHAVIOUR
			};

			IAlias(void) : 
				mAliasName(StringUtil::BLANK),
				mAliasType(AT_UNDEFINED) {};
			virtual ~IAlias(void) {};

			/** 
			*/
			const String& getAliasName(void) const {return mAliasName;};
			void setAliasName(String aliasName) {mAliasName = aliasName;};

			/** 
			*/
			const AliasType getAliasType(void) const {return mAliasType;};
			void setAliasType(AliasType aliasType) {mAliasType = aliasType;};

		protected:
			String mAliasName;
			AliasType mAliasType;
	};

}
#endif
