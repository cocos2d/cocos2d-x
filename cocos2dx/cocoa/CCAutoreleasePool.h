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
    Array*    _managedObjectArray;    
public:
    AutoreleasePool(void);
    ~AutoreleasePool(void);

    void addObject(Object *pObject);
    void removeObject(Object *pObject);

    void clear();
};

class CC_DLL PoolManager
{
    Array*    _releasePoolStack;    
    AutoreleasePool*                    _curReleasePool;

    AutoreleasePool* getCurReleasePool();
public:
    PoolManager();
    ~PoolManager();
    void finalize();
    void push();
    void pop();

    void removeObject(Object* pObject);
    void addObject(Object* pObject);

    static PoolManager* sharedPoolManager();
    static void purgePoolManager();

    friend class AutoreleasePool;
};

// end of base_nodes group
/// @}

NS_CC_END

#endif //__AUTORELEASEPOOL_H__
