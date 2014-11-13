/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_I_VISUALDATA_H__
#define __PU_I_VISUALDATA_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** This abstract class is used for assigning visual data to some other class. Visual data can be anything,
		from SceneNodes to specific renderdata.
	*/
	class _ParticleUniverseExport IVisualData
	{
		public:
			IVisualData(void) {};
			virtual ~IVisualData(void) {};
			virtual void setVisible(bool visible) = 0;
	};

}
#endif
