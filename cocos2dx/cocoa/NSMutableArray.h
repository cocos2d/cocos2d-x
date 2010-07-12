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

#ifndef __COCOA_NS_MUTATLE_ARRAY_H__
#define __COCOA_NS_MUTATLE_ARRAY_H__

#include "NSObject.h"
#include "../platform/platform.h"
#include <vector>

class NSMutableArray
{
public:
	NSMutableArray(UINT32 uSize = 0);
    ~NSMutableArray(void);

	UINT32 count(void);
	UINT32 getIndexOfObject(NSObject *pObject);
	bool containsObject(NSObject *pObject);
	NSObject* getLastObject(void);	

	// Adding objects
	void addObject(NSObject *pObject);
	void addObjectsFromArray(NSMutableArray *pArray);
    void insertObjectAtIndex(NSObject *pObject, UINT32 uIndex);

	// Removing objects
	void removeLastObject(void);
	void removeObject(NSObject *pObject);
	void removeObjectAtIndex(UINT32 uIndex);
	void removeAllObjects(void);

	std::vector<NSObject *>::iterator begin(void);
	std::vector<NSObject *>::iterator end(void);

public:
	static NSMutableArray* arrayWithObjects(NSObject *pObject1, ...);
	static NSMutableArray* arrayWithArray(NSMutableArray *pArray);

private:
	std::vector<NSObject *> m_array;
};

#endif // __COCOA_NS_MUTATLE_ARRAY_H__
