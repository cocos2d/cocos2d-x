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

#include <vector>
#include <string>
#include "base/CCRef.h"


/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN



/** @class AutoReleasePool
 * @brief
 * @~english
 * A pool for managing autorlease objects.
 * @~chinese 
 * 自动释放对象管理池。
 * @js NA
 */
class CC_DLL AutoreleasePool
{
public:

    /**
     * @warning @~english Don't create an autorelease pool in heap, create it in stack.
     * @~chinese 不要在堆上创建autorelease池，而要在栈上创建它。
     * @js NA
     * @lua NA
     */
    AutoreleasePool();
    

    /** @~english
     * Create an autorelease pool with specific name. This name is useful for debugging.
     * @~chinese 
     * 用指定的名字创建一个autorelease池。这个名字对于调试非常有用。
     * @warning @~english Don't create an autorelease pool in heap, create it in stack.
     * @~chinese 不要在堆上创建autorelease池，而要在栈上创建它。
     * @js NA
     * @lua NA
     *
     * @param name @~english The name of created autorelease pool.
     * @~chinese 创建的autorelease池名字。
     */
    AutoreleasePool(const std::string &name);
    

    /**
     * @js NA
     * @lua NA
     */
    ~AutoreleasePool();


    /**@~english
     * Add a given object to this autorelease pool.
     *
     * The same object may be added several times to an autorelease pool. When the
     * pool is destructed, the object's `Ref::release()` method will be called
     * the same times as it was added.
     *
     * @~chinese 
     * 将给定对象添加到这个autorelease池。
     * 
     * 同一个对象可以添加几次autorelease池。当
     * 池销毁的时候,对象的`Ref::release()`方法应该被调用相同的次数。
     *
     * @param object    @~english The object to be added into the autorelease pool.
     * @~chinese 添加到autorelease池的对象。
     * @js NA
     * @lua NA
     */
    void addObject(Ref *object);


    /**@~english
     * Clear the autorelease pool.
     *
     * It will invoke each element's `release()` function.
     *
     * @~chinese 
     * 清空autorelease池。
     * 
     * 它将调用每个元素的`release()`的函数。
     * 
     * @js NA
     * @lua NA
     */
    void clear();
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)

    /**@~english
     * Whether the autorelease pool is doing `clear` operation.
     *
     * @~chinese 
     * 获取管理池当前是否正在做清空操作。
     * 
     * @return @~english True if autorelase pool is clearning, false if not.
     *
     * @~chinese 如果autorelase池清空了返回真，如果不是返回假。
     * 
     * @js NA
     * @lua NA
     */
    bool isClearing() const { return _isClearing; };
#endif
    

    /**@~english
     * Checks whether the autorelease pool contains the specified object.
     *
     * @~chinese 
     * 检查autorelease池中是否包含指定的对象。
     * 
     * @param object @~english The object to be checked.
     * @~chinese 被检查的对象。
     * @return @~english True if the autorelease pool contains the object, false if not
     * @~chinese autorelease池包含该对象返回真，如果不包含返回假。
     * @js NA
     * @lua NA
     */
    bool contains(Ref* object) const;


    /**@~english
     * Dump the objects that are put into the autorelease pool. It is used for debugging.
     *
     * The result will look like:
     * Object pointer address     object id     reference count
     *
     * @~chinese 
     * 输出放在autorelease池的对象。用于调试。
     * 
     * 输出格式：
     * 对象 指针地址 对象id 引用计数
     * 
     * @js NA
     * @lua NA
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

// end of base group

/** @} */


/**
 * @cond
 */
class CC_DLL PoolManager
{
public:

    CC_DEPRECATED_ATTRIBUTE static PoolManager* sharedPoolManager() { return getInstance(); }
    static PoolManager* getInstance();
    
    CC_DEPRECATED_ATTRIBUTE static void purgePoolManager() { destroyInstance(); }
    static void destroyInstance();
    

    /**@~english
     * Get current auto release pool, there is at least one auto release pool that created by engine.
     * You can create your own auto release pool at demand, which will be put into auto release pool stack.
     * @~chinese 
     * 得到当前自动释放池，至少有一个自动释放池，是由引擎创建的。
     * 您可以按需创建你自己的自动释放池，它将投入自动释放池堆栈。
     */
    AutoreleasePool *getCurrentPool() const;

    /** @~english Checks whether the autorelease pool stack contains the specified object.
     * @~chinese 检查自动释放池堆栈是否包含指定对象。
     * @return @~english True if the autorelease pool stack contains the object, false if not
     * @~chinese autorelease池堆栈包含该对象返回真，如果不包含返回假。
     */
    bool isObjectInPools(Ref* obj) const;


    friend class AutoreleasePool;
    
private:
    PoolManager();
    ~PoolManager();
    
    void push(AutoreleasePool *pool);
    void pop();
    
    static PoolManager* s_singleInstance;
    
    std::vector<AutoreleasePool*> _releasePoolStack;
};

/**
 * @endcond
 */

NS_CC_END

#endif //__AUTORELEASEPOOL_H__
