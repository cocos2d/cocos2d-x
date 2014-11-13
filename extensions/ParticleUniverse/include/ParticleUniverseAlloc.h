/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_ALLOC_H__
#define __PU_ALLOC_H__

//#include "OgreMemoryAllocatorConfig.h"
//
//namespace ParticleUniverse
//{
//	// Below a trick to use an enum of the Ogre namespace into the ParticleUniverse namespace
//	typedef Ogre::MemoryCategory MemoryCategory;
//	static const MemoryCategory MEMCATEGORY_GENERAL = Ogre::MEMCATEGORY_GENERAL;
//	static const MemoryCategory MEMCATEGORY_SCENE_OBJECTS = Ogre::MEMCATEGORY_SCENE_OBJECTS;
//	static const MemoryCategory MEMCATEGORY_SCENE_CONTROL = Ogre::MEMCATEGORY_SCENE_CONTROL;
//	static const MemoryCategory MEMCATEGORY_SCRIPTING = Ogre::MEMCATEGORY_SCRIPTING;
//
//	// Define the new and delete macro's
//	#if OGRE_DEBUG_MODE
//		#define PU_NEW_T(T, category) new (::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T), __FILE__, __LINE__, __FUNCTION__)) T
//		#define PU_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}		
//		#define PU_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__)), count) 
//		#define PU_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
//		#define PU_NEW new (__FILE__, __LINE__, __FUNCTION__)
//		#define PU_DELETE delete
//		#define PU_ALLOC_T(T, count, category) static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))
//		#define PU_FREE(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)
//		#define PU_DELETE_ARRAY_BYTES(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)
//
//	#else
//		#define PU_NEW_T(T, category) new (::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T))) T
//		#define PU_DELETE_T(ptr, T, category) if(ptr){(ptr)->~T(); ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
//		#define PU_NEW_ARRAY_T(T, count, category) ::Ogre::constructN(static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count))), count)
//		#define PU_DELETE_ARRAY_T(ptr, T, count, category) if(ptr){for (size_t b = 0; b < count; ++b) { (ptr)[b].~T();} ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr);}
//		#define PU_NEW new 
//		#define PU_DELETE delete
//		#define PU_ALLOC_T(T, count, category) static_cast<T*>(::Ogre::CategorisedAllocPolicy<category>::allocateBytes(sizeof(T)*(count)))
//		#define PU_FREE(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)
//		#define PU_DELETE_ARRAY_BYTES(ptr, category) ::Ogre::CategorisedAllocPolicy<category>::deallocateBytes((void*)ptr)
//	#endif
//
//	// Typedef the allocation policy for factories
//	typedef Ogre::FactoryAlloc FactoryAlloc;
//	typedef Ogre::FXAlloc FXAlloc;
//	typedef Ogre::SerializerAlloc SerializerAlloc;
//
//}

#endif
