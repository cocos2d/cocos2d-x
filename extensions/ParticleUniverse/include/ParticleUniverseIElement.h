/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_I_ELEMENT_H__
#define __PU_I_ELEMENT_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** The IElement is used to identify classes that must be set as part of a section in case a script is
		parsed.
	@remarks
		I.e. If the parses encounters a ´technique´ section in a particle universe script, a ParticleTechnique
		object is created and must be set in the current section of the Context object. the
		ParticleTechnique object must be of type IElement to be stored in the Context object.
	*/
	class _ParticleUniverseExport IElement
	{
		public:
			IElement(void) {};
			virtual ~IElement(void) {};
	};

}
#endif
