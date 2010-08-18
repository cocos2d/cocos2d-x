/* cocos2d for windows
 *
 * http://cocos2d-win.blogspot.com
 *
 * Copyright (C) 2010 KOO C.H
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the 'cocos2d for windows' license.
 *
 * You will find a copy of this license within the cocos2d for windows
 * distribution inside the "LICENSE" file.
 *
 */
#ifndef __CCMUTABLE_DICTIONARY_H__
#define __CCMUTABLE_DICTIONARY_H__

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


#endif //__CCMUTABLE_DICTIONARY_H__