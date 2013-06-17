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

#include "CCDictionary.h"
#include "CCString.h"
#include "CCInteger.h"
#include "platform/CCFileUtils.h"

using namespace std;

NS_CC_BEGIN

// -----------------------------------------------------------------------
// CCDictElement

CCDictElement::CCDictElement(const char* pszKey, CCObject* pObject)
{
    CCAssert(pszKey && strlen(pszKey) > 0, "Invalid key value.");
    _intKey = 0;
    const char* pStart = pszKey;
    
    int len = strlen(pszKey);
    if (len > MAX_KEY_LEN )
    {
        char* pEnd = (char*)&pszKey[len-1];
        pStart = pEnd - (MAX_KEY_LEN-1);
    }
    
    strcpy(_strKey, pStart);
    
    _object = pObject;
    memset(&hh, 0, sizeof(hh));
}

CCDictElement::CCDictElement(intptr_t iKey, CCObject* pObject)
{
    _strKey[0] = '\0';
    _intKey = iKey;
    _object = pObject;
    memset(&hh, 0, sizeof(hh));
}

CCDictElement::~CCDictElement()
{

}

// -----------------------------------------------------------------------
// CCDictionary

CCDictionary::CCDictionary()
: _elements(NULL)
, _dictType(kCCDictUnknown)
{

}

CCDictionary::~CCDictionary()
{
    removeAllObjects();
}

unsigned int CCDictionary::count()
{
    return HASH_COUNT(_elements);
}

CCArray* CCDictionary::allKeys()
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;

    CCArray* pArray = CCArray::createWithCapacity(iKeyCount);

    CCDictElement *pElement, *tmp;
    if (_dictType == kCCDictStr)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            CCString* pOneKey = new CCString(pElement->_strKey);
            pArray->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    else if (_dictType == kCCDictInt)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            CCInteger* pOneKey = new CCInteger(pElement->_intKey);
            pArray->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    
    return pArray;
}

CCArray* CCDictionary::allKeysForObject(CCObject* object)
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    CCArray* pArray = CCArray::create();

    CCDictElement *pElement, *tmp;

    if (_dictType == kCCDictStr)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            if (object == pElement->_object)
            {
                CCString* pOneKey = new CCString(pElement->_strKey);
                pArray->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    else if (_dictType == kCCDictInt)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            if (object == pElement->_object)
            {
                CCInteger* pOneKey = new CCInteger(pElement->_intKey);
                pArray->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    return pArray;
}

CCObject* CCDictionary::objectForKey(const std::string& key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (_dictType == kCCDictUnknown) return NULL;
    // CCDictionary only supports one kind of key, string or integer.
    // This method uses string as key, therefore we should make sure that the key type of this CCDictionary is string.
    CCAssert(_dictType == kCCDictStr, "this dictionary does not use string as key.");

    CCObject* pRetObject = NULL;
    CCDictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->_object;
    }
    return pRetObject;
}

CCObject* CCDictionary::objectForKey(intptr_t key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (_dictType == kCCDictUnknown) return NULL;
    // CCDictionary only supports one kind of key, string or integer.
    // This method uses integer as key, therefore we should make sure that the key type of this CCDictionary is integer.
    CCAssert(_dictType == kCCDictInt, "this dictionary does not use integer as key.");

    CCObject* pRetObject = NULL;
    CCDictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->_object;
    }
    return pRetObject;
}

const CCString* CCDictionary::valueForKey(const std::string& key)
{
    CCString* pStr = dynamic_cast<CCString*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = CCString::create("");
    }
    return pStr;
}

const CCString* CCDictionary::valueForKey(intptr_t key)
{
    CCString* pStr = dynamic_cast<CCString*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = CCString::create("");
    }
    return pStr;
}

void CCDictionary::setObject(CCObject* pObject, const std::string& key)
{
    CCAssert(key.length() > 0 && pObject != NULL, "Invalid Argument!");
    if (_dictType == kCCDictUnknown)
    {
        _dictType = kCCDictStr;
    }

    CCAssert(_dictType == kCCDictStr, "this dictionary doesn't use string as key.");

    CCDictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->_object != pObject)
    {
        CCObject* pTmpObj = pElement->_object;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }
}

void CCDictionary::setObject(CCObject* pObject, intptr_t key)
{
    CCAssert(pObject != NULL, "Invalid Argument!");
    if (_dictType == kCCDictUnknown)
    {
        _dictType = kCCDictInt;
    }

    CCAssert(_dictType == kCCDictInt, "this dictionary doesn't use integer as key.");

    CCDictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->_object != pObject)
    {
        CCObject* pTmpObj = pElement->_object;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }

}

void CCDictionary::removeObjectForKey(const std::string& key)
{
    if (_dictType == kCCDictUnknown)
    {
        return;
    }
    
    CCAssert(_dictType == kCCDictStr, "this dictionary doesn't use string as its key");
    CCAssert(key.length() > 0, "Invalid Argument!");
    CCDictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    removeObjectForElememt(pElement);
}

void CCDictionary::removeObjectForKey(intptr_t key)
{
    if (_dictType == kCCDictUnknown)
    {
        return;
    }
    
    CCAssert(_dictType == kCCDictInt, "this dictionary doesn't use integer as its key");
    CCDictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    removeObjectForElememt(pElement);
}

void CCDictionary::setObjectUnSafe(CCObject* pObject, const std::string& key)
{
    pObject->retain();
    CCDictElement* pElement = new CCDictElement(key.c_str(), pObject);
    HASH_ADD_STR(_elements, _strKey, pElement);
}

void CCDictionary::setObjectUnSafe(CCObject* pObject, const intptr_t key)
{
    pObject->retain();
    CCDictElement* pElement = new CCDictElement(key, pObject);
    HASH_ADD_PTR(_elements, _intKey, pElement);
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
        HASH_DEL(_elements, pElement);
        pElement->_object->release();
        CC_SAFE_DELETE(pElement);
    }
}

void CCDictionary::removeAllObjects()
{
    CCDictElement *pElement, *tmp;
    HASH_ITER(hh, _elements, pElement, tmp) 
    {
        HASH_DEL(_elements, pElement);
        pElement->_object->release();
        CC_SAFE_DELETE(pElement);

    }
}

CCObject* CCDictionary::copyWithZone(CCZone* pZone)
{
    CCAssert(pZone == NULL, "CCDictionary should not be inherited.");
    CCDictionary* pNewDict = new CCDictionary();

    CCDictElement* pElement = NULL;
    CCObject* pTmpObj = NULL;

    if (_dictType == kCCDictInt)
    {
        CCDICT_FOREACH(this, pElement)
        {
            pTmpObj = pElement->getObject()->copy();
            pNewDict->setObject(pTmpObj, pElement->getIntKey());
            pTmpObj->release();
        }
    }
    else if (_dictType == kCCDictStr)
    {
        CCDICT_FOREACH(this, pElement)
        {
            pTmpObj = pElement->getObject()->copy();
            pNewDict->setObject(pTmpObj, pElement->getStrKey());
            pTmpObj->release();
        }
    }

    return pNewDict;
}

CCObject* CCDictionary::randomObject()
{
    if (_dictType == kCCDictUnknown)
    {
        return NULL;
    }
    
    CCObject* key = allKeys()->randomObject();
    
    if (_dictType == kCCDictInt)
    {
        return objectForKey(((CCInteger*)key)->getValue());
    }
    else if (_dictType == kCCDictStr)
    {
        return objectForKey(((CCString*)key)->getCString());
    }
    else
    {
        return NULL;
    }
}

CCDictionary* CCDictionary::create()
{
    CCDictionary* pRet = new CCDictionary();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

CCDictionary* CCDictionary::createWithDictionary(CCDictionary* srcDict)
{
    CCDictionary* pNewDict = (CCDictionary*)srcDict->copy();
    pNewDict->autorelease();
    return pNewDict;
}

CCDictionary* CCDictionary::createWithContentsOfFileThreadSafe(const char *pFileName)
{
    return CCFileUtils::sharedFileUtils()->createCCDictionaryWithContentsOfFile(pFileName);
}

void CCDictionary::acceptVisitor(CCDataVisitor &visitor)
{
    return visitor.visit(this);
}

CCDictionary* CCDictionary::createWithContentsOfFile(const char *pFileName)
{
    CCDictionary* pRet = createWithContentsOfFileThreadSafe(pFileName);
    pRet->autorelease();
    return pRet;
}

bool CCDictionary::writeToFile(const char *fullPath)
{
    return CCFileUtils::sharedFileUtils()->writeToFile(this, fullPath);
}


NS_CC_END
