/****************************************************************************
Copyright (c) 2010 ForzeField Studios S.L. http://forzefield.com
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
#ifndef __CCVECTOR_H__
#define __CCVECTOR_H__

#include "ccMacros.h"

#include <vector>
#include <functional>
#include <algorithm>    // std::for_each

NS_CC_BEGIN

template<class T>
class CC_DLL Vector
{
public:
    Vector<T>()
    : _data()
    {
        
    }
    
    /** creates an emptry Vector */
    explicit Vector<T>(int capacity)
    : _data()
    {
        CCLOGINFO("In the default constructor with capacity of Vector.");
        reserve(capacity);
    }

    virtual ~Vector<T>()
    {
        CCLOGINFO("In the destructor of Vector.");
        clear();
    }

    Vector<T>(const Vector<T>& other)
    {
        CCLOGINFO("In the copy constructor!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** Move constructor */
    Vector<T>(Vector<T>&& other)
    {
        CCLOGINFO("In the move constructor of Vector!");
        _data = std::move(other._data);
    }
    
    Vector<T>& operator=(const Vector<T>& other)
    {
        CCLOGINFO("In the copy assignment operator!");
        clear();
        _data = other._data;
        addRefForAllObjects();
        return *this;
    }
    
    Vector<T>& operator=(Vector<T>&& other)
    {
        CCLOGINFO("In the move assignment operator!");
        _data = std::move(other._data);
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
    
    /** Sets capacity of current array */
    void reserve(int capacity)
    {
        _data.reserve(capacity);
    }
    
    /** Returns capacity of the array */
    int capacity() const
    {
        return _data.capacity();
    }
    
    // Querying an Array

    /** Returns element count of the array */
    int size() const
    {
        return  static_cast<int>(_data.size());
    }
    
    bool empty() const
    {
        return _data.empty();
    }
    
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    int getIndex(T object) const
    {
        int i = 0;
        for (auto it = _data.begin(); it != _data.end(); ++it, ++i)
        {
            if (*it == object)
            {
                return i;
            }
        }
        
        return -1;
    }

    /** Returns an element with a certain index */
    T at(int index) const
    {
        CCASSERT( index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
        return _data[index];
    }

    T front() const
    {
        return _data.front();
    }
    
    /** Returns the last element of the array */
    T back() const
    {
        return _data.back();
    }

    /** Returns a random element */
    T getRandomObject() const
    {
        if (!_data.empty())
        {
            int randIdx = rand() % _data.size();
            return *(_data.begin() + randIdx);
        }
        return nullptr;
    }

    /** Returns a Boolean value that indicates whether object is present in array. */
    bool contains(T object) const
    {
        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
    }

    /** returns true if the the arrays are equal */
    bool equals(const Vector<T> &other)
    {
        size_t s = this->size();
        if (s != other.size())
            return false;
        
        for (int i = 0; i < s; i++)
        {
            if (!this->at(i)->isEqual(other.at(i)))
            {
                return false;
            }
        }
        return true;
    }

    // Adding Objects

    /** Add a certain object */
    void pushBack(T object)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.push_back( object );
        object->retain();
    }
    
    /** Add all elements of an existing array */
    void insert(const Vector<T>& other)
    {
        for( auto it = other.begin(); it != other.end(); ++it ) {
            _data.push_back( *it );
            (*it)->retain();
        }
    }

    /** Insert a certain object at a certain index */
    void insert(int index, T object)
    {
        CCASSERT(index >= 0 && index <= size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        _data.insert((std::begin(_data) + index), object);
        object->retain();
    }
    
    // Removing Objects

    /** Remove last object */
    void popBack()
    {
        CCASSERT(!_data.empty(), "no objects added");
        auto last = _data.back();
        _data.pop_back();
        last->release();
    }

    /** Remove a certain object */
    void removeObject(T object, bool toRelease = true)
    {
        CCASSERT(object != nullptr, "The object should not be nullptr");
        auto iter = std::find(_data.begin(), _data.end(), object);
        if (iter != _data.end())
            _data.erase(iter);
        if (toRelease)
            object->release();
    }

    /** Removes an element with a certain index */
    void remove(int index)
    {
        CCASSERT(!_data.empty() && index >=0 && index < size(), "Invalid index!");
        auto it = std::next( begin(), index );
        (*it)->release();
        _data.erase(it);
    }

    /** Removes all objects */
    void clear()
    {
        for( auto it = std::begin(_data); it != std::end(_data); ++it ) {
            (*it)->release();
        }
        _data.clear();
    }

    // Rearranging Content

    /** Swap two elements */
    void swap(T object1, T object2)
    {
        auto idx1 = getIndex(object1);
        auto idx2 = getIndex(object2);

        CCASSERT(idx1>=0 && idx2>=0, "invalid object index");

        std::swap( _data[idx1], _data[idx2] );
    }
    
    /** Swap two elements with certain indexes */
    void swap(int index1, int index2)
    {
        CCASSERT(index1 >=0 && index1 < size() && index2 >= 0 && index2 < size(), "Invalid indices");

        std::swap( _data[index1], _data[index2] );
    }

    /** Replace object at index with another object. */
    void replace(int index, T object)
    {
        CCASSERT(index >= 0 && index < size(), "Invalid index!");
        CCASSERT(object != nullptr, "The object should not be nullptr");
        
        _data[index]->release();
        _data[index] = object;
        object->retain();
    }

    /** reverses the array */
    void reverse()
    {
        std::reverse( std::begin(_data), std::end(_data) );
    }
    
    /** Shrinks the array so the memory footprint corresponds with the number of items */
    void shrinkToFit()
    {
        _data.shrink_to_fit();
    }
    
    void forEach(const std::function<void(T)>& callback)
    {
        if (empty())
            return;
        
        std::for_each(_data.cbegin(), _data.cend(), [&callback](const T& obj){
            callback(obj);
        });
    }
    
    void forEach(const std::function<void(T)>& callback) const
    {
        if (empty())
            return;
        
        std::for_each(_data.cbegin(), _data.cend(), [&callback](const T& obj){
            callback(obj);
        });
    }
  
    void forEachReverse(const std::function<void(T)>& callback)
    {
        if (empty())
            return;
        
        std::for_each(_data.crbegin(), _data.crend(), [&callback](const T& obj){
            callback(obj);
        });
    }
    
    void forEachReverse(const std::function<void(T)>& callback) const
    {
        if (empty())
            return;
        
        std::for_each(_data.crbegin(), _data.crend(), [&callback](const T& obj){
            callback(obj);
        });
    }
    
    void sort(const std::function<bool(T, T)>& callback)
    {
        if (empty())
            return;
        
        std::sort(_data.begin(), _data.end(), [&callback](T a, T b) -> bool{
            return callback(a, b);
        });
    }
    
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    typedef typename std::vector<T>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
    
    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
    reverse_iterator rbegin() { return _data.rbegin(); }
    const_reverse_iterator rbegin() const { return _data.rbegin(); }
    
    reverse_iterator rend() { return _data.rend(); }
    const_reverse_iterator rend() const { return _data.rend(); }
    
    const_reverse_iterator crbegin() const { return _data.crbegin(); }
    const_reverse_iterator crend() const { return _data.crend(); }
    
protected:
    
    void addRefForAllObjects()
    {
        std::for_each(_data.begin(), _data.end(), [](T obj){
            obj->retain();
        });
    }
    
    std::vector<T> _data;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCVECTOR_H__
