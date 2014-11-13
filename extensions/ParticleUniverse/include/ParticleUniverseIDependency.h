/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_I_DEPENDENCY_H__
#define __PU_I_DEPENDENCY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** Abstract (pure virtual) dependency class
	@remarks
		In some cases, an attribute of a ParticleSystem or its underlying components (ParticleEmitter, ...) may 
		depend on another value that changes over time. The ´changing value´ is wrapped into a IDependency class
		and the attribute is ´continuesly´ changed by the IDependency subclass.
	*/
	class _ParticleUniverseExport IDependency : public IElement
	{
		public:
			IDependency(void) : IElement() {};
			virtual ~IDependency(void){};
	};

}
#endif
