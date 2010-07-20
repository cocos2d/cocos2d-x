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

template<class T>
NSMutableArray<T>::NSMutableArray(UINT32 uSize)
{
	m_array = m_array.resize(uSize);
}

template<class T>
NSMutableArray<T>::~NSMutableArray(void)
{
	removeAllObjects();
}

template<class T>
typename NSMutableArray<T>::NSMutableArrayIterator NSMutableArray<T>::begin(void)
{
	return m_array.begin();
}

template<class T>
typename NSMutableArray<T>::NSMutableArrayIterator NSMutableArray<T>::end(void)
{
	return m_array.end();
}

template<class T>
void NSMutableArray<T>::addObject(T pObject)
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

template<class T>
void NSMutableArray<T>::insertObjectAtIndex(T pObject, UInt32 uIndex)
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

template<class T>
void NSMutableArray<T>::addObjectsFromArray(NSMutableArray<T> *pArray)
{
	if (pArray && pArray->count() > 0)
	{
		NSMutableArray<T>::NSMutableArrayIterator iter;
		for (iter = pArray->begin(); iter != pArray->end(); ++iter)
		{
			if (*iter)
			{
				m_array.push_back(*iter);
			}
		}
	}
}

template<class T>
UINT32 NSMutableArray<T>::count(void)
{
	return m_array.size();
}

template<class T>
void NSMutableArray<T>::removeObject(T pObject)
{
	if (m_array.empty() || (! pObject))
	{
		return;
	}

	NSMutableArray<T>::NSMutableArrayIterator iter;
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

template<class T>
void NSMutableArray<T>::removeAllObjects(void)
{
	NSMutableArray<T>::NSMutableArrayIterator iter;
	for (iter = m_array.begin(); iter != m_array.end(); ++iter)
	{
		if (*iter)
		{
			(*iter)->release();
		}
	}

	m_array.clear();
}

template<class T>
void NSMutableArray<T>::removeLastObject(void)
{
	INT32 count = this->count();

	if (count > 0)
	{
		removeObjectAtIndex(count - 1);
	}
}

template<class T>
void NSMutableArray<T>::removeObjectAtIndex(UINT32 uIndex)
{
	if (m_array.empty() || uIndex == 0)
	{
		return;
	}

	T pObject = m_array.at(uIndex);
	if (pObject)
	{
		pObject->release();
	}

	m_array.erase(m_array.begin() + uIndex);
}

template<class T>
bool NSMutableArray<T>::containsObject(T pObject)
{
	if (m_array.empty() || (! pObject))
	{
		return false;
	}

	bool bRet = false;
	NSMutableArray<T>::NSMutableArrayIterator iter;
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

template<class T>
void NSMutableArray<T>::replaceObjectAtIndex(UINT32 uIndex, T pObject)
{
    if (m_array.empty() || uIndex == 0)
	{
		return;
	}

	// release the object
	T pTmp = m_array.at(uIndex);
	if (pTmp )
	{
		pTmp->release();
	}

	m_array[uIndex] = pObject;
}

template<class T>
UINT32 NSMutableArray<T>::getIndexOfObject(T pObject)
{
	if (m_array.empty() || (pObject == NULL))
	{
        return 0;
	}

	NSMutableArray<T>::NSMutableArrayIterator iter;
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

template<class T>
T NSMutableArray<T>::getLastObject(void)
{
	T pObject = NULL;
	INT32 count = this->count();

	if (count > 0)
	{
		pObject = m_array[count - 1];
	}

	return pObject;
}

template<class T>
NSMutableArray<T>* arrayWithObjects(T pObject1, ...)
{
	NSMutableArray<T> *pArray = new NSMutableArray<T>();

	va_list params;
	va_start(params, pObject1);

	T pFirst = pObject1;
	while (pFirst)
	{
		pArray->addObject(pFirst);
		pFirst = va_arg(params, T);
	}

	va_end(params);

	return pArray;
}

template<class T>
NSMutableArray<T>* NSMutableArray<T>::arrayWithArray(NSMutableArray<T> *pArray)
{
	if (pArray == NULL)
	{
		return NULL;
	}

	NSMutableArray<T> *pNewArray = new NSMutableArray<T>();
	NSMutableArray<T>::NSMutableArrayIterator iter;
	for (iter = pArray->begin(); iter != pArray->end(); ++iter)
	{
		pNewArray->addObject(*iter);
	}

	return pNewArray;
}

template<class T>
T NSMutableArray<T>::getObjectAtIndex(UINT32 uIndex)
{
	assert(uIndex < count());
	assert(uIndex >= 0);

	if (uIndex <= 0 || uIndex >= count())
	{
		return NULL;
	}

	return m_array[uIndex];
}
