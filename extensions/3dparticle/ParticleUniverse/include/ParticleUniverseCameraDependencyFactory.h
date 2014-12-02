/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CAMERA_DEPENDECY_FACTORY_H__
#define __PU_CAMERA_DEPENDECY_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCameraDependency.h"

namespace ParticleUniverse
{
	/** This is the factory class with which a CameraDependency is created.
    */
	class _ParticleUniverseExport CameraDependencyFactory : public FactoryAlloc
	{
	    public:

			CameraDependencyFactory(void) {};
	        virtual ~CameraDependencyFactory(void) {};

			/** 
	        */
			CameraDependency* create(void)
			{
				return PU_NEW_T(CameraDependency, MEMCATEGORY_SCENE_OBJECTS)();
			};

			/** 
	        */
			CameraDependency* create(Real threshold, bool inc)
			{
				return PU_NEW_T(CameraDependency, MEMCATEGORY_SCENE_OBJECTS)(threshold, inc);
			};

			/** 
	        */
			CameraDependency* clone(CameraDependency* cameraDependency)
			{
				if (cameraDependency)
				{
					CameraDependency* newCameraDependency = create();
					cameraDependency->copyAttributesTo(newCameraDependency);
					return newCameraDependency;
				}

				return 0;
			}
			
			/** Delete a CameraDependency
	        */
			void destroy (CameraDependency* cameraDependency)
			{
				PU_DELETE_T(cameraDependency, CameraDependency, MEMCATEGORY_SCENE_OBJECTS);
			};
	};

}
#endif
