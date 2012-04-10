#include "CCDictionary.h"
#include "CCString.h"
#include "CCInteger.h"

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

CCObject* CCDictionary::objectForKey(const char* key)
{
	if (m_eDictType == kCCDictUnknown && m_eDictType == kCCDictUnknown) return NULL;
	CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as key.");

	CCObject* pRetObject = NULL;
	CCDictElement *pElement = NULL;
	HASH_FIND_STR(m_pElements,key, pElement);
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

bool CCDictionary::setObject(CCObject* pObject, const char* key)
{
	CCAssert(key != NULL && strlen(key) > 0 && pObject != NULL, "Invalid Argument!");
	if (m_eOldDictType == kCCDictUnknown)
	{
		m_eOldDictType = kCCDictStr;
	}
	m_eDictType = kCCDictStr;
	CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use string as key.");

	bool bRet = false;
	CCDictElement *pElement = NULL;
	HASH_FIND_STR(m_pElements, key, pElement);
	if (pElement == NULL)
	{
		pObject->retain();
		pElement = new CCDictElement(key, pObject);
		HASH_ADD_STR(m_pElements, m_szKey, pElement);
		bRet = true;
	}
	else
	{
		CCObject* pTmpObj = pElement->m_pObject;
		pTmpObj->retain();
		removeObjectForKey(key);
		setObject(pObject, key);
		pTmpObj->release();
		bRet = true;
	}
	return bRet;
}

bool CCDictionary::setObject(CCObject* pObject, int key)
{
	CCAssert(pObject != NULL, "Invalid Argument!");
	if (m_eOldDictType == kCCDictUnknown)
	{
		m_eOldDictType = kCCDictInt;
	}
	m_eDictType = kCCDictInt;
	CCAssert(m_eDictType == m_eOldDictType, "this dictionary does not use integer as key.");

	bool bRet = false;
	CCDictElement *pElement = NULL;
	HASH_FIND_INT(m_pElements, &key, pElement);
	if (pElement == NULL)
	{
		pObject->retain();
		pElement = new CCDictElement(key, pObject);
		HASH_ADD_INT(m_pElements, m_iKey, pElement);
		bRet = true;
	}
	else
	{
		CCObject* pTmpObj = pElement->m_pObject;
		pTmpObj->retain();
		removeObjectForKey(key);
		setObject(pObject, key);
		pTmpObj->release();
		bRet = true;
	}
	return bRet;
}

void CCDictionary::removeObjectForKey(const char* key)
{
	CCAssert(m_eDictType == kCCDictStr, "this dictionary does not use string as its key");
	CCAssert(key != NULL && strlen(key) > 0, "Invalid Argument!");
	CCDictElement *pElement = NULL;
	HASH_FIND_STR(m_pElements, key, pElement);
	if (pElement)
	{
		HASH_DEL(m_pElements, pElement);
		pElement->m_pObject->release();
		CC_SAFE_DELETE(pElement);
	}
}

void CCDictionary::removeObjectForKey(int key)
{
	CCAssert(m_eDictType == kCCDictInt, "this dictionary does not use integer as its key");
	CCDictElement *pElement = NULL;
	HASH_FIND_INT(m_pElements, &key, pElement);
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

/* need deep copy ?*/

CCDictionary* CCDictionary::dictionaryWithDictionary(CCDictionary* srcDict)
{
	CCDictionary* pNewDict = (CCDictionary*)srcDict->copyWithZone(NULL);
	pNewDict->autorelease();
	return pNewDict;
}

NS_CC_END
