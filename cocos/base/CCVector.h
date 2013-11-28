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

#include <vector>
#include <algorithm>
#include "ccMacros.h"

NS_CC_BEGIN

template<class T>
class CC_DLL Vector
{
public:
    /** creates an emptry Vector */
    Vector<T>(long capacity=7)
    : _data()
    {
        CCLOG("In the constructor of Vector.");
        init(capacity);
    }

    virtual ~Vector<T>() {
        CCLOG("In the destructor of Vector.");
        removeAllObjects();
    }

    Vector<T>(const Vector<T>& other)
    {
        CCLOG("In the copy constructor!");
        copy(other);
    }
    
    const Vector<T>& operator=(const Vector<T>& other)
    {
        CCLOG("In the assignment operator!");
        copy(other);
        return *this;
    }
    
    T operator[](long index) const
    {
        return getObjectAtIndex(index);
    }
    
    /** Initializes an array with capacity */
    bool init(long capacity)
    {
        _data.reserve(capacity);
        return true;
    }
    
    void copy(const Vector<T>& other)
    {
        if (this == &other)
            return;
        
        removeAllObjects();
        init(other.count());
        addObjectsFromArray(other);
    }
    
    // Querying an Array

    /** Returns element count of the array */
    long count() const
    {
        return _data.size();
    }
    
    /** Returns capacity of the array */
    long capacity() const
    {
        return _data.capacity();
    }
    
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    long getIndexOfObject(T object) const
    {
        long i=0;
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
    T getObjectAtIndex(long index) const
    {
        CCASSERT(index>=0 && index < count(), "index out of range in getObjectAtIndex()");
        return _data[index];
    }

    /** Returns the last element of the array */
    T getLastObject() const
    {
        return _data.back();
    }

    /** Returns a random element */
    T getRandomObject() const
    {
        return *_data.begin();
    }

    /** Returns a Boolean value that indicates whether object is present in array. */
    bool containsObject(T object) const
    {
        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
    }

    /** returns true if the the arrays are equal */
    bool isEqualToArray(const Vector<T> &otherArray)
    {
        for (long i = 0; i< this->count(); i++)
        {
            if (!this->getObjectAtIndex(i)->isEqual(otherArray.getObjectAtIndex(i)))
            {
                return false;
            }
        }
        return true;
    }

    // Adding Objects

    /** Add a certain object */
    void addObject(T object)
    {
        _data.push_back( object );
        object->retain();
    }

    /** Add all elements of an existing array */
    void addObjectsFromArray(const Vector<T>& otherArray)
    {
        for( auto it = otherArray.begin(); it != otherArray.end(); ++it ) {
            _data.push_back( *it );
            (*it)->retain();
        }
    }

    /** Insert a certain object at a certain index */
    void insertObject(T object, long index)
    {
        _data.insert( std::next( std::begin(_data, index), object ) );
        object->retain();
    }

    /** sets a certain object at a certain index */
    void setObject(T object, long index)
    {
        _data[index] = object;
        object->retain();
    }
    /** sets a certain object at a certain index without retaining. Use it with caution */
    void fastSetObject(T object, long index)
    {
        _data[index] = object;
    }

    // Removing Objects

    /** Remove last object */
    void removeLastObject()
    {
        CCASSERT(_data.size(), "no objects added");
        auto last = _data.back();
        _data.pop_back();
        last->release();
    }

    /** Remove a certain object */
    void removeObject(T object)
    {
        _data.erase( std::remove( _data.begin(), _data.end(), object ) );
        object->release();
    }

    /** Removes an element with a certain index */
    void removeObjectAtIndex(long index)
    {
        auto it = std::next( begin(), index );
        (*it)->release();
        _data.erase(it);
    }

    /** Removes all objects */
    void removeAllObjects()
    {
        for( auto it = std::begin(_data); it != std::end(_data); ++it ) {
            (*it)->release();
        }
        _data.clear();
    }

    /** Fast way to remove a certain object */
    void fastRemoveObject(T object) {
        removeObjectAtIndex(index);
    }

    /** Fast way to remove an element with a certain index */
    void fastRemoveObjectAtIndex(long index)
    {
        removeObjectAtIndex(index);
    }

    // Rearranging Content

    /** Swap two elements */
    void swapObjects(T object1, T object2)
    {
        long idx1 = getIndexOfObject(object1);
        long idx2 = getIndexOfObject(object2);

        CCASSERT(idx1>=0 && idx2>=2, "invalid object index");

        std::swap( _data[idx1], _data[idx2] );
    }
    
    /** Swap two elements with certain indexes */
    void swap(long index1, long index2)
    {
        CCASSERT(index1 >=0 && index1 < count() && index2 >= 0 && index2 < count(), "Invalid indices");

        std::swap( _data[index1], _data[index2] );
    }

    /** Replace object at index with another object. */
    void replaceObjectAtIndex(long index, T object)
    {
        if( object != _data[index] ) {
            object->retain();
            _data[index]->release();
            _data[index] = object;
        }
    }

    /** reverses the array */
    void reverseObjects()
    {
        std::reverse( std::begin(_data), std::end(_data) );
    }
    
    /** Shrinks the array so the memory footprint corresponds with the number of items */
    void reduceMemoryFootprint()
    {
        _data.shrink_to_fit();
    }
  
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    iterator cbegin() { return _data.cbegin(); }
    const_iterator cbegin() const { return _data.cbegin(); }
    
    iterator cend() { return _data.cend(); }
    const_iterator cend() const { return _data.cend(); }

protected:
    std::vector<T> _data;

};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCVECTOR_H__
