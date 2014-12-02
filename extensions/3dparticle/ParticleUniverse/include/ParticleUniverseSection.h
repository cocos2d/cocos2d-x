/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SECTION_H__
#define __PU_SECTION_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** The Section class is used for parsing. A section is a piece of data between brackets {}.
	*/
	class _ParticleUniverseExport Section
	{
		public:
			IElement* element;
			String elementName;
			String sectionName;

			Section(void) : elementName(StringUtil::BLANK), sectionName(StringUtil::BLANK) {};
			virtual ~Section(void) {};
	};

}
#endif
