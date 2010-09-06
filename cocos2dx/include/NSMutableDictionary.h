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
#ifndef __NSMUTABLE_DICTIONARY_H__
#define __NSMUTABLE_DICTIONARY_H__

#include <map>
#include <vector>
#include "NSObject.h"
#include "NSMutableArray.h"

using namespace std;
namespace   cocos2d {

template<class _T, class _ValueT = NSObject*>
class NSMutableDictionary : public NSObject
{
public:
	typedef std::map<_T, _ValueT>	NSObjectMap;
	typedef typename NSObjectMap::iterator	NSObjectMapIter;

protected:
	typedef pair<_T, _ValueT> Int_Pair;
	NSObjectMap		m_Map;
	bool			m_bBegin;
	NSObjectMapIter m_MapIter;

public:
	NSMutableDictionary(void)
	{
		m_bBegin = false;
	}

	~NSMutableDictionary(void)
	{
		removeAllObjects();
	}

	/// return the number of items
	unsigned int count()
	{
		return m_Map.size();
	}

	/// return all the keys
	std::vector<std::string> allKeys()
	{
		std::vector<std::string> tRet;
		if (m_Map.size() > 0)
		{
			NSObjectMapIter it;
			for( it = m_Map.begin(); it != m_Map.end(); ++it)
			{
				tRet.push_back(it->first);
			}
		}
		return tRet;
	}

	/** @warning : We use '==' to compare two objects*/
	std::vector<std::string> allKeysForObject(_ValueT object)
	{
		std::vector<std::string> tRet;
		if (m_Map.size() > 0)
		{
			NSObjectMapIter it;
			for( it= m_Map.begin(); it != m_Map.end(); ++it)
			{
				if (it->second == object)
				{
					tRet.push_back(it->first);
				}
			}
		}
		return tRet;
	}

	_ValueT objectForKey(_T key)			///< 
	{
		NSObjectMapIter it;

		it = m_Map.find(key);

		if(it == m_Map.end()) //no match case
			return NULL;

		return it->second;
	}


	bool setObject(_ValueT pObject, _T key)
	{
		pair<NSObjectMapIter, bool > pr;

		pr = m_Map.insert( Int_Pair(key, pObject) );

		if(pr.second == true)
		{
			pObject->retain(); 
			return true;
		}

		return false;
	}

	void removeObjectForKey(_T key)
	{
		NSObjectMapIter it;

		it = m_Map.find(key);

		if(it == m_Map.end()) //no match case
			return;

		if(it->second )
		{
			it->second->release() ; 
			m_Map.erase(it);
		}
	}

	bool begin()
	{
		if(m_Map.size() == 0)
			return false;

		m_MapIter = m_Map.begin();
		m_bBegin = true;

		return true;
	}

	_ValueT next(_T* key = NULL)
	{
		if(!m_bBegin)
			return NULL;

		_ValueT pObject = m_MapIter->second;

		if(m_MapIter == m_Map.end())
		{
			m_bBegin = false;
		}
		else
		{
			if(key)
			{
				*key = m_MapIter->first;
			}

			m_MapIter++;

			if(m_MapIter == m_Map.end())
			{
				m_bBegin = false;
			}
		}

		return pObject;
	}

	void end()
	{
		m_bBegin = false;
	}

	void removeAllObjects()
	{
		if (m_Map.size() > 0)
		{
			NSObjectMapIter it;
			for( it = m_Map.begin(); it != m_Map.end(); ++it)
			{
				if (it->second)
				{
					it->second->release();
				}
			}
		}
		m_Map.clear();
	}

	static NSMutableDictionary<_T, _ValueT>* dictionaryWithDictionary(NSMutableDictionary<_T, _ValueT>* srcDict)
	{
		NSMutableDictionary<_T, _ValueT>* pNewDict = new NSMutableDictionary<_T, _ValueT>();

		srcDict->begin();

		_T key;
		_ValueT value;

		while( (value = srcDict->next(&key)) )
		{
			pNewDict->setObject(value, key);
		}

		srcDict->end();

		return pNewDict;
	}
};

#define NSDictionary	NSMutableDictionary
}//namespace   cocos2d 


#endif //__NSMUTABLE_DICTIONARY_H__