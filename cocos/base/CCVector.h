/****************************************************************************
Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
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
#ifndef __CCVECTOR_H__
#define __CCVECTOR_H__

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include <vector>
#include <functional>
#include <algorithm> // for std::find

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

/*
 * @~english
 * Similar to std::vector, but it will manage reference count automatically internally.
 * Which means it will invoke Ref::retain() when adding an element, and invoke Ref::release() when removing an element.
 * @~chinese 
 * 类似于std::vector,但是在内部自动管理引用计数。
 * 这意味着它被添加的时候将调用Ref::retain()，被删除的时候将调用Ref::release()。
 * @warn @~english The element should be `Ref` or its sub-class.
 * @~chinese 元素应该为“Ref”或其子类。
 * @lua NA
 */
template<class T>
class Vector
{
public:
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    
    /** @~english Iterator, can be used to loop the Vector.  @~chinese 迭代器,可用于循环遍历Vector。*/
    typedef typename std::vector<T>::iterator iterator;

    /** @~english Const iterator, can be used to loop the Vector.  @~chinese 常量迭代器,可用于循环遍历Vector。*/
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    /** @~english Reversed iterator, can be used to loop the Vector in reverse sequence.  @~chinese 反向迭代器,可用于反向循环遍历Vector队列。*/
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;

    /** @~english Reversed iterator, can be used to loop the Vector in reverse sequence.  @~chinese 反向迭代器,可用于反向循环遍历Vector队列。*/
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
    
    /** @~english Returns an iterator pointing the first element of the Vector.  @~chinese 返回一个迭代器指向Vector的第一个元素。*/
    iterator begin() { return _data.begin(); }

    /** @~english Returns an iterator pointing the first element of the Vector.  @~chinese 返回一个迭代器指向Vector的第一个元素。*/
    const_iterator begin() const { return _data.begin(); }
    
    /**
     * @~english
     * Returns an iterator referring to the `past-the-end` element in the Vector container.
     * The past-the-end element is the theoretical element that would follow the last element in the Vector.
     * It does not point to any element, and thus shall not be dereferenced.
     * @~chinese 
     * 返回一个迭代器容器中的的past-the-end元素。
     * past-the-end元素是按照Vector中的最后一个元素。
     * 它不指向任何元素,因此不能反向引用。
     */
    iterator end() { return _data.end(); }

    /**
     * @~english
     * Returns iterator referring to the `past-the-end` element in the Vector container.
     * The past-the-end element is the theoretical element that would follow the last element in the Vector.
     * It does not point to any element, and thus shall not be dereferenced.
     * @~chinese 
     * 返回一个迭代器容器中的的past-the-end元素。
     * past-the-end元素是按照Vector中的最后一个元素。
     * 它不指向任何元素,因此不能反向引用。
     */
    const_iterator end() const { return _data.end(); }
    
    /** @~english Returns a const_iterator pointing the first element of the Vector.  @~chinese 返回一个const_iterator指向Vector的第一个元素。*/
    const_iterator cbegin() const { return _data.cbegin(); }

    /** @~english Returns a const_iterator pointing the `past-the-end` element of the Vector.  @~chinese 返回一个const_iterator指向Vector的past-the-end元素。*/
    const_iterator cend() const { return _data.cend(); }
    
    /** @~english Returns a reverse iterator pointing to the last element of the Vector.  @~chinese 返回一个反向迭代器指向Vector的最后一个元素。*/
    reverse_iterator rbegin() { return _data.rbegin(); }

    /** @~english Returns a reverse iterator pointing to the last element of the Vector.  @~chinese 返回一个反向迭代器指向Vector的最后一个元素。*/
    const_reverse_iterator rbegin() const { return _data.rbegin(); }
    
    /**
     * @~english Returns a reverse iterator pointing to the theoretical element preceding the
     * first element of the vector (which is considered its reverse end).
     * @~chinese 返回一个反向迭代器，指向Vector的第一元素前面的theoretical元素（这被认为是它的反向最后一个）。
     */
    reverse_iterator rend() { return _data.rend(); }

    /**
     * @~english Returns a reverse iterator pointing to the theoretical element preceding the
     * first element of the vector (which is considered its reverse end).
     * @~chinese 返回一个反向迭代器，指向Vector的第一元素前面的theoretical元素（这被认为是它的反向最后一个）。
     */
    const_reverse_iterator rend() const { return _data.rend(); }
    
    /** @~english Returns a const_reverse_iterator pointing to the last element in the container  @~chinese 返回一个const_reverse_iterator指向最后一个元素的容器 */
    const_reverse_iterator crbegin() const { return _data.crbegin(); }

    /**
     * @~english Returns a const_reverse_iterator pointing to the theoretical element preceding the first element in
     * the container (which is considered its reverse end). 
     * @~chinese 返回一个const_reverse_iterator指向容器中第一个theoretical元素（这被认为是他的反向最后一个）
     */
    const_reverse_iterator crend() const { return _data.crend(); }
    
    /** @~english Constructor.  @~chinese 构造函数。 */
    Vector<T>()
    : _data()
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
    }
    
    /**
     * @~english
     * Constructor with a capacity. 
     * @~chinese 
     * 构造函数，使用capacity构造。
     * @param capacity @~english Capacity of the Vector.
     * @~chinese Vector的Capacity。
     */
    explicit Vector<T>(ssize_t capacity)
    : _data()
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the default constructor with capacity of Vector.");
        reserve(capacity);
    }

    /** @~english Destructor.  @~chinese 析构函数。 */
    ~Vector<T>()
    {
        CCLOGINFO("In the destructor of Vector.");
        clear();
    }

    /** @~english Copy constructor.  @~chinese 拷贝构造函数。 */
    Vector<T>(const Vector<T>& other)
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the copy constructor!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** @~english Constructor with std::move semantic.  @~chinese 使用std::move构造。*/
    Vector<T>(Vector<T>&& other)
    {
        static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::Vector<T>!");
        CCLOGINFO("In the move constructor of Vector!");
        _data = std::move(other._data);
    }
    
    /** @~english Copy assignment operator.  @~chinese 拷贝赋值运算符。 */
    Vector<T>& operator=(const Vector<T>& other)
    {
        if (this != &other) {
            CCLOGINFO("In the copy assignment operator!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    /** @~english Copy assignment operator with std::move semantic.  @~chinese 拷贝赋值运算符与std::move语义。*/
    Vector<T>& operator=(Vector<T>&& other)
    {
        if (this != &other) {
            CCLOGINFO("In the move assignment operator!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
// Don't uses operator since we could not decide whether it needs 'retain'/'release'.
//    T& operator[](int index)
//    {
//        return _data[index];
//    }
//    
//    const T& operator[](int index) const
//    {
//        return _data[index];
//    }
    
    /**
     * @~english
     * Requests that the vector capacity be at least enough to contain n elements.
     * @~chinese 
     * 要求载体容量至少足以包含n个元素。
     * @param capacity @~english Minimum capacity requested of the Vector.
     * @~chinese 要求Vector的最小容量。
     */
    void reserve(ssize_t n)
    {
        _data.reserve(n);
    }
    
    /**
     * @brief @~english Returns the size of the storage space currently allocated for the Vector, expressed in terms of elements.
     * @~chinese 返回当前分配给Vector的存储空间的大小。
     *  @note @~english This capacity is not necessarily equal to the Vector size.
     *        It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
     * @~chinese 这种capacity并不一定等于Vector的大小。
     * 它可以相等或者更大,额外的空间可以容纳增长而不需要在每个插入的时候重新分配。
     *  @return @~english The size of the currently allocated storage capacity in the Vector, measured in terms of the number elements it can hold.
     * @~chinese 当前分配存储容量Vector中的大小,它所能容纳的元素数量。
     */
    ssize_t capacity() const
    {
        return _data.capacity();
    }
    
    /**
     * @brief @~english Returns the number of elements in the Vector.
     * @~chinese 返回Vector中元素的数量。
     *  @note @~english This is the number of actual objects held in the Vector, which is not necessarily equal to its storage capacity.
     * @~chinese 这是实际对象的Vector的数量,并不一定等于它的存储容量。
     *  @return @~english The number of elements in the Vector.
     * @~chinese Vector中的元素的数量。
     */
    ssize_t size() const
    {
        return  _data.size();
    }
    
    /** @brief @~english Returns whether the Vector is empty (i.e. whether its size is 0).
     * @~chinese 返回Vector是否为空(即无论其大小为0)。
     *  @note @~english This function does not modify the container in any way. To clear the content of a vector, see Vector<T>::clear.
     * @~chinese 此功能不会修改容器以任何方式。要清除一个载体的内容，请参阅Vector<T>::clear。
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** @~english Returns the maximum number of elements that the Vector can hold.  @~chinese 返回Vector可以容纳的最大元素数量。 */
    ssize_t max_size() const
    {
        return _data.max_size();
    }
    
    /** @~english Returns index of a certain object, return UNIT_MAX if doesn't contain the object  @~chinese 返回索引的对象,如果不包含对象则返回UNIT_MAX */
    ssize_t getIndex(T object) const
    {
        auto iter = std::find(_data.begin(), _data.end(), object);
        if (iter != _data.end())
            return iter - _data.begin();

        return -1;
    }

    /**
     * @brief @~english Find the object in the Vector.
     * @~chinese 查找Vector中的对象
     *  @param object @~english The object to find.
     * @~chinese 查找对象
     *  @return @~english Returns an iterator which refers to the element that its value is equals to object.
     *          Returns Vector::end() if not found.
     * @~chinese 返回一个指向元素的iterator。
     * 如果不存在则返回Vector::end()
     */
    const_iterator find(T object) const
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    /** @brief @~english Find the object in the Vector.
     * @~chinese 查找Vector中的对象。
     *  @param object @~english The object to find.
     * @~chinese 查找对象。
     *  @return @~english Returns an iterator which refers to the element that its value is equals to object.
     *          Returns Vector::end() if not found.
     * @~chinese 返回一个指向元素的iterator。
     * 如果不存在则返回Vector::end()
     */
    iterator find(T object)
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    /** @~english Returns the element at position 'index' in the Vector.  @~chinese 返回元素在Vector中的位置索引。*/
    T at(ssize_t index) const
    {
        CCASSERT( index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
        return _data[index];
    }

    /** @~english Returns the first element in the Vector.  @~chinese 返回Vector中的第一个元素。 */
    T front() const
    {
        return _data.front();
    }
    
    /** @~english Returns the last element of the Vector.  @~chinese 返回Vector的最后一个元素。*/
    T back() const
    {
        return _data.back();
    }

    /** @~english Returns a random element of the Vector.  @~chinese 返回Vector中的一个随机元素。*/
    T getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            return *(_data.begin() + randIdx);
        }
        return nullptr;
    }

    /**
     * @~english
     * Checks whether an object is in the container.
     * @~chinese 
     * 检查一个对象是否在容器中。
     * @param object @~english The object to be checked.
     * @~chinese 被检查的对象。
     * @return @~english True if the object is in the container, false if not.
     * @~chinese 如果对象在容器里返回true，如果不在，则返回false。
     */
    bool contains(T object) const
    {
        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
    }

    /**
     * @~english
     * Checks whether two vectors are equal.
     * @~chinese 
     * 检查两个Vector是否相等。
     * @param other @~english The vector to be compared.
     * @~chinese 比较的vector对象。
     * @return @~english True if two vectors are equal, false if not.
     * @~chinese 如果两个Vector是相等的则返回true,如果不想等则返回false。
     */
    bool equals(const Vector<T> &other)
    {
        ssize_t s = this->size();
        if (s != other.size())
            return false;
        
        for (ssize_t i = 0; i < s; i++)
        {
            if (this->at(i) != other.at(i))
            {
                return false;
            }
        }
        return true;
    }

    // Adds objects
    
    /** @~english Adds a new element at the end of the Vector.  @~chinese 添加一个新元素到Vector内。*/
    void pushBack(T object)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.push_back( object );
        object->retain();
    }
    
    /** @~english Push all elements of an existing Vector to the end of current Vector.  @~chinese 在现有Vector的最后，插入指定Vector的元素。*/
    void pushBack(const Vector<T>& other)
    {
        for(const auto &obj : other) {
            _data.push_back(obj);
            obj->retain();
        }
    }

    /**
     * @~english
     * Insert an object at certain index.
     * @~chinese 
     * 在特定索引插入一个对象。
     * @param index @~english The index to be inserted at.
     * @~chinese 被插入的索引。
     * @param object @~english The object to be inserted.
     * @~chinese 被插入的对象。
     */
    void insert(ssize_t index, T object)
    {
        CCASSERT(index >= 0 && index <= size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.insert((std::begin(_data) + index), object);
        object->retain();
    }
    
    // Removes Objects

    /** @~english Removes the last element in the Vector.  @~chinese 删除Vector中的最后一个元素。*/
    void popBack()
    {
        CCASSERT(!_data.empty(), "no objects added");
        auto last = _data.back();
        _data.pop_back();
        last->release();
    }
    
    /**
     * @~english Remove a certain object in Vector.
     * @~chinese 删除Vector中的一个特定对象。
     *  @param object @~english The object to be removed.
     * @~chinese 要删除的对象。
     *  @param removeAll @~english Whether to remove all elements with the same value.
     *                   If its value is 'false', it will just erase the first occurrence.
     * @~chinese Vector中是否包含需要删除的对象
     * 如果它的值是false，则只会删除第一个匹配的元素。
     */
    void eraseObject(T object, bool removeAll = false)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        if (removeAll)
        {
            for (auto iter = _data.begin(); iter != _data.end();)
            {
                if ((*iter) == object)
                {
                    iter = _data.erase(iter);
                    object->release();
                }
                else
                {
                    ++iter;
                }
            }
        }
        else
        {
            auto iter = std::find(_data.begin(), _data.end(), object);
            if (iter != _data.end())
            {
                _data.erase(iter);
                object->release();
            }
        }
    }

    /**
     * @brief @~english Removes from the vector with an iterator.
     * @~chinese 从Vector迭代器删除。
     *  @param position @~english Iterator pointing to a single element to be removed from the Vector.
     * @~chinese 迭代器，指向从Vector中删除的一个元素。
     *  @return @~english An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     * @~chinese 一个迭代指向的元素的新的位置，接着由所述函数调用删除的最后一个元素。
     * 如果在容器结尾操作，则擦除序列中的最后一个元素。
     */
    iterator erase(iterator position)
    {
        CCASSERT(position >= _data.begin() && position < _data.end(), "Invalid position!");
        (*position)->release();
        return _data.erase(position);
    }
    
    /**
     * @brief @~english Removes from the Vector with a range of elements (  [first, last)  ).
     * @~chinese 从Vector中移除了一系列的元素([第一个元素, 最后一个元素))。
     *  @param first @~english The beginning of the range.
     * @~chinese 开始的范围。
     *  @param last @~english The end of the range, the 'last' will not be removed, it's only for indicating the end of range.
     * @~chinese 结束的范围,“最后”不会被删除,它只是用来指示结束的范围。
     *  @return @~english An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     * @~chinese 迭代器指向元素的新位置,接着由所述函数擦除最后一个元素。
     * 如果在容器结尾操作，则擦除序列中的最后一个元素。
     */
    iterator erase(iterator first, iterator last)
    {
        for (auto iter = first; iter != last; ++iter)
        {
            (*iter)->release();
        }
        
        return _data.erase(first, last);
    }
    
    /**
     * @brief @~english Removes from the Vector by index.
     * @~chinese 从Vector删除索引。
     *  @param index @~english The index of the element to be removed from the Vector.
     * @~chinese 从Vector中删除的元素索引。
     *  @return @~english An iterator pointing to the successor of Vector[index].
     * @~chinese 一个迭代器指向Vector[index]的替代者。
     */
    iterator erase(ssize_t index)
    {
        CCASSERT(!_data.empty() && index >=0 && index < size(), "Invalid index!");
        auto it = std::next( begin(), index );
        (*it)->release();
        return _data.erase(it);
    }

    /**
     * @brief @~english Removes all elements from the Vector (which are destroyed), leaving the container with a size of 0.
     * @~chinese 从Vector中删除所有元素,使容器的大小变为0。
     *  @note @~english All the elements in the Vector will be released (reference count will be decreased).
     * @~chinese 所有Vector中的元素将被释放（reference数将减少）。
     */
    void clear()
    {
        for( auto it = std::begin(_data); it != std::end(_data); ++it ) {
            (*it)->release();
        }
        _data.clear();
    }

    // Rearranging Content

    /** @~english Swap the values object1 and object2.  @~chinese 交换Object1和Object2的值。*/
    void swap(T object1, T object2)
    {
        ssize_t idx1 = getIndex(object1);
        ssize_t idx2 = getIndex(object2);

        CCASSERT(idx1>=0 && idx2>=0, "invalid object index");

        std::swap( _data[idx1], _data[idx2] );
    }
    
    /** @~english Swap two elements by indexes.  @~chinese 交换两个元素的索引。*/
    void swap(ssize_t index1, ssize_t index2)
    {
        CCASSERT(index1 >=0 && index1 < size() && index2 >= 0 && index2 < size(), "Invalid indices");

        std::swap( _data[index1], _data[index2] );
    }

    /** @~english Replace value at index with given object.  @~chinese 在对象替中根据索引替换值。*/
    void replace(ssize_t index, T object)
    {
        CCASSERT(index >= 0 && index < size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        _data[index]->release();
        _data[index] = object;
        object->retain();
    }

    /** @~english Reverses the Vector.  @~chinese 颠倒Vector。*/
    void reverse()
    {
        std::reverse( std::begin(_data), std::end(_data) );
    }
    
    /** @~english Requests the container to reduce its capacity to fit its size.  @~chinese 请求容器缩减容量大小. */
    void shrinkToFit()
    {
        _data.shrink_to_fit();
    }
    
protected:
    
    /** @~english Retains all the objects in the vector  @~chinese 保留在载体中的所有对象 */
    void addRefForAllObjects()
    {
        for(const auto &obj : _data) {
            obj->retain();
        }
    }
    
    std::vector<T> _data;
};

// end of base group
/** @} */

NS_CC_END

#endif // __CCVECTOR_H__
