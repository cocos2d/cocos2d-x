/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CONTROLLER_H__
#define __PU_CONTROLLER_H__

// If the Ogre renderer is replaced by another renderer, the Controller class must be re-implemented
#include "OgreController.h"

namespace ParticleUniverse
{
	/** Using a subclass of public Ogre::Controller does not work, because of some conversion issues between Ogre::Controller and Controller in 
		the ControllerManager (i.e. in the createFrameTimePassthroughController() function).
	*/
	using Ogre::Controller;
//	template <typename T> class Controller : public Ogre::Controller <T>{};
	template <typename T> class ControllerValue : public Ogre::ControllerValue <T>{};
}

#endif
