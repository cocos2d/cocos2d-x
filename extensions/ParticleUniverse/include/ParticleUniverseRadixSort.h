/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_RADIX_SORT_H__
#define __PU_RADIX_SORT_H__

#include "OgreRadixSort.h"

namespace ParticleUniverse
{
	// If the Ogre renderer is replaced by another renderer, the RadixSort class must be re-implemented
	template <class TContainer, class TContainerValueType, typename TCompValueType>	class RadixSort : 
		public Ogre::RadixSort<TContainer, TContainerValueType, TCompValueType>{};

	typedef Ogre::SortMode SortMode;
	static const SortMode SM_DIRECTION = Ogre::SM_DIRECTION;
	static const SortMode SM_DISTANCE = Ogre::SM_DISTANCE;
}

#endif
