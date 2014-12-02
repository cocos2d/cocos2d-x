/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_POOL_H__
#define __PU_POOL_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseException.h"
#include <list>

namespace ParticleUniverse
{
	/** Simple pool, use to store and retrieve precreated objects.
	@remarks
		This templated pool stores objects in a list and offers a few functions to retrieve objects and traverse through the 
		pool.
    */
	template <typename T>
	class _ParticleUniverseExport Pool
	{
		public:
			typedef list<T*> PoolList;
			typedef typename PoolList::iterator PoolIterator; // The 'typename' MUST be added, since T is not a fixed type
			PoolIterator mPoolIterator;

			//-----------------------------------------------------------------------
			Pool (bool managed = false) : mManaged(managed)
			{
				if (mManaged)
				{
					// Unused.
				}
			};
			//-----------------------------------------------------------------------
			virtual ~Pool (void)
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
			/** Returns the number of all released elements.
			*/
			inline size_t getSize(void)
			{
				return mReleased.size();
			};
			//-----------------------------------------------------------------------
			/** Reset the iterator, so that traversing through the pool starts from the beginning.
			@remarks
				Objects in the pool are ´locked´ (unused) by default. If an object is released (´unlocked´) it is exposed 
				to the outside world. Traversing through the pool implies traversing through the 'released' objects.
			*/
			inline void resetIterator (void)
			{
				mPoolIterator = mReleased.begin();
			};
			//-----------------------------------------------------------------------
			/** Return the first 'released' element in the pool.
			@remarks
				Together with the function getNext(), this function is a convenient function that is used
				to iterate through the pool.
			*/
			inline T* getFirst (void)
			{
				resetIterator();
				if (end())
					return 0;

				return *mPoolIterator;
			};
			//-----------------------------------------------------------------------
			/** Return the next 'released' element in the pool.
			@remarks
				Together with the functions resetIterator() and end(), this function is a convenient function that is used
				to iterate through the pool.
			*/
			inline T* getNext (void)
			{
				if (end())
					return 0;

				mPoolIterator++;
				if (end())
					return 0;

				return *mPoolIterator;
			};
			//-----------------------------------------------------------------------
			/** Determines whether the end of the pool has been reached.
			@remarks
				This function is often used in a while-expression to traverses through the 'released' elements of the pool.
			*/
			inline bool end (void)
			{
				return mPoolIterator == mReleased.end();
			};
			//-----------------------------------------------------------------------
			/** Clear the pool.
			@remarks
				The elements in the pool are all removed but not deleted. Clearing a pool is only interesting if the 
				pool doesn´t manage the elements itself (creation and destruction of elements is done outside the pool).
			*/
			inline void clear (void)
			{
				mLocked.clear();
				mReleased.clear();
			};
			//-----------------------------------------------------------------------
			/** 
			*/
			inline void addElement (T* element)
			{
				if (mManaged)
					EXCEPT(Exception::ERR_NOT_IMPLEMENTED, "It is not allowed to add elements, because the pool manages the creation/destruction.", 
				        "Pool::addElement");

				mLocked.push_back(element);
			};
			//-----------------------------------------------------------------------
			/** Retrieve an object from the pool.
			@remarks
				This function does not only retrieve an object, but the object is also marked as ´released´. This means
				that the object is exposed to the outside world. If objects in pool are traversed, only the released objects
				are taken into account.
			*/
			inline T* releaseElement (void)
			{
				// Return with 0 if no elements left
				if (mLocked.empty())
					return 0;

				// Move element from locked elements to released elements and return it
				T* t = mLocked.front();
				mReleased.splice(mReleased.end(), mLocked, mLocked.begin());
				return t;
			};
			//-----------------------------------------------------------------------
			/** Release all elements in the pool.
			@remarks
				All precreated objects in the pool are exposed to the outside world.
			*/
			inline void releaseAllElements (void)
			{
				// Move all elements from locked elements to released elements
				mReleased.splice(mReleased.end(), mLocked);
				resetIterator();
			};
			//-----------------------------------------------------------------------
			/** Lock the element to which the internal iterator points.
			@remarks
				Relased elements that are not used anymore should be locked again. This means that they are skipped in the 
				next iteration. This is a major performance saver if a large number of elements are involved.
				Performance is also the reason that there is no lockElement() function with an element as argument, since this
				would include a search for each element that will be locked.
				The alternative is the lockLatestElement() function. This function can be used while iterating the pool.
				In the iteration-loop every ´released´ element is validated and if a certain condition exists, the element 
				can be locked by means of lockLatestElement().
			*/
			inline void lockLatestElement (void)
			{
				// Move element pointed by mPoolIterator from released elements to locked elements
				mLocked.push_back(*mPoolIterator);
				mPoolIterator = mReleased.erase(mPoolIterator);
				if (mPoolIterator != mReleased.begin() && mPoolIterator != mReleased.end())
				{
					mPoolIterator--;
				}
			};
			//-----------------------------------------------------------------------
			/** Lock all elements in the pool.
			@remarks
				All released objects are locked.
			*/
			inline void lockAllElements (void)
			{
				// Move all elements from released elements to locked elements
				mLocked.splice(mLocked.end(), mReleased);
				resetIterator();
			};
			//-----------------------------------------------------------------------
			/** Returns the complete list with active elements.
			*/
			inline PoolList& getActiveElementsList(void)
			{
				return mReleased;
			};

		protected:
			// Determine whether the pool is responsible for creation and destruction of the elements
			bool mManaged;

			// List with precreated 'released' elements
			PoolList mReleased;

			// List with precreated 'locked' elements
			PoolList mLocked;
	};

}
#endif
