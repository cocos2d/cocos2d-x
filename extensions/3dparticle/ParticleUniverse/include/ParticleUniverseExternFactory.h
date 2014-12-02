/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_EXTERN_FACTORY_H__
#define __PU_EXTERN_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExtern.h"
#include "ParticleUniverseExternTokens.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseScriptReader.h"

namespace ParticleUniverse
{
	/** This is the base factory of all Extern implementations.
    */
	class _ParticleUniverseExport ExternFactory : public ScriptReader, public ScriptWriter, public FactoryAlloc
	{
	    protected:

			/** 
	        */
			template <class T>
			Extern* _createExtern(void)
			{
				Extern* externObject = PU_NEW T();
				externObject->setExternType(getExternType());
				return externObject;
			};

	public:
			ExternFactory(void){};
			virtual ~ExternFactory(void){};

		    /** Returns the type of the factory, which identifies the Extern type this factory creates. */
			virtual String getExternType(void) const = 0;

			/** Creates a new Extern instance.
		    @remarks
	        */
		    virtual Extern* createExtern(void) = 0;

			/** Delete an Extern.
	        */
			void destroyExtern (Extern* externObject)
			{
				if (externObject)
					PU_DELETE externObject;
			};
	};

}
#endif
