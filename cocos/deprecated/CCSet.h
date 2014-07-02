/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies

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
#include "base/CCRef.h"
#include "base/CCDataVisitor.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

typedef std::set<Ref *>::iterator __SetIterator;

class CC_DLL __Set : public Ref
{
public:
    /**
     * @js ctor
     */
    __Set(void);
    __Set(const __Set &rSetObject);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~__Set(void);

    /**
    * @brief Create and return a new empty set.
    */
    static __Set * create();

    /**
    *@brief Return a copy of the Set, it will copy all the elements.
    */
    __Set* copy();
    /**
    *@brief It is the same as copy().
    */
    __Set* mutableCopy();
    /**
    *@brief Return the number of elements the Set contains.
    */
    int count();
    /**
    *@brief Add a element into Set, it will retain the element.
    */
    void addObject(Ref *pObject);
    /**
    *@brief Remove the given element, nothing todo if no element equals pObject.
    */
    void removeObject(Ref *pObject);
    /**
     *@brief Remove all elements of the set
     */
    void removeAllObjects();
    /**
    *@brief Check if Set contains a element equals pObject.
    */
    bool containsObject(Ref *pObject);
    /**
    *@brief Return the iterator that points to the first element.
    * @js NA
    * @lua NA
    */
    __SetIterator begin();
    /**
    *@brief Return the iterator that points to the position after the last element.
    * @js NA
    * @lua NA
    */
    __SetIterator end();
    /**
    *@brief Return the first element if it contains elements, or null if it doesn't contain any element.
    */
    Ref* anyObject();
    /**
     * @js NA
     * @lua NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);

private:
    std::set<Ref *> *_set;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CC_SET_H__

