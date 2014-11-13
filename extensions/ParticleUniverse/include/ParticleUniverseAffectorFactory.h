/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_AFFECTOR_FACTORY_H__
#define __PU_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseAffectorTokens.h"

namespace ParticleUniverse
{
	/** This is the base factory of all ParticleAffector implementations.
    */
	class _ParticleUniverseExport ParticleAffectorFactory : public ScriptReader, public ScriptWriter, public FactoryAlloc
	{
	    protected:

			/** 
	        */
			template <class T>
			ParticleAffector* _createAffector(void)
			{
				ParticleAffector* particleAffector = PU_NEW_T(T, MEMCATEGORY_SCENE_OBJECTS)();
				particleAffector->setAffectorType(getAffectorType());
				return particleAffector;
			};

		public:
			ParticleAffectorFactory(void) {};
	        virtual ~ParticleAffectorFactory(void) {};

		    /** Returns the type of the factory, which identifies the particle affector type this factory creates. */
			virtual String getAffectorType(void) const = 0;

			/** Creates a new affector instance.
		    @remarks
	        */
		    virtual ParticleAffector* createAffector(void) = 0;

			/** Delete an affector
	        */
			void destroyAffector (ParticleAffector* affector)
			{
				PU_DELETE_T(affector, ParticleAffector, MEMCATEGORY_SCENE_OBJECTS);
			};
	};

}
#endif
