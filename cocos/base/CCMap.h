/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies
 
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

#define USE_STD_UNORDERED_MAP 1

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include <vector>

#if USE_STD_UNORDERED_MAP
#include <unordered_map>
#else
#include <map>
#endif


/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

 /**
  * @~english
  * Similar to std::unordered_map, but it will manage reference count automatically internally.
  * Which means it will invoke Ref::retain() when adding an element, and invoke Ref::release() when removing an element.
  * @~chinese 
  * 类似于std::unordered_map,但是在内部自动管理引用计数。
  * 这意味着它将在插入的时候调用Ref::retain()，删除的时候调用Ref::release()
  *
  * @warning @~english The element should be `Ref` or its sub-class.
  * @~chinese 元素应该是“Ref”或其子类。
  *
  * @js NA
  * @lua NA
  */
template <class K, class V>
class Map
{
public: 
#if USE_STD_UNORDERED_MAP
    typedef std::unordered_map<K, V> RefMap;
#else
    typedef std::map<K, V> RefMap;
#endif
    
    // ------------------------------------------
    // Iterators
    // ------------------------------------------

    /** @~english Iterator, can be used to loop the Map.  @~chinese 迭代器,可用于遍历map。*/
    typedef typename RefMap::iterator iterator;

    /** @~english Const iterator, can be used to loop the Map.  @~chinese 常量迭代器,可用于循环Map。*/
    typedef typename RefMap::const_iterator const_iterator;
    
    /** @~english Return iterator to beginning.  @~chinese 返回迭代器开始。*/
    iterator begin() { return _data.begin(); }

    /** @~english Return const_iterator to beginning.  @~chinese 返回const_iterator开头。*/
    const_iterator begin() const { return _data.begin(); }
    
    /** @~english Return iterator to end. @~chinese 返回迭代器末尾。*/
    iterator end() { return _data.end(); }

    /** @~english Return const_iterator to end. @~chinese 返回const_iterator结尾。*/
    const_iterator end() const { return _data.end(); }
    
    /** @~english Return const_iterator to beginning. @~chinese 返回const_iterator开头。*/
    const_iterator cbegin() const { return _data.cbegin(); }

    /** @~english Return const_iterator to end. @~chinese 返回const_iterator结尾。*/
    const_iterator cend() const { return _data.cend(); }
    
    /** @~english Default constructor  @~chinese 默认构造函数 */
    Map<K, V>()
    : _data()
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the default constructor of Map!");
    }
    
    /** @~english Constructor with capacity.  @~chinese capacity构造函数。 */
    explicit Map<K, V>(ssize_t capacity)
    : _data()
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the constructor with capacity of Map!");
        _data.reserve(capacity);
    }
    
    /** @~english Copy constructor.  @~chinese Copy构造函数。 */
    Map<K, V>(const Map<K, V>& other)
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the copy constructor of Map!");
        _data = other._data;
        addRefForAllObjects();
    }
    
    /** @~english Move constructor.  @~chinese Move构造函数。 */

    Map<K, V>(Map<K, V>&& other)
    {
        static_assert(std::is_convertible<V, Ref*>::value, "Invalid Type for cocos2d::Map<K, V>!");
        CCLOGINFO("In the move constructor of Map!");
        _data = std::move(other._data);
    }
    
    /**
     * @~english
     * Destructor.
     * It will release all objects in map.
     *
     * @~chinese 
     * 析构函数。
     * 释放map中的所有对象。
     */
    ~Map<K, V>()
    {
        CCLOGINFO("In the destructor of Map!");
        clear();
    }
    
    /** @~english Sets capacity of the map.  @~chinese 设置Map的capacity。 */
    void reserve(ssize_t capacity)
    {
#if USE_STD_UNORDERED_MAP
        _data.reserve(capacity);
#endif
    }
    
    /** @~english Returns the number of buckets in the Map container.  @~chinese 返回map中buckets的数量。 */
    ssize_t bucketCount() const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_count();
#else
        return 0;
#endif
    }
    
    /** @~english Returns the number of elements in bucket n.  @~chinese 返回bucket n的元素数量。 */
    ssize_t bucketSize(ssize_t n) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_size(n);
#else
        return 0;
#endif
    }
    
    /** @~english Returns the bucket number where the element with key k is located.  @~chinese 返回的bucket数与密钥K元素的位置。 */
    ssize_t bucket(const K& k) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket(k);
#else
        return 0;
#endif
    }
    
    /** @~english The number of elements in the map.  @~chinese Map中的元素的数量。 */
    ssize_t size() const
    {
        return _data.size();
    }
    
    /**
     * @~english
     * Returns a bool value indicating whether the map container is empty, i.e. whether its size is 0.
     * @~chinese 
     * 返回一个bool值,该值指示Map容器是否为空,无论其大小是否为0。
     *  @note @~english This function does not modify the content of the container in any way.
     *        To clear the content of an array object, member function unordered_map::clear exists.
     * @~chinese 这个函数并不以任何方式修改容器的内容。
     *        清除一个数组对象的内容,成员函数 unordered_map:clear 存在。
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** @~english Returns all keys in the map.  @~chinese 返回所有键的映射。 */
    std::vector<K> keys() const
    {
        std::vector<K> keys;

        if (!_data.empty())
        {
            keys.reserve(_data.size());
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }
    
    /** @~english Returns all keys that matches the object.  @~chinese 返回所有键相匹配的对象。 */
    std::vector<K> keys(V object) const
    {
        std::vector<K> keys;
        
        if (!_data.empty())
        {
            keys.reserve(_data.size() / 10);
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                if (iter->second == object)
                {
                    keys.push_back(iter->first);
                }
            }
        }
        
        keys.shrink_to_fit();
        
        return keys;
    }
    
    /**
     * @~english
     * Returns a reference to the mapped value of the element with key k in the map.
     *
     * @~chinese 
     * 返回引用的映射值与k元素的映射。
     * 
     *  @note @~english If key does not match the key of any element in the container, the function return nullptr.
     * @~chinese 如果密钥不匹配的关键任何元素的容器,该函数返回nullptr。
     *  @param key @~english Key value of the element whose mapped value is accessed.
     *       Member type K is the keys for the elements in the container. defined in Map\<K, V\> as an alias of its first template parameter (Key).
     * @~chinese 映射访问元素的关键值。
     * 成员K是在容器中的元素的键。在Map\<K, V\> K，V作为其第一个模板参数的别名（关键）
     */
    const V at(const K& key) const
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    V at(const K& key)
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    /**
     * @~english
     * Searches the container for an element with 'key' as key and returns an iterator to it if found,
     *         otherwise it returns an iterator to Map\<K, V\>\:\:end (the element past the end of the container).
     *
     * @~chinese 
     * 搜索的容器元素与“关键”键和返回一个迭代器,如果找到,
     * 否则返回一个迭代器映射\<K, V\>\:\:end
     * 
     * @param key @~english Key to be searched for.
     *        Member type 'K' is the type of the keys for the elements in the container,
     *        defined in Map\<K, V\> as an alias of its first template parameter (Key).
     * @~chinese 寻找键。
     * 成员类型“K”容器中的元素的键,
     * Map\<K, V\>中定义的别名,它的第一个模板参数
     */
    const_iterator find(const K& key) const
    {
        return _data.find(key);
    }
    
    iterator find(const K& key)
    {
        return _data.find(key);
    }
    
    /**
     * @~english
     * Inserts new elements in the map.
     *
     * @~chinese 
     * 插入新元素的映射。
     * 
     * @note @~english If the container has already contained the key, this function will erase the old pair(key, object)  and insert the new pair.
     * @~chinese 如果容器已经包含的关键,该函数将删除旧的一对(关键对象)并插入新的一对。
     * @param key @~english The key to be inserted.
     * @~chinese 被插入的键。
     * @param object @~english The object to be inserted.
     * @~chinese 被插入的对象。
     */
    void insert(const K& key, V object)
    {
        CCASSERT(object != nullptr, "Object is nullptr!");
        erase(key);
        _data.insert(std::make_pair(key, object));
        object->retain();
    }
    
    /**
     * @~english
     * Removes an element with an iterator from the Map<K, V> container.
     *
     * @~chinese 
     * 从Map中删除一个元素的迭代器< K、V >容器。
     * 
     * @param position @~english Iterator pointing to a single element to be removed from the Map<K, V>.
     *        Member type const_iterator is a forward iterator type.
     * @~chinese 从Map上要删除迭代器指向的单个元素< K、V >。
     * const_iterator是一个向前迭代器的类型。
     */
    iterator erase(const_iterator position)
    {
        CCASSERT(position != _data.cend(), "Invalid iterator!");
        position->second->release();
        return _data.erase(position);
    }
    
    /**
     * @~english
     * Removes an element with an iterator from the Map<K, V> container.
     *
     * @~chinese 
     * 从Map中删除一个元素的迭代器< K、V >容器。
     * 
     * @param k @~english Key of the element to be erased.
     *        Member type 'K' is the type of the keys for the elements in the container,
     *        defined in Map<K, V> as an alias of its first template parameter (Key).
     * @~chinese 删除的键元素。
     * “K”类型的容器中的元素的键,
     * Map < K、V >中定义的别名,它的第一个模板参数
     */

    size_t erase(const K& k)
    {
        auto iter = _data.find(k);
        if (iter != _data.end())
        {
            iter->second->release();
            _data.erase(iter);
            return 1;
        }
        
        return 0;
    }
    
    /**
     * @~english
     * Removes some elements with a vector which contains keys in the map.
     *
     * @~chinese 
     * 删除某些元素与向量中包含的键映射。
     * 
     * @param keys @~english Keys of elements to be erased.
     * @~chinese 被删除的键元素。
     */
    void erase(const std::vector<K>& keys)
    {
        for(const auto &key : keys) {
            this->erase(key);
        }
    }
    
    /**
     * @~english
     * All the elements in the Map<K,V> container are dropped:
     *  their reference count will be decreased, and they are removed from the container,
     *  leaving it with a size of 0.
     * @~chinese 
     * 终止Map上的所有元素< K、V >容器:
     * 他们的引用计数将减少并从容器中删除,
     * 留下一个大小为0的元素。
     */
    void clear()
    {
        for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
        {
            iter->second->release();
        }
        
        _data.clear();
    }
    
    /**
     * @~english
     * Gets a random object in the map.
     * @~chinese 
     * 得到一个随机对象的映射。
     * @return @~english Returns the random object if the map isn't empty, otherwise it returns nullptr.
     * @~chinese 如果Map不是空的，则返回随机对象,否则返回nullptr。
     */
    V getRandomObject() const
    {
        if (!_data.empty())
        {
            ssize_t randIdx = rand() % _data.size();
            const_iterator randIter = _data.begin();
            std::advance(randIter , randIdx);
            return randIter->second;
        }
        return nullptr;
    }
    
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
    
    /** @~english Copy assignment operator.  @~chinese 拷贝赋值运算符。 */
    Map<K, V>& operator= ( const Map<K, V>& other )
    {
        if (this != &other) {
            CCLOGINFO("In the copy assignment operator of Map!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    /** @~english Move assignment operator.  @~chinese 移动赋值运算符。 */
    Map<K, V>& operator= ( Map<K, V>&& other )
    {
        if (this != &other) {
            CCLOGINFO("In the move assignment operator of Map!");
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
protected:
    
    /** @~english Retains all the objects in the map  @~chinese 保留所有的对象Map */
    void addRefForAllObjects()
    {
        for (auto iter = _data.begin(); iter != _data.end(); ++iter)
        {
            iter->second->retain();
        }
    }
    
    RefMap _data;
};


NS_CC_END
// end group
/// @}

#endif /* __CCMAP_H__ */
