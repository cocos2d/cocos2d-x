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

/************************************************************************/
/* CCSet implements some functions of NSSet, but it is too simple.
/* It is used only for cocos2dx, don't use it in your code, or you may have
/* trouble.
/************************************************************************/

#include <set>
#include "CCObject.h"

namespace   cocos2d {

typedef std::set<CCObject *>::iterator CCSetIterator;

class CC_DLL CCSet : public CCObject
{
public:
	CCSet(void);
	CCSet(const CCSet &rSetObject);
	virtual ~CCSet(void);

	CCSet* copy();
	CCSet* mutableCopy();
	int count();
	void addObject(CCObject *pObject);
	void removeObject(CCObject *pObject);
	bool contaiCCObject(CCObject *pObject);
	CCSetIterator begin();
	CCSetIterator end();
    CCObject* anyObject();

private:
    std::set<CCObject *> *m_pSet;
};

typedef CCSet NSMutableSet;
}//namespace   cocos2d 

#endif // __NS_SET_H__

