#include "CCDictionary.h"
#include "CCString.h"
#include "CCInteger.h"

NS_CC_BEGIN

CCDictionary2::CCDictionary2()
: m_pElements(NULL)
, m_eDictType(kCCDictUnknown)
, m_eOldDictType(kCCDictUnknown)
{

}

CCDictionary2::~CCDictionary2()
{
	removeAllObjects();
}

unsigned int CCDictionary2::count()
{
	return HASH_COUNT(m_pElements);
}

CCArray* CCDictionary2::allKeys()
{
	int iKeyCount = this->count();
	if (iKeyCount <= 0) return NULL;
	CCArray* pArray = CCArray::arrayWithCapacity(iKeyCount);

	tDictElement *pElement, *tmp;
	if (m_eDictType == kCCDictStr)
	{
		HASH_ITER(hh, m_pElements, pElement, tmp) 
		{
			CCString* pOneKey = new CCString(pElement->szKey);
			pOneKey->autorelease();
			pArray->addObject(pOneKey);
		}
	}
	else if (m_eDictType == kCCDictInt)
	{
		HASH_ITER(hh, m_pElements, pElement, tmp) 
		{
			CCInteger* pOneKey = new CCInteger(pElement->iKey);
			pOneKey->autorelease();
			pArray->addObject(pOneKey);
		}
	}
	
	return pArray;
}

CCArray* CCDictionary2::allKeysForObject(CCObject* object)
{
	int iKeyCount = this->count();
	if (iKeyCount <= 0) return NULL;
	CCArray* pArray = CCArray::array();

	tDictElement *pElement, *tmp;

	if (m_eDictType == kCCDictStr)
	{
		HASH_ITER(hh, m_pElements, pElement, tmp) 
		{
			if (object == pElement->object)
			{
				CCString* pOneKey = new CCString(pElement->szKey);
				pOneKey->autorelease();
				pArray->addObject(pOneKey);
			}
		}
	}
	else if (m_eDictType == kCCDictInt)
	{
		HASH_ITER(hh, m_pElements, pElement, tmp) 
		{
			if (object == pElement->object)
			{
				CCInteger* pOneKey = new CCInteger(pElement->iKey);
				pOneKey->autorelease();
				pArray->addObject(pOneKey);
			}
		}
	}
	return pArray;
}

CCObject* CCDictionary2::objectForKey(const char* key)
{
	CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as key.");

	CCObject* pRetObject = NULL;
	tDictElement *pElement = NULL;
	HASH_FIND_STR(m_pElements,key, pElement);
	if (pElement != NULL)
	{
		pRetObject = pElement->object;
	}
	return pRetObject;
}

CCObject* CCDictionary2::objectForKey(int key)
{
	CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as key.");

	CCObject* pRetObject = NULL;
	tDictElement *pElement = NULL;
	HASH_FIND_INT(m_pElements, &key, pElement);
	if (pElement != NULL)
	{
		pRetObject = pElement->object;
	}
	return pRetObject;
}

bool CCDictionary2::setObject(CCObject* pObject, const char* key)
{
	CCAssert(key != NULL && strlen(key) > 0 && pObject != NULL, "Invalid Argument!");
	if (m_eOldDictType == kCCDictUnknown)
	{
		m_eOldDictType = kCCDictStr;
	}
	m_eDictType = kCCDictStr;
	CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use string as key.");

	bool bRet = false;
	tDictElement *pElement = NULL;
	HASH_FIND_STR(m_pElements, key, pElement);
	if (pElement == NULL)
	{
		pElement = (tDictElement*)calloc(sizeof(*pElement), 1);
		strcpy(pElement->szKey, key);
		pObject->retain();
		pElement->object = pObject;
		HASH_ADD_STR(m_pElements, szKey, pElement);
		bRet = true;
	}
	else
	{
		pElement->object->retain();
		removeObjectForKey(key);
		setObject(pObject, key);
		pElement->object->release();
		bRet = true;
	}
	return bRet;
}

bool CCDictionary2::setObject(CCObject* pObject, int key)
{
	CCAssert(pObject != NULL, "Invalid Argument!");
	if (m_eOldDictType == kCCDictUnknown)
	{
		m_eOldDictType = kCCDictInt;
	}
	m_eDictType = kCCDictInt;
	CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use integer as key.");

	bool bRet = false;
	tDictElement *pElement = NULL;
	HASH_FIND_INT(m_pElements, &key, pElement);
	if (pElement == NULL)
	{
		pElement = (tDictElement*)calloc(sizeof(*pElement), 1);
		pElement->iKey = key;
		pObject->retain();
		pElement->object = pObject;
		HASH_ADD_INT(m_pElements, iKey, pElement);
		bRet = true;
	}
	else
	{
		pElement->object->retain();
		removeObjectForKey(key);
		setObject(pObject, key);
		pElement->object->release();
		bRet = true;
	}
	return bRet;
}

void CCDictionary2::removeObjectForKey(const char* key)
{
	CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as its key");
	CCAssert(key != NULL && strlen(key) > 0, "Invalid Argument!");
	tDictElement *pElement = NULL;
	HASH_FIND_STR(m_pElements, key, pElement);
	if (pElement)
	{
		HASH_DEL(m_pElements, pElement);
		pElement->object->release();
		free(pElement);
	}
}

void CCDictionary2::removeObjectForKey(int key)
{
	CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as its key");
	tDictElement *pElement = NULL;
	HASH_FIND_INT(m_pElements, &key, pElement);
	if (pElement != NULL)
	{
		HASH_DEL(m_pElements, pElement);
		pElement->object->release();
		free(pElement);
	}
}

void CCDictionary2::removeAllObjects()
{
	tDictElement *pElement, *tmp;
	HASH_ITER(hh, m_pElements, pElement, tmp) 
	{
		HASH_DEL(m_pElements, pElement);
		pElement->object->release();
		free(pElement);
	}
}

CCDictionary2* CCDictionary2::dictionaryWithDictionary(CCDictionary2* srcDict)
{
	return NULL;
}

NS_CC_END
