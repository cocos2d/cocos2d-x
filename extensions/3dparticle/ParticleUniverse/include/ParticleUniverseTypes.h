/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TYPES_H__
#define __PU_TYPES_H__

#include "cocos2d.h"

namespace ParticleUniverse
{
	// Define types
	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
	typedef unsigned int uint;
	typedef unsigned short ushort;
	typedef int int32;
	typedef short int16;
	typedef unsigned char uchar;

	/** Define other types. Particle Universe needs its own types to be independent from external resources, such as the Ogre renderer. 
		For now, the types are still borrowed from Ogre. If the Ogre renderer is replaced by another renderer, the types below must be re-implemented.
	*/
	typedef float Real;
	typedef cocos2d::Vec3 Vector3;
	typedef cocos2d::Vec4 Vector4;
	typedef cocos2d::Vec2 Vector2;
	typedef cocos2d::Quaternion Quaternion;
	typedef cocos2d::Vec4 ColourValue;
	typedef std::string String;
//	typedef Ogre::StringUtil StringUtil;
//	typedef Ogre::StringConverter StringConverter;
//	typedef Ogre::StringVector StringVector;
//	typedef Ogre::StringVectorPtr StringVectorPtr;

//	// Typedef's for specific 'Ogre' containers.
//	// vector container
//	template <class T> struct vector : public std::vector<T, Ogre::STLAllocator<T*, Ogre::GeneralAllocPolicy> >
//	{
//	};
//
//	// list container
//	template <class T> struct list : public std::list<T, Ogre::STLAllocator<T*, Ogre::GeneralAllocPolicy> >
//	{ 
//	};
//
//	// map container
//	template <class T, class M> struct map : public std::map<T, M, std::less<T>, Ogre::STLAllocator<T*, Ogre::GeneralAllocPolicy> >
//	{ 
//	};
}

#endif
