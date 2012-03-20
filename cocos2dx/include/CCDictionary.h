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

NS_CC_BEGIN

class CCDictionary;

class CC_DLL CCDictElement
{
public:
	CCDictElement(const char* pszKey, CCObject* pObject)
	{
		init();
		strncpy(m_szKey, pszKey, sizeof(m_szKey));
		m_pObject = pObject;
	}

	CCDictElement(int iKey, CCObject* pObject)
	{
		init();
		m_iKey = iKey;
		m_pObject = pObject;
	}

	inline const char* getStrKey() const
	{
		return m_szKey;
	}

	inline int getIntKey() const 
	{
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
	char m_szKey[256]; /* hash key of string type*/
	int  m_iKey;      /* hash key of integer type */
	CCObject* m_pObject;/* hash value */
public:
	UT_hash_handle hh; /* makes this class hashable */
	friend class CCDictionary;
};


// #define CCDICT_FOREACH(__dict__, pElement)	                       \
// for (pElement = __dict__->m_pElements; pElement != NULL; \
// 	pElement = (CCDictElement*)pElement->hh.next)

#define CCDICT_FOREACH(__dict__, __el__) \
	CCDictElement* tmp##__dict____el__ = NULL; \
	HASH_ITER(hh, (__dict__)->m_pElements, __el__, tmp##__dict____el__)


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

	CCObject* objectForKey(const char* key);
	CCObject* objectForKey(int key);

	bool setObject(CCObject* pObject, const char* key);
	bool setObject(CCObject* pObject, int key);

	void removeObjectForKey(const char* key);
	void removeObjectForKey(int key);

	void removeAllObjects();

	virtual CCObject* copyWithZone(CCZone* pZone);
	static CCDictionary* dictionaryWithDictionary(CCDictionary* srcDict);

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

NS_CC_END

#endif /* __CCDICTIONARY_H__ */
