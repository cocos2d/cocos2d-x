/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include <stack>
#include <vector>
#include <string>
#include "base/CCRef.h"

NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */

class CC_DLL AutoreleasePool
{
public:
    /**
     * @warn Don't create an auto release pool in heap, create it in stack.
     * @js NA
     * @lua NA
     */
    AutoreleasePool();
    
    /**
     * Create an autorelease pool with specific name. This name is useful for debugging.
     */
    AutoreleasePool(const std::string &name);
    
    /**
     * @js NA
     * @lua NA
     */
    ~AutoreleasePool();

    /**
     * Add a given object to this pool.
     *
     * The same object may be added several times to the same pool; When the
     * pool is destructed, the object's Ref::release() method will be called
     * for each time it was added.
     *
     * @param object    The object to add to the pool.
     * @js NA
     * @lua NA
     */
    void addObject(Ref *object);

    /**
     * Clear the autorelease pool.
     *
     * Ref::release() will be called for each time the managed object is
     * added to the pool.
     * @js NA
     * @lua NA
     */
    void clear();
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    /**
     * Whether the pool is doing `clear` operation.
     */
    bool isClearing() const { return _isClearing; };
#endif
    
    /**
     * Checks whether the pool contains the specified object.
     */
    bool contains(Ref* object) const;

    /**
     * Dump the objects that are put into autorelease pool. It is used for debugging.
     *
     * The result will look like:
     * Object pointer address     object id     reference count
     *
     */
    void dump();
    
private:
    /**
     * The underlying array of object managed by the pool.
     *
     * Although Array retains the object once when an object is added, proper
     * Ref::release() is called outside the array to make sure that the pool
     * does not affect the managed object's reference count. So an object can
     * be destructed properly by calling Ref::release() even if the object
     * is in the pool.
     */
    std::vector<Ref*> _managedObjectArray;
    std::string _name;
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    /**
     *  The flag for checking whether the pool is doing `clear` operation.
     */
    bool _isClearing;
#endif
};

class CC_DLL PoolManager
{
public:
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static PoolManager* sharedPoolManager() { return getInstance(); }
    static PoolManager* getInstance();
    
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgePoolManager() { destroyInstance(); }
    static void destroyInstance();
    
    /**
     * Get current auto release pool, there is at least one auto release pool that created by engine.
     * You can create your own auto release pool at demand, which will be put into auto releae pool stack.
     */
    AutoreleasePool *getCurrentPool() const;

    bool isObjectInPools(Ref* obj) const;

    /**
     * @js NA
     * @lua NA
     */
    friend class AutoreleasePool;
    
private:
    PoolManager();
    ~PoolManager();
    
    void push(AutoreleasePool *pool);
    void pop();
    
    static PoolManager* s_singleInstance;
    
    std::deque<AutoreleasePool*> _releasePoolStack;
    AutoreleasePool *_curReleasePool;
};

// end of base_nodes group
/// @}

NS_CC_END

#endif //__AUTORELEASEPOOL_H__
