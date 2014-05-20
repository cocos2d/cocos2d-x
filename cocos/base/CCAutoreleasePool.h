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
     * @warn 在栈上创建AutoreleasePool,不要在堆上创建。
     * @js NA
     * @lua NA
     */
    AutoreleasePool();
    
    /**
     * 创建一个特定名称的AutoreleasePool. 这个名称在调试的时候有用。
     */
    AutoreleasePool(const std::string &name);
    
    /**
     * @js NA
     * @lua NA
     */
    ~AutoreleasePool();

    /**
     * 添加一个对象到当前pool。
     *
     * 同一个对象可以多次添加到pool，
     * 当pool被销毁的时候，对象的Ref::release()方法将被调用多次（和add的次数一致）
     *
     * @param object    将被加入到pool的对象.
     * @js NA
     * @lua NA
     */
    void addObject(Ref *object);

    /**
     * 清理pool.
     *
     * 对象的Ref::release()方法将被调用多次 （和add的次数一致）
     * 
     * @js NA
     * @lua NA
     */
    void clear();
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    /**
     * pool是否正在做清理操作。
     */
    bool isClearing() const { return _isClearing; };
#endif
    
    /**
     * 检查pool是否包含指定的对象。
     */
    bool contains(Ref* object) const;

    /**
     * 打印添加到pool的所有对象信息。调试使用。
     *
     * 结果将以下面的格式输出:
     * 对象指针地址     对象id     引用计数
     *
     */
    void dump();
    
private:
    /**
     * 内部数组管理pool中的对象。
     *
     * 尽管数组中包含了添加到pool的对象，
     * 对象的Ref::release()方法是在数组外被调用以保证不影响对象的引用计数。
     * 所以对象可以调用Ref::release()来销毁，即使对象已被添加到pool。
     */
    std::vector<Ref*> _managedObjectArray;
    std::string _name;
    
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    /**
     *  用来检查pool是否在清理的标识。
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
     * 获取当前pool，引擎至少会创建一个AutoreleasePool。
     * 你可以创建自己的AutoreleasePool，并添加到AutoreleasePool栈。
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
