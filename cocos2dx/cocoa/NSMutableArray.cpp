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

#include "NSMutableArray.h"
#include <stdarg.h>
#include <vector>
#include <assert.h>

using namespace std;

NSMutableArray::NSMutableArray(UINT32 uSize)
{
	m_array = vector<NSObject *>(uSize);
}

NSMutableArray::~NSMutableArray(void)
{
	removeAllObjects();
}

vector<NSObject *>::iterator NSMutableArray::begin(void)
{
	return m_array.begin();
}

vector<NSObject *>::iterator NSMutableArray::end(void)
{
	return m_array.end();
}

void NSMutableArray::addObject(NSObject *pObject)
{
	// make sure the pointer is not null
	if (pObject == NULL)
	{
		return;
	}

	// add the refrence
	pObject->retain();

	// the array is full, push back
	m_array.push_back(pObject);
}

void NSMutableArray::insertObjectAtIndex(NSObject *pObject, UInt32 uIndex)
{
	// make sure the object is not null
	if (pObject == NULL)
	{
		return;
	}

	// add the refrence of the object
	pObject->retain();

	// insert the object
	m_array.insert(m_array.begin() + uIndex, pObject);
}

void NSMutableArray::addObjectsFromArray(NSMutableArray *pArray)
{
	if (pArray && pArray->count() > 0)
	{
		vector<NSObject *>::iterator iter;
		for (iter = pArray->begin(); iter != pArray->end(); ++iter)
		{
			if (*iter)
			{
				m_array.push_back(*iter);
			}
		}
	}
}

UINT32 NSMutableArray::count(void)
{
	return m_array.size();
}

void NSMutableArray::removeObject(NSObject *pObject)
{
	if (m_array.empty() || (! pObject))
	{
		return;
	}

	vector<NSObject *>::iterator iter;
	int i;
	for (iter = m_array.begin(), i = 0; iter != m_array.end(); ++iter, ++i)
	{
		if (*iter == pObject)
		{
			m_array.erase(iter);

			pObject->release();

			break;
		}
	}
}

void NSMutableArray::removeAllObjects(void)
{
	vector<NSObject *>::iterator iter;
	for (iter = m_array.begin(); iter != m_array.end(); ++iter)
	{
		if (*iter)
		{
			(*iter)->release();
		}
	}

	m_array.clear();
}

void NSMutableArray::removeLastObject(void)
{
	INT32 count = this->count();

	if (count > 0)
	{
		removeObjectAtIndex(count - 1);
	}
}

void NSMutableArray::removeObjectAtIndex(UINT32 uIndex)
{
	if (m_array.empty() || uIndex == 0)
	{
		return;
	}

	NSObject *pObject = m_array.at(uIndex);
	if (pObject)
	{
		pObject->release();
	}

	m_array.erase(m_array.begin() + uIndex);
}

bool NSMutableArray::containsObject(NSObject *pObject)
{
	if (m_array.empty() || (! pObject))
	{
		return false;
	}

	bool bRet = false;
	vector<NSObject *>::iterator iter;
	for (iter = m_array.begin(); iter != m_array.end(); ++iter)
	{
		if (*iter == pObject)
		{
			bRet = true;
			break;
		}
	}

	return bRet;
}

void NSMutableArray::replaceObjectAtIndex(UINT32 uIndex, NSObject *pObject)
{
    if (m_array.empty() || uIndex == 0)
	{
		return;
	}

	// release the object
	NSObject *pTmp = m_array.at(uIndex);
	if (pTmp )
	{
		pTmp->release();
	}

	m_array[uIndex] = pObject;
}

UINT32 NSMutableArray::getIndexOfObject(NSObject *pObject)
{
	if (m_array.empty() || (pObject == NULL))
	{
        return 0;
	}

	vector<NSObject *>::iterator iter;
	UINT32 uRet = 0;
	INT32 i;
	for (iter = m_array.begin(), i = 0; iter != m_array.end(); ++iter, ++i)
	{
		if (*iter == pObject)
		{
			uRet = i;
			break;
		}
	}

	return uRet;
}

NSObject* NSMutableArray::getLastObject(void)
{
	NSObject *pObject = NULL;
	INT32 count = this->count();

	if (count > 0)
	{
		pObject = m_array[count - 1];
	}

	return pObject;
}

NSMutableArray* arrayWithObjects(NSObject *pObject1, ...)
{
	NSMutableArray *pArray = new NSMutableArray();

	va_list params;
	va_start(params, pObject1);

	NSObject *pFirst = pObject1;
	while (pFirst)
	{
		pArray->addObject(pFirst);
		pFirst = va_arg(params, NSObject *);
	}

	va_end(params);

	return pArray;
}

NSMutableArray* arrayWithArray(NSMutableArray *pArray)
{
	if (pArray == NULL)
	{
		return NULL;
	}

	NSMutableArray *pNewArray = new NSMutableArray();
	vector<NSObject *>::iterator iter;

	for (iter = pArray->begin(); iter != pArray->end(); ++iter)
	{
		pNewArray->addObject(*iter);
	}

	return pNewArray;
}

NSObject* NSMutableArray::getObjectAtIndex(UINT32 uIndex)
{
	assert(uIndex < count());
	assert(uIndex >= 0);

	if (uIndex <= 0 || uIndex >= count())
	{
		return NULL;
	}

	return m_array[uIndex];
}
