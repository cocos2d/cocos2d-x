/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SCRIPT_WRITER_H__
#define __PU_SCRIPT_WRITER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	class ParticleScriptSerializer;

	/*	A class that implements the ScriptWriter, is responsible for writing (serialization) to a particle script.
	*/
	class _ParticleUniverseExport ScriptWriter
    {

		public:
			ScriptWriter(void) {};
			virtual ~ScriptWriter(void) {};

			/** Child classes must implement this pure virtual function, which must be used to write an object or attribute to
				a particle script.
			**/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element) = 0;
	};

}
#endif
