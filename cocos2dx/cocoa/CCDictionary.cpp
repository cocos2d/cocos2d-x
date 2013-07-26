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
// DictElement

DictElement::DictElement(const char* pszKey, Object* pObject)
{
    CCASSERT(pszKey && strlen(pszKey) > 0, "Invalid key value.");
    _intKey = 0;
    const char* pStart = pszKey;
    
    size_t len = strlen(pszKey);
    if (len > MAX_KEY_LEN )
    {
        char* pEnd = (char*)&pszKey[len-1];
        pStart = pEnd - (MAX_KEY_LEN-1);
    }
    
    strcpy(_strKey, pStart);
    
    _object = pObject;
    memset(&hh, 0, sizeof(hh));
}

DictElement::DictElement(intptr_t iKey, Object* pObject)
{
    _strKey[0] = '\0';
    _intKey = iKey;
    _object = pObject;
    memset(&hh, 0, sizeof(hh));
}

DictElement::~DictElement()
{

}

// -----------------------------------------------------------------------
// Dictionary

Dictionary::Dictionary()
: _elements(NULL)
, _dictType(kDictUnknown)
{

}

Dictionary::~Dictionary()
{
    removeAllObjects();
}

unsigned int Dictionary::count()
{
    return HASH_COUNT(_elements);
}

Array* Dictionary::allKeys()
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;

    Array* pArray = Array::createWithCapacity(iKeyCount);

    DictElement *pElement, *tmp;
    if (_dictType == kDictStr)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            String* pOneKey = new String(pElement->_strKey);
            pArray->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    else if (_dictType == kDictInt)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            Integer* pOneKey = new Integer(pElement->_intKey);
            pArray->addObject(pOneKey);
            CC_SAFE_RELEASE(pOneKey);
        }
    }
    
    return pArray;
}

Array* Dictionary::allKeysForObject(Object* object)
{
    int iKeyCount = this->count();
    if (iKeyCount <= 0) return NULL;
    Array* pArray = Array::create();

    DictElement *pElement, *tmp;

    if (_dictType == kDictStr)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            if (object == pElement->_object)
            {
                String* pOneKey = new String(pElement->_strKey);
                pArray->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    else if (_dictType == kDictInt)
    {
        HASH_ITER(hh, _elements, pElement, tmp) 
        {
            if (object == pElement->_object)
            {
                Integer* pOneKey = new Integer(pElement->_intKey);
                pArray->addObject(pOneKey);
                CC_SAFE_RELEASE(pOneKey);
            }
        }
    }
    return pArray;
}

Object* Dictionary::objectForKey(const std::string& key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (_dictType == kDictUnknown) return NULL;
    // Dictionary only supports one kind of key, string or integer.
    // This method uses string as key, therefore we should make sure that the key type of this Dictionary is string.
    CCASSERT(_dictType == kDictStr, "this dictionary does not use string as key.");

    Object* pRetObject = NULL;
    DictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->_object;
    }
    return pRetObject;
}

Object* Dictionary::objectForKey(intptr_t key)
{
    // if dictionary wasn't initialized, return NULL directly.
    if (_dictType == kDictUnknown) return NULL;
    // Dictionary only supports one kind of key, string or integer.
    // This method uses integer as key, therefore we should make sure that the key type of this Dictionary is integer.
    CCASSERT(_dictType == kDictInt, "this dictionary does not use integer as key.");

    Object* pRetObject = NULL;
    DictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    if (pElement != NULL)
    {
        pRetObject = pElement->_object;
    }
    return pRetObject;
}

const String* Dictionary::valueForKey(const std::string& key)
{
    String* pStr = dynamic_cast<String*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = String::create("");
    }
    return pStr;
}

const String* Dictionary::valueForKey(intptr_t key)
{
    String* pStr = dynamic_cast<String*>(objectForKey(key));
    if (pStr == NULL)
    {
        pStr = String::create("");
    }
    return pStr;
}

void Dictionary::setObject(Object* pObject, const std::string& key)
{
    CCASSERT(key.length() > 0 && pObject != NULL, "Invalid Argument!");
    if (_dictType == kDictUnknown)
    {
        _dictType = kDictStr;
    }

    CCASSERT(_dictType == kDictStr, "this dictionary doesn't use string as key.");

    DictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->_object != pObject)
    {
        Object* pTmpObj = pElement->_object;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }
}

void Dictionary::setObject(Object* pObject, intptr_t key)
{
    CCASSERT(pObject != NULL, "Invalid Argument!");
    if (_dictType == kDictUnknown)
    {
        _dictType = kDictInt;
    }

    CCASSERT(_dictType == kDictInt, "this dictionary doesn't use integer as key.");

    DictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    if (pElement == NULL)
    {
        setObjectUnSafe(pObject, key);
    }
    else if (pElement->_object != pObject)
    {
        Object* pTmpObj = pElement->_object;
        pTmpObj->retain();
        removeObjectForElememt(pElement);
        setObjectUnSafe(pObject, key);
        pTmpObj->release();
    }

}

void Dictionary::removeObjectForKey(const std::string& key)
{
    if (_dictType == kDictUnknown)
    {
        return;
    }
    
    CCASSERT(_dictType == kDictStr, "this dictionary doesn't use string as its key");
    CCASSERT(key.length() > 0, "Invalid Argument!");
    DictElement *pElement = NULL;
    HASH_FIND_STR(_elements, key.c_str(), pElement);
    removeObjectForElememt(pElement);
}

void Dictionary::removeObjectForKey(intptr_t key)
{
    if (_dictType == kDictUnknown)
    {
        return;
    }
    
    CCASSERT(_dictType == kDictInt, "this dictionary doesn't use integer as its key");
    DictElement *pElement = NULL;
    HASH_FIND_PTR(_elements, &key, pElement);
    removeObjectForElememt(pElement);
}

void Dictionary::setObjectUnSafe(Object* pObject, const std::string& key)
{
    pObject->retain();
    DictElement* pElement = new DictElement(key.c_str(), pObject);
    HASH_ADD_STR(_elements, _strKey, pElement);
}

void Dictionary::setObjectUnSafe(Object* pObject, const intptr_t key)
{
    pObject->retain();
    DictElement* pElement = new DictElement(key, pObject);
    HASH_ADD_PTR(_elements, _intKey, pElement);
}

void Dictionary::removeObjectsForKeys(Array* pKeyArray)
{
    Object* pObj = NULL;
    CCARRAY_FOREACH(pKeyArray, pObj)
    {
        String* pStr = static_cast<String*>(pObj);
        removeObjectForKey(pStr->getCString());
    }
}

void Dictionary::removeObjectForElememt(DictElement* pElement)
{
    if (pElement != NULL)
    {
        HASH_DEL(_elements, pElement);
        pElement->_object->release();
        CC_SAFE_DELETE(pElement);
    }
}

void Dictionary::removeAllObjects()
{
    DictElement *pElement, *tmp;
    HASH_ITER(hh, _elements, pElement, tmp) 
    {
        HASH_DEL(_elements, pElement);
        pElement->_object->release();
        CC_SAFE_DELETE(pElement);

    }
}

Object* Dictionary::randomObject()
{
    if (_dictType == kDictUnknown)
    {
        return NULL;
    }
    
    Object* key = allKeys()->randomObject();
    
    if (_dictType == kDictInt)
    {
        return objectForKey( static_cast<Integer*>(key)->getValue());
    }
    else if (_dictType == kDictStr)
    {
        return objectForKey( static_cast<String*>(key)->getCString());
    }
    else
    {
        return NULL;
    }
}

Dictionary* Dictionary::create()
{
    Dictionary* pRet = new Dictionary();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    return pRet;
}

Dictionary* Dictionary::createWithDictionary(Dictionary* srcDict)
{
    return srcDict->clone();
}

Dictionary* Dictionary::createWithContentsOfFileThreadSafe(const char *pFileName)
{
    return FileUtils::getInstance()->createDictionaryWithContentsOfFile(pFileName);
}

void Dictionary::acceptVisitor(DataVisitor &visitor)
{
    return visitor.visit(this);
}

Dictionary* Dictionary::createWithContentsOfFile(const char *pFileName)
{
    Dictionary* pRet = createWithContentsOfFileThreadSafe(pFileName);
    pRet->autorelease();
    return pRet;
}

bool Dictionary::writeToFile(const char *fullPath)
{
    return FileUtils::getInstance()->writeToFile(this, fullPath);
}

Dictionary* Dictionary::clone() const
{
    Dictionary* newDict = new Dictionary();
    newDict->autorelease();
    
    DictElement* element = NULL;
    Object* tmpObj = NULL;
    Clonable* obj = NULL;
    if (_dictType == kDictInt)
    {
        CCDICT_FOREACH(this, element)
        {
            obj = dynamic_cast<Clonable*>(element->getObject());
            if (obj)
            {
                tmpObj = dynamic_cast<Object*>(obj->clone());
                if (tmpObj)
                {
                    newDict->setObject(tmpObj, element->getIntKey());
                }
            }
            else
            {
                CCLOGWARN("%s isn't clonable.", typeid(*element->getObject()).name());
            }
        }
    }
    else if (_dictType == kDictStr)
    {
        CCDICT_FOREACH(this, element)
        {
            obj = dynamic_cast<Clonable*>(element->getObject());
            if (obj)
            {
                tmpObj = dynamic_cast<Object*>(obj->clone());
                if (tmpObj)
                {
                    newDict->setObject(tmpObj, element->getStrKey());
                }
            }
            else
            {
                CCLOGWARN("%s isn't clonable.", typeid(*element->getObject()).name());
            }
        }
    }
    
    return newDict;
}

NS_CC_END
