/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ATTACHABLE_TOKENS_H__
#define __PU_ATTACHABLE_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAttachable.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** 
    */
	class _ParticleUniverseExport AttachableWriter : public ScriptWriter
	{
		public:
			
			AttachableWriter(void) {};
			virtual ~AttachableWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
