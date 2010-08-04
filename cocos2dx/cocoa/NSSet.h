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

#ifndef __NS_SET_H__
#define __NS_SET_H__

#include <set>
#include "NSObject.h"

namespace   cocos2d {

typedef std::set<NSObject *>::iterator NSSetIterator;

class NSSet : public NSObject
{
public:
	NSSet(void);
	NSSet(const NSSet &rSetObject);
	virtual ~NSSet(void);

	NSSet* copy();
	NSSet* mutableCopy();
	int count();
	void addObject(NSObject *pObject);
	void removeObject(NSObject *pObject);
	bool containsObject(NSObject *pObject);
	NSSetIterator begin();
	NSSetIterator end();

private:
	std::set<NSObject *> m_set;
};

typedef NSSet NSMutableSet;
}//namespace   cocos2d 

#endif // __NS_SET_H__

