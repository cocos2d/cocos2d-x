#include "CCDictionary.h"
#include "CCString.h"
#include "CCInteger.h"

using namespace std;

NS_CC_BEGIN

CCDictionary::CCDictionary()
: m_pElements(NULL)
, m_eDictType(kCCDictUnknown)
, m_eOldDictType(kCCDictUnknown)
{

}

CCDictionary::~CCDictionary()
{
    removeAllObjects();
}

unsigned int CCDictionary::count()
{
    return HASH_COUNT(m_pElements);
}

CCArray* CCDictionary::allKeys()
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    CCArray* pArray = CCArray::arrayWithCapacity(iKeyCount);

    CCDictElement *pElement, *tmp;
    if (m_eDictType == kCCDictStr)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            CCString* pOneKey = new CCString(pElement->m_szKey);
            pOneKey->autorelease();
            pArray->addObject(pOneKey);
        }
    }
    else if (m_eDictType == kCCDictInt)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            CCInteger* pOneKey = new CCInteger(pElement->m_iKey);
            pOneKey->autorelease();
            pArray->addObject(pOneKey);
        }
    }
    
    return pArray;
}

CCArray* CCDictionary::allKeysForObject(CCObject* object)
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    CCArray* pArray = CCArray::array();

    CCDictElement *pElement, *tmp;

    if (m_eDictType == kCCDictStr)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            if (object == pElement->m_pObject)
            {
                CCString* pOneKey = new CCString(pElement->m_szKey);
                pOneKey->autorelease();
                pArray->addObject(pOneKey);
            }
        }
    }
    else if (m_eDictType == kCCDictInt)
    {
        HASH_ITER(hh, m_pElements, pElement, tmp) 
        {
            if (object == pElement->m_pObject)
            {
                CCInteger* pOneKey = new CCInteger(pElement->m_iKey);
                pOneKey->autorelease();
                pArray->addObject(pOneKey);
            }
        }
    }
    return pArray;
}

CCObject* CCDictionary::objectForKey(const std::string& key)
{
    if (m_eDictType == kCCDictUnknown && m_eDictType == kCCDictUnknown) return NULL;
    CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as key.");

    CCObject* pRetObject = NULL;
    CCDictElement *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->m_pObject;
    }
    return pRetObject;
}

CCObject* CCDictionary::objectForKey(int key)
{
    if (m_eDictType == kCCDictUnknown && m_eDictType == kCCDictUnknown) return NULL;
    CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as key.");

    CCObject* pRetObject = NULL;
    CCDictElement *pElement = NULL;
    HASH_FIND_INT(m_pElements, &key, pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->m_pObject;
    }
    return pRetObject;
}

const CCString* CCDictionary::valueForKey(const std::string& key)
{
    CCString* pStr = (CCString*)objectForKey(key);
    if (pStr == NULL)
    {
        pStr = CCString::stringWithCString("");
    }
    return pStr;
}

const CCString* CCDictionary::valueForKey(int key)
{
    CCString* pStr = (CCString*)objectForKey(key);
    if (pStr == NULL)
    {
        pStr = CCString::stringWithCString("");
    }
    return pStr;
}

void CCDictionary::setObject(CCObject* pObject, const std::string& key)
{
    CCAssert(key.length() > 0 && pObject != NULL, "Invalid Argument!");
    if (m_eOldDictType == kCCDictUnknown)
    {
        m_eOldDictType = kCCDictStr;
    }
    m_eDictType = kCCDictStr;
    CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use string as key.");

    CCDictElement *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->m_pObject != pObject)
    {
        CCObject* pTmpObj = pElement->m_pObject;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }
}

void CCDictionary::setObject(CCObject* pObject, int key)
{
    CCAssert(pObject != NULL, "Invalid Argument!");
    if (m_eOldDictType == kCCDictUnknown)
    {
        m_eOldDictType = kCCDictInt;
    }
    m_eDictType = kCCDictInt;
    CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use integer as key.");

    CCDictElement *pElement = NULL;
    HASH_FIND_INT(m_pElements, &key, pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->m_pObject != pObject)
    {
        CCObject* pTmpObj = pElement->m_pObject;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }

}

void CCDictionary::removeObjectForKey(const std::string& key)
{
    if (m_eOldDictType == kCCDictUnknown) 
    {
        return;
    }
    CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as its key");
    CCAssert(key.length() > 0, "Invalid Argument!");
    CCDictElement *pElement = NULL;
    HASH_FIND_STR(m_pElements, key.c_str(), pElement);
    removeObjectForElememt(pElement);
}

void CCDictionary::removeObjectForKey(int key)
{
    if (m_eOldDictType == kCCDictUnknown) 
    {
        return;
    }
    CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as its key");
    CCDictElement *pElement = NULL;
    HASH_FIND_INT(m_pElements, &key, pElement);
    removeObjectForElememt(pElement);
}

void CCDictionary::setObjectUnSafe(CCObject* pObject, const std::string& key)
{
    pObject->retain();
    CCDictElement* pElement = new CCDictElement(key.c_str(), pObject);
    HASH_ADD_STR(m_pElements, m_szKey, pElement);
}

void CCDictionary::setObjectUnSafe(CCObject* pObject, const int key)
{
    pObject->retain();
    CCDictElement* pElement = new CCDictElement(key, pObject);
    HASH_ADD_INT(m_pElements, m_iKey, pElement);
}

void CCDictionary::removeObjectsForKeys(CCArray* pKeyArray)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(pKeyArray, pObj)
    {
        CCString* pStr = (CCString*)pObj;
        removeObjectForKey(pStr->getCString());
    }
}

void CCDictionary::removeObjectForElememt(CCDictElement* pElement)
{
    if (pElement != NULL)
    {
        HASH_DEL(m_pElements, pElement);
        pElement->m_pObject->release();
        CC_SAFE_DELETE(pElement);
    }
}

void CCDictionary::removeAllObjects()
{
    CCDictElement *pElement, *tmp;
    HASH_ITER(hh, m_pElements, pElement, tmp) 
    {
        HASH_DEL(m_pElements, pElement);
        pElement->m_pObject->release();
        CC_SAFE_DELETE(pElement);
    }
}

CCObject* CCDictionary::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCDirctionary should not be inherited.");
    CCDictionary* pNewDict = new CCDictionary();

    CCDictElement* pElement = NULL;
    if (m_eDictType == kCCDictInt)
    {
        CCDICT_FOREACH(this, pElement)
        {
            pNewDict->setObject(pElement->getObject()->copy()->autorelease(), pElement->getIntKey());
        }
    }
    else if (m_eDictType == kCCDictStr)
    {
        CCDICT_FOREACH(this, pElement)
        {
            pNewDict->setObject(pElement->getObject()->copy()->autorelease(), pElement->getStrKey());
        }
    }

    return pNewDict;
}

CCDictionary* CCDictionary::dictionary()
{
    CCDictionary* pRet = new CCDictionary();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

CCDictionary* CCDictionary::dictionaryWithDictionary(CCDictionary* srcDict)
{
    CCDictionary* pNewDict = (CCDictionary*)srcDict->copy();
    pNewDict->autorelease();
    return pNewDict;
}

extern CCDictionary* ccFileUtils_dictionaryWithContentsOfFileThreadSafe(const char *pFileName);

CCDictionary* CCDictionary::dictionaryWithContentsOfFileThreadSafe(const char *pFileName)
{
    return ccFileUtils_dictionaryWithContentsOfFileThreadSafe(pFileName);
}

CCDictionary* CCDictionary::dictionaryWithContentsOfFile(const char *pFileName)
{
    CCDictionary* pRet = dictionaryWithContentsOfFileThreadSafe(pFileName);
    pRet->autorelease();
    return pRet;
}

NS_CC_END
