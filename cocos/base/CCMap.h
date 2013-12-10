/****************************************************************************
Copyright (c) 2012 - 2013 cocos2d-x.org

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

#ifndef __CCMAP_H__
#define __CCMAP_H__

#include <vector>
#include <unordered_map>
#include <algorithm>    // std::for_each

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

template <class K, class V>
class CC_DLL Map
{
public:
    Map<K, V>()
    : _data()
    {
        CCLOGINFO("In the default constructor of Map!");
    }
    
    explicit Map<K, V>(int capacity)
    : _data()
    {
        CCLOGINFO("In the constructor with capacity of Map!");
        _data.reserve(capacity);
    }

    Map<K, V>(const Map<K, V>& other)
    {
        CCLOGINFO("In the copy constructor of Map!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    Map<K, V>(Map<K, V>&& other)
    {
        CCLOGINFO("In the move constructor of Map!");
        _data = std::move(other._data);
    }
    
    ~Map<K, V>()
    {
        CCLOGINFO("In the destructor of Map!");
        clear();
    }

    /** Sets capacity of current array */
    void reserve(int capacity)
    {
        _data.reserve(capacity);
    }
    
    /** Returns capacity of the array */
    size_t capacity() const
    {
        return _data.capacity();
    }
    
    size_t size() const
    {
        return _data.size();
    }

    bool empty() const
    {
        return _data.empty();
    }
    
    std::vector<K> keys() const
    {
        std::vector<K> keys;

        if (!_data.empty())
        {
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }

    std::vector<K> keys(V object) const
    {
        std::vector<K> keys;
        
        for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
        {
            if (iter->second == object)
            {
                keys.push_back(iter->first);
            }
        }
        
        return keys;
    }

    V at(const K& key) const
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        
        return nullptr;
    }
    
    void insert(const K& key, V object)
    {
        CCASSERT(object != nullptr, "Object is nullptr!");
        remove(key);
        _data.insert(std::make_pair(key, object));
        object->retain();
    }

    void remove(const K& key)
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
        {
            iter->second->release();
            _data.erase(iter);
        }
    }
    
    void remove(const std::vector<K>& keys)
    {
        std::for_each(keys.cbegin(), keys.cend(), [this](const K& key){
            this->remove(key);
        });
    }
    
    void clear()
    {
        for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
        {
            iter->second->release();
        }
        
        _data.clear();
    }
    
    V getRandomObject() const
    {
        if (!_data.empty())
        {
            int randIdx = rand() % _data.size();
            return (_data.begin() + randIdx)->second;
        }
        return nullptr;
    }
    
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef std::unordered_map<K, V> RefMap;
    
    typedef typename RefMap::iterator iterator;
    typedef typename RefMap::const_iterator const_iterator;

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
// Don't uses operator since we could not decide whether it needs 'retain'/'release'.
//    V& operator[] ( const K& key )
//    {
//        CCLOG("copy: [] ref");
//        return _data[key];
//    }
//    
//    V& operator[] ( K&& key )
//    {
//        CCLOG("move [] ref");
//        return _data[key];
//    }
    
//    const V& operator[] ( const K& key ) const
//    {
//        CCLOG("const copy []");
//        return _data.at(key);
//    }
//    
//    const V& operator[] ( K&& key ) const
//    {
//        CCLOG("const move []");
//        return _data.at(key);
//    }
    
    Map<K, V>& operator= ( const Map<K, V>& other )
    {
        CCLOGINFO("In the copy assignment operator of Map!");
        clear();
        _data = other._data;
        addRefForAllObjects();
        return *this;
    }

    Map<K, V>& operator= ( Map<K, V>&& other )
    {
        CCLOGINFO("In the move assignment operator of Map!");
        _data = std::move(other._data);
        return *this;
    }
    
protected:
    
    void addRefForAllObjects()
    {
        for (auto iter = _data.begin(); iter != _data.end(); ++iter)
        {
            iter->second->retain();
        }
    }
    
    RefMap _data;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCMAP_H__ */
