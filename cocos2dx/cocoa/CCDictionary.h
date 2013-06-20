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

#ifndef __CCDICTIONARY_H__
#define __CCDICTIONARY_H__

#include "support/data_support/uthash.h"
#include "CCObject.h"
#include "CCArray.h"
#include "CCString.h"

NS_CC_BEGIN

class Dictionary;

/**
 * @addtogroup data_structures
 * @{
 */


/**
 *  DictElement is used for traversing Dictionary.
 *
 *  A DictElement is one element of Dictionary, it contains two properties, key and object.
 *  Its key has two different type (integer and string).
 *
 *  @note The key type is unique, all the elements in Dictionary has the same key type(integer or string).
 *  @code
 *  DictElement* pElement;
 *  CCDICT_FOREACH(dict, pElement)
 *  {
 *      const char*key = pElement->getStrKey();
 *      // You certainly know the type of value, so we assume that it's a Sprite.
 *      Sprite* pSprite = (Sprite*)pElement->getObject();
 *      // ......
 *  }
 *  @endcode
 *
 */
class CC_DLL DictElement
{
private:
    /**
     *  Constructor of DictElement. It's only for internal usage. Dictionary is its friend class.
     *  
     *  @param  pszKey    The string key of this element.
     *  @param  pObject   The object of this element.
     */
    DictElement(const char* pszKey, Object* pObject);

    /**
     *  Constructor of DictElement. It's only for internal usage. Dictionary is its friend class.
     *
     *  @param  iKey    The integer key of this element.
     *  @param  pObject   The object of this element.
     */
    DictElement(intptr_t iKey, Object* pObject);
    
public:
    /**
     *  The destructor of DictElement.
     */
    ~DictElement();

    // Inline functions need to be implemented in header file on Android.
    
    /**
     * Get the string key of this element.
     * @note    This method assumes you know the key type in the element. 
     *          If the element's key type is integer, invoking this method will cause an assert.
     *
     * @return  The string key of this element.
     */
    inline const char* getStrKey() const
    {
        CCAssert(_strKey[0] != '\0', "Should not call this function for integer dictionary");
        return _strKey;
    }

    /**
     * Get the integer key of this element.
     * @note    This method assumes you know the key type in the element.
     *          If the element's key type is string, invoking this method will cause an assert.
     *
     * @return  The integer key of this element.
     */
    inline intptr_t getIntKey() const
    {
        CCAssert(_strKey[0] == '\0', "Should not call this function for string dictionary");
        return _intKey;
    }
    
    /**
     * Get the object of this element.
     *
     * @return  The object of this element.
     */
    inline Object* getObject() const { return _object; }

private:
    // The max length of string key.
    #define   MAX_KEY_LEN   256
    // char array is needed for HASH_ADD_STR in UT_HASH.
    // So it's a pain that all elements will allocate 256 bytes for this array.
    char      _strKey[MAX_KEY_LEN];     // hash key of string type
    intptr_t  _intKey;       // hash key of integer type
    Object* _object;    // hash value
public:
    UT_hash_handle hh;      // makes this class hashable
    friend class Dictionary; // declare Dictionary as friend class
};

/** The macro for traversing dictionary
 *  
 *  @note It's faster than getting all keys and traversing keys to get objects by objectForKey.
 *        It's also safe to remove elements while traversing.
 */
#define CCDICT_FOREACH(__dict__, __el__) \
    DictElement* pTmp##__dict__##__el__ = NULL; \
    if (__dict__) \
    HASH_ITER(hh, (__dict__)->_elements, __el__, pTmp##__dict__##__el__)



/**
 *  Dictionary is a class like NSDictionary in Obj-C .
 *
 *  @note Only the pointer of Object or its subclass can be inserted to Dictionary.
 *  @code
 *  // Create a dictionary, return an autorelease object.
 *  Dictionary* pDict = Dictionary::create();
 *
 *  // Insert objects to dictionary
 *  String* pValue1 = String::create("100");
 *  String* pValue2 = String::create("120");
 *  Integer* pValue3 = Integer::create(200);
 *  pDict->setObject(pValue1, "key1");
 *  pDict->setObject(pValue2, "key2");
 *  pDict->setObject(pValue3, "key3");
 *
 *  // Get the object for key
 *  String* pStr1 = (String*)pDict->objectForKey("key1");
 *  CCLog("{ key1: %s }", pStr1->getCString());
 *  Integer* pInteger = (Integer*)pDict->objectForKey("key3");
 *  CCLog("{ key3: %d }", pInteger->getValue());
 *  @endcode
 *
 */

class CC_DLL Dictionary : public Object
{
public:
    /** 
     * The constructor of Dictionary.
     */
    Dictionary();

    /**
     * The destructor of Dictionary
     */
    ~Dictionary();

    /**
     *  Get the count of elements in Dictionary.
     *
     *  @return  The count of elements.
     */
    unsigned int count();

    /**
     *  Return all keys of elements.
     *
     *  @return  The array contains all keys of elements. It's an autorelease object yet.
     */
    Array* allKeys();

    /** 
     *  Get all keys according to the specified object.
     *  @warning  We use '==' to compare two objects
     *  @return   The array contains all keys for the specified object. It's an autorelease object yet.
     */
    Array* allKeysForObject(Object* object);

    /**
     *  Get the object according to the specified string key.
     *
     *  @note The dictionary needs to use string as key. If integer is passed, an assert will appear.
     *  @param key  The string key for searching.
     *  @return The object matches the key. You need to force convert it to the type you know.
     *  @code
     *     // Assume that the elements are String* pointers. Convert it by following code.
     *     String* pStr = (String*)pDict->objectForKey("key1");
     *     // Do something about pStr.
     *     // If you don't know the object type, properly you need to use dynamic_cast<SomeType*> to check it.
     *     String* pStr2 = dynamic_cast<String*>(pDict->objectForKey("key1"));
     *     if (pStr2 != NULL) {
     *          // Do something about pStr2
     *     }
     *  @endcode
     *  @see objectForKey(intptr_t)
     */
    Object* objectForKey(const std::string& key);
    
    /**
     *  Get the object according to the specified integer key.
     *
     *  @note The dictionary needs to use integer as key. If string is passed, an assert will appear.
     *  @param key  The integer key for searching.
     *  @return The object matches the key.
     *  @see objectForKey(const std::string&)
     */
    Object* objectForKey(intptr_t key);
    
    /** Get the value according to the specified string key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are String pointer.
     *  @param key  The string key for searching
     *  @return An instance of String.
     *          It will return an empty string if the objects aren't String pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     */
    const String* valueForKey(const std::string& key);
    
    /** Get the value according to the specified integer key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are String pointer.
     *  @param key  The string key for searching.
     *  @return An instance of String.
     *          It will return an empty string if the objects aren't String pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     */
    const String* valueForKey(intptr_t key);

    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Whe the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(Object*, intptr_t)
     */
    void setObject(Object* pObject, const std::string& key);
    
    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Then the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(Object*, const std::string&)
     */
    void setObject(Object* pObject, intptr_t key);

    /** 
     *  Remove an object by the specified string key.
     *
     *  @param key  The string key for searching.
     *  @see removeObjectForKey(intptr_t), removeObjectsForKeys(Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     */
    void removeObjectForKey(const std::string& key);
    
    /**
     *  Remove an object by the specified integer key.
     *
     *  @param key  The integer key for searching.
     *  @see removeObjectForKey(const std::string&), removeObjectsForKeys(Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     */
    void removeObjectForKey(intptr_t key);
    
    /**
     *  Remove objects by an array of keys.
     *
     *  @param pKeyArray  The array contains keys to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     */
    void removeObjectsForKeys(Array* pKeyArray);
    
    /**
     *  Remove an object by an element.
     *
     *  @param pElement  The element need to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(Array*), removeAllObjects().
     */
    void removeObjectForElememt(DictElement* pElement);
    
    /**
     *  Remove all objects in the dictionary.
     *
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(Array*), removeObjectForElememt(DictElement*).
     */
    void removeAllObjects();

    /// @{
    /// @name Function override
    /**
     *  This function is used for deepcopy elements from source dictionary to destination dictionary.
     *  You shouldn't invoke this function manually since it's called by Object::copy.
     */
    virtual Object* copyWithZone(Zone* pZone);
    /// @}
    
    /**
     *  Return a random object in the dictionary.
     *
     *  @return The random object. 
     *  @see objectForKey(intptr_t), objectForKey(const std::string&)
     */
    Object* randomObject();
    
    /**
     *  Create a dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see createWithDictionary(Dictionary*), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     */
    static Dictionary* create();

    /**
     *  Create a dictionary with an existing dictionary.
     *
     *  @param srcDict The exist dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see create(), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     */
    static Dictionary* createWithDictionary(Dictionary* srcDict);
    
    /**
     *  Create a dictionary with a plist file.
     *  @param  pFileName  The name of the plist file.
     *  @return A dictionary which is an autorelease object.
     *  @see create(), createWithDictionary(Dictionary*), createWithContentsOfFileThreadSafe(const char*).
     */
    static Dictionary* createWithContentsOfFile(const char *pFileName);
    
    /**
     *  Write a dictionary to a plist file.
     *  @param fullPath The full path of the plist file. You can get writeable path by getWritablePath()
     *  @return true if successed, false if failed
     */
    bool writeToFile(const char *fullPath);
     
    /**
     *  Create a dictionary with a plist file.
     *  
     *  @note the return object isn't an autorelease object.
     *        This can make sure not using autorelease pool in a new thread.
     *        Therefore, you need to manage the lifecycle of the return object.
     *        It means that when you don't need it, CC_SAFE_RELEASE needs to be invoked.
     *
     *  @param  pFileName  The name of the plist file.
     *  @return A dictionary which isn't an autorelease object.
     */
    static Dictionary* createWithContentsOfFileThreadSafe(const char *pFileName);

    /* override functions */
    virtual void acceptVisitor(DataVisitor &visitor);

private:
    /** 
     *  For internal usage, invoked by setObject.
     */
    void setObjectUnSafe(Object* pObject, const std::string& key);
    void setObjectUnSafe(Object* pObject, const intptr_t key);
    
public:
    /**
     *  All the elements in dictionary.
     * 
     *  @note For internal usage, we need to declare this member variable as public since it's used in UT_HASH.
     */
    DictElement* _elements;
private:
    
    /** The support type of dictionary, it's confirmed when setObject is invoked. */
    enum DictType
    {
        kDictUnknown = 0,
        kDictStr,
        kDictInt
    };
    
    /** 
     *  The type of dictionary, it's assigned to kDictUnknown by default.
     */
    DictType _dictType;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCDICTIONARY_H__ */
