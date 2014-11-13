/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CONTROLLER_MANAGER_H__
#define __PU_CONTROLLER_MANAGER_H__

// If the Ogre renderer is replaced by another renderer, the ControllerManager class must be re-implemented
#include "OgreControllerManager.h"

namespace ParticleUniverse
{
	typedef Ogre::ControllerValueRealPtr ControllerValueRealPtr;
	typedef Ogre::ControllerManager ControllerManager;
}

#endif
