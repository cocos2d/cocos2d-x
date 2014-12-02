/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SINGLETON_H__
#define __PU_SINGLETON_H__

// If the Ogre renderer is replaced by another renderer, the Singleton class must be re-implemented
#include "OgreSingleton.h"

namespace ParticleUniverse
{
	template <typename T> class Singleton : public Ogre::Singleton<T>{};
}

#endif
