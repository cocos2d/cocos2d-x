/****************************************************************************
Copyright (c) 2012      cocos2d-x.org
 opyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCDICTIONARY_H__
#define __CCDICTIONARY_H__

#include "2d/uthash.h"
#include "base/CCRef.h"
#include "CCArray.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

class __Dictionary;

/**
 * @addtogroup data_structures
 * @{
 */


/**
 *  DictElement 用于遍历字典.
 *
 *  一个 DictElement 字典中的一个元素, 包含两个属性, key 和 object.
 *  key 有两种类型 (integer 和 string).
 *
 *  @note key 的类型唯一, 所有的字典元素都有相同的类型(integer 或者 string).
 *  @code
 *  DictElement* pElement;
 *  CCDICT_FOREACH(dict, pElement)
 *  {
 *      const char*key = pElement->getStrKey();
 *      // 你当然知道key的值, 我们确保它是一个Sprite.
 *      Sprite* pSprite = static_cast<Sprite*>(pElement->getObject());
 *      // ......
 *  }
 *  @endcode
 *
 */
class CC_DLL DictElement
{
private:
    /**
     *  DictElement的构造函数. 只做内部使用. Dictionary 是它的友元类.
     *  
     *  @param  pszKey    string key类型元素.
     *  @param  pObject   object对象元素.
     */
    DictElement(const char* pszKey, Ref* pObject);

    /**
     *  DictElement的构造函数. 只做内部使用. Dictionary 是它的友元类.
     *
     *  @param  iKey      integer key类型元素.
     *  @param  pObject   object对象元素.
     */
    DictElement(intptr_t iKey, Ref* pObject);
    
public:
    /**
     *  DictElement的析构函数.
     * @js NA
     * @lua NA
     */
    ~DictElement();

    // 在android头文件中，内联函数需要被实现
    /**
     * 获取string key元素.
     * @note    该方法确保你知道key类型中的元素. 
     *          如果key类型是integer, 调用该方法将导致一个断言.
     *
     * @return  string key元素.
     */
    inline const char* getStrKey() const
    {
        CCASSERT(_strKey[0] != '\0', "Should not call this function for integer dictionary");
        return _strKey;
    }

    /**
     * 获取integer key类型元素.
     * @note    该方法确保你知道key类型中的元素.
     *          如果key类型是string, 调用该方法将导致一个断言.
     *
     * @return  integer key元素.
     */
    inline intptr_t getIntKey() const
    {
        CCASSERT(_strKey[0] == '\0', "Should not call this function for string dictionary");
        return _intKey;
    }
    
    /**
     * 获取该元素的对象.
     *
     * @return 该元素的对象.
     */
    inline Ref* getObject() const { return _object; }

private:
    // string key的最大长度.
    #define   MAX_KEY_LEN   256
    // char array 需要 HASH_ADD_STR in UT_HASH.
    // 所以这是一个痛苦的过程，为这个数组所有元素分配256个字节
    char      _strKey[MAX_KEY_LEN];     // string 类型的 hash key 
    intptr_t  _intKey;       //integer 类型的 hash key  
    Ref* _object;    // hash 值
public:
    UT_hash_handle hh;      // 让这个类可哈希
    friend class __Dictionary; // 声明一个 Dictionary 作为友元类
};

/** 这个宏用作遍历字典
 *  
 *  @note 它比获取所有的key然后遍历key值快很多。
 *        在遍历的时候移除也是安全的.
 */
#define CCDICT_FOREACH(__dict__, __el__) \
    DictElement* pTmp##__dict__##__el__ = nullptr; \
    if (__dict__) \
    HASH_ITER(hh, (__dict__)->_elements, __el__, pTmp##__dict__##__el__)



/**
 *  Dictionary 就像 Obj-C 中的 NSDictionary .
 *
 *  @note 只有对象的指针 或者它的子类 能往 Dictionary里面插入数据.
 *  @code
 *  // 创建一个dictionary, 返回autorelease object.
 *  Dictionary* pDict = Dictionary::create();
 *
 *  // 插入对象进Dictionary
 *  String* pValue1 = String::create("100");
 *  String* pValue2 = String::create("120");
 *  Integer* pValue3 = Integer::create(200);
 *  pDict->setObject(pValue1, "key1");
 *  pDict->setObject(pValue2, "key2");
 *  pDict->setObject(pValue3, "key3");
 *
 *  // 获取object的key
 *  String* pStr1 = static_cast<String*>(pDict->objectForKey("key1"));
 *  log("{ key1: %s }", pStr1->getCString());
 *  Integer* pInteger = static_cast<Integer*>(pDict->objectForKey("key3"));
 *  log("{ key3: %d }", pInteger->getValue());
 *  @endcode
 *
 */

class CC_DLL __Dictionary : public Ref, public Clonable
{
public:
    /**
     * Dictionary的构造函数.
     * @js NA
     * @lua NA
     */
    __Dictionary();

    /**
     * Dictionary的析构函数
     * @js NA
     * @lua NA
     */
    ~__Dictionary();

    /** 初始化dictionary. 如果初始化成功，返回true . 
     * @js NA
     * @lua NA
     */
    bool init();
    /**
     *  获取Dictionary中元素个数.
     *
     *  @return  元素个数.
     * @js NA
     */
    unsigned int count();

    /**
     *  返回所有元素的 key.
     *
     *  @return  数组包含所有元素的key. 它也是autorelease类型.
     * @js NA
     */
    __Array* allKeys();

    /** 
     *  获取根据指定对象条件下的所有key.
     *  @warning  使用 '==' 比较两个对象
     *  @return  数组 包含指定条件下的所有key对应的对象. 它也是autorelease object.
     * @js NA
     */
    __Array* allKeysForObject(Ref* object);

    /**
     *  根据这个特定的string key，获取所有的object.
     *
     *  @note 这个 dictionary 需要使用string类型的key. 如果使用integer, 可能引发断言.
     *  @param key  用于搜索的string类型的key.
     *  @return 这个 object必须匹配 key. 你需要强制转换为你知道的那个类型.
     *  @code
     *     // 假设这个元素是 String* pointers. 转换代码如下.
     *     String* pStr = static_cast<String*>(pDict->objectForKey("key1"));
     *     // Do something about pStr.
     *     // 如果你不知道这个对象的类型, 最好使用 dynamic_cast<SomeType*>去检查它.
     *     String* pStr2 = dynamic_cast<String*>(pDict->objectForKey("key1"));
     *     if (pStr2 != NULL) {
     *          // Do something about pStr2
     *     }
     *  @endcode
     *  @see objectForKey(intptr_t)
     * @js NA
     */
    Ref* objectForKey(const std::string& key);
    
    /**
     *  根据特殊的integer key获取object.
     *
     *  @note 这个dictionary 需要使用integer作为key. 如果是加入string类型的key, 将会发生断言.
     *  @param key  用于搜索的 integer key.
     *  @return 这个object 匹配 key.
     *  @see objectForKey(const std::string&)
     * @js NA
     */
    Ref* objectForKey(intptr_t key);
    
    /** 根据特定的string key，获取值.
     *
     *  @note 小心使用这个函数由于它假设这个dictionary里面的对象是__String pointer.
     *  @param key  用于搜索的 string key
     *  @return 返回一个String实例.
     *          如果没被找到或者这个string不存在，将返回空.
     *  @see valueForKey(intptr_t)
     *  @js NA
     */
    const __String* valueForKey(const std::string& key);
    
    /** 根据特定的integer key获取值.
     *
     *  @note 小心使用这个函数由于它假设这个dictionary里面的对象是__String pointer.
     *  @param key  用于搜索的 string key.
     *  @return 返回一个String实例.
     *          如果没被找到或者这个string不存在，将返回空.
     *  @see valueForKey(intptr_t)
     *  @js NA
     */
    const __String* valueForKey(intptr_t key);

    /** 插入一个对象进dictionary, 匹配插入特定的string key.
     *
     *  @note 当这个方法首次调用时, 这个key将被设置为string类型.
     *       这之后你不能使用 setObject 设置integer key.
     *        如果Dictionary包含了你传递的key, 匹配这个key的对象将被释放，从这个dictionary   里移除.然后新的对象将被插入。
     *
     *  @param pObject  被插入的对象.
     *  @param key      用于搜索的string key.
     *  @see setObject(Ref*, intptr_t)
     * @js NA
     */
    void setObject(Ref* pObject, const std::string& key);
    
    /** 插入一个对象进dictionary, 用特定的string key匹配它.
     *
     *  @note 当这个方法首次被调用时, 这个key的类型将被设置为string类型.
     *       这之后你不能setObject为integer类型.
     *        如果dictionary中已经存在了这个key, 这个key所对应的对象将被释放和移除.
     *        新的对象将会插入.
     *  @param pObject  被插入的对象.
     *  @param key      用于搜索的string key.
     *  @see setObject(Ref*, const std::string&)
     *  @js NA
     */
    void setObject(Ref* pObject, intptr_t key);

    /** 
     *  根据特定的string key移除对应的对象.
     *
     *  @param key  用于搜索的string key.
     *  @see removeObjectForKey(intptr_t), removeObjectsForKeys(__Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectForKey(const std::string& key);
    
    /**
     *  根据特定的integer key，移除对象的对象.
     *
     *  @param key  用于搜索的integer key.
     *  @see removeObjectForKey(const std::string&), removeObjectsForKeys(__Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectForKey(intptr_t key);
    
    /**
     *  根据array中得keys移除对应的所有对象.
     *
     *  @param pKeyArray  包含这个keys的数组里的对象都会被移除.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectsForKeys(__Array* pKey__Array);
    
    /**
     *  根据某个元素移除对应的对象
     *
     *  @param pElement  这个element对应的对象将被移除.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(__Array*), removeAllObjects().
     * @js NA
     * @lua NA
     */
    void removeObjectForElememt(DictElement* pElement);
    
    /**
     *  移除dictionary中所有对象.
     *
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(__Array*), removeObjectForElememt(DictElement*).
     * @js NA
     */
    void removeAllObjects();
    
    /**
     *  返回dictionary中随机的一个对象.
     *
     *  @return The random object. 
     *  @see objectForKey(intptr_t), objectForKey(const std::string&)
     *  @js NA
     *  @lua NA
     */
    Ref* randomObject();
    
    /**
     *  创建一个dictionary.
     *  @return 返回一个autorelease dictionary.
     *  @see createWithDictionary(Dictionary*), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static __Dictionary* create();

    /**
     *  根据现存的dictionary创建一个新的dictionary.
     *
     *  @param srcDict 现存的dictionary.
     *  @return 一个autorelease类型的dictionary.
     *  @see create(), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static __Dictionary* createWithDictionary(__Dictionary* srcDict);
    
    /**
     *  根据plist文件创建一个dictionary.
     *  @param  pFileName  plist文件的名字.
     *  @return 一个autorelease类型的dictionary.
     *  @see create(), createWithDictionary(Dictionary*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static __Dictionary* createWithContentsOfFile(const char *pFileName);
    
    /**
     *  往plist文件中写入一个dictionary.
     *  @param fullPath plist文件的全路径. 通过 getWritablePath()可以获取可写的路径
     *  @return true 表示创建成功, false 表示创建失败
     *  @js NA
     *  @lua NA
     */
    bool writeToFile(const char *fullPath);
     
    /**
     *  根据plist文件创建一个dictionary.
     *  
     *  @note 返回值不是autorelease类型.
     *        这能确保在新的线程中不适用autorelease pool.
     *        因此, 你需要管理好返回对象的生命周期.
     *        这意味着你不需要它时, CC_SAFE_RELEASE 需要被调用.
     *
     *  @param  pFileName  plist 文件.
     *  @return 不是autorelease类型的dictionary.
     *  @js NA
     *  @lua NA
     */
    static __Dictionary* createWithContentsOfFileThreadSafe(const char *pFileName);

    /* 重载方法
     *  @js NA
     *  @lua NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual __Dictionary* clone() const;
    
private:
    /** 
     *  对于内部使用, 通过调用setObject.
     */
    void setObjectUnSafe(Ref* pObject, const std::string& key);
    void setObjectUnSafe(Ref* pObject, const intptr_t key);
    
public:
    /**
     *  dictionary中得所有元素.
     * 
     *  @note 对于内部使用, 我们需要把这个成员变量声明为public，因为它在UT_HASH中使用.
     */
    DictElement* _elements;
private:
    
    /** dictionary支持的类型, 它已经声明了当setObject被调用时. */
    enum DictType
    {
        kDictUnknown = 0,
        kDictStr,
        kDictInt
    };
    
    /** 
     *  dictionary类型, 默认分配为kDictUnknown类型.
     */
    DictType _dictType;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCDICTIONARY_H__ */
