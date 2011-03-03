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

#include "NSObject.h"
#include "NSMutableArray.h"

namespace cocos2d {
class CCX_DLL NSAutoreleasePool : public NSObject
{
	NSMutableArray<NSObject*>*	m_pManagedObjectArray;	
public:
	NSAutoreleasePool(void);
	~NSAutoreleasePool(void);

	void addObject(NSObject *pObject);
	void removeObject(NSObject *pObject);

	void clear();
};

class CCX_DLL NSPoolManager
{
	NSMutableArray<NSAutoreleasePool*>*	m_pReleasePoolStack;	
	NSAutoreleasePool*					m_pCurReleasePool;

	NSAutoreleasePool* getCurReleasePool();
public:
	NSPoolManager();
	~NSPoolManager();
	void finalize();
	void push();
	void pop();

	void removeObject(NSObject* pObject);
	void addObject(NSObject* pObject);

	static NSPoolManager* getInstance();

	friend class NSAutoreleasePool;
};

}

#endif //__AUTORELEASEPOOL_H__
