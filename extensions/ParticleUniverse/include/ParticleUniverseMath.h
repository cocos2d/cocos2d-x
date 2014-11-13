/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_MATH_H__
#define __PU_MATH_H__

#include "OgreMath.h"


namespace ParticleUniverse
{
	// If the Ogre renderer is replaced by another renderer, the types below must be re-implemented.
	typedef Ogre::Radian Radian;
	typedef Ogre::Angle Angle;
	typedef Ogre::Math Math;

	// To be re-implemented:
	// ====================
	// Math::Abs
	// Math::Ceil
	// Math::Cos
	// Math::RangeRandom
	// Math::Sin
	// Math::Sign
	// Math::Sqrt
	// Math::UnitRandom
	// Math::SymmetricRandom

	// Math::POS_INFINITY
	// Math::NEG_INFINITY
	// Math::TWO_PI
	// Math::PI
}
#endif
