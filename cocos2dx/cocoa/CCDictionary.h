/****************************************************************************
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

#ifndef __CCDICTIONARY_H__
#define __CCDICTIONARY_H__

#include "support/data_support/uthash.h"
#include "CCObject.h"
#include "CCArray.h"
#include "CCString.h"

NS_CC_BEGIN

class CCDictionary;

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCDictElement
{
    #define MAX_KEY_LEN  256
public:
    CCDictElement(const char* pszKey, CCObject* pObject)
    {
        init();
        m_pObject = pObject;

        const char* pStart = pszKey;
        
        int len = strlen(pszKey);
        if (len > MAX_KEY_LEN )
        {
            char* pEnd = (char*)&pszKey[len-1];
            pStart = pEnd - (MAX_KEY_LEN-1);
        }

        strcpy(m_szKey, pStart);
    }

    CCDictElement(intptr_t iKey, CCObject* pObject)
    {
        init();
        m_iKey = iKey;
        m_pObject = pObject;
    }

    inline const char* getStrKey() const
    {
        CCAssert(m_szKey[0] != '\0', "Should not call this function for integer dictionary");
        return m_szKey;
    }

    inline intptr_t getIntKey() const 
    {
        CCAssert(m_szKey[0] == '\0', "Should not call this function for string dictionary");
        return m_iKey;
    }

    inline CCObject* getObject() const
    {
        return m_pObject;
    }

private:
    inline void init()
    {
        m_iKey = 0;
        m_pObject = NULL;
        memset(m_szKey, 0, sizeof(m_szKey));
        memset(&hh, 0, sizeof(hh));
    }

private:
    char m_szKey[MAX_KEY_LEN+1];  /** hash key of string type*/
    intptr_t  m_iKey;   /** hash key of integer type */
    CCObject* m_pObject;/** hash value */
public:
    UT_hash_handle hh; /* makes this class hashable */
    friend class CCDictionary;
};


#define CCDICT_FOREACH(__dict__, __el__) \
    CCDictElement* pTmp##__dict__##__el__ = NULL; \
    HASH_ITER(hh, (__dict__)->m_pElements, __el__, pTmp##__dict__##__el__)


class CC_DLL CCDictionary : public CCObject
{
public:
    CCDictionary();
    ~CCDictionary();

    /// return the number of items
    unsigned int count();

    /// return all the keys
    CCArray* allKeys();

    /** @warning : We use '==' to compare two objects*/
    CCArray* allKeysForObject(CCObject* object);

    CCObject* objectForKey(const std::string& key);
    CCObject* objectForKey(int key);
    const CCString* valueForKey(const std::string& key);
    const CCString* valueForKey(int key);


    void setObject(CCObject* pObject, const std::string& key);
    void setObject(CCObject* pObject, int key);

    void removeObjectForKey(const std::string& key);
    void removeObjectForKey(int key);
    void removeObjectsForKeys(CCArray* pKeyArray);
    void removeObjectForElememt(CCDictElement* pElement);
    void removeAllObjects();

    virtual CCObject* copyWithZone(CCZone* pZone);

    /* static functions */
    //@deprecated: Please use create() instead. This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCDictionary* dictionary();

    //@deprecated: Please use createWithDictionary(CCDictionary*) instead. This interface will be deprecated sooner or later.
    CC_DEPRECATED_ATTRIBUTE static CCDictionary* dictionaryWithDictionary(CCDictionary* srcDict);
    
    /**
    @brief   Generate a CCDictionary pointer by file
    @param   pFileName  The file name of *.plist file
    @return  The CCDictionary pointer generated from the file
    @deprecated: Please use createWithContentsOfFile(const char*) instead. This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCDictionary* dictionaryWithContentsOfFile(const char *pFileName);

    /*
    @brief The same meaning as dictionaryWithContentsOfFile(), but it doesn't call autorelease, so the
           invoker should call release().
    @deprecated: Please use createWithContentsOfFileThreadSafe(const char*) instead. This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCDictionary* dictionaryWithContentsOfFileThreadSafe(const char *pFileName);

    static CCDictionary* create();

    static CCDictionary* createWithDictionary(CCDictionary* srcDict);
    /**
    @brief   Generate a CCDictionary pointer by file
    @param   pFileName  The file name of *.plist file
    @return  The CCDictionary pointer generated from the file
    */
    static CCDictionary* createWithContentsOfFile(const char *pFileName);

    /*
    @brief The same meaning as dictionaryWithContentsOfFile(), but it doesn't call autorelease, so the
           invoker should call release().
    */
    static CCDictionary* createWithContentsOfFileThreadSafe(const char *pFileName);

private:
    void setObjectUnSafe(CCObject* pObject, const std::string& key);
    void setObjectUnSafe(CCObject* pObject, const int key);
    
public:
    CCDictElement* m_pElements;
private:
    
    enum CCDictType
    {
        kCCDictUnknown = 0,
        kCCDictStr,
        kCCDictInt
    };
    CCDictType m_eDictType;
    CCDictType m_eOldDictType;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCDICTIONARY_H__ */
