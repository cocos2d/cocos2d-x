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
    * @brief 创建并返回一个新的空集.
    */
    static __Set * create();

    /**
    *@brief Return 一个集合的 copy, 它将 copy 所有的集合元素.
    */
    __Set* copy();
    /**
    *@brief 和copy()功能一致.
    */
    __Set* mutableCopy();
    /**
    *@brief Return 集合中包含的元素个数.
    */
    int count();
    /**
    *@brief 往集合中添加一个元素, 它将 retain 这个元素.
    */
    void addObject(Ref *pObject);
    /**
    *@brief Remove给出的元素, 如果集合中不存在这个元素则什么都不做.
    */
    void removeObject(Ref *pObject);
    /**
     *@brief 移除 集合中得所有元素
     */
    void removeAllObjects();
    /**
    *@brief 检查集合中是否存在和 pObject一样的元素.
    */
    bool containsObject(Ref *pObject);
    /**
    *@brief 返回集合中第一个元素的迭代器.
    * @js NA
    * @lua NA
    */
    __SetIterator begin();
    /**
    *@brief 返回集合的最后一个元素之后位置的迭代器.
    * @js NA
    * @lua NA
    */
    __SetIterator end();
    /**
    *@brief  如果它包含这个元素则返回第一个元素, 否则返回null .
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

