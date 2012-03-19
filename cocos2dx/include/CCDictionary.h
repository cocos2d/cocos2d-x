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

typedef struct _dictElement
{
	char szKey[20]; /* hash key of string type*/
	int  iKey;      /* hash key of integer type */
	CCObject* object;/* hash value */
	UT_hash_handle hh; /* makes this class hashable */  
}tDictElement;

#define CCDICT_FOREACH(__dict__, __object__)	                   \
for (tDictElement* pElement = __dict__->m_pElements;               \
	pElement != NULL && (__object__ = pElement->object) != NULL;   \
	pElement = (tDictElement*)pElement->hh.next)

class CC_DLL CCDictionary2 : public CCObject
{
public:
	CCDictionary2();
	~CCDictionary2();

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

	static CCDictionary2* dictionaryWithDictionary(CCDictionary2* srcDict);

public:
	tDictElement* m_pElements;
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
