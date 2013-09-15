/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __AUTORELEASEPOOL_H__
#define __AUTORELEASEPOOL_H__

#include "CCObject.h"
#include "CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

class CC_DLL AutoreleasePool : public Object
{
    /**
     * The underlying array of object managed by the pool.
     *
     * Although Array retains the object once when an object is added, proper
     * Object::release() is called outside the array to make sure that the pool
     * does not affect the managed object's reference count. So an object can
     * be destructed properly by calling Object::release() even if the object
     * is in the pool.
     */
    Array   *_managedObjectArray;
public:
    /**
     * @js NA
     * @lua NA
     */
    AutoreleasePool();
    /**
     * @js NA
     * @lua NA
     */
    ~AutoreleasePool();

    /**
     * Add a given object to this pool.
     *
     * The same object may be added several times to the same pool; When the
     * pool is destructed, the object's Object::release() method will be called
     * for each time it was added.
     *
     * @param object    The object to add to the pool.
     * @js NA
     * @lua NA
     */
    void addObject(Object *object);

    /**
     * Remove a given object from this pool.
     *
     * @param object    The object to be removed from the pool.
     * @js NA
     * @lua NA
     */
    void removeObject(Object *object);

    /**
     * Clear the autorelease pool.
     *
     * Object::release() will be called for each time the managed object is
     * added to the pool.
     * @js NA
     * @lua NA
     */
    void clear();
};

class CC_DLL PoolManager
{
    Array           *_releasePoolStack;
    AutoreleasePool *_curReleasePool;

    AutoreleasePool *getCurReleasePool();
public:
    /**
     * @js NA
     * @lua NA
     */
    static PoolManager* sharedPoolManager();
    /**
     * @js NA
     * @lua NA
     */
    static void purgePoolManager();
    /**
     * @js NA
     * @lua NA
     */
    PoolManager();
    /**
     * @js NA
     * @lua NA
     */
    ~PoolManager();

    /**
     * Clear all the AutoreleasePool on the pool stack.
     * @js NA
     * @lua NA
     */
    void finalize();

    /**
     * Push a new AutoreleasePool to the pool stack.
     * @js NA
     * @lua NA
     */
    void push();

    /**
     * Pop one AutoreleasePool from the pool stack.
     *
     * This method will ensure that there is at least one AutoreleasePool on
     * the stack.
     *
     * The AutoreleasePool being poped is destructed.
     * @js NA
     * @lua NA
     */
    void pop();

    /**
     * Remove a given object from the current autorelease pool.
     *
     * @param object    The object to be removed.
     *
     * @see AutoreleasePool::removeObject
     * @js NA
     * @lua NA
     */
    void removeObject(Object *object);

    /**
     * Add a given object to the current autorelease pool.
     *
     * @param object    The object to add.
     *
     * @see AutoreleasePool::addObject
     * @js NA
     * @lua NA
     */
    void addObject(Object *object);
    /**
     * @js NA
     * @lua NA
     */
    friend class AutoreleasePool;
};

// end of base_nodes group
/// @}

NS_CC_END

#endif //__AUTORELEASEPOOL_H__
