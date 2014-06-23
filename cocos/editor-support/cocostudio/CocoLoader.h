/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef _COCOLOADER_H
#define _COCOLOADER_H

#include <stdio.h>
#include <vector>
#include <cstdio>
#include <stdint.h>
#include "json/rapidjson.h"
#include "json/document.h"

#pragma pack (4)

namespace cocostudio{
        

struct  stExpCocoAttribDesc
{
	rapidjson::Type	m_Type;
	uint64_t m_szName;
	uint64_t m_szDefaultValue;
public:
	
	void ReBuild(char* pStringMemoryAddr)
	{
		m_szName = m_szName + (uint64_t)pStringMemoryAddr;
		m_szDefaultValue = m_szDefaultValue + (uint64_t)pStringMemoryAddr;
	}
};

struct  stExpCocoObjectDesc
{
	uint32_t		m_nAttribNum;
	uint64_t		m_szName;
	uint64_t		m_pAttribDescArray;

public:
	stExpCocoObjectDesc()
	{
		m_nAttribNum = 0;
		m_szName = 0;
		m_pAttribDescArray = 0;
	}
	void ReBuild(char* pAttribMemoryAddr,char* pStringMemoryAddr)
	{
		m_szName = m_szName + (uint64_t)pStringMemoryAddr;
		m_pAttribDescArray = m_pAttribDescArray + (uint64_t)pAttribMemoryAddr;
		stExpCocoAttribDesc* tpAttribDescArray = (stExpCocoAttribDesc*)m_pAttribDescArray;
		for(uint32_t i = 0 ; i < m_nAttribNum ; i++)
		{
			tpAttribDescArray[i].ReBuild(pStringMemoryAddr);
		}
	}
	
};
   
class CocoLoader;

struct stExpCocoNode
{
protected:
	int32_t	m_ObjIndex;
	int32_t	m_AttribIndex;
	uint32_t	m_ChildNum;
	uint64_t	m_szValue;
	uint64_t	m_ChildArray;
    
public:
    rapidjson::Type	 GetType(CocoLoader*	pCoco);
	char*	GetName(CocoLoader*	pCoco);
	char*	GetValue();
	int	GetChildNum();
	stExpCocoNode*	GetChildArray();
    
public:
	inline  void	ReBuild(char* cocoNodeAddr,char* pStringMemoryAddr);
	void	WriteJson(CocoLoader* pCoco, void* pFileName = NULL, int vLayer = 0, bool bEndNode = false, bool bParentNodeIsArray = false);
};


struct	stCocoFileHeader
{
	char	m_FileDesc[32];
	char	m_Version[32];
	uint32_t	m_nFirstUsed;
	uint32_t	m_ObjectCount;
	uint64_t	m_lAttribMemAddr;
	uint64_t	m_CocoNodeMemAddr;
	uint64_t	m_lStringMemAddr;
	
};


class CocoLoader
{
private:
	stCocoFileHeader*	m_pFileHeader;
	stExpCocoNode*		m_pRootNode;
	stExpCocoObjectDesc*	m_pObjectDescArray;

public:
	CocoLoader();
	~CocoLoader();

public:
	bool	ReadCocoBinBuff(char* pBinBuff);
	stCocoFileHeader*	GetFileHeader(){return m_pFileHeader;}
	stExpCocoNode*		GetRootCocoNode(){return	m_pRootNode;}
	stExpCocoObjectDesc*	GetCocoObjectDescArray(){return	m_pObjectDescArray;}
	stExpCocoObjectDesc*	GetCocoObjectDesc(const char* szObjDesc);
};

}

#pragma pack ()
#endif
