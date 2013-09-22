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
 * @js NA
 * @lua NA
 */

class CC_DLL CCAutoreleasePool : public CCObject
{
    CCArray*    m_pManagedObjectArray;    
public:
    CCAutoreleasePool(void);
    ~CCAutoreleasePool(void);

    void addObject(CCObject *pObject);
    void removeObject(CCObject *pObject);

    void clear();
};

/**
 * @js NA
 * @lua NA
 */
class CC_DLL CCPoolManager
{
    CCArray*    m_pReleasePoolStack;    
    CCAutoreleasePool*                    m_pCurReleasePool;

    CCAutoreleasePool* getCurReleasePool();
public:
    CCPoolManager();
    ~CCPoolManager();
    void finalize();
    void push();
    void pop();

    void removeObject(CCObject* pObject);
    void addObject(CCObject* pObject);

    static CCPoolManager* sharedPoolManager();
    static void purgePoolManager();

    friend class CCAutoreleasePool;
};

// end of base_nodes group
/// @}

NS_CC_END

#endif //__AUTORELEASEPOOL_H__
