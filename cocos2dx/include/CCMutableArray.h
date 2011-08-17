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

#ifndef __COCOA_CC_MUTATLE_ARRAY_H__
#define __COCOA_CC_MUTATLE_ARRAY_H__

#include "CCObject.h"
#include <vector>
#include <assert.h>
#include <stdarg.h>

namespace   cocos2d {

// the element should be pointer of CCObject or it's sub class
template<class T = CCObject*>
class CCMutableArray : public CCObject
{
public:
	typedef std::vector<T>								CCObjectArray;
	typedef typename CCObjectArray::iterator			CCMutableArrayIterator;
	typedef typename CCObjectArray::reverse_iterator	CCMutableArrayRevIterator;

public:
	CCMutableArray(unsigned int uSize = 0)
	{
		m_array.resize(uSize);
	}

	virtual ~CCMutableArray(void)
	{
		removeAllObjects();
	}

	unsigned int count(void)
	{
		unsigned int uCount = 0;
		
		if (!m_array.empty())
		{
			CCMutableArrayIterator it;
			for (it = m_array.begin(); it != m_array.end(); ++it)
			{
				if (*it == NULL)
				{
					break;
				}

				++uCount;
			}
		}

		return uCount;
	}

	unsigned int getIndexOfObject(T pObject)
	{
		if (m_array.empty() || (pObject == NULL))
		{
			return 0;
		}

		CCMutableArrayIterator iter;
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
		CCMutableArrayIterator iter;
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

		// if the vector is empty, push back
		if (m_array.empty())
		{
			m_array.push_back(pObject);
			return;
		}

		// find a position to store
		int count = 0;;
        CCMutableArrayIterator it;
		for (it = m_array.begin(); it != m_array.end(); ++it)
		{
			if (*it == NULL)
			{
				m_array[count] = pObject;
				return;
			}
            
			++count;
		} 

		// the array is full, push back
		m_array.push_back(pObject);
	}

	void addObjectsFromArray(CCMutableArray<T> *pArray)
	{
		if (pArray && pArray->count() > 0)
		{
			CCMutableArrayIterator iter;
			for (iter = pArray->begin(); iter != pArray->end(); ++iter)
			{
				if (*iter)
				{
                    (*iter)->retain();
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

		// resize the capacity if the index out of it
		if (uIndex >= m_array.capacity())
		{
			m_array.resize(uIndex + 4);
		}

		// insert the object
		m_array.insert(m_array.begin() + uIndex, pObject);
	}

	// Removing objects
	void removeLastObject(bool bDeleteObject = true)
	{
		int count = this->count();

		if (count > 0)
		{
			removeObjectAtIndex(count - 1, bDeleteObject);
		}
	}

	void removeObject(T pObject, bool bDeleteObject = true)
	{
		if (m_array.empty() || (! pObject))
		{
			return;
		}

		CCMutableArrayIterator iter;
		int i;
		for (iter = m_array.begin(), i = 0; iter != m_array.end(); ++iter, ++i)
		{
			if (*iter == pObject)
			{
				m_array.erase(iter);
                
				if (bDeleteObject)
				{
                    pObject->release();
				}			

				break;
			}
		}
	}

	void removeObjectsInArray(CCMutableArray<T>* pDeleteArray)
	{
		if(pDeleteArray && pDeleteArray->count())
		{
			CCMutableArrayIterator it;
			for( it = pDeleteArray->m_array.begin(); it != pDeleteArray->m_array.end(); ++it)
			{
				removeObject(*it);
			}
		}
	}

	void removeObjectAtIndex(unsigned int uIndex, bool bDeleteObject = true)
	{
		if (m_array.empty())
		{
			return;
		}

		if (bDeleteObject)
		{
			T pObject = m_array.at(uIndex);
			if (pObject)
			{
				pObject->release();
			}
		}
		
		m_array.erase(m_array.begin() + uIndex);
	}

	void removeAllObjects(bool bDeleteObject = true)
	{
		if (bDeleteObject)
		{
			CCMutableArrayIterator iter;
			for (iter = m_array.begin(); iter != m_array.end(); ++iter)
			{
				if (*iter)
				{
					(*iter)->release();
				}
			}
		}		

		m_array.clear();
	}

	void replaceObjectAtIndex(unsigned int uIndex, T pObject, bool bDeleteObject = true)
	{
		if (m_array[uIndex] && bDeleteObject)
		{
			m_array[uIndex]->release();
		}

		m_array[uIndex] = pObject;

		// add the ref
		if (pObject)
		{
			pObject->retain();
		}
	}

	CCMutableArrayIterator begin(void)
	{
		return m_array.begin();
	}

	CCMutableArrayRevIterator rbegin(void)
	{
		return m_array.rbegin();
	}

	CCMutableArrayIterator getLastValidIterator(void)
	{
		CCMutableArrayIterator iter;
		CCMutableArrayIterator ret;
		for (iter = m_array.begin(); iter != m_array.end(); ++iter)
		{
			ret = iter;
			if (! (*iter))
			{
				break;
			}
		}

		return ret;
	}

	/*
	 * end is a keyword of lua, so should use other name
	 * to export to lua
	*/
	CCMutableArrayIterator endToLua(void)
	{
		return m_array.end();
	}

	CCMutableArrayIterator end(void)
	{
		return m_array.end();
	}

	CCMutableArrayRevIterator rend(void)
	{
		return m_array.rend();
	}

	CCMutableArray<T>* copy(void)
	{
		CCMutableArray* pArray = new CCMutableArray();

		pArray->m_array.assign(m_array.begin(), m_array.end());

		if(pArray->count() > 0)
		{
			CCMutableArrayIterator it;
			for(it = pArray->begin(); it != pArray->end(); ++it)
			{
				if(*it)
				{
					(*it)->retain();
				}
			}
		}

		return pArray;
	}

public:
	static CCMutableArray<T>* arrayWithObjects(T pObject1, ...)
	{
		CCMutableArray<T> *pArray = new CCMutableArray<T>();
        pArray->autorelease();

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

	static CCMutableArray<T>* arrayWithArray(CCMutableArray<T> *pSrcArray)
	{
        CCMutableArray<T> *pDestArray = NULL;
        
		if (pSrcArray == NULL)
		{
            pDestArray = new CCMutableArray<T>();
		}
        else
        {
            pDestArray = pSrcArray->copy();
        }
        
        pDestArray->autorelease();
        
		return pDestArray;
	}

private:
	std::vector<T> m_array;
};

}//namespace   cocos2d 

#endif // __COCOA_CC_MUTATLE_ARRAY_H__
