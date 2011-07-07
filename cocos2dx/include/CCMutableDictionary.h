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
#ifndef __CCMUTABLE_DICTIONARY_H__
#define __CCMUTABLE_DICTIONARY_H__

#include <map>
#include <vector>
#include <string>
#include "CCObject.h"
#include "CCMutableArray.h"
#include "ccMacros.h"

using namespace std;
namespace   cocos2d {
class CCString;

template<class _KeyT, class _ValueT = CCObject*>
class CCMutableDictionary : public CCObject
{
public:
	typedef std::map<_KeyT, _ValueT>	CCObjectMap;
	typedef typename CCObjectMap::iterator	CCObjectMapIter;

protected:
	typedef pair<_KeyT, _ValueT> Int_Pair;
	CCObjectMap		m_Map;
	bool			m_bBegin;
	CCObjectMapIter m_MapIter;

public:
	CCMutableDictionary(void)
	{
		m_bBegin = false;
	}

	~CCMutableDictionary(void)
	{
		removeAllObjects();
	}

	/// return the number of items
	unsigned int count()
	{
		return m_Map.size();
	}

	/// return all the keys
	std::vector<_KeyT> allKeys()
	{
		std::vector<_KeyT> tRet;
		if (m_Map.size() > 0)
		{
			CCObjectMapIter it;
			for( it = m_Map.begin(); it != m_Map.end(); ++it)
			{
				tRet.push_back(it->first);
			}
		}
		return tRet;
	}

	/** @warning : We use '==' to compare two objects*/
	std::vector<_KeyT> allKeysForObject(_ValueT object)
	{
		std::vector<_KeyT> tRet;
		if (m_Map.size() > 0)
		{
			CCObjectMapIter it;
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

	_ValueT objectForKey(const _KeyT& key)			///< 
	{
		CCObjectMapIter it;

		it = m_Map.find(key);

		if(it == m_Map.end()) //no match case
			return NULL;

		return it->second;
	}


	bool setObject(_ValueT pObject, const _KeyT& key)
	{
		pair<CCObjectMapIter, bool > pr;

		pr = m_Map.insert( Int_Pair(key, pObject) );

		if(pr.second == true)
		{
			pObject->retain(); 
			return true;
		}

		return false;
	}

	void removeObjectForKey(const _KeyT& key)
	{
		CCObjectMapIter it;

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

	_ValueT next(_KeyT* key = NULL)
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

			++m_MapIter;

			if(m_MapIter == m_Map.end())
			{
				m_bBegin = false;
			}
		}

		return pObject;
	}

	/*
	* end is a keyword of lua, so should use other name
	* to export to lua
	*/
	void endToLua()
	{
		end();
	} 

	void end()
	{
		m_bBegin = false;
	}

	void removeAllObjects()
	{
		if (m_Map.size() > 0)
		{
			CCObjectMapIter it;
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

	static CCMutableDictionary<_KeyT, _ValueT>* dictionaryWithDictionary(CCMutableDictionary<_KeyT, _ValueT>* srcDict)
	{
		CCMutableDictionary<_KeyT, _ValueT>* pNewDict = new CCMutableDictionary<_KeyT, _ValueT>();

		srcDict->begin();

		_KeyT key;
		_ValueT value;

		while( (value = srcDict->next(&key)) )
		{
			pNewDict->setObject(value, key);
		}

		srcDict->end();

		return pNewDict;
	}
};

#define CCDictionary	CCMutableDictionary
typedef CCDictionary<std::string, CCString*> CCStringToStringDictionary;
}//namespace   cocos2d 


#endif //__CCMUTABLE_DICTIONARY_H__