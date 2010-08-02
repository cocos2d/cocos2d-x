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

#ifndef __COCOA_NS_MUTATLE_ARRAY_H__
#define __COCOA_NS_MUTATLE_ARRAY_H__

#include "cocoa/NSObject.h"
#include <vector>
#include <assert.h>

// the element should be pointer of NSObject or it's sub class
template<class T = NSObject*>
class NSMutableArray : public NSObject
{
public:
	typedef std::vector<T>								NSObjectArray;
	typedef typename NSObjectArray::iterator			NSMutableArrayIterator;
	typedef typename NSObjectArray::reverse_iterator	NSMutableArrayRevIterator;

public:
	NSMutableArray(unsigned int uSize = 0)
	{
		m_array.resize(uSize);
	}

	~NSMutableArray(void)
	{
		removeAllObjects();
	}

	unsigned int count(void)
	{
		return m_array.size();
	}

	unsigned int getIndexOfObject(T pObject)
	{
		if (m_array.empty() || (pObject == NULL))
		{
			return 0;
		}

		NSMutableArray<T>::NSMutableArrayIterator iter;
		unsigned int uRet = 0;
		int i;
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

	bool containsObject(T pObject)
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

	T getLastObject(void)
	{
        T pObject = NULL;
		int count = this->count();

		if (count > 0)
		{
			pObject = m_array[count - 1];
		}

		return pObject;
	}

	T getObjectAtIndex(unsigned int uIndex)
	{
		assert(uIndex < count());

		if (uIndex >= count())
		{
			return NULL;
		}

		return m_array[uIndex];
	}

	// Adding objects
	void addObject(T pObject)
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

	void addObjectsFromArray(NSMutableArray<T> *pArray)
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

    void insertObjectAtIndex(T pObject, unsigned int uIndex)
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

	// Removing objects
	void removeLastObject(void)
	{
		int count = this->count();

		if (count > 0)
		{
			removeObjectAtIndex(count - 1);
		}
	}

	void removeObject(T pObject)
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

	void removeObjectAtIndex(unsigned int uIndex)
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

	void removeAllObjects(void)
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

	void replaceObjectAtIndex(unsigned int uIndex, T pObject)
	{
		if (uIndex >= count())
		{
			// index out of range
			assert(0);
			return;
		}

		// release the object
		T pTmp = m_array[uIndex];
		if (pTmp)
		{
			pTmp->release();		
		}

		m_array[uIndex] = pObject;

		// add the ref
		if (pObject)
		{
			pObject->retain();
		}
	}

	NSMutableArrayIterator begin(void)
	{
		return m_array.begin();
	}

	NSMutableArrayIterator end(void)
	{
		return m_array.end();
	}

public:
	static NSMutableArray<T>* arrayWithObjects(T pObject1, ...)
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

	static NSMutableArray<T>* arrayWithArray(NSMutableArray<T> *pArray)
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

private:
	std::vector<T> m_array;
};

#define NSArray NSMutableArray

#endif // __COCOA_NS_MUTATLE_ARRAY_H__
