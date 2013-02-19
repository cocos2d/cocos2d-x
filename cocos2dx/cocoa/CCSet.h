/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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

#ifndef __CC_SET_H__
#define __CC_SET_H__

#include <set>
#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

typedef std::set<CCObject *>::iterator CCSetIterator;

class CC_DLL CCSet : public CCObject
{
public:
    CCSet(void);
    CCSet(const CCSet &rSetObject);
    virtual ~CCSet(void);

    /**
    *@brief Return a copy of the CCSet, it will copy all the elements.
    */
    CCSet* copy();
    /**
    *@brief It is the same as copy().
    */
    CCSet* mutableCopy();
    /**
    *@brief Return the number of elements the CCSet contains.
    */
    int count();
    /**
    *@brief Add a element into CCSet, it will retain the element.
    */
    void addObject(CCObject *pObject);
    /**
    *@brief Remove the given element, nothing todo if no element equals pObject.
    */
    void removeObject(CCObject *pObject);
    /**
     *@brief Remove all elements of the set
     */
    void removeAllObjects();
    /**
    *@brief Check if CCSet contains a element equals pObject.
    */
    bool containsObject(CCObject *pObject);
    /**
    *@brief Return the iterator that points to the first element.
    */
    CCSetIterator begin();
    /**
    *@brief Return the iterator that points to the position after the last element.
    */
    CCSetIterator end();
    /**
    *@brief Return the first element if it contains elements, or null if it doesn't contain any element.
    */
    CCObject* anyObject();

private:
    std::set<CCObject *> *m_pSet;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CC_SET_H__

