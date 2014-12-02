/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ANY_H__
#define __PU_ANY_H__

#include "OgreAny.h"

namespace ParticleUniverse
{
	// If the Ogre renderer is replaced by another renderer, the Any class and any_cast must be re-implemented
	typedef Ogre::Any Any;
    template <typename ValueType> ValueType* any_cast(Any* operand)
	{
		return Ogre::any_cast<ValueType>(operand);
	}
}

#endif
