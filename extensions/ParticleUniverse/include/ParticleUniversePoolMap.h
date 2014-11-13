/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_POOLMAP_H__
#define __PU_POOLMAP_H__

#include "ParticleUniversePrerequisites.h"
#include <map>

namespace ParticleUniverse
{
	/** The PoolMap is an extention of the regular Pool. The PoolMap contains objects that can be found by name.
	*/
	template <typename T>
	class _ParticleUniverseExport PoolMap
	{
		public:
			typedef std::multimap<String, T*> PoolMapMap;
			typedef typename PoolMapMap::iterator PoolMapIterator; // The 'typename' MUST be added, since T is not a fixed type
			PoolMapIterator mPoolMapIterator;

			//-----------------------------------------------------------------------
			PoolMap (bool managed = false) : mManaged(managed)
			{
				if (mManaged)
				{
					// Unused.
				}
			};
			//-----------------------------------------------------------------------
			virtual ~PoolMap (void)
			{
				if (mManaged)
				{
					// Unused.
				}
			};
			//-----------------------------------------------------------------------
			/** Returns true if the number of released elements is 0.
			*/
			inline bool isEmpty(void)
			{
				return mReleased.empty();
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline size_t getSize(void)
			{
				return mReleased.size();
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline void resetIterator (void)
			{
				mPoolMapIterator = mReleased.begin();
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline T* getFirst (void)
			{
				resetIterator();
				if (end())
					return 0;

				return mPoolMapIterator->second;
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline T* getNext (void)
			{
				if (end())
					return 0;

				mPoolMapIterator++;
				if (end())
					return 0;
				
				return mPoolMapIterator->second;
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline bool end (void)
			{
				return mPoolMapIterator == mReleased.end();
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline void clear (void)
			{
				mLocked.clear();
				mReleased.clear();
			};
			//-----------------------------------------------------------------------
			/** Add an element to the PoolMap.
			@remarks
				Can only be done if the pool doesn't manage the creation and desctruction of the elements.
			*/
			inline void addElement (const String& key, T* element)
			{
				if (mManaged)
					EXCEPT(Exception::ERR_NOT_IMPLEMENTED, "It is not allowed to add elements, because the pool manages the creation/destruction.", 
				        "PoolMap::addElement");

				mLocked.insert(make_pair(key, element));
			};

			//-----------------------------------------------------------------------
			/** Get an element from the pool.
			@remarks
				This function does not only retrieve an object, but the object is also marked as ´released´. This means
				that the object is exposed to the outside world. If objects in pool are traversed, only the released objects
				are taken into account.
			*/
			inline T* releaseElement (const String& key)
			{
				// Return with 0 if no elements left
				if (mLocked.empty())
					return 0;

				// Return the first element that is encountered
				T* t = 0;
				PoolMapIterator it;
				it = mLocked.find(key);
				if (it != mLocked.end())
				{
					// Get the element and move it to the released elements list
					t = it->second;
					mReleased.insert(make_pair(key, t));
					mLocked.erase(it);
				}

				return t;
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline void releaseAllElements (void)
			{
				// Move all elements from locked elements to released elements
				PoolMapIterator it;
				for (it = mLocked.begin(); it != mLocked.end(); ++it)
				{
					mReleased.insert(make_pair(it->first, it->second));
				}
				mLocked.clear();
				resetIterator();
			};
			//-----------------------------------------------------------------------
			/** Todo
			*/
			inline void lockLatestElement (void)
			{
				// Move element pointed by iterator from released elements to locked elements
				mLocked.insert(make_pair(mPoolMapIterator->first, mPoolMapIterator->second));
				mReleased.erase(mPoolMapIterator++); // Watch the ++ at the end to set mPoolMapIterator to the next element
				if (mPoolMapIterator != mReleased.begin() && mPoolMapIterator != mReleased.end())
				{
					mPoolMapIterator--;
				}
			};
			//-----------------------------------------------------------------------
			/** Lock all elements in the pool.
			@remarks
				All released objects are locked.
			*/
			inline void lockAllElements (void)
			{
				// Move all elements from release elements to locked elements
				PoolMapIterator it;
				for (it = mReleased.begin(); it != mReleased.end(); ++it)
				{
					mLocked.insert(make_pair(it->first, it->second));
				}
				mReleased.clear();
				resetIterator();
			};

		protected:
			bool mManaged; // Determine whether the pool is responsible for creation and destruction of the elements
			PoolMapMap mReleased;
			PoolMapMap mLocked;
	};

}
#endif
